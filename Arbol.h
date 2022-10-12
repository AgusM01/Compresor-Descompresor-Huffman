#ifndef __ARBOL_H__
#define __ARBOL_H__
#include <stddef.h>
#include "Elemento.h"

typedef struct _Arbol{
  char caracter;
  int peso;
  struct _Arbol* right;
  struct _Arbol* left;
}Arbol;
typedef Arbol* PArbol;


/*
  *Genera el árbol de carácteres.
*/
PArbol* crea_array_de_arboles(PArbol* arbolDeCaracteres,
                                  Elemento* arrayDeCaracteres, int lengthArray);
/*
  *Función utilizada por mergesort para ordenar sub-arreglos
*/
PArbol* merge(PArbol* B1, PArbol* B2, int lengthB1, int lengthB2);
/*
  *Ordena el arreglo de menor a mayor utilizando Mergesort.
*/
PArbol* merge_sort(PArbol* array, int lengthArray);
/*
  *Une dos árboles.
*/
PArbol unir_arboles(Arbol* arbol1, Arbol* arbol2);
/*
  *Genera el árbol completo.
*/
PArbol genera_arbol_completo(PArbol** arbolDeCaracteres, int lengthArray);
/*
  *Libera un arbol.
*/
void libera_arbol(PArbol arbol);



#endif //__ARBOL_H__