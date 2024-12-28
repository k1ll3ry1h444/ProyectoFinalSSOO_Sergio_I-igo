//Sergio
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "../helpers.h"
#include "../cabeceras.h"
#include "../bytemaps_utils.h"

void copiar(EXT_ENTRADA_DIR *directorio, EXT_BLQ_INODOS *inodos, EXT_BYTE_MAPS *ext_bytemaps, EXT_SIMPLE_SUPERBLOCK *ext_superblock, EXT_DATOS *memdatos, char *nombreorigen, char *nombredestino, FILE *fich) {
    // Busca inodo del archivo origen
    int inodoOrigen = -1;
    for (int i = 0; i < MAX_FICHEROS; i++) {
        if (strcmp(directorio[i].dir_nfich, nombreorigen) == 0) {
            inodoOrigen = directorio[i].dir_inodo;
            break;
        }
    }

    if (inodoOrigen == -1) {
        fprintf(stderr, "error: fichero origen no encontrado\n");
        return;
    }

    // Verificar si el destino es válido antes de realizar la copia
    int inodoDestino = -1;
    for (int i = 0; i < MAX_FICHEROS; i++) {
        if (directorio[i].dir_inodo == NULL_INODO) { // Encontramos un espacio libre
            inodoDestino = i; // Asignamos el índice del espacio libre al destino
            break;
        }
    }

    if (inodoDestino == -1) {
        fprintf(stderr, "error: no hay espacio disponible para el archivo de destino\n");
        return;
    }

    // Verifica que el número de archivo de destino es válido, es decir, mayor o igual que el primero no vacío
    int destino_valido = 0;
    for (int i = 0; i < MAX_FICHEROS; i++) {
        if (directorio[i].dir_inodo == inodoDestino && directorio[i].dir_nfich[0] == '\0') {
            destino_valido = 1;  // Si hay espacio vacío, el destino es válido
            break;
        }
    }

    if (!destino_valido) {
        fprintf(stderr, "error: archivo de destino no válido\n");
        return;
    }

    // Encuentra el inodo de destino libre
    int inodoDestinoLibre = buscar_inodo_libre(ext_bytemaps);
    if (inodoDestinoLibre == -1) {
        fprintf(stderr, "error: no hay inodos libres\n");
        return;
    }

    // Copia la información del inodo
    inodos->blq_inodos[inodoDestinoLibre].size_fichero = inodos->blq_inodos[inodoOrigen].size_fichero;
    memcpy(inodos->blq_inodos[inodoDestinoLibre].i_nbloque, inodos->blq_inodos[inodoOrigen].i_nbloque, MAX_NUMS_BLOQUE_INODO * sizeof(unsigned short int));

    // Copia los bloques de datos
    for (int i = 0; i < MAX_NUMS_BLOQUE_INODO; i++) {
        if (inodos->blq_inodos[inodoOrigen].i_nbloque[i] != NULL_BLOQUE) {
            int bloqueLibre = buscar_bloque_libre(ext_bytemaps);
            if (bloqueLibre == -1) {
                fprintf(stderr, "error: no hay bloques libres\n");
                return;
            }
            marcar_bloque_ocupado(ext_bytemaps, bloqueLibre);
            inodos->blq_inodos[inodoDestinoLibre].i_nbloque[i] = bloqueLibre;
            copiar_bloque(&memdatos[bloqueLibre], &memdatos[inodos->blq_inodos[inodoOrigen].i_nbloque[i]]);
        }
    }

    // Crea una nueva entrada en el directorio para el archivo destino
    strcpy(directorio[inodoDestino].dir_nfich, nombredestino);
    directorio[inodoDestino].dir_inodo = inodoDestinoLibre;

    printf("Copia realizada con éxito: %s a %s\n", nombreorigen, nombredestino);
}

