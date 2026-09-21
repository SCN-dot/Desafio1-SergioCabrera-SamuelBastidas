#include <iostream>
#include "bits.h"
#include "tablero.h"
#include "juego.h"
#include "interfaz.h"
#include <cstdlib>
#include <ctime>

using namespace std;

static int pedirEntero(const char* mensaje) {
    int valor;
    cout << mensaje;
    while (!(cin >> valor)) {
        cin.clear();
        cin.ignore(1000000, '\n');
        cout << "Entrada invalida, Porfavor ingrese un numero entero: ";
    }
    // Se descarta cualquier basura restante en la misma linea
    // (por ejemplo, si el usuario escribio "3 abc").
    cin.ignore(1000000, '\n');
    return valor;
}

static int pedirEnteroRango(const char* mensaje, int minimo, int maximo) {
    int valor;
    while (true) {
        valor = pedirEntero(mensaje);
        if (valor >= minimo && valor <= maximo) {
            break;
        }
        cout << "Valor fuera de rango [" << minimo << ", " << maximo << "]\n";
    }
    return valor;
}

static void imprimirMenu() {
    cout << "\n           MENU SWEET CRUSH           \n";
    cout << "1. Eliminar ficha\n";
    cout << "2. Insertar fila\n";
    cout << "3. Eliminar fila\n";
    cout << "4. Insertar columna\n";
    cout << "5. Eliminar columna\n";
    cout << "6. Mostrar tablero\n";
    cout << "7. Mostrar estadisticas\n";
    cout << "0. Salir\n";
    cout << "\n";
}

