//Sergio

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "cabeceras.h"

int copiar(EXT_ENTRADA_DIR *directorio, EXT_BLQ_INODOS *inodos, EXT_BYTE_MAPS *ext_bytemaps, EXT_SIMPLE_SUPERBLOCK *ext_superblock, EXT_DATOS *memdatos, char *nombreorigen, char *nombredestino, FILE *fich){
    //Busca inodo del archivo origen
    int inodoOrigen = -1;
    for(int i = 0; i < MAX_FICHEROS; i++){
        if(strcmp(directorio[i].dir_nfich, nombreorigen) == 0){
            inodoOrigen = directorio[i].dir_inodo;
            break;
        }
    }
    if(inodoOrigen == -1){
        fprintf(stderr, "error: fichero origen no encontrado\n");
        return -1;
    }

    //Busca inodo libre
    int inodoDestino = buscar_inodo_libre(ext_bytemaps);
    if (inodoDestino == -1){
        fprintf(stderr, "error: no hay inodos libres\n");
        return -1;
    }

    //Copia la informacion del inodo
    inodos -> blq_inodos[inodoDestino].size_fichero = inodos -> blq_inodos[inodoOrigen].size_fichero;
    memcpy(inodos -> blq_inodos[inodoDestino].i_nbloque, inodos -> blq_inodos[inodoOrigen].i_nbloque, MAX_NUMS_BLOQUE_INODO * sizeof(unsigned short int));

    //Copia los bloques de datos
    for(int i = 0; i < MAX_NUMS_BLOQUE_INODO; i++){
        if(inodos -> blq_inodos[inodoOrigen].i_nbloque[i] != NULL_BLOQUE){
            int bloqueLibre = buscar_bloque_libre(ext_bytemaps);
            if(bloqueLibre == -1){
                fprintf(stderr, "error: no hay bloques libres\n");
                return -1;
            }
            marcar_bloque_ocupado(ext_bytemaps, bloqueLibre);
            inodos -> blq_inodos[inodoDestino].i_nbloque[i] = bloqueLibre;
            copiar_bloque(&memdatos[bloqueLibre], &memdatos[inodos -> blq_inodos[inodoOrigen].i_nbloque[i]]);
        }
    }

    //Crea una nueva entrada en el directorio
    for(int i = 0; i < MAX_FICHEROS; i++){
        if(directorio[i].dir_inodo == NULL_INODO){
            strcpy(directorio[i].dir_nfich, nombredestino);
            directorio[i].dir_inodo = inodoDestino;
            break;
        }
    }

    return 0;
    
}