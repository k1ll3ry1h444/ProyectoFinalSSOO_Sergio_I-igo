//Sergio

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cabeceras.h"

void marcar_bloque_ocupado(EXT_BYTE_MAPS *ext_bytemaps, unsigned int bloque){
    if(bloque < MAX_BLOQUES_PARTICION){
        ext_bytemaps -> bmap_bloques[bloque] = 1;
    }else{
        fprintf(stderr, "error: bloque fuera de rango\n");
        exit(EXIT_FAILURE);
    }
}

void marcar_bloque_libre(EXT_BYTE_MAPS *ext_bytemaps, unsigned int bloque){
    if(bloque < MAX_BLOQUES_PARTICION){
        ext_bytemaps -> bmap_bloques[bloque] = 0;
    }else{
        fprintf(stderr, "error: bloque fuera de rango\n");
        exit(EXIT_FAILURE);
    }
}

int buscar_bloque_libre(EXT_BYTE_MAPS *ext_bytemaps){
    for(int i = 0; i < MAX_BLOQUES_PARTICION; i++){
        if(ext_bytemaps -> bmap_bloques[i] == 0){
            return i;
        }
    }
    return -1;
}

void marcar_inodo_ocupado(EXT_BYTE_MAPS *ext_bytemaps, unsigned int inodo){
    if(inodo < MAX_INODOS){
        ext_bytemaps -> bmap_inodos[inodo] = 1;
    }else{
        fprintf(stderr, "error: inodo fuera de rango\n");
        exit(EXIT_FAILURE);
    }
}

void marcar_inodo_libre(EXT_BYTE_MAPS *ext_bytemaps, unsigned int inodo){
    if(inodo < MAX_INODOS){
        ext_bytemaps -> bmap_inodos[inodo] = 0;
    }else{
        fprintf(stderr, "error: inodo fuera de rango\n");
        exit(EXIT_FAILURE);
    }
}

int buscar_inodo_libre(EXT_BYTE_MAPS *ext_bytemaps){
    for(int i = 0; i < MAX_INODOS; i++){
        if(ext_bytemaps -> bmap_inodos[i] == 0){
            return i;
        }
    }
    return -1;
}

