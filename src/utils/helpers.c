//Sergio

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../cabeceras.h"



int validar_ruta(const char *ruta){
    FILE *archivo = fopen(ruta, "rb");
    if(archivo == NULL){
        return 0;
    }
    fclose(archivo);
    return 1;
}

void copiar_bloque(EXT_DATOS *destino, EXT_DATOS *origen){
    memcpy(destino -> dato, origen -> dato, SIZE_BLOQUE);
}

void lanzar_error(const char *mensaje){
    fprintf(stderr, "error: %s\n", mensaje);
    exit(EXIT_FAILURE);
}

// Función que guarda un directorio y sus inodos en un archivo binario
void grabarInodosyDirectorio(EXT_ENTRADA_DIR *directorio, EXT_BLQ_INODOS *inodos, FILE *fich) {
    if (directorio == NULL || inodos == NULL || fich == NULL) {
        printf("Error: Puntero nulo en grabarInodosyDirectorio.\n");
        return;
    }

    // Guarda las entradas del directorio
    size_t bytes_escritos = fwrite(directorio, sizeof(EXT_ENTRADA_DIR), 1, fich);
    if (bytes_escritos != 1) {
        printf("Error al escribir las entradas del directorio en el archivo.\n");
    }

    // Guarda los inodos
    bytes_escritos = fwrite(inodos, sizeof(EXT_BLQ_INODOS), 1, fich);
    if (bytes_escritos != 1) {
        printf("Error al escribir los inodos en el archivo.\n");
    }
}

// Función que guarda los byte maps (mapas de bits) en un archivo binario
void grabarByteMaps(EXT_BYTE_MAPS *ext_bytemaps, FILE *fich) {
    if (ext_bytemaps == NULL || fich == NULL) {
        printf("Error: Puntero nulo en grabarByteMaps.\n");
        return;
    }

    // Guarda los mapas de bits
    size_t bytes_escritos = fwrite(ext_bytemaps, sizeof(EXT_BYTE_MAPS), 1, fich);
    if (bytes_escritos != 1) {
        printf("Error al escribir los byte maps en el archivo.\n");
    }
}
// Función que guarda datos en un archivo binario
void grabarDatos(EXT_DATOS *memdatos, FILE *fich) {
    if (memdatos == NULL || fich == NULL) {
        printf("Error: Puntero nulo en grabarDatos.\n");
        return;
    }

    // Guarda los datos
    size_t bytes_escritos = fwrite(memdatos, sizeof(EXT_DATOS), 1, fich);
    if (bytes_escritos != 1) {
        printf("Error al escribir los datos en el archivo.\n");
    }
}
