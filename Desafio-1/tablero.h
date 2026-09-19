#ifndef TABLERO_H
#define TABLERO_H

#include "bits.h"

const int TAM_MINIMO = 1;

const int TAM_MAXIMO = 1000;

unsigned char generarCeldaRandom();

bool esPosicionValida(int fila, int col, int filas, int columnas);

bool inicializarTablero(unsigned char*& tab, int& filas, int& columnas, int& capacidadBytes, int filasIniciales, int columnasIniciales);

void destruirTablero(unsigned char*& tab, int& filas, int& columnas, int& capacidadBytes);

bool agregarFila(unsigned char*& tab, int& filas, int columnas, int& capacidadBytes, int posicion);

bool quitarFila(unsigned char*& tab, int& filas, int columnas, int& capacidadBytes, int posicion);

bool agregarColumna(unsigned char*& tab, int filas, int& columnas, int& capacidadBytes, int posicion);

bool quitarColumna(unsigned char*& tab, int filas, int& columnas, int& capacidadBytes, int posicion);

#endif // TABLERO_H
