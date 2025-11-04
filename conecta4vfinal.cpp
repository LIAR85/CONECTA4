

#include <iostream>
#include <vector>
#include <limits>

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
bool verificarVictoriaHorizontal(const vector<vector<char>>& tablero, char ficha);
bool verificarVictoriaVertical(const vector<vector<char>>& tablero, char ficha);
bool verificarVictoriaDiagonal(const vector<vector<char>>& tablero, char ficha);
bool hayGanador(const vector<vector<char>>& tablero, char ficha);
bool tableroLleno(const vector<vector<char>>& tablero);
void limpiarPantalla();

int main() {
    vector<vector<char>> tablero(NUM_FILAS, vector<char>(NUM_COLUMNAS));
    bool jugarOtraVez = true;
    char respuesta;
    
    cout << "======================================" << endl;
    cout << "     BIENVENIDO AL CONECTA 4" << endl;
    cout << "======================================" << endl;
    cout << "Jugador 1: " << FICHA_JUGADOR1 << endl;
    cout << "Jugador 2: " << FICHA_JUGADOR2 << endl;
    cout << "======================================" << endl;
    
    while (jugarOtraVez) {
        // Inicializar el tablero para una nueva partída
        inicializarTablero(tablero);
        
        int turnoActual = 1; // 1 para jugador 1, 2 para jugador 2
        bool juegoTerminado = false;
        char fichaActual; // aqui guardo que simbolo usar (X o O)
        
        // Bucle principal del juego
        while (!juegoTerminado) {
            limpiarPantalla(); // limpio la pantalla para que se vea mejor
            mostrarTablero(tablero);
            
            // Determinar el símbolo del jugador actual
            fichaActual = (turnoActual == 1) ? FICHA_JUGADOR1 : FICHA_JUGADOR2;
            
            cout << "\nTurno del Jugador " << turnoActual << " (" << fichaActual << ")" << endl;
            cout << "Elige una columna (1-7): ";
            
            int columnaElegida;
            cin >> columnaElegida;
            
            // Validar entrada - esto lo aprendi de stackoverflow
            if (cin.fail()) {
                cin.clear(); // limpiar el estado de error
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "ERROR: Debes ingresar un número. Presiona Enter para continuar...";
                cin.get();
                continue; // regresa al inicio del bucle
            }
            
            // Convertir a índice (restar 1 porque el usuario ingresa 1-7)
            columnaElegida--;
            
            // Verificar si la columna es válida
            if (!columnaEsValida(tablero, columnaElegida)) {
                cout << "ERROR: Columna inválida o llena. Presiona Enter para continuar...";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.get();
                continue;
            }
            
            // Colocar la ficha en el tablero
            colocarFicha(tablero, columnaElegida, fichaActual);
            
            // Verificar si hay ganador - aqui checo todas las posibilidades
            if (hayGanador(tablero, fichaActual)) {
                limpiarPantalla();
                mostrarTablero(tablero);
                cout << "\n¡¡¡FELICIDADES!!!" << endl;
                cout << "¡El Jugador " << turnoActual << " (" << fichaActual << ") ha GANADO!" << endl;
                juegoTerminado = true;
            }
            // Verificar empate
            else if (tableroLleno(tablero)) {
                limpiarPantalla();
                mostrarTablero(tablero);
                cout << "\n¡EMPATE! El tablero está lleno." << endl;
                cout << "No hay ganador esta vez." << endl;
                juegoTerminado = true;
            }
            else {
                // Cambiar de turno
                turnoActual = (turnoActual == 1) ? 2 : 1;
            }
        }
        
        // Preguntar si quieren jugar otra partida
        cout << "\n¿Quieren jugar otra partida? (s/n): ";
        cin >> respuesta;
        
        if (respuesta == 's' || respuesta == 'S') {
            jugarOtraVez = true;
        } else {
            jugarOtraVez = false;
            cout << "\n¡Gracias por jugar! Hasta luego." << endl;
        }
    }
    
    return 0;
}