int main() {
    // Semilla aleatoria: se llama UNA SOLA VEZ.
    srand(static_cast<unsigned int>(time(nullptr)));

    // Estado del tablero
    unsigned char* matrizJuego = nullptr;
    int numFilas = 0;
    int numCols = 0;
    int capacidadBuffer = 0;

    // Variables de estado: las 6 exigidas por el enunciado mas el total de cascadas de la partida
    int jugadasUsuario = 0;
    int totalCeldasEliminadas = 0;
    int totalRachasDetectadas = 0;
    int cascadasEnJugada = 0;
    int totalCascadas = 0;
    int puntajeAcumulado = 0;
    // (numFilas y numCols, ya declaradas arriba, son las otras 2)

    cout << "Inicio de Sweet Crush\n\n";

    int filasInicio = pedirEnteroRango("Ingrese filas iniciales (1-1000): ", TAM_MINIMO, TAM_MAXIMO);

    int columnasInicio = pedirEnteroRango("Ingrese columnas iniciales (1-1000): ", TAM_MINIMO, TAM_MAXIMO);

    if (!inicializarTablero(matrizJuego, numFilas, numCols, capacidadBuffer, filasInicio, columnasInicio)) {
        cout << "No se pudo crear el tablero. Fin del programa\n";
        return 1;
    }

    /* Relleno inicial: se hace una sola vez, inmediatamente despues de inicializarTablero (ver juego.h) */
    llenarTableroInicial(matrizJuego, numFilas, numCols);

    /* Tras el relleno inicial tambien puede haber rachas "de arranque" (por puro azar); se resuelven antes de la primera jugada */
    ejecutarCascadas(matrizJuego, numFilas, numCols, totalCeldasEliminadas, totalRachasDetectadas, cascadasEnJugada, totalCascadas, puntajeAcumulado);

    imprimirTablero(matrizJuego, numFilas, numCols);

    bool enPartida = true;
    while (enPartida) {
        imprimirMenu();
        int seleccion = pedirEnteroRango("Elija una opcion: ", 0, 7);

        switch (seleccion) {
        case 1: {  // Eliminar ficha (jugada del usuario)
            int renglon = pedirEnteroRango("Fila : ", 0, numFilas - 1);
            int col = pedirEnteroRango("Columna : ", 0, numCols - 1);

            bool resultado = quitarCeldaJugador(matrizJuego, numFilas, numCols, renglon, col, jugadasUsuario, totalCeldasEliminadas);
            if (!resultado) {
                cout << "Movimiento invalido: la posicion ya estaba vacia.\n";
                break;
            }

            /* Contrato de juego.h: tras quitarCeldaJugador el tablero ya no tiene huecos pendientes, asi que se dispara de inmediato el ciclo de cascadas */
            ejecutarCascadas(matrizJuego, numFilas, numCols, totalCeldasEliminadas, totalRachasDetectadas, cascadasEnJugada, totalCascadas, puntajeAcumulado);

            imprimirTablero(matrizJuego, numFilas, numCols);
            imprimirEstadisticas(numFilas, numCols, jugadasUsuario, totalCeldasEliminadas, totalRachasDetectadas, cascadasEnJugada, totalCascadas, puntajeAcumulado);
            break;
        }

        case 2: {  // Insertar fila
            int indice = pedirEnteroRango("Posicion para insertar fila (fila , columna) : ", 0, numFilas);
            if (!agregarFila(matrizJuego, numFilas, numCols, capacidadBuffer, indice)) {
                cout << "No se pudo insertar la fila (limite de dimension alcanzado).\n";
                break;
            }

            /* agregarFila ya rellena la fila nueva; el tablero queda sin huecos, asi que corresponde resolver cascadas por si la fila nueva genero rachas */
            ejecutarCascadas(matrizJuego, numFilas, numCols, totalCeldasEliminadas, totalRachasDetectadas, cascadasEnJugada, totalCascadas, puntajeAcumulado);

            imprimirTablero(matrizJuego, numFilas, numCols);
            imprimirEstadisticas(numFilas, numCols, jugadasUsuario, totalCeldasEliminadas, totalRachasDetectadas, cascadasEnJugada, totalCascadas, puntajeAcumulado);
            break;
        }

        case 3: {  // Eliminar fila
            int indice = pedirEnteroRango("Posicion de fila a eliminar : ", 0, numFilas - 1);
            if (!quitarFila(matrizJuego, numFilas, numCols, capacidadBuffer, indice)) {
                cout << "No se pudo eliminar la fila (dimension minima alcanzada).\n";
                break;
            }

            /* quitarFila recompacta pero no rellena huecos con celdas nuevas (no hay huecos: se borra una fila completa), asi que el tablero queda sin CELDA_VACIA
            pendiente. Se resuelven cascadas por si la nueva vecindad entre filas genero rachas*/
            ejecutarCascadas(matrizJuego, numFilas, numCols, totalCeldasEliminadas, totalRachasDetectadas, cascadasEnJugada, totalCascadas, puntajeAcumulado);

            imprimirTablero(matrizJuego, numFilas, numCols);
            imprimirEstadisticas(numFilas, numCols, jugadasUsuario, totalCeldasEliminadas, totalRachasDetectadas, cascadasEnJugada, totalCascadas, puntajeAcumulado);
            break;
        }

        case 4: { // Insertar columna
            int indice = pedirEnteroRango("Posicion para insertar columna (fila , columna): ", 0, numCols);
            if (!agregarColumna(matrizJuego, numFilas, numCols, capacidadBuffer, indice)) {
                cout << "No se pudo insertar la columna (limite de dimension alcanzado).\n";
                break;
            }

            ejecutarCascadas(matrizJuego, numFilas, numCols, totalCeldasEliminadas, totalRachasDetectadas, cascadasEnJugada, totalCascadas, puntajeAcumulado);

            imprimirTablero(matrizJuego, numFilas, numCols);
            imprimirEstadisticas(numFilas, numCols, jugadasUsuario, totalCeldasEliminadas, totalRachasDetectadas, cascadasEnJugada, totalCascadas, puntajeAcumulado);
            break;
        }

        case 5: { // Eliminar columna
            int indice = pedirEnteroRango("Posicion de columna a eliminar : ", 0, numCols - 1);
            if (!quitarColumna(matrizJuego, numFilas, numCols, capacidadBuffer, indice)) {
                cout << "No se pudo eliminar la columna (dimension minima alcanzada).\n";
                break;
            }

            ejecutarCascadas(matrizJuego, numFilas, numCols, totalCeldasEliminadas, totalRachasDetectadas, cascadasEnJugada, totalCascadas, puntajeAcumulado);

            imprimirTablero(matrizJuego, numFilas, numCols);
            imprimirEstadisticas(numFilas, numCols, jugadasUsuario, totalCeldasEliminadas, totalRachasDetectadas, cascadasEnJugada, totalCascadas, puntajeAcumulado);
            break;
        }

        case 6: // Mostrar tablero (sin modificarlo)
            imprimirTablero(matrizJuego, numFilas, numCols);
            break;

        case 7: // Mostrar estadisticas (sin modificar nada)
            imprimirEstadisticas(numFilas, numCols, jugadasUsuario, totalCeldasEliminadas, totalRachasDetectadas, cascadasEnJugada, totalCascadas, puntajeAcumulado);
            break;

        case 0: // Salir
            enPartida = false;
            break;
        }
    }

    destruirTablero(matrizJuego, numFilas, numCols, capacidadBuffer);

    cout << "\nFin del programa. Gracias por jugar\n";
    return 0;
}
