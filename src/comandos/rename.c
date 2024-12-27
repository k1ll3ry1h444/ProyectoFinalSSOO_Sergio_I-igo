//Sergio

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "cabeceras.h"

int renombrar(EXT_ENTRADA_DIR *directorio, EXT_BLQ_INODOS *inodos, char *nombreantiguo, char *nombrenuevo){
    //Busca inodo del archivo
    int inodo = -1;
    for(int i = 0; i < MAX_FICHEROS; i++){
        if(strcmp(directorio[i].dir_nfich, nombreantiguo) == 0){
            inodo = directorio[i].dir_inodo;
            break;
        }
    }
    if(inodo == -1){
        fprintf(stderr, "error: fichero no encontrado\n");
        return -1;
    }

    //Cambia el nombre del archivo
    for(int i = 0; i < MAX_FICHEROS; i++){
        if(strcmp(directorio[i].dir_nfich, nombrenuevo) == 0){
            fprintf(stderr, "error: nombre de archivo ya en uso\n");
            return -1;
        }
    }
    for(int i = 0; i < MAX_FICHEROS; i++){
        if(strcmp(directorio[i].dir_nfich, nombreantiguo) == 0){
            strcpy(directorio[i].dir_nfich, nombrenuevo);
            break;
        }
    }

    return 0;
}
