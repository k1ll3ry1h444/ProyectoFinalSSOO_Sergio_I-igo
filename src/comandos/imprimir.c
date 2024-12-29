//Sergio
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "../cabeceras.h"

int imprimir(EXT_ENTRADA_DIR *directorio, EXT_BLQ_INODOS *inodos, EXT_DATOS *memdatos, char *nombre) {
    printf("Imprimiendo %s...\n", nombre);

    // Busca el inodo del archivo
    int inodo = -1;
    for (int i = 0; i < MAX_FICHEROS; i++) {
        if (strcmp(directorio[i].dir_nfich, nombre) == 0) {
            inodo = directorio[i].dir_inodo;
            break;
        }
    }
    if (inodo == -1) {
        fprintf(stderr, "error: fichero no encontrado\n");
        return -1;
    }

    // Buffer donde se concatenarán los bloques
    char buffer_total[SIZE_TOTAL_ARCHIVO] = {0};  // Define un tamaño apropiado para el archivo
    int offset = 0;  // Puntero para agregar los datos al buffer

    // Concatenamos los bloques de datos en un único string
    for (int i = 0; i < MAX_NUMS_BLOQUE_INODO; i++) {
        int bloque = inodos->blq_inodos[inodo].i_nbloque[i];
        
        // Verifica si el bloque está asignado
        if (bloque != NULL_BLOQUE) {
            // Asegúrate de que no excedas el límite de tamaño del archivo
            int data_len = strlen((char *)memdatos[bloque].dato);
            if (offset + data_len < SIZE_TOTAL_ARCHIVO) {
                memcpy(buffer_total + offset, memdatos[bloque].dato, data_len);
                offset += data_len;  // Actualiza el puntero para el siguiente bloque
            } else {
                // Si el buffer es demasiado pequeño, cortamos
                printf("Advertencia: el archivo es demasiado grande para imprimir completamente.\n");
                break;
            }
        }
    }

    // Imprime el contenido completo del archivo
    printf("Contenido del archivo %s:\n", nombre);
    printf("%s\n", buffer_total);  // Imprime el contenido concatenado

    return 0;
}



