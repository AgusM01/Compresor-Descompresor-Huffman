#ifndef __CODIFICACION_H__
#define __CODIFICACION_H__
#include <stddef.h>
#include "Arbol.h"
#define CANT_CARACTERES 256

typedef struct _Codificacion {
  char *codigo;
  int size;
} Codificacion;


/*
  *Crea un arreglo de estructuras Codificacion en la que cada caracter 
  tiene su codificacion y el tamaño de la misma.
*/
void crea_arreglo_codificado(Codificacion * arregloDeCodificacion,
                             PArbol arbolDeCaracteres, char **arr, int posicion,
                             int arrLength, int direccion);
/*
  *Serializa la forma del arbol.
*/
void serializa_forma_arbol(PArbol arbolDeCaracteres, char *arr, int *posicion);
/*
 *Serializa las hojas del arbol.
*/
void serializa_hojas(PArbol arbolDeCaracteres, char *arr, int *posicion);
/*
  *Codifica el contenido del archivo.
*/
char *codificacion_contenido(int size, char *contenido,
                             Codificacion * arregloDeCodificacion,
                             int *sizeFinal);

#endif                          //__CODIFICACION_H__
