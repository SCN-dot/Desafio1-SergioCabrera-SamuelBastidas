#ifndef INTERFAZ_H
#define INTERFAZ_H

char obtenerSimboloFicha(unsigned char codigo);

void mostrarTableroFichas(const unsigned char* tablero, int filas, int columnas);

void mostrarTableroBinario(const unsigned char* tablero, int filas, int columnas);

void mostrarTablero(const unsigned char* tablero, int filas, int columnas);

void mostrarEstadisticas(int filas, int columnas, int eliminacionesUsuario, int fichasEliminadasTotal, int combinacionesDetectadas, int cascadasJugadaActual, int puntuacion);

#endif // INTERFAZ_H
