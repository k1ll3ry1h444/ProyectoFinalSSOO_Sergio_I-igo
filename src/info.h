#ifndef INFO_H
#define INFO_H

#include "super_bloque.h"
#include "cabeceras.h"

// Declaración de la función para mostrar la información del superbloque
void info(EXT_SIMPLE_SUPERBLOCK *superbloque);

// Declaración de la función principal para procesar el archivo del superbloque
int info_func(int argc, char *argv[]);

#endif  
