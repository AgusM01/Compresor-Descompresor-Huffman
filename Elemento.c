#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "io.h"
#include "Elemento.h"

/*
  *Recorre el contenido completando así el arreglo.
*/
Elemento *completa_arreglo(int size, char *contenido, int lengthArray) {
  Elemento *array = malloc(sizeof(Elemento) * lengthArray);
  assert(array != NULL);
  for (int i = 0; i < lengthArray; i++) {
    array[i].frecuencia = 0;
    array[i].caracter = (unsigned char) i;
  }
  for (int i = 0; i < size; i++) {
    array[(unsigned char) contenido[i]].frecuencia += 1;
  }
  return array;
}
