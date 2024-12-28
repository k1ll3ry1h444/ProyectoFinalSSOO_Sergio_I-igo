#ifndef HELPERS_H
#define HELPERS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cabeceras.h"

/* Prototipos de las funciones */

int validar_ruta(const char *ruta);

void copiar_bloque(EXT_DATOS *destino, EXT_DATOS *origen);

void lanzar_error(const char *mensaje);

// Función para grabar un directorio y sus inodos en un archivo binario
void grabarInodosyDirectorio(EXT_ENTRADA_DIR *directorio, EXT_BLQ_INODOS *inodos, FILE *fich);

// Función para grabar los byte maps (mapas de bits) en un archivo binario
void grabarByteMaps(EXT_BYTE_MAPS *ext_bytemaps, FILE *fich);

// Función para grabar datos en un archivo binario
void grabarDatos(EXT_DATOS *memdatos, FILE *fich);

#endif 
