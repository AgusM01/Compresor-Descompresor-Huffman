#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "io.h"
#include "Codificacion.h"
#include "Arbol.h"


/*
  *Genera el árbol de carácteres.
*/
PArbol* crea_array_de_arboles(PArbol* arrayDeArboles, Elemento* arrayDeElemento, int lengthArray){
int i;
for (i = 0; i < lengthArray; i++){
    PArbol nuevoArbol = malloc(sizeof(Arbol));
    assert(nuevoArbol != NULL);
    nuevoArbol->caracter = arrayDeElemento[i].caracter;
    nuevoArbol->peso = arrayDeElemento[i].frecuencia;
    nuevoArbol->left = NULL;
    nuevoArbol->right = NULL;
    arrayDeArboles[i] = nuevoArbol;
} //Completa el array con los caracteres en el archivo

for (int i = lengthArray; i < 256; i++){ /*Este for está de más, nos olvidamos de borrarlo.*/
    PArbol nuevoArbol = malloc(sizeof(Arbol));
     assert(nuevoArbol != NULL);
     nuevoArbol->peso = 0;
     nuevoArbol->left = NULL;
     nuevoArbol->right = NULL;
     arrayDeArboles[i] = nuevoArbol;
 } //Completa el array para tener los 256 caracteres.
 return arrayDeArboles;
}

/*
  Une ordenadamente dos arreglos.
*/
PArbol* merge(PArbol* B1, PArbol* B2, int lengthB1, int lengthB2){
  int i = 0, j = 0, k = 0;
  PArbol* arrayOrdenado = malloc(sizeof(PArbol)* (lengthB1+lengthB2));
  assert(arrayOrdenado != NULL);
  while ((i < lengthB1) && (j < lengthB2)){
      if (B1[i]->peso <= B2[j]->peso){
        arrayOrdenado[k] = B1[i];
        i++;
      }
      else if (B2[j]->peso < B1[i]->peso){
          arrayOrdenado[k] = B2[j];
          j++;
      }
      k++;
    }

  while (i < lengthB1){
    arrayOrdenado[k] = B1[i];
    i++;
    k++;
  }
  while (j < lengthB2){
    arrayOrdenado[k] = B2[j];
    j++;
    k++;
  }
  return arrayOrdenado;
}
/*
  *Ordena el arreglo de menor a mayor utilizando Mergesort.
*/
PArbol* merge_sort(PArbol* array, int lengthArray){ 
    assert(lengthArray > 0);
    if (lengthArray < 2){
        PArbol *newArray = malloc(sizeof(PArbol) *lengthArray);
		    assert(newArray != NULL);
        newArray[0] = array[0];
        return newArray;
    }

    int m;
    m = lengthArray / 2;

    PArbol *A1, *A2;
    A1 = &array[0]; //A1 va desde 0 a m - 1
    A2 = &array[m]; //A2 va desde m a lengthArray

    PArbol *B1, *B2;
    
    B1 = merge_sort(A1,m); //Separo el array en sub-arrays de un elemento
    B2 = merge_sort(A2, (lengthArray - m)); //Separo el array en sub-arrays de un elemento

    PArbol* arrayOrdenado;
    arrayOrdenado = merge(B1, B2, m, (lengthArray - m));
    free(B1);
    free(B2);
    return arrayOrdenado;
}
/*
  *Une dos árboles.
*/
PArbol unir_arboles(Arbol* arbol1, Arbol* arbol2){ 
    PArbol arbolCombinado = malloc(sizeof(Arbol));
    assert(arbolCombinado != NULL);
    arbolCombinado->left = arbol1;
    arbolCombinado->right = arbol2;
    arbolCombinado->peso = arbol1->peso + arbol2->peso;
    return arbolCombinado;
}
/*
  *Genera arbol de Huffmann.
*/
PArbol genera_arbol_completo(PArbol** arrayDeArboles, int lengthArray){
    int lengthArbolActual = 0;
    PArbol* array2DeArboles; /*Array auxiliar para ordenar el arbol en cada iteración.*/
    while(lengthArbolActual < lengthArray - 1){
        
        array2DeArboles = merge_sort(*arrayDeArboles, lengthArray); /*Ordena el arbol de menor a mayor.*/
        free((*arrayDeArboles));
        *arrayDeArboles = array2DeArboles;
        /*Une un arbol con su siguiente ubicandolo en la posicion en el arreglo de este ultimo*/
        (*arrayDeArboles)[lengthArbolActual + 1] = unir_arboles((*arrayDeArboles)[lengthArbolActual],
                                                             (*arrayDeArboles)[lengthArbolActual + 1]); 
        lengthArbolActual++;
    }
    return (*arrayDeArboles)[lengthArbolActual]; //Esta es la raíz del arbol creado.
}
/*
  *Libera un arbol.
*/
void libera_arbol(PArbol arbol){
  if(arbol == NULL)
    return;

  if (arbol->left == NULL){
    free(arbol);
    return;
  }
  libera_arbol(arbol->left);
  libera_arbol(arbol->right);
  free(arbol);
}
   