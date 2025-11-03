/*
 * CONECTA 4 - Juego para 2 jugadores
 * VERSION 1 - Estructura básica y tablero
 * Tablero: 6 filas x 7 columnas
 */

#include <iostream>
#include <vector>

using namespace std;

// Constantes del juego
const int NUM_FILAS = 6;
const int NUM_COLUMNAS = 7;
const char CELDA_VACIA = '.';
const char FICHA_JUGADOR1 = 'X';
const char FICHA_JUGADOR2 = 'O';

// Declaración de funciones
void inicializarTablero(vector<vector<char>>& tablero);
void mostrarTablero(const vector<vector<char>>& tablero);
bool columnaEsValida(const vector<vector<char>>& tablero, int columna);
bool colocarFicha(vector<vector<char>>& tablero, int columna, char ficha);

int main() {
    vector<vector<char>> tablero(NUM_FILAS, vector<char>(NUM_COLUMNAS));
    
    cout << "======================================" << endl;
    cout << "     BIENVENIDO AL CONECTA 4" << endl;
    cout << "======================================" << endl;
    cout << "Jugador 1: " << FICHA_JUGADOR1 << endl;
    cout << "Jugador 2: " << FICHA_JUGADOR2 << endl;
    cout << "======================================" << endl;
    
    // Inicializar el tablero
    inicializarTablero(tablero);
    
    int turnoActual = 1;
    char fichaActual;
    
    // Bucle principal del juego (solo 10 turnos de prueba)
    for (int turnos = 0; turnos < 10; turnos++) {
        mostrarTablero(tablero);
        
        // Determinar el símbolo del jugador actual
        fichaActual = (turnoActual == 1) ? FICHA_JUGADOR1 : FICHA_JUGADOR2;
        
        cout << "\nTurno del Jugador " << turnoActual << " (" << fichaActual << ")" << endl;
        cout << "Elige una columna (1-7): ";
        
        int columnaElegida;
        cin >> columnaElegida;
        
        // Convertir a índice (restar 1 porque el usuario ingresa 1-7)
        columnaElegida--;
        
        // Verificar si la columna es válida
        if (!columnaEsValida(tablero, columnaElegida)) {
            cout << "ERROR: Columna inválida o llena. Intenta de nuevo..." << endl;
            turnos--; // No contar este turno
            continue;
        }
        
        // Colocar la ficha
        colocarFicha(tablero, columnaElegida, fichaActual);
        
        // Cambiar de turno
        turnoActual = (turnoActual == 1) ? 2 : 1;
    }
    
    mostrarTablero(tablero);
    cout << "\nPartida de prueba terminada." << endl;
    cout << "Faltan implementar las verificaciones de victoria..." << endl;
    
    return 0;
}

// Inicializa el tablero con celdas vacías
void inicializarTablero(vector<vector<char>>& tablero) {
    for (int fila = 0; fila < NUM_FILAS; fila++) {
        for (int columna = 0; columna < NUM_COLUMNAS; columna++) {
            tablero[fila][columna] = CELDA_VACIA;
        }
    }
}

// Muestra el tablero en la consola
void mostrarTablero(const vector<vector<char>>& tablero) {
    cout << "\n  TABLERO DE JUEGO" << endl;
    cout << "  ";
    for (int i = 1; i <= NUM_COLUMNAS; i++) {
        cout << i << "   ";
    }
    cout << endl;
    
    cout << "  ";
    for (int i = 0; i < NUM_COLUMNAS; i++) {
        cout << "====";
    }
    cout << endl;
    
    for (int fila = 0; fila < NUM_FILAS; fila++) {
        cout << "| ";
        for (int columna = 0; columna < NUM_COLUMNAS; columna++) {
            cout << tablero[fila][columna] << " | ";
        }
        cout << endl;
        
        cout << "  ";
        for (int i = 0; i < NUM_COLUMNAS; i++) {
            cout << "====";
        }
        cout << endl;
    }
}

// Verifica si una columna es válida (está en rango y no está llena)
bool columnaEsValida(const vector<vector<char>>& tablero, int columna) {
    // Verificar que esté en el rango
    if (columna < 0 || columna >= NUM_COLUMNAS) {
        return false;
    }
    
    // Verificar que la columna no esté llena (la primera fila debe estar vacía)
    return tablero[0][columna] == CELDA_VACIA;
}

// Coloca una ficha en la columna especificada
bool colocarFicha(vector<vector<char>>& tablero, int columna, char ficha) {
    // Buscar la fila más baja disponible en la columna
    for (int fila = NUM_FILAS - 1; fila >= 0; fila--) {
        if (tablero[fila][columna] == CELDA_VACIA) {
            tablero[fila][columna] = ficha;
            return true;
        }
    }
    return false;
}
