#ifndef BITS_H
#define BITS_H

//Cantidad de bits de cada ficha, NO cambiar
const int BITS_POR_FICHA = 3;

//Mascara para aislar 3 bits  (0b111 = 7)
const unsigned char MASCARA_FICHA = 0x07;

const unsigned char CODIGO_VACIO = 6;
const unsigned char CODIGO_MARCA = 7;


int calcularBytesNecesarios(int filas, int columnas);

int calcularBitInicial(int fila, int columna, int numColumnas);

unsigned char obtenerFicha(const unsigned char* tablero, int fila, int columnas, int numColumnas);

void escribirFicha(unsigned char* tablero, int fila, int columna, int numColumnas, unsigned char valor);

#endif // BITS_H