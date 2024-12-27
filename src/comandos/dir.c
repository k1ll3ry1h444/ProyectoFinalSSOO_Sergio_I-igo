//Iñigo
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "cabeceras.h"

void Directorio(EXT_ENTRADA_DIR *directorio, EXT_BLQ_INODOS *inodos) {
    printf("Archivos en el directorio:\n");
    printf("%-20s %-10s %-10s %-15s\n", "Nombre", "Inodo", "Tamaño", "Bloques Ocupados");
    printf("---------------------------------------------------------------\n");

    for (int i = 0; i < MAX_FICHEROS; i++) {
        if (directorio[i].dir_nfich[0] != '\0') { // Verifica si hay una entrada válida
            EXT_SIMPLE_INODE *inodo = &inodos->blq_inodos[directorio[i].dir_inodo];

            printf("%-20s %-10d %-10d ", directorio[i].dir_nfich, directorio[i].dir_inodo, inodo->size_fichero);

            // Imprimir bloques ocupados
            for (int j = 0; j < MAX_NUMS_BLOQUE_INODO; j++) {
                if (inodo->i_nbloque[j] != NULL_BLOQUE) {
                    printf("%d ", inodo->i_nbloque[j]);
                }
            }
            printf("\n");
        }
    }
}

int buscaFich(EXT_ENTRADA_DIR *directorio, char *nombre) {
    for (int i = 0; i < MAX_FICHEROS; i++) {
        if (strcmp(directorio[i].dir_nfich, nombre) == 0) {
            return i; // Devuelve el índice de la entrada encontrada
        }
    }
    return -1; // Archivo no encontrado
}


