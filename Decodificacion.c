#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "io.h"
#include "Codificacion.h"

/*
    *Parsea el arbol.
*/
PArbol parseo_arbol(char *arbolComprimido, int *posicion) {
  PArbol nuevoNodo = malloc(sizeof *nuevoNodo);
  assert(nuevoNodo != NULL);
  nuevoNodo->left = NULL;
  nuevoNodo->right = NULL;

  if (arbolComprimido[*posicion] == '\n')
    return nuevoNodo;

  if (arbolComprimido[*posicion] == '1') {
    *posicion += 1;
    return nuevoNodo;
  } else if (arbolComprimido[*posicion] == '0') {
    *posicion += 1;
    nuevoNodo->left = parseo_arbol(arbolComprimido, posicion);
    nuevoNodo->right = parseo_arbol(arbolComprimido, posicion);
  }
  return nuevoNodo;
}

/*
    *Serializa las hojas del arbol en la decodificacion.
*/
PArbol serializa_hojas_decodificacion(PArbol arbolDecodificado,
                                      char *arbolCodificado, int *posicion) {
  if (arbolDecodificado->left == NULL) {
    arbolDecodificado->caracter = arbolCodificado[*posicion];
    *posicion += 1;
    return arbolDecodificado;
  }
  serializa_hojas_decodificacion(arbolDecodificado->left, arbolCodificado,
                                 posicion);
  serializa_hojas_decodificacion(arbolDecodificado->right, arbolCodificado,
                                 posicion);
  return arbolDecodificado;
}

/*
    *Crea un arreglo que contiene todo el contenido decodificado.
*/
void decodificacion_de_archivo(PArbol arbolDecodificadoCompleto,
                               char *archivoCodificado,
                               char **archivoDecodificado,
                               int *posicionArchivoCodificado,
                               int *posicionArchivoDecodificado) {

  if (arbolDecodificadoCompleto->left == NULL) {
    (*archivoDecodificado)[*posicionArchivoDecodificado] =
        arbolDecodificadoCompleto->caracter;
    *posicionArchivoDecodificado += 1;
    return;
  }
  char caracter = archivoCodificado[*posicionArchivoCodificado];
  *posicionArchivoCodificado += 1;
  if (caracter == '0') {
    decodificacion_de_archivo(arbolDecodificadoCompleto->left,
                              archivoCodificado, archivoDecodificado,
                              posicionArchivoCodificado,
                              posicionArchivoDecodificado);
    return;
  }
  decodificacion_de_archivo(arbolDecodificadoCompleto->right, archivoCodificado,
                            archivoDecodificado, posicionArchivoCodificado,
                            posicionArchivoDecodificado);
}
