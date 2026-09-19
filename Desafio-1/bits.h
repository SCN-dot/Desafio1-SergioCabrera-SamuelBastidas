#ifndef BITS_H
#define BITS_H

//Cantidad de bits de cada ficha, NO cambiar
const int BITS_POR_CELDA = 3;

//Mascara para aislar 3 bits  (0b111 = 7)
const unsigned char MASCARA_CELDA = 0x07;

const unsigned char CELDA_VACIA = 6;
const unsigned char CELDA_MARCADA = 7;


int calcularTamanoBytes(int filas, int columnas);

int calcularOffsetBit(int fila, int col, int totalColumnas);

unsigned char leerCelda(const unsigned char* tab, int fila, int col, int totalColumnas);

void guardarCelda(unsigned char* tab, int fila, int col, int totalColumnas, unsigned char dato);

#endif // BITS_H