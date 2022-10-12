#include <stdio.h>
#include <stdlib.h>
#include "Codificacion.h"
#include "io.h"
#include <assert.h>
#include "test.h"

int main() {
  //assert(argc == 2);
  char *contenido;
  int size;
  Elemento *arrayDeElemento;
  int lengthArray = 0;
  /*
   **Guarda el contenido del archivo en contenido.
   **Guarda tamaño del archivo en size.
   */
  contenido = readfile("archivoAComprimir", &size);

  arrayDeElemento = completa_arreglo(size, contenido, CANT_CARACTERES);
  PArbol *arrayDeArboles = malloc(sizeof(PArbol) * CANT_CARACTERES);
  assert(arrayDeArboles != NULL);
  PArbol arbolDeCaracteres;
  PArbol *arrayDeArbolesOrdenado;
  /*Creo un array de arboles en donde cada caracter es un árbol. */
  arrayDeArboles =
      crea_array_de_arboles(arrayDeArboles, arrayDeElemento, CANT_CARACTERES);
  free(arrayDeElemento);

  /*A partir de mi array de árboles, genero el árbol completo. */
  arbolDeCaracteres = genera_arbol_completo(&arrayDeArboles, CANT_CARACTERES);
  free(arrayDeArboles);

  Codificacion *arregloDeCodificacion =
      malloc(sizeof(Codificacion) * CANT_CARACTERES);
  assert(arregloDeCodificacion != NULL);

  char *arr = malloc(sizeof(char) * CANT_CARACTERES);
  assert(arr != NULL);

  /*Le asigno a cada caracter su codificacion. */
  crea_arreglo_codificado(arregloDeCodificacion, arbolDeCaracteres, &arr, 0,
                          CANT_CARACTERES, 0);
  free(arr);

  //Para este punto tenemos la codifdicacion de cada simbolo.
  //Ahora se codifica el árbol.
  char *arrArbol = malloc(sizeof(char) * (CANT_CARACTERES * 3 + 1));
  /*Son 256 caracteres + 511 nodos + \n que agrego para separar = 769 */
  assert(arrArbol != NULL);
  int posicion = 0;
  /*Serializa la forma del arbol */
  serializa_forma_arbol(arbolDeCaracteres, arrArbol, &posicion);
  
  /*Agrego un \n para separar la forma de las hojas */
  arrArbol[posicion] = '\n';
  /*Serializo las hojas del arbol */
  serializa_hojas(arbolDeCaracteres, arrArbol, &posicion);
  /*Libero el árbol */
  libera_arbol(arbolDeCaracteres);
  /*Escribo la codificacion del arbol en el archivo hf.tree.txt */
  writefile("hf.tree.txt", arrArbol, posicion);
  /*Libero el array que contiene la codificacion del arbol. */
  free(arrArbol);
  /*Ahora debemos codificar las hojas. */
  int sizeFinal;
  char *contenidoCodificado;
  /*Codifica el contenido del archivo */
  contenidoCodificado =
      codificacion_contenido(size, contenido, arregloDeCodificacion,
                             &sizeFinal);
  free(contenido);
  int sizeFinalPostImplode;
  char *contenidoCodificadoPostImplode;
  /*Implosiona el contenido codificado */
  contenidoCodificadoPostImplode =
      implode(contenidoCodificado, sizeFinal, &sizeFinalPostImplode);
  /*Escribe el archivo codificado */
  writefile("f.hf.txt", contenidoCodificadoPostImplode, sizeFinalPostImplode);

  /*Libero la memoria restante */
  for (int i = 0; i < CANT_CARACTERES; i++) {
    free(arregloDeCodificacion[i].codigo);
  }
  free(arregloDeCodificacion);
  free(contenidoCodificado);
  free(contenidoCodificadoPostImplode);
  return 0;
}
