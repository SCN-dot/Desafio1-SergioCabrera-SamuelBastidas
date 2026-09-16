#ifndef TABLERO_H
#define TABLERO_H

#include "bits.h"

const int DIMENSION_MINIMA = 1;

const int DIMENSION_MAXIMA = 1000;

unsigned char generarFichaAleatoria();

bool posicionValida(int fila, int columna, int filas, int columnas);

bool crearTablero(unsigned char*& tablero, int& filas, int& columnas, int& capacidadBytes, int filasIniciales, int columnasIniciales);

void liberarTablero(unsigned char*& tablero, int& filas, int& columnas, int& capacidadBytes);

bool insertarFila(unsigned char*& tablero, int& filas, int columnas, int& capacidadBytes, int posicion);

bool eliminarFila(unsigned char*& tablero, int& filas, int columnas, int& capacidadBytes, int posicion);

bool insertarColumna(unsigned char*& tablero, int filas, int& columnas, int& capacidadBytes, int posicion);

bool eliminarColumna(unsigned char*& tablero, int filas, int& columnas, int& capacidadBytes, int posicion);

#endif // TABLERO_H
