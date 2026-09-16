#include "tablero.h"
#include <cstdlib>

// la libreria <cstdlib> es usada para la generacion random

unsigned char generarFichaAleatoria() {

    return static_cast<unsigned char>(rand() % 6);
}

bool posicionValida(int fila, int columna, int filas, int columnas){

    return (fila >= 0 && fila < filas && columna >= 0 && columna < columnas);
}

bool crearTablero(unsigned char*& tablero, int& filas, int& columnas, int& capacidadBytes, int filasIniciales, int columnasIniciales){

    if (tablero != nullptr){
        return false;
    }

    if (filasIniciales < DIMENSION_MINIMA || columnasIniciales < DIMENSION_MINIMA){
        return false;
    }
    if (filasIniciales > DIMENSION_MAXIMA || columnasIniciales > DIMENSION_MAXIMA){
        return false;
    }

    int bytesNecesarios = calcularBytesNecesarios(filasIniciales, columnasIniciales);

    tablero = new unsigned char[bytesNecesarios];
    for (int i = 0; i < bytesNecesarios; i++){
        tablero[i] = 0;
    }

    filas = filasIniciales;
    columnas = columnasIniciales;
    capacidadBytes = bytesNecesarios;

    return true;
}

void liberarTablero(unsigned char*& tablero, int& filas, int& columnas, int& capacidadBytes){
    if (tablero != nullptr){
        delete[] tablero;
        tablero = nullptr;
    }
    filas = 0;
    columnas = 0;
    capacidadBytes = 0;
}

bool insertarFila(unsigned char*& tablero, int& filas, int columnas, int& capacidadBytes, int posicion){

    if (columnas < DIMENSION_MINIMA){
        return false;
    }
    if (posicion < 0 || posicion > filas){
        return false;
    }
    if (filas + 1 > DIMENSION_MAXIMA){
        return false;
    }

    int nuevasFilas = filas + 1;
    int bytesNecesarios = calcularBytesNecesarios(nuevasFilas, columnas);

    unsigned char* nuevoTablero = new unsigned char[bytesNecesarios];
    for (int i = 0; i < bytesNecesarios; i++){
        nuevoTablero[i] = 0;
    }

    for (int f = 0; f < filas; f++){
        int filaDestino = (f < posicion) ? f : f + 1;
        for (int c = 0; c < columnas; c++){
            unsigned char valor = obtenerFicha(tablero, f, c, columnas);
            escribirFicha(nuevoTablero, filaDestino, c, columnas, valor);
        }
    }

    for (int c = 0; c < columnas; c++){
        escribirFicha(nuevoTablero, posicion, c, columnas, generarFichaAleatoria());
    }

    delete[] tablero;
    tablero = nuevoTablero;
    filas = nuevasFilas;
    capacidadBytes = bytesNecesarios;

    return true;
}

bool eliminarFila(unsigned char*& tablero, int& filas, int columnas, int& capacidadBytes, int posicion){

    if (posicion < 0 || posicion >= filas){
        return false;
    }
    if (filas - 1 < DIMENSION_MINIMA){
        return false;
    }

    int nuevasFilas = filas - 1;
    int bytesUsadosNuevos = calcularBytesNecesarios(nuevasFilas, columnas);

    unsigned char* recompactado = new unsigned char[bytesUsadosNuevos];
    for (int i = 0; i < bytesUsadosNuevos; i++){
        recompactado[i] = 0;
    }

    int filaDestino = 0;
    for (int f = 0; f < filas; f++){
        if (f == posicion){
            continue;
        }

        for (int c = 0; c < columnas; c++){
            unsigned char valor = obtenerFicha(tablero, f, c, columnas);
            escribirFicha(recompactado, filaDestino, c, columnas, valor);
        }
        filaDestino++;
    }

    bool reducirMemoria = (bytesUsadosNuevos * 100 < capacidadBytes * 65);

    if (reducirMemoria) {
        delete[] tablero;
        tablero = recompactado;
        capacidadBytes = bytesUsadosNuevos;
    }
    else {
        for (int i = 0; i < bytesUsadosNuevos; i++)
            tablero[i] = recompactado[i];
        for (int i = bytesUsadosNuevos; i < capacidadBytes; i++)
            tablero[i] = 0;
        delete[] recompactado;
    }

    filas = nuevasFilas;
    return true;
}

bool insertarColumna(unsigned char*& tablero, int filas, int& columnas, int& capacidadBytes, int posicion){

    if (filas < DIMENSION_MINIMA){
        return false;
    }
    if (posicion < 0 || posicion > columnas){
        return false;
    }
    if (columnas + 1 > DIMENSION_MAXIMA){
        return false;
    }

    int nuevasColumnas = columnas + 1;
    int bytesNecesarios = calcularBytesNecesarios(filas, nuevasColumnas);

    unsigned char* nuevoTablero = new unsigned char[bytesNecesarios];
    for (int i = 0; i < bytesNecesarios; i++){
        nuevoTablero[i] = 0;
    }

    for (int f = 0; f < filas; f++){
        for (int c = 0; c < columnas; c++){
            int columnaDestino = (c < posicion) ? c : c + 1;
            unsigned char valor = obtenerFicha(tablero, f, c, columnas);
            escribirFicha(nuevoTablero, f, columnaDestino, nuevasColumnas, valor);
        }
        escribirFicha(nuevoTablero, f, posicion, nuevasColumnas, generarFichaAleatoria());
    }

    delete[] tablero;
    tablero = nuevoTablero;
    columnas = nuevasColumnas;
    capacidadBytes = bytesNecesarios;

    return true;
}

bool eliminarColumna(unsigned char*& tablero, int filas, int& columnas, int& capacidadBytes, int posicion){
    if (posicion < 0 || posicion >= columnas){
        return false;
    }
    if (columnas - 1 < DIMENSION_MINIMA){
        return false;
    }

    int nuevasColumnas = columnas - 1;
    int bytesUsadosNuevos = calcularBytesNecesarios(filas, nuevasColumnas);

    unsigned char* recompactado = new unsigned char[bytesUsadosNuevos];
    for (int i = 0; i < bytesUsadosNuevos; i++){
        recompactado[i] = 0;
    }

    for (int f = 0; f < filas; f++){
        int columnaDestino = 0;
        for (int c = 0; c < columnas; c++){
            if (c == posicion){
                continue; // se omite la columna eliminida
            }

            unsigned char valor = obtenerFicha(tablero, f, c, columnas);
            escribirFicha(recompactado, f, columnaDestino, nuevasColumnas, valor);
            columnaDestino++;
        }
    }

    bool reducirMemoria = (bytesUsadosNuevos * 100 < capacidadBytes * 65);

    if (reducirMemoria){
        delete[] tablero;
        tablero = recompactado;
        capacidadBytes = bytesUsadosNuevos;
    }
    else{
        for (int i = 0; i < bytesUsadosNuevos; i++){
            tablero[i] = recompactado[i];
        }
        for (int i = bytesUsadosNuevos; i < capacidadBytes; i++){
            tablero[i] = 0;
        }
        delete[] recompactado;
    }

    columnas = nuevasColumnas;
    return true;
}