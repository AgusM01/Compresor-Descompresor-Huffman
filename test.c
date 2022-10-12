#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Codificacion.h"
#include "Decodificacion.h"
#include "io.h"

void mergesort_test() {
  PArbol *ArrayDeArboles = malloc(sizeof(*ArrayDeArboles) * 6);
  assert(ArrayDeArboles != NULL);
  Arbol nuevoNodo1;
  nuevoNodo1.peso = 1;
  nuevoNodo1.caracter = 'a';
  Arbol nuevoNodo2;
  nuevoNodo2.caracter = 'b';
  nuevoNodo2.peso = 2;
  Arbol nuevoNodo3;
  nuevoNodo3.caracter = 'c';
  nuevoNodo3.peso = 3;
  Arbol nuevoNodo4;
  nuevoNodo4.caracter = 'd';
  nuevoNodo4.peso = 4;
  Arbol nuevoNodo5;
  nuevoNodo5.caracter = 'e';
  nuevoNodo5.peso = 5;
  Arbol nuevoNodo6;
  nuevoNodo6.caracter = 'f';
  nuevoNodo6.peso = 6;

  ArrayDeArboles[0] = &nuevoNodo3;
  ArrayDeArboles[1] = &nuevoNodo2;
  ArrayDeArboles[2] = &nuevoNodo5;
  ArrayDeArboles[3] = &nuevoNodo4;
  ArrayDeArboles[4] = &nuevoNodo1;
  ArrayDeArboles[5] = &nuevoNodo6;


  PArbol *arrayOrdenado;
  arrayOrdenado = merge_sort(ArrayDeArboles, 6);
  assert(arrayOrdenado[0] == &nuevoNodo1);
  assert(arrayOrdenado[1] == &nuevoNodo2);
  assert(arrayOrdenado[2] == &nuevoNodo3);
  assert(arrayOrdenado[3] == &nuevoNodo4);
  assert(arrayOrdenado[4] == &nuevoNodo5);
  assert(arrayOrdenado[5] == &nuevoNodo6);

  free(ArrayDeArboles);
  free(arrayOrdenado);
}
void unir_arboles_test() {
  Arbol arbol1;
  Arbol arbol2;
  arbol1.peso = 3;
  arbol2.peso = 7;

  PArbol unionA1A2;
  unionA1A2 = unir_arboles(&arbol1, &arbol2);
  assert(unionA1A2->peso == 10);
  assert(unionA1A2->left == &arbol1);
  assert(unionA1A2->right == &arbol2);

  free(unionA1A2);
}

void completa_arreglo_test() {
  char arr[] = { 'a', 'b', 'c' };
  Elemento *array;
  array = completa_arreglo(3, arr, CANT_CARACTERES);

  assert(array[(unsigned char) 'a'].frecuencia == 1);
  assert(array[(unsigned char) 'b'].frecuencia == 1);
  assert(array[(unsigned char) 'c'].frecuencia == 1);
  free(array);
}

void tests() {
  mergesort_test();
  unir_arboles_test();
  completa_arreglo_test();
}
