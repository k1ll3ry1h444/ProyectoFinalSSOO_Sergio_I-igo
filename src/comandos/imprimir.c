//Sergio

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "../cabeceras.h"


int imprimir(EXT_ENTRADA_DIR *directorio, EXT_BLQ_INODOS *inodos, EXT_DATOS *memdatos, char *nombre){
    //Busca inodo del archivo
    int inodo = -1;
    for(int i = 0; i < MAX_FICHEROS; i++){
        if(strcmp(directorio[i].dir_nfich, nombre) == 0){
            inodo = directorio[i].dir_inodo;
            break;
        }
    }
    if(inodo == -1){
        fprintf(stderr, "error: fichero no encontrado\n");
        return -1;
    }

    //Recorre los bloques de datos y lo imprime
    for(int i = 0; i < MAX_NUMS_BLOQUE_INODO; i++){
        if(inodos -> blq_inodos[inodo].i_nbloque[i] != NULL_BLOQUE){
            printf("%s", memdatos[inodos -> blq_inodos[inodo].i_nbloque[i]].dato);
        }
    }

    return 0;
}
