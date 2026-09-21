# Sweet Crush - Desafio 1

Juego Sweet Crush para consola en C++. Cada ficha se guarda en 3 bits dentro de un unico bloque de memoria dinamica.

Autores: Sergio Cabrera y Samuel Bastidas

## Archivos

bits.h / bits.cpp: lectura y escritura de fichas de 3 bits
tablero.h / tablero.cpp: memoria dinamica del tablero, filas y columnas
juego.h / juego.cpp: deteccion de combinaciones, gravedad y cascadas
interfaz.h / interfaz.cpp: impresion del tablero y estadisticas
main.cpp: menu y programa principal
Informe_Final_Desafio_1_.pdf: informe del desafio
Informe_Preliminar_Desafio_1.pdf: Primer informe del desafio 

## Compilar y ejecutar

Con Qt Creator: crear un proyecto de consola en C++, agregar todos los archivos .h y .cpp y ejecutar.

## Uso

Al iniciar, el programa pide las filas y columnas del tablero (de 1 a 1000), lo llena con fichas aleatorias y lo muestra. Las filas y columnas se numeran desde 0.

Fichas: X, O, #, @, &, $.

### Menu

Opcion y Que hace 

1 Eliminar ficha: Pide fila y columna y elimina esa ficha. Las fichas de arriba caen y los huecos se rellenan con fichas nuevas aleatorias.
2 Insertar fila: Pide una posicion (de 0 hasta el numero actual de filas) e inserta ahi una fila nueva con fichas aleatorias. Las filas siguientes se desplazan hacia abajo.
3 Eliminar fila: Pide la posicion de una fila y la elimina. El tablero debe conservar al menos 1 fila. 
4 Insertar columna: Pide una posicion (de 0 hasta el numero actual de columnas) e inserta ahi una columna nueva con fichas aleatorias. Las columnas siguientes se desplazan hacia la derecha. 
5 Eliminar columna: Pide la posicion de una columna y la elimina. El tablero debe conservar al menos 1 columna. 
6 Mostrar tablero: Muestra el tablero en formato de fichas y en formato binario, sin modificarlo. 
7 Mostrar estadisticas: Muestra dimensiones actuales, eliminaciones del usuario, fichas eliminadas, combinaciones detectadas, cascadas de la ultima jugada, cascadas totales y puntuacion. 
0 Salir: Libera la memoria del tablero y termina el programa. 

Las opciones 1 a 5 modifican el tablero. Despues de cada una, el programa busca combinaciones de 3 o mas fichas iguales en horizontal o vertical, las elimina y repite el proceso (cascadas) hasta que no queden mas. Luego muestra el tablero y las estadisticas.

Cada ficha eliminada dentro de una combinacion suma 10 puntos.
