#ifndef SUPER_BLOQUE_H
#define SUPER_BLOQUE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cabeceras.h"

/* Prototipos de las funciones */

// Función que guarda un superbloque en un archivo binario
void grabarSuperBloque(EXT_SIMPLE_SUPERBLOCK *ext_superblock, FILE *fich);

// Función que lee un superbloque desde un archivo binario
void leeSuperBloque(EXT_SIMPLE_SUPERBLOCK *psup, FILE *fich);

#endif /* FUNCIONES_SUPERBLOQUE_H */
