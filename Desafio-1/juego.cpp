#include "juego.h"
#include "bits.h"
#include "tablero.h"


void llenarTableroInicial(unsigned char* tab, int filas, int columnas) {
    for (int f = 0; f < filas; f++) {
        for (int c = 0; c < columnas; c++) {
            guardarCelda(tab, f, c, columnas, generarCeldaRandom());
        }
    }
}

bool quitarCeldaJugador(unsigned char* tab, int filas, int columnas, int fila, int col, int& jugadasUsuario, int& totalCeldasEliminadas) {
    if (!esPosicionValida(fila, col, filas, columnas)) {
        return false;
    }

    if (leerCelda(tab, fila, col, columnas) == CELDA_VACIA) {
        return false;
    }

    guardarCelda(tab, fila, col, columnas, CELDA_VACIA);
    aplicarCaidaFichas(tab, filas, columnas);

    jugadasUsuario++;
    totalCeldasEliminadas++;

    return true;
}

static void marcarEnMapa(unsigned char* mapa, int indice) {
    int byteIndice = indice >> 3;
    int bitIndice = indice & 7;
    mapa[byteIndice] = static_cast<unsigned char>(mapa[byteIndice] | (1u << bitIndice));
}

static bool estaMarcadoEnMapa(const unsigned char* mapa, int indice) {
    int byteIndice = indice >> 3;
    int bitIndice = indice & 7;
    return (mapa[byteIndice] & static_cast<unsigned char>(1u << bitIndice)) != 0;
}

bool detectarYLimpiarRachas(unsigned char* tab, int filas, int columnas, int& celdasMarcadas, int& rachasEncontradas) {
    celdasMarcadas = 0;
    rachasEncontradas = 0;

    int totalCeldas = filas * columnas;
    int bytesMapa = (totalCeldas + 7) / 8;
    unsigned char* mapaMarcas = new unsigned char[bytesMapa];
    for (int i = 0; i < bytesMapa; i++) {
        mapaMarcas[i] = 0;
    }

    for (int f = 0; f < filas; f++) {
        int c = 0;
        while (c < columnas) {
            unsigned char valor = leerCelda(tab, f, c, columnas);
            if (valor > VALOR_MAXIMO_FICHA) {
                c++;
                continue;
            }

            int inicioRacha = c;
            int longitud = 1;
            while (c + 1 < columnas && leerCelda(tab, f, c + 1, columnas) == valor) {
                c++;
                longitud++;
            }

            if (longitud >= RACHA_MINIMA) {
                rachasEncontradas++;
                for (int cc = inicioRacha; cc <= c; cc++)
                    marcarEnMapa(mapaMarcas, f * columnas + cc);
            }
            c++;
        }
    }

    for (int c = 0; c < columnas; c++) {
        int f = 0;
        while (f < filas) {
            unsigned char valor = leerCelda(tab, f, c, columnas);
            if (valor > VALOR_MAXIMO_FICHA) {
                f++;
                continue;
            }

            int inicioRacha = f;
            int longitud = 1;
            while (f + 1 < filas && leerCelda(tab, f + 1, c, columnas) == valor) {
                f++;
                longitud++;
            }

            if (longitud >= RACHA_MINIMA) {
                rachasEncontradas++;
                for (int ff = inicioRacha; ff <= f; ff++)
                    marcarEnMapa(mapaMarcas, ff * columnas + c);
            }
            f++;
        }
    }

    bool huboAlgo = false;
    for (int indice = 0; indice < totalCeldas; indice++) {
        if (estaMarcadoEnMapa(mapaMarcas, indice)) {
            int f = indice / columnas;
            int c = indice % columnas;
            guardarCelda(tab, f, c, columnas, CELDA_MARCADA);
            celdasMarcadas++;
            huboAlgo = true;
        }
    }

    delete[] mapaMarcas;

    for (int f = 0; f < filas; f++) {
        for (int c = 0; c < columnas; c++) {
            if (leerCelda(tab, f, c, columnas) == CELDA_MARCADA) {
                guardarCelda(tab, f, c, columnas, CELDA_VACIA);
            }
        }
    }

    return huboAlgo;
}

void aplicarCaidaFichas(unsigned char* tab, int filas, int columnas) {
    for (int c = 0; c < columnas; c++) {
        for (int f = filas - 1; f >= 0; f--) {
            if (leerCelda(tab, f, c, columnas) != CELDA_VACIA) {
                continue;
            }

            int origen = f - 1;
            while (origen >= 0 && leerCelda(tab, origen, c, columnas) == CELDA_VACIA) {
                origen--;
            }

            if (origen >= 0) {
                unsigned char valor = leerCelda(tab, origen, c, columnas);
                guardarCelda(tab, f, c, columnas, valor);
                guardarCelda(tab, origen, c, columnas, CELDA_VACIA);
            } else {
                guardarCelda(tab, f, c, columnas, generarCeldaRandom());
            }
        }
    }
}

void ejecutarCascadas(unsigned char* tab, int filas, int columnas, int& totalCeldasEliminadas, int& totalRachasDetectadas, int& cascadasEnJugada, int& totalCascadas, int& puntajeAcumulado) {
    cascadasEnJugada = 0;

    int celdasMarcadas = 0;
    int rachasEncontradas = 0;

    while (detectarYLimpiarRachas(tab, filas, columnas, celdasMarcadas, rachasEncontradas)) {
        totalCeldasEliminadas += celdasMarcadas;
        totalRachasDetectadas += rachasEncontradas;
        puntajeAcumulado += celdasMarcadas * PUNTOS_POR_CELDA;
        cascadasEnJugada++;
        totalCascadas++;

        aplicarCaidaFichas(tab, filas, columnas);
    }
}
