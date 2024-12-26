//Sergio

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cabeceras.h"

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

void print_bytemaps(EXT_BYTE_MAPS *ext_bytemaps){
    printf("Bytemap de Inodos: ");
    for(int i = 0; i < MAX_INODOS; i++){
        printf("%d", ext_bytemaps -> bmap_inodos[i]);
    }
    printf("\nBytemap de Bloques: ");
    for(int i = 0; i < MAX_BLOQUES_PARTICION; i++){
        printf("%d", ext_bytemaps -> bmap_bloques[i]);
    }
    printf("\n");
}