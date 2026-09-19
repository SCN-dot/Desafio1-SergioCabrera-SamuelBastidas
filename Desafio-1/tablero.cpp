#include "tablero.h"
#include <cstdlib>

// la libreria <cstdlib> es usada para la generacion random

unsigned char generarCeldaRandom() {

    return static_cast<unsigned char>(rand() % 6);
}

bool esPosicionValida(int fila, int columna, int filas, int columnas){

    return (fila >= 0 && fila < filas && columna >= 0 && columna < columnas);
}

bool inicializarTablero(unsigned char*& tab, int& filas, int& columnas, int& capacidadBytes, int filasIniciales, int columnasIniciales){

    if (tab != nullptr){
        return false;
    }

    if (filasIniciales < TAM_MINIMO || columnasIniciales < TAM_MINIMO){
        return false;
    }
    if (filasIniciales > TAM_MAXIMO || columnasIniciales > TAM_MAXIMO){
        return false;
    }

    int bytesReq = calcularTamanoBytes(filasIniciales, columnasIniciales);

    tab = new unsigned char[bytesReq];
    for (int i = 0; i < bytesReq; i++){
        tab[i] = 0;
    }

    filas = filasIniciales;
    columnas = columnasIniciales;
    capacidadBytes = bytesReq;

    return true;
}

void destruirTablero(unsigned char*& tab, int& filas, int& columnas, int& capacidadBytes){
    if (tab != nullptr){
        delete[] tab;
        tab = nullptr;
    }
    filas = 0;
    columnas = 0;
    capacidadBytes = 0;
}

bool agregarFila(unsigned char*& tab, int& filas, int columnas, int& capacidadBytes, int posicion){

    if (columnas < TAM_MINIMO){
        return false;
    }
    if (posicion < 0 || posicion > filas){
        return false;
    }
    if (filas + 1 > TAM_MAXIMO){
        return false;
    }

    int nuevasFilas = filas + 1;
    int bytesReq = calcularTamanoBytes(nuevasFilas, columnas);

    unsigned char* nuevoTablero = new unsigned char[bytesReq];
    for (int i = 0; i < bytesReq; i++){
        nuevoTablero[i] = 0;
    }

    for (int fi = 0; fi < filas; fi++){
        int filaDestino;
        if (fi < posicion) {
            filaDestino = fi;
        } else {
            filaDestino = fi + 1;
        }
        for (int ci = 0; ci < columnas; ci++){
            unsigned char valor = leerCelda(tab, fi, ci, columnas);
            guardarCelda(nuevoTablero, filaDestino, ci, columnas, valor);
        }
    }

    for (int ci = 0; ci < columnas; ci++){
        guardarCelda(nuevoTablero, posicion, ci, columnas, generarCeldaRandom());
    }

    delete[] tab;
    tab = nuevoTablero;
    filas = nuevasFilas;
    capacidadBytes = bytesReq;

    return true;
}

bool quitarFila(unsigned char*& tab, int& filas, int columnas, int& capacidadBytes, int posicion){

    if (posicion < 0 || posicion >= filas) {
        return false;
    }
    if (filas - 1 < TAM_MINIMO) {
        return false;
    }

    int nuevasFilas = filas - 1;
    int bytesUsadosNuevos = calcularTamanoBytes(nuevasFilas, columnas);

    bool reducirMemoria = (bytesUsadosNuevos * 100 < capacidadBytes * 65);

    if (reducirMemoria) {
        unsigned char* recompactado = new unsigned char[bytesUsadosNuevos];
        for (int i = 0; i < bytesUsadosNuevos; i++){
            recompactado[i] = 0;
        }

        int filaDestino = 0;
        for (int fi = 0; fi < filas; fi++){
            if (fi == posicion){
                continue;
            }

            for (int ci = 0; ci < columnas; ci++){
                unsigned char valor = leerCelda(tab, fi, ci, columnas);
                guardarCelda(recompactado, filaDestino, ci, columnas, valor);
            }
            filaDestino++;
        }

        delete[] tab;
        tab = recompactado;
        capacidadBytes = bytesUsadosNuevos;
    } else {
        int filaDestino = 0;
        for (int fi = 0; fi < filas; fi++){
            if (fi == posicion){
                continue;
            }

            for (int ci = 0; ci < columnas; ci++){
                unsigned char valor = leerCelda(tab, fi, ci, columnas);
                guardarCelda(tab, filaDestino, ci, columnas, valor);
            }
            filaDestino++;
        }

        for (int i = bytesUsadosNuevos; i < capacidadBytes; i++){
            tab[i] = 0;
        }
    }

    filas = nuevasFilas;
    return true;
}

bool agregarColumna(unsigned char*& tab, int filas, int& columnas, int& capacidadBytes, int posicion){

    if (filas < TAM_MINIMO){
        return false;
    }
    if (posicion < 0 || posicion > columnas){
        return false;
    }
    if (columnas + 1 > TAM_MAXIMO){
        return false;
    }

    int nuevasColumnas = columnas + 1;
    int bytesReq = calcularTamanoBytes(filas, nuevasColumnas);

    unsigned char* nuevoTablero = new unsigned char[bytesReq];
    for (int i = 0; i < bytesReq; i++){
        nuevoTablero[i] = 0;
    }

    for (int fi = 0; fi < filas; fi++){
        for (int ci = 0; ci < columnas; ci++){
            int columnaDestino;
            if (ci < posicion) {
                columnaDestino = ci;
            } else {
                columnaDestino = ci + 1;
            }
            unsigned char valor = leerCelda(tab, fi, ci, columnas);
            guardarCelda(nuevoTablero, fi, columnaDestino, nuevasColumnas, valor);
        }
        guardarCelda(nuevoTablero, fi, posicion, nuevasColumnas, generarCeldaRandom());
    }

    delete[] tab;
    tab = nuevoTablero;
    columnas = nuevasColumnas;
    capacidadBytes = bytesReq;

    return true;
}

bool quitarColumna(unsigned char*& tab, int filas, int& columnas, int& capacidadBytes, int posicion){
    if (posicion < 0 || posicion >= columnas){
        return false;
    }
    if (columnas - 1 < TAM_MINIMO){
        return false;
    }

    int nuevasColumnas = columnas - 1;
    int bytesUsadosNuevos = calcularTamanoBytes(filas, nuevasColumnas);

    bool reducirMemoria = (bytesUsadosNuevos * 100 < capacidadBytes * 65);

    if (reducirMemoria){
        unsigned char* recompactado = new unsigned char[bytesUsadosNuevos];
        for (int i = 0; i < bytesUsadosNuevos; i++){
            recompactado[i] = 0;
        }

        for (int fi = 0; fi < filas; fi++){
            int columnaDestino = 0;
            for (int ci = 0; ci < columnas; ci++){
                if (ci == posicion){
                    continue; // se omite la columna eliminida
                }

                unsigned char valor = leerCelda(tab, fi, ci, columnas);
                guardarCelda(recompactado, fi, columnaDestino, nuevasColumnas, valor);
                columnaDestino++;
            }
        }

        delete[] tab;
        tab = recompactado;
        capacidadBytes = bytesUsadosNuevos;
    } else{
        for (int fi = 0; fi < filas; fi++){
            int columnaDestino = 0;
            for (int ci = 0; ci < columnas; ci++){
                if (ci == posicion){
                    continue; // se omite la columna eliminida
                }

                unsigned char valor = leerCelda(tab, fi, ci, columnas);
                guardarCelda(tab, fi, columnaDestino, nuevasColumnas, valor);
                columnaDestino++;
            }
        }

        for (int i = bytesUsadosNuevos; i < capacidadBytes; i++){
            tab[i] = 0;
        }
    }

    columnas = nuevasColumnas;
    return true;
}