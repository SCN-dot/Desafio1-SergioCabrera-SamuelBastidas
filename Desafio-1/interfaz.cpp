#include "interfaz.h"
#include "bits.h"
#include <iostream>

using namespace std;

static int contarDigitos(int valor)
{
    bool negativo = (valor < 0);
    int magnitud = negativo ? -valor : valor;

    int digitos = 1;
    while (magnitud >= 10)
    {
        magnitud /= 10;
        digitos++;
    }
    if (negativo)
        digitos++;

    return digitos;
}

static void imprimirEnteroConAncho(int valor, int ancho)
{
    int relleno = ancho - contarDigitos(valor);
    for (int i = 0; i < relleno; i++)
        cout << ' ';
    cout << valor;
}

static void imprimirCaracterConAncho(char c, int ancho)
{
    int relleno = ancho - 1;
    for (int i = 0; i < relleno; i++)
        cout << ' ';
    cout << c;
}

char obtenerSimboloFicha(unsigned char codigo)
{
    if (codigo <= 5)
        return static_cast<char>('A' + codigo);
    if (codigo == CODIGO_VACIO)
        return '.';
    if (codigo == CODIGO_MARCA)
        return '?';

    return '!';
}

void mostrarTableroFichas(const unsigned char* tablero, int filas, int columnas)
{
    cout << "\n    Tablero (formato fichas)    \n";

    cout << "     ";
    for (int c = 0; c < columnas; c++)
        imprimirEnteroConAncho(c, 3);
    cout << "\n";

    for (int f = 0; f < filas; f++)
    {
        imprimirEnteroConAncho(f, 3);
        cout << "  ";
        for (int c = 0; c < columnas; c++)
        {
            unsigned char codigo = obtenerFicha(tablero, f, c, columnas);
            imprimirCaracterConAncho(obtenerSimboloFicha(codigo), 3);
        }
        cout << "\n";
    }
    cout << "\n";
}

void mostrarTableroBinario(const unsigned char* tablero, int filas, int columnas)
{
    int bytesNecesarios = calcularBytesNecesarios(filas, columnas);

    cout << "    Tablero (formato binario,    " << bytesNecesarios << " bytes)    \n";

    const int BYTES_POR_LINEA = 8;
    for (int i = 0; i < bytesNecesarios; i++)
    {
        // Se imprime cada byte del bit mas significativo (7) al menos
        // significativo (0), que es el orden convencional de lectura.
        for (int bit = 7; bit >= 0; bit--)
        {
            unsigned char mascara = static_cast<unsigned char>(1u << bit);
            cout << ((tablero[i] & mascara) ? '1' : '0');
        }
        cout << ' ';

        if ((i + 1) % BYTES_POR_LINEA == 0)
            cout << "\n";
    }
    if (bytesNecesarios % BYTES_POR_LINEA != 0)
        cout << "\n";
    cout << "\n";
}

void mostrarTablero(const unsigned char* tablero, int filas, int columnas)
{
    mostrarTableroFichas(tablero, filas, columnas);
    mostrarTableroBinario(tablero, filas, columnas);
}

void mostrarEstadisticas(int filas, int columnas, int eliminacionesUsuario,
                         int fichasEliminadasTotal, int combinacionesDetectadas,
                         int cascadasJugadaActual, int puntuacion)
{
    cout << "    ESTADISTICAS    \n";
    cout << "Dimensiones actuales:        " << filas << " x " << columnas << "\n";
    cout << "Eliminaciones del usuario:   " << eliminacionesUsuario << "\n";
    cout << "Fichas eliminadas (total):   " << fichasEliminadasTotal << "\n";
    cout << "Combinaciones detectadas:    " << combinacionesDetectadas << "\n";
    cout << "Cascadas (jugada actual):    " << cascadasJugadaActual << "\n";
    cout << "Puntuacion:                  " << puntuacion << "\n\n";
}