// Inicializa el tablero con celdas vacías
void inicializarTablero(vector<vector<char>>& tablero) {
    // doble for para llenar toda la matriz con puntos
    for (int fila = 0; fila < NUM_FILAS; fila++) {
        for (int columna = 0; columna < NUM_COLUMNAS; columna++) {
            tablero[fila][columna] = CELDA_VACIA; // pongo puntos en todas las celdas
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
    // Buscar la fila más baja disponible en la columna (efecto gravedad)
    for (int fila = NUM_FILAS - 1; fila >= 0; fila--) { // empiezo desde abajo
        if (tablero[fila][columna] == CELDA_VACIA) {
            tablero[fila][columna] = ficha; // coloco la ficha aqui
            return true; // exito!
        }
    }
    return false; // no se pudo colocar (columna llena)
}

// Verifica si hay 4 fichas consecutivas en horizontal
bool verificarVictoriaHorizontal(const vector<vector<char>>& tablero, char ficha) {
    for (int fila = 0; fila < NUM_FILAS; fila++) {
        for (int columna = 0; columna <= NUM_COLUMNAS - 4; columna++) {
            // checo 4 fichas seguidas en la misma fila
            if (tablero[fila][columna] == ficha &&
                tablero[fila][columna + 1] == ficha &&
                tablero[fila][columna + 2] == ficha &&
                tablero[fila][columna + 3] == ficha) {
                return true; // gano!
            }
        }
    }
    return false; // no encontre 4 seguidas
}

// Verifica si hay 4 fichas consecutivas en vertical
bool verificarVictoriaVertical(const vector<vector<char>>& tablero, char ficha) {
    for (int columna = 0; columna < NUM_COLUMNAS; columna++) {
        for (int fila = 0; fila <= NUM_FILAS - 4; fila++) {
            if (tablero[fila][columna] == ficha &&
                tablero[fila + 1][columna] == ficha &&
                tablero[fila + 2][columna] == ficha &&
                tablero[fila + 3][columna] == ficha) {
                return true;
            }
        }
    }
    return false;
}

// Verifica si hay 4 fichas consecutivas en diagonal
bool verificarVictoriaDiagonal(const vector<vector<char>>& tablero, char ficha) {
    // Diagonal descendente (de arriba-izquierda a abajo-derecha ↘)
    // esta parte fue la mas dificil de programar
    for (int fila = 0; fila <= NUM_FILAS - 4; fila++) {
        for (int columna = 0; columna <= NUM_COLUMNAS - 4; columna++) {
            if (tablero[fila][columna] == ficha &&
                tablero[fila + 1][columna + 1] == ficha &&
                tablero[fila + 2][columna + 2] == ficha &&
                tablero[fila + 3][columna + 3] == ficha) {
                return true; // diagonal descendente ganadora
            }
        }
    }
    
    // Diagonal ascendente (de abajo-izquierda a arriba-derecha ↗)
    // esta diagonal va hacia arriba, por eso resto en las filas
    for (int fila = 3; fila < NUM_FILAS; fila++) {
        for (int columna = 0; columna <= NUM_COLUMNAS - 4; columna++) {
            if (tablero[fila][columna] == ficha &&
                tablero[fila - 1][columna + 1] == ficha &&
                tablero[fila - 2][columna + 2] == ficha &&
                tablero[fila - 3][columna + 3] == ficha) {
                return true; // diagonal ascendente ganadora
            }
        }
    }
    
    return false;
}

// Verifica si hay un ganador
bool hayGanador(const vector<vector<char>>& tablero, char ficha) {
    return verificarVictoriaHorizontal(tablero, ficha) ||
           verificarVictoriaVertical(tablero, ficha) ||
           verificarVictoriaDiagonal(tablero, ficha);
}

// Verifica si el tablero está completamente lleno
bool tableroLleno(const vector<vector<char>>& tablero) {
    for (int columna = 0; columna < NUM_COLUMNAS; columna++) {
        if (tablero[0][columna] == CELDA_VACIA) {
            return false;
        }
    }
    return true;
}

// Limpia la pantalla de la consola
void limpiarPantalla() {
    // esto funciona diferente en Windows y Mac/Linux
    #ifdef _WIN32
        system("cls"); // para windows
    #else
        system("clear"); // para mac y linux
    #endif
}
