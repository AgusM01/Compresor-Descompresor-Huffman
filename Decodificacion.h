#ifndef __DECODIFICACION_H__
#define __DECODIFICACION_H__
#include <stddef.h>
#include "Arbol.h"

/*
    *Parsea el arbol.
*/
PArbol parseo_arbol(char *arbolComprimido, int *posicion);
/*
    *Serializa las hojas del arbol en la decodificacion.
*/
PArbol serializa_hojas_decodificacion(PArbol arbolDecodificado,
                                      char *arbolCodificado, int *posicion);
/*
    *Crea un arreglo que contiene todo el contenido decodificado.
*/
void decodificacion_de_archivo(PArbol arbolDecodificadoCompleto,
                               char *archivoCodificado,
                               char **archivoDecodificado,
                               int *posicionArchivoCodificado,
                               int *posicionArchivoDecodificado);

#endif                          //__DECODIFICACION_H__
