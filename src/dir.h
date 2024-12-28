#ifndef DIR_H
#define DIR_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "cabeceras.h"

// Prototipos de las funciones
void Directorio(EXT_ENTRADA_DIR *directorio, EXT_BLQ_INODOS *inodos);
int buscaFich(EXT_ENTRADA_DIR *directorio, EXT_BLQ_INODOS *inodos, char *nombre);

#endif 
