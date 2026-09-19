#ifndef JUEGO_H
#define JUEGO_H

const int RACHA_MINIMA = 3;

const int PUNTOS_POR_CELDA = 10;

const unsigned char VALOR_MAXIMO_FICHA = 5;


void llenarTableroInicial(unsigned char* tab, int filas, int columnas);


bool quitarCeldaJugador(unsigned char* tab, int filas, int columnas, int fila, int col, int& jugadasUsuario, int& totalCeldasEliminadas);


bool detectarYLimpiarRachas(unsigned char* tab, int filas, int columnas, int& celdasMarcadas, int& rachasEncontradas);


void aplicarCaidaFichas(unsigned char* tab, int filas, int columnas);


void ejecutarCascadas(unsigned char* tab, int filas, int columnas, int& totalCeldasEliminadas, int& totalRachasDetectadas, int& cascadasEnJugada, int& totalCascadas, int& puntajeAcumulado);

#endif // JUEGO_H
