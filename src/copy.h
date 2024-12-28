#ifndef COPY_H
#define COPY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "helpers.h"
#include "bytemaps_utils.h"
#include "cabeceras.h"

// Prototipos de las funciones
int copiar(EXT_ENTRADA_DIR *directorio, EXT_BLQ_INODOS *inodos, EXT_BYTE_MAPS *ext_bytemaps, EXT_SIMPLE_SUPERBLOCK *ext_superblock, EXT_DATOS *memdatos, char *nombreorigen, char *nombredestino, FILE *fich);

// Prototipos de funciones auxiliares utilizados en copiar
int buscar_inodo_libre(EXT_BYTE_MAPS *ext_bytemaps);
int buscar_bloque_libre(EXT_BYTE_MAPS *ext_bytemaps);
void marcar_bloque_ocupado(EXT_BYTE_MAPS *ext_bytemaps, unsigned int bloque);
void copiar_bloque(EXT_DATOS *destino, EXT_DATOS *origen);

#endif