#include "bits.h"

int calcularBytesNecesarios(int filas, int columnas){

    int totalBits = filas * columnas * BITS_POR_FICHA;

    int bytesNecesarios = (totalBits + 7) / 8;

    return bytesNecesarios;
}

int calcularBitInicial(int fila, int columna, int numColumnas){

    int indiceLogico = fila * numColumnas + columna;

    return indiceLogico * BITS_POR_FICHA;
}

unsigned char obtenerFicha(const unsigned char* tablero, int fila, int columna, int numColumnas){

    int bitInicial = calcularBitInicial(fila,columna,numColumnas);
    int byteIndex = bitInicial / 8;
    int desplazamiento = bitInicial % 8;

    unsigned char valor = 0;

    if (desplazamiento <= 5){

        valor = (tablero[byteIndex] >> desplazamiento) & MASCARA_FICHA;
    }
    else if (desplazamiento == 6) {

        unsigned char bitsBajos = (tablero[byteIndex] >> 6) & 0x03;
        unsigned char bitAlto = tablero[byteIndex + 1] & 0x01;

        valor = bitsBajos | (bitAlto << 2);
    }
    else {

        unsigned char bitBajo = (tablero[byteIndex] >> 7) & 0x01;
        unsigned char bitsAltos = tablero[byteIndex + 1] & 0x03;

        valor = bitBajo | (bitsAltos << 1);
    }// desplazamiento == 7

    return valor;
}

void escribirFicha (unsigned char* tablero, int fila, int columna, int numColumnas, unsigned char valor){

    int bitInicial = calcularBitInicial(fila,columna,numColumnas);
    int byteIndex = bitInicial / 8;
    int desplazamiento = bitInicial % 8;

    valor &= MASCARA_FICHA;

    if (desplazamiento <= 5) {

        unsigned char mascaraLimpiar = static_cast<unsigned char>(~(MASCARA_FICHA << desplazamiento));

        tablero[byteIndex] = (tablero[byteIndex] & mascaraLimpiar) | (valor << desplazamiento);
    }
    else if (desplazamiento == 6) {

        unsigned char bitsBajos = valor & 0x03;         // bits 0-1 de la ficha
        unsigned char bitAlto   = (valor >> 2) & 0x01;  // bit 2 de la ficha

        tablero[byteIndex]     = (tablero[byteIndex] & 0x3F) | (bitsBajos << 6);
        tablero[byteIndex + 1] = (tablero[byteIndex + 1] & 0xFE) | bitAlto;
    }
    else {

        unsigned char bitBajo   = valor & 0x01;
        unsigned char bitsAltos = (valor >> 1) & 0x03;

        tablero[byteIndex]     = (tablero[byteIndex] & 0x7F) | (bitBajo << 7);
        tablero[byteIndex + 1] = (tablero[byteIndex + 1] & 0xFC) | bitsAltos;
    }
}