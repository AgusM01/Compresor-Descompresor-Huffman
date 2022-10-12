#include <stdio.h>
#include <stdlib.h>
#include "Decodificacion.h"
#include "io.h"
#include <assert.h>
#include "test.h"

int main(){
  char *archivoCodificadoImplosionado;
  char *archivoCodificado;
  char *arbolCodificado;
  int sizeArchivo, sizeArbol;
  /*
   **Guarda el contenido del archivo en archivoCodificado.
   **Guarda tamaño del archivo en size.
   */
  archivoCodificadoImplosionado = readfile("f.hf.txt", &sizeArchivo);
  /*Tengo el archivo codificado implosionado. */
  arbolCodificado = readfile("hf.tree.txt", &sizeArbol);
  /*Tengo el arbol codificado. */
  int newSize;
  archivoCodificado =
      explode(archivoCodificadoImplosionado, sizeArchivo, &newSize);
  free(archivoCodificadoImplosionado);
  /*Tengo el archivo codificado explosionado. */

  PArbol arbolDecodificado;
  int posicion = 0;
  /*Parsea el arbol */
  arbolDecodificado = parseo_arbol(arbolCodificado, &posicion);

  //posicion += 1;                //Aumenta la posicion 1 vez para ubicar en el inicio de la serializacion de las hojas.
  //Ya tengo la forma del arbol codificada.
  PArbol arbolDecodificadoCompleto;
  arbolDecodificadoCompleto =
      serializa_hojas_decodificacion(arbolDecodificado, arbolCodificado,
                                     &posicion);
  free(arbolCodificado);
  /*
     arboDecodificadoCompleto es ahora el arbol que utilicé
     para codificar mi archivo.
     Ahora resta decodificar nuevamente el archivo.
   */
  char *archivoDecodificado = malloc(sizeof(char) * newSize);   /*Por la manera que codifique, se que el tamaño del arreglo "archivoCodificado" será mayor.*/
  assert(archivoDecodificado != NULL);
  int posicionArchivoCodificado = 0, posicionArchivoDecodificado = 0;

  while (posicionArchivoCodificado < newSize) {
    decodificacion_de_archivo(arbolDecodificadoCompleto, archivoCodificado,
                              &archivoDecodificado, &posicionArchivoCodificado,
                              &posicionArchivoDecodificado);
  }
  /*Escribe el archivo descomprimido */
  writefile("archivoDescomprimido", archivoDecodificado,
            posicionArchivoDecodificado);

  /*Libera lo que quedaba por liberar */
  free(archivoCodificado);
  libera_arbol(arbolDecodificado);
  free(archivoDecodificado);
  return 0;
}
