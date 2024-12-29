#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "../cabeceras.h"

// Función para imprimir el contenido del directorio
void Directorio(EXT_ENTRADA_DIR *directorio, EXT_BLQ_INODOS *inodos) {
    printf("Archivos en el directorio:\n");
    printf("%-20s %-10s %-10s %-15s\n", "Nombre", "Inodo", "Tamaño", "Bloques Ocupados");
    printf("---------------------------------------------------------------\n");

    int archivos_encontrados = 0;

    for (int i = 0; i < MAX_FICHEROS; i++) {
        if (directorio[i].dir_nfich[0] != '\0') { // Verifica si hay una entrada válida
            archivos_encontrados = 1; // Encontramos al menos un archivo
            EXT_SIMPLE_INODE *inodo = &inodos->blq_inodos[directorio[i].dir_inodo];

            // Verificar si el inodo asociado es válido
            if (directorio[i].dir_inodo < 0 || directorio[i].dir_inodo >= MAX_FICHEROS) {
                continue; // Saltamos al siguiente archivo
            }

            // Información básica
            printf("%-20s %-10d %-10d ", 
                   directorio[i].dir_nfich, 
                   directorio[i].dir_inodo, 
                   inodo->size_fichero);

            // Variable para contar los bloques ocupados
            int bloques_ocupados = 0;

            // Iterar sobre los bloques del inodo
            for (int j = 0; j < MAX_NUMS_BLOQUE_INODO; j++) {
                if (inodo->i_nbloque[j] != NULL_BLOQUE) {
                    printf("%d ", inodo->i_nbloque[j]);
                    bloques_ocupados++;
                } else {
                    break; // Detener si se encuentra un bloque vacío
                }
            }

            printf("\n");
        }
    }

    // Si no se encontraron archivos en el directorio
    if (!archivos_encontrados) {
        printf("No hay archivos en el directorio.\n");
    }
}

// Función para buscar un archivo en el directorio
int buscaFich(EXT_ENTRADA_DIR *directorio, EXT_BLQ_INODOS *inodos, char *nombre) {
    if (nombre == NULL || strlen(nombre) == 0) {
        printf("ERROR: Nombre de archivo inválido.\n");
        return -1; // Nombre inválido
    }

    for (int i = 0; i < MAX_FICHEROS; i++) {
        // Aseguramos que estamos buscando un archivo con un nombre no vacío
        if (strcmp(directorio[i].dir_nfich, nombre) == 0) {
            return i; // Devuelve el índice de la entrada encontrada
        }
    }
    return -1; // Archivo no encontrado
}
