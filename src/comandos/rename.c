// Sergio
#include <stdio.h>
#include <string.h>
#include "../cabeceras.h"

// Función para renombrar un archivo en el directorio
int renombrar(EXT_ENTRADA_DIR *directorio, EXT_BLQ_INODOS *inodos, char *nombre_actual, char *nuevo_nombre) {
    // Verificar si el nuevo nombre no está vacío
    if (nuevo_nombre == NULL || strlen(nuevo_nombre) == 0) {
        fprintf(stderr, "error: nuevo nombre de archivo no válido\n");
        return -1;
    }

    // Buscar el archivo en el directorio
    int indice = -1;
    for (int i = 0; i < MAX_FICHEROS; i++) {
        if (strcmp(directorio[i].dir_nfich, nombre_actual) == 0) {
            indice = i;
            break;
        }
    }

    // Verificar si el archivo actual existe en el directorio
    if (indice == -1) {
        fprintf(stderr, "error: archivo no encontrado\n");
        return -1;
    }

    // Verificar si ya existe un archivo con el nuevo nombre
    for (int i = 0; i < MAX_FICHEROS; i++) {
        if (strcmp(directorio[i].dir_nfich, nuevo_nombre) == 0) {
            fprintf(stderr, "error: ya existe un archivo con el nombre %s\n", nuevo_nombre);
            return -1;
        }
    }

    // Realizar el cambio de nombre en el directorio
    strcpy(directorio[indice].dir_nfich, nuevo_nombre);
    return 0; // El archivo se ha renombrado exitosamente
}
