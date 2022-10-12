#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "io.h"
#include "Codificacion.h"

/*
  *Crea un arreglo de estructuras Codificacion en la que cada caracter 
  tiene su codificacion y el tamaño de la misma.
*/
void crea_arreglo_codificado(Codificacion* arregloDeCodificacion, PArbol arbolDeCaracteres, char** arr, int posicion, int arrLength, int direccion){
    char direccionChar = '0';
    if (direccion == 1)
        direccionChar = '1';

    if(posicion == 0){ /*Ver*/
      (*arr)[posicion] = direccionChar;
    }
    else{
      (*arr)[posicion - 1] = direccionChar;
    }
    if (arbolDeCaracteres->left == NULL){
        char* codificacion = malloc(sizeof(int) * posicion);
        assert(codificacion != NULL);
        for (int i = 0; i < posicion; i++){
            codificacion[i] = (*arr)[i];
        }
        arregloDeCodificacion[(unsigned char)arbolDeCaracteres->caracter].codigo = codificacion;
        arregloDeCodificacion[(unsigned char)arbolDeCaracteres->caracter].size = posicion;
        return;
    }
    crea_arreglo_codificado(arregloDeCodificacion, arbolDeCaracteres->left, arr, (posicion + 1), arrLength, 0);
    crea_arreglo_codificado(arregloDeCodificacion, arbolDeCaracteres->right, arr, (posicion + 1), arrLength, 1);
}

/*
  *Serializa la forma del arbol.
*/
void serializa_forma_arbol(PArbol arbolDeCaracteres, char* arr, int* posicion){
    if (arbolDeCaracteres->left == NULL){
      arr[*posicion] = '1';
      *posicion += 1;
      return;
    }
    arr[*posicion] = '0';
    *posicion += 1;
    serializa_forma_arbol(arbolDeCaracteres->left, arr, posicion);
    serializa_forma_arbol(arbolDeCaracteres->right, arr, posicion);
}
/*
 *Serializa las hojas del arbol.
*/
void serializa_hojas(PArbol arbolDeCaracteres, char* arr, int* posicion){
  
  if(arbolDeCaracteres->left == NULL){
    arr[*posicion] = arbolDeCaracteres->caracter;
    *posicion += 1;
    return;
  }
  serializa_hojas(arbolDeCaracteres->left, arr, posicion);
  serializa_hojas(arbolDeCaracteres->right, arr, posicion);
}
/*
  *Codifica el contenido del archivo.
*/
char* codificacion_contenido(int size, char* contenido, Codificacion* arregloDeCodificacion, int* sizeFinal){
  int posicionArray = 0;
  int sizeContenidoCodificado = 1000;
  char* contenidoCodificado = malloc(sizeof(char) * sizeContenidoCodificado);
  assert(contenidoCodificado != NULL);
  for(int i = 0; i < size; i++){
    for(int j = 0; j < arregloDeCodificacion[(unsigned char)contenido[i]].size; j++){
      if(posicionArray == sizeContenidoCodificado){
        sizeContenidoCodificado *= 4;
        contenidoCodificado = realloc(contenidoCodificado, sizeof(char) * sizeContenidoCodificado);
      }
      contenidoCodificado[posicionArray] = arregloDeCodificacion[(unsigned char)contenido[i]].codigo[j];
      posicionArray += 1;
    }
  }
  *sizeFinal = posicionArray;
  return contenidoCodificado;
}
