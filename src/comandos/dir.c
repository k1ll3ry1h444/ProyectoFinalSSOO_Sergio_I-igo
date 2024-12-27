//Iñigo
#include <stdio.h>
#include <string.h>

void Directorio(EXT_ENTRADA_DIR *directorio, EXT_BLQ_INODOS *inodos) {
    printf("Archivos en el directorio:\n");
    printf("%-20s %-10s %-10s %-15s\n", "Nombre", "Inodo", "Tamaño", "Bloques Ocupados");
    printf("---------------------------------------------------------------\n");

    for (int i = 0; i < MAX_ENTRADAS_DIR; i++) {
        if (directorio[i].nombre[0] != '\0') { // Verifica si hay una entrada válida
            EXT_INODO *inodo = &inodos->inodos[directorio[i].inodo];

            printf("%-20s %-10d %-10d ", directorio[i].nombre, directorio[i].inodo, inodo->tamanyo_fichero);
            
            // Imprimir bloques ocupados
            for (int j = 0; j < MAX_BLOQUES_POR_INODO; j++) {
                if (inodo->bloques[j] != 0) {
                    printf("%d ", inodo->bloques[j]);
                }
            }
            printf("\n");
        }
    }
}


int buscaFich(EXT_ENTRADA_DIR *directorio, EXT_BLQ_INODOS *inodos, char *nombre) {
    for (int i = 0; i < MAX_ENTRADAS_DIR; i++) {
        if (strcmp(directorio[i].nombre, nombre) == 0) {
            return i; // Devuelve el índice de la entrada encontrada
        }
    }
    return -1; // Archivo no encontrado
}

