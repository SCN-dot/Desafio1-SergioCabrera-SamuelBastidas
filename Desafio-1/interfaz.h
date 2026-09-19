#ifndef INTERFAZ_H
#define INTERFAZ_H

char simboloDeCelda(unsigned char codigo);

void imprimirTabSimbolos(const unsigned char* tab, int filas, int columnas);

void imprimirTabBinario(const unsigned char* tab, int filas, int columnas);

void imprimirTablero(const unsigned char* tab, int filas, int columnas);

void imprimirEstadisticas(int filas, int columnas, int jugadasUsuario, int totalCeldasEliminadas, int totalRachasDetectadas, int cascadasEnJugada, int totalCascadas, int puntosT);

#endif // INTERFAZ_H
