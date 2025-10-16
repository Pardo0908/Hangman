#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <cctype>
using namespace std;

const int FILAS = 10;
const int COLS = 50;
const int MAX_LETRAS = 26;
const int MAX_INTENTOS = 6;

struct Palabra {
    char texto[COLS];
    char pista[COLS];
};

void seleccionarPalabra(Palabra palabras[], int total, char destino[], char pistaDestino[]) {
    srand(time(NULL));
    int indice = rand() % total;
    strcpy(destino, palabras[indice].texto);
    strcpy(pistaDestino, palabras[indice].pista);
}

void inicializarEstado(char estadoPalabra[], int longitud) {
    for (int i = 0; i < longitud; i++) {
        estadoPalabra[i] = '_';
    }
    estadoPalabra[longitud] = '\0';
}

void mostrarEstado(char estadoPalabra[], int longitud, int intentosRestantes, 
                   char letrasIntentadas[], int totalIntentadas, char pista[]) {
    int errores = MAX_INTENTOS - intentosRestantes;
    
    cout << "\n  +---+";
    cout << "\n  |   " << (errores >= 1 ? "O" : " ");
    
    if (errores == 2) cout << "\n  |   |";
    else if (errores == 3) cout << "\n  |  /|";
    else if (errores >= 4) cout << "\n  |  /|\\";
    else cout << "\n  |";
    
    if (errores == 5) cout << "\n  |  /";
    else if (errores >= 6) cout << "\n  |  / \\";
    else cout << "\n  |";
    
    cout << "\n _|_\n";
    
    cout << "\nPalabra: ";
    for (int i = 0; i < longitud; i++) {
        cout << estadoPalabra[i] << " ";
    }
    
    cout << "\nIntentos: " << intentosRestantes << "/" << MAX_INTENTOS;
    cout << " | Pista: " << pista;
    
    cout << "\nUsadas: ";
    if (totalIntentadas == 0) cout << "(ninguna)";
    else {
        for (int i = 0; i < totalIntentadas; i++) {
            cout << letrasIntentadas[i];
            if (i < totalIntentadas - 1) cout << ", ";
        }
    }
    cout << "\n";
}

bool validarEntrada(char &letra, char letrasIntentadas[], int totalIntentadas) {
    letra = toupper(letra);
    
    if (!isalpha(letra)) {
        cout << "Error: Solo letras A-Z\n";
        return false;
    }
    
    for (int i = 0; i < totalIntentadas; i++) {
        if (letrasIntentadas[i] == letra) {
            cout << "Ya usaste esa letra\n";
            return false;
        }
    }
    
    return true;
}

bool verificarLetra(char letra, char palabraSecreta[], char estadoPalabra[], int longitud) {
    bool encontrada = false;
    for (int i = 0; i < longitud; i++) {
        if (palabraSecreta[i] == letra) {
            estadoPalabra[i] = letra;
            encontrada = true;
        }
    }
    return encontrada;
}

bool verificarVictoria(char estadoPalabra[], int longitud) {
    for (int i = 0; i < longitud; i++) {
        if (estadoPalabra[i] == '_') return false;
    }
    return true;
}

void registrarIntento(char letra, char letrasIntentadas[], int &totalIntentadas) {
    letrasIntentadas[totalIntentadas] = letra;
    totalIntentadas++;
}

int main() {
    Palabra palabras[FILAS] = {
        {"PROGRAMAR", "Escribir codigo"},
        {"COMPUTADORA", "Maquina electronica"},
        {"ALGORITMO", "Secuencia de pasos"},
        {"VARIABLE", "Almacena datos"},
        {"FUNCION", "Bloque de codigo"},
        {"ARREGLO", "Coleccion de datos"},
        {"BUCLE", "Repeticion de codigo"},
        {"COMPILADOR", "Traduce codigo"},
        {"DEBUGGER", "Encuentra errores"},
        {"SINTAXIS", "Reglas del lenguaje"}
    };
    
    char jugarOtraVez;
    
    do {
        cout << "\n=== JUEGO DEL AHORCADO ===\n";
        cout << "Tienes " << MAX_INTENTOS << " intentos. ¡Buena suerte!\n";
        
        char palabraSecreta[COLS];
        char pista[COLS];
        seleccionarPalabra(palabras, FILAS, palabraSecreta, pista);
        int longitud = strlen(palabraSecreta);
        
        char estadoPalabra[COLS];
        inicializarEstado(estadoPalabra, longitud);
        
        char letrasIntentadas[MAX_LETRAS];
        int totalIntentadas = 0;
        int intentosRestantes = MAX_INTENTOS;
        bool juegoActivo = true;
        
        while (juegoActivo && intentosRestantes > 0) {
            mostrarEstado(estadoPalabra, longitud, intentosRestantes, 
                         letrasIntentadas, totalIntentadas, pista);
            
            char letra;
            bool entradaValida = false;
            
            while (!entradaValida) {
                cout << "\nLetra: ";
                cin >> letra;
                entradaValida = validarEntrada(letra, letrasIntentadas, totalIntentadas);
            }
            
            registrarIntento(letra, letrasIntentadas, totalIntentadas);
            
            if (verificarLetra(letra, palabraSecreta, estadoPalabra, longitud)) {
                cout << "Correcto!\n";
            } else {
                intentosRestantes--;
                cout << "Incorrecto!\n";
            }
            
            if (verificarVictoria(estadoPalabra, longitud)) {
                cout << "\n*** FELICIDADES ***\n";
                cout << "Palabra: " << palabraSecreta << "\n";
                cout << "Errores: " << (MAX_INTENTOS - intentosRestantes) << "/" << MAX_INTENTOS << "\n";
                juegoActivo = false;
            }
        }
        
        if (intentosRestantes == 0) {
            mostrarEstado(estadoPalabra, longitud, 0, letrasIntentadas, totalIntentadas, pista);
            cout << "\n*** GAME OVER ***\n";
            cout << "La palabra era: " << palabraSecreta << "\n";
        }
        
        cout << "\nJugar otra vez? (S/N): ";
        cin >> jugarOtraVez;
        jugarOtraVez = toupper(jugarOtraVez);
        
    } while (jugarOtraVez == 'S');
    
    cout << "\nGracias por jugar!\n";
    return 0;
}
