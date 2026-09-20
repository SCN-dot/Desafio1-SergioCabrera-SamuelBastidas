#include "interfaz.h"
#include "bits.h"
#include <iostream>

using namespace std;

static int contarCifras(int valor) {
    bool negativo = (valor < 0);
    int magnitud;
    if (negativo) {
        magnitud = -valor;
    } else {
        magnitud = valor;
    }

    int cifras = 1;
    while (magnitud >= 10) {
        magnitud /= 10;
        cifras++;
    }
    if (negativo) {
        cifras++;
    }

    return cifras;
}

static void imprimirNumeroAlineado(int valor, int ancho) {
    int relleno = ancho - contarCifras(valor);
    for (int i = 0; i < relleno; i++)
        cout << ' ';
    cout << valor;
}

static void imprimirCaracterAlineado(char c, int ancho) {
    int relleno = ancho - 1;
    for (int i = 0; i < relleno; i++) {
        cout << ' ';
    }
    cout << c;
}

char simboloDeCelda(unsigned char codigo) {
    switch (codigo) {
    case 0: return 'X';
    case 1: return 'O';
    case 2: return '#';
    case 3: return '@';
    case 4: return '&';
    case 5: return '$';
    }

    if (codigo == CELDA_VACIA) {
        return '.';
    }
    if (codigo == CELDA_MARCADA) {
        return '?';
    }

    return '!';
}

void imprimirTabSimbolos(const unsigned char* tab, int filas, int columnas) {
    cout << "\n    Tablero (formato fichas)    \n";

    int anchoFila = contarCifras(filas - 1);       // solo depende de las filas

    int anchoCol = contarCifras(columnas - 1) + 1; // solo depende de las columnas
    if (anchoCol < 3) {
        anchoCol = 3;
    }

    // CAMBIO 2: prefijo del encabezado = prefijo de las filas (anchoFila + 2)
    for (int i = 0; i < anchoFila + 2; i++) {
        cout << ' ';
    }
    for (int ci = 0; ci < columnas; ci++) {
        imprimirNumeroAlineado(ci, anchoCol);      // CAMBIO 3
    }
    cout << "\n";

    for (int fi = 0; fi < filas; fi++) {
        imprimirNumeroAlineado(fi, anchoFila);     // CAMBIO 3
        cout << "  ";
        for (int ci = 0; ci < columnas; ci++) {
            unsigned char codigo = leerCelda(tab, fi, ci, columnas);
            imprimirCaracterAlineado(simboloDeCelda(codigo), anchoCol);  // CAMBIO 3
        }
        cout << "\n";
    }
    cout << "\n";
}

void imprimirTabBinario(const unsigned char* tab, int filas, int columnas) {
    int bytesNecesarios = calcularTamanoBytes(filas, columnas);

    cout << "    Tablero (formato binario,    " << bytesNecesarios << " bytes)    \n";

    const int BYTES_POR_LINEA = 8;
    for (int i = 0; i < bytesNecesarios; i++) {
        // Se imprime cada byte del bit mas significativo (7) al menos
        // significativo (0)
        for (int bit = 7; bit >= 0; bit--) {
            unsigned char mascara = static_cast<unsigned char>(1u << bit);
            char bitImpreso;
            if ((tab[i] & mascara)) {
                bitImpreso = '1';
            } else {
                bitImpreso = '0';
            }
            cout << bitImpreso;
        }
        cout << ' ';

        if ((i + 1) % BYTES_POR_LINEA == 0) {
            cout << "\n";
        }
    }
    if (bytesNecesarios % BYTES_POR_LINEA != 0) {
        cout << "\n";
    }
    cout << "\n";
}

void imprimirTablero(const unsigned char* tab, int filas, int columnas) {
    imprimirTabSimbolos(tab, filas, columnas);
    imprimirTabBinario(tab, filas, columnas);
}

void imprimirEstadisticas(int filas, int columnas, int jugadasUsuario, int totalCeldasEliminadas, int totalRachasDetectadas, int cascadasEnJugada, int totalCascadas, int puntosT)
{
    cout << "    ESTADISTICAS    \n";
    cout << "Dimensiones actuales:        " << filas << " x " << columnas << "\n";
    cout << "Eliminaciones del usuario:   " << jugadasUsuario << "\n";
    cout << "Fichas eliminadas (total):   " << totalCeldasEliminadas << "\n";
    cout << "Combinaciones detectadas:    " << totalRachasDetectadas << "\n";
    cout << "Cascadas (jugada actual):    " << cascadasEnJugada<< "\n";
    cout << "Cascadas (total):            " << totalCascadas << "\n";
    cout << "Puntuacion:                  " << puntosT << "\n\n";
}
