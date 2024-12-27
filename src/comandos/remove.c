//Sergio

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "cabeceras.h"

int borrar(EXT_ENTRADA_DIR *directorio, EXT_BLQ_INODOS *inodos, EXT_BYTE_MAPS *ext_bytemaps, EXT_SIMPLE_SUPERBLOCK *ext_superblock, char *nombre, FILE *fich){
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

    //Marca los bloques de datos como libres
    for(int i = 0; i < MAX_NUMS_BLOQUE_INODO; i++){
        if(inodos -> blq_inodos[inodo].i_nbloque[i] != NULL_BLOQUE){
            marcar_bloque_libre(ext_bytemaps, inodos -> blq_inodos[inodo].i_nbloque[i]);
        }
    }

    //Marca el inodo como libre
    marcar_inodo_libre(ext_bytemaps, inodo);

    //Elimina la entrada del directorio
    for(int i = 0; i < MAX_FICHEROS; i++){
        if(strcmp(directorio[i].dir_nfich, nombre) == 0){
            strcpy(directorio[i].dir_nfich, "");
            directorio[i].dir_inodo = NULL_INODO;
            break;
        }
    }

    //Actualiza el superbloque
    ext_superblock -> s_free_blocks_count += MAX_NUMS_BLOQUE_INODO;
    ext_superblock -> s_free_inodes_count++;

    //Guarda los cambios
    grabarInodosyDirectorio(directorio, inodos, fich);
    grabarByteMaps(ext_bytemaps, fich);
    grabarSuperBloque(ext_superblock, fich);

    return 0;
}