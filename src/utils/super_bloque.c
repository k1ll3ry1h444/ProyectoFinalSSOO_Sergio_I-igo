#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../cabeceras.h"

// Función que guarda un superbloque en un archivo binario
void grabarSuperBloque(EXT_SIMPLE_SUPERBLOCK *ext_superblock, FILE *fich) {
    if (ext_superblock == NULL || fich == NULL) {
        printf("Error: Puntero nulo en grabarSuperBloque.\n");
        return;
    }

    // Escribe el superbloque en el archivo
    size_t bytes_escritos = fwrite(ext_superblock, sizeof(EXT_SIMPLE_SUPERBLOCK), 1, fich);
    if (bytes_escritos != 1) {
        printf("Error al escribir el superbloque en el archivo.\n");
    } else {
        printf("Superbloque guardado exitosamente.\n");
    }
}

// Función que lee un superbloque desde un archivo binario
void leeSuperBloque(EXT_SIMPLE_SUPERBLOCK *psup, FILE *fich) {
    if (psup == NULL || fich == NULL) {
        printf("Error: Puntero nulo en leeSuperBloque.\n");
        return;
    }

    // Lee el superbloque del archivo
    size_t bytes_leidos = fread(psup, sizeof(EXT_SIMPLE_SUPERBLOCK), 1, fich);
    if (bytes_leidos != 1) {
        printf("Error al leer el superbloque del archivo.\n");
    } else {
        printf("Superbloque leído exitosamente.\n");
    }
}
