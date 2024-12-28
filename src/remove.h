#ifndef REMOVE_H
#define REMOVE_H

#include <stdio.h>
#include <string.h>
#include "bytemaps_utils.h"
#include "super_bloque.h"

#include "cabeceras.h"

// Prototipo de la función borrar
int borrar(EXT_ENTRADA_DIR *directorio, EXT_BLQ_INODOS *inodos, EXT_BYTE_MAPS *ext_bytemaps, EXT_SIMPLE_SUPERBLOCK *ext_superblock, char *nombre, FILE *fich);

#endif 
