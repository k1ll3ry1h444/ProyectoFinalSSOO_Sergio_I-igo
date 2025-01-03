// Sergio
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "../bytemaps_utils.h"
#include "../super_bloque.h"
#include "../helpers.h"
#include "../cabeceras.h"

int borrar(EXT_ENTRADA_DIR *directorio, EXT_BLQ_INODOS *inodos, EXT_BYTE_MAPS *ext_bytemaps, EXT_SIMPLE_SUPERBLOCK *ext_superblock, char *nombre, FILE *fich) {
    // Busca el inodo del archivo a eliminar
    int inodo = -1;
    for (int i = 0; i < MAX_FICHEROS; i++) {
        if (strcmp(directorio[i].dir_nfich, nombre) == 0) {
            inodo = directorio[i].dir_inodo;
            break; // Detenemos la búsqueda al encontrar el archivo
        }
    }

    if (inodo == -1) {
        fprintf(stderr, "error: fichero no encontrado\n");
        return -1;
    }

    // Marca los bloques de datos como libres
    for (int i = 0; i < MAX_NUMS_BLOQUE_INODO; i++) {
        if (inodos->blq_inodos[inodo].i_nbloque[i] != NULL_BLOQUE) {
            marcar_bloque_libre(ext_bytemaps, inodos->blq_inodos[inodo].i_nbloque[i]);
            inodos->blq_inodos[inodo].i_nbloque[i] = NULL_BLOQUE; // Limpia la referencia al bloque
        }
    }

    // Marca el inodo como libre
    marcar_inodo_libre(ext_bytemaps, inodo);

    // Elimina la entrada del directorio
    for (int i = 0; i < MAX_FICHEROS; i++) {
        if (directorio[i].dir_inodo == inodo) {
            directorio[i].dir_inodo = NULL_INODO;
            memset(directorio[i].dir_nfich, 0, sizeof(directorio[i].dir_nfich)); // Limpia el nombre del archivo
            break; // Detenemos la iteración tras eliminar la entrada
        }
    }

    printf("Archivo eliminado: %s\n", nombre);
    return 0;
}