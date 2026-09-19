#include "bits.h"

int calcularTamanoBytes(int filas, int columnas) {

    int totalBits = filas * columnas * BITS_POR_CELDA;

    int bytesNecesarios = (totalBits + 7) / 8;

    return bytesNecesarios;
}

int calcularOffsetBit(int fila, int col, int totalColumnas) {

    int indiceL = fila * totalColumnas + col;

    return indiceL * BITS_POR_CELDA;
}

unsigned char leerCelda(const unsigned char* tab, int fila, int col, int totalColumnas) {

    int bitInicial = calcularOffsetBit(fila,col,totalColumnas);
    int Index = bitInicial >> 3;
    int desplazamiento = bitInicial & 7;

    unsigned char dato = 0;

    if (desplazamiento <= 5){

        dato = (tab[Index] >> desplazamiento) & MASCARA_CELDA;
    } else if (desplazamiento == 6) {

        unsigned char bitsBajos = (tab[Index] >> 6) & 0x03;
        unsigned char bitAlto = tab[Index + 1] & 0x01;

        dato = bitsBajos | (bitAlto << 2);
    } else {

        unsigned char bitBajo = (tab[Index] >> 7) & 0x01;
        unsigned char bitsAltos = tab[Index + 1] & 0x03;

        dato = bitBajo | (bitsAltos << 1);
    }// desplazamiento == 7

    return dato;
}

void guardarCelda (unsigned char* tab, int fila, int col, int totalColumnas, unsigned char dato) {

    int bitInicial = calcularOffsetBit(fila,col,totalColumnas);
    int Index = bitInicial >> 3;
    int desplazamiento = bitInicial & 7;

    dato &= MASCARA_CELDA;

    if (desplazamiento <= 5) {

        unsigned char mascaraLimpiar = static_cast<unsigned char>(~(MASCARA_CELDA << desplazamiento));

        tab[Index] = (tab[Index] & mascaraLimpiar) | (dato << desplazamiento);
    }
    else if (desplazamiento == 6) {

        unsigned char bitsBajos = dato & 0x03;
        unsigned char bitAlto   = (dato >> 2) & 0x01;

        unsigned char mascaraActual   = static_cast<unsigned char>(~(0x03 << 6));
        unsigned char mascaraSiguiente = static_cast<unsigned char>(~0x01);

        tab[Index]     = (tab[Index] & mascaraActual) | (bitsBajos << 6);
        tab[Index + 1] = (tab[Index + 1] & mascaraSiguiente) | bitAlto;
    }
    else {

        unsigned char bitBajo   = dato & 0x01;
        unsigned char bitsAltos = (dato >> 1) & 0x03;

        unsigned char mascaraActual   = static_cast<unsigned char>(~(0x01 << 7));
        unsigned char mascaraSiguiente = static_cast<unsigned char>(~0x03);

        tab[Index]     = (tab[Index] & mascaraActual) | (bitBajo << 7);
        tab[Index + 1] = (tab[Index + 1] & mascaraSiguiente) | bitsAltos;
    }
}