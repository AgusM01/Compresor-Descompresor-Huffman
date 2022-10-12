#ifndef __ELEMENTO_H__
#define __ELEMENTO_H__
#include <stddef.h>

typedef struct _Elemento {
  int caracter;
  int frecuencia;
} Elemento;

/*
  *Recorre el contenido completando así el arreglo.
*/
Elemento *completa_arreglo(int size, char *contenido, int lengthArray);

#endif//__ELEMENTO_H__
