//Iñigo
#include <stdio.h>
#include <stdint.h>

// Estructura del superbloque
typedef struct {
    uint32_t s_block_count;       // Número total de bloques
    uint32_t s_inode_count;       // Número total de inodos
    uint32_t s_first_data_block;  // Índice del primer bloque de datos
} EXT_SIMPLE_SUPERBLOCK;

// Función que guarda un superbloque en un archivo binario
void grabarSuperBloque(EXT_SIMPLE_SUPERBLOCK *ext_superblock, FILE *fich) {
    if (ext_superblock == NULL || fich == NULL) {
        printf("Error: Puntero nulo en grabarSuperBloque.\n");
        return;
    }

    // Escribe el superbloque en el archivo
    size_t bytes_escritos = fwrite(ext_superblock, sizeof(EXT_SIMPLE_SUPERBLOCK), 1, fich);
    if (bytes_escritos != 1) {
        printf("Error al escribir el superbloque en el archivo.\n");
    } else {
        printf("Superbloque guardado exitosamente.\n");
    }
}

// Función que lee un superbloque desde un archivo binario
void leeSuperBloque(EXT_SIMPLE_SUPERBLOCK *psup, FILE *fich) {
    if (psup == NULL || fich == NULL) {
        printf("Error: Puntero nulo en leeSuperBloque.\n");
        return;
    }

    // Lee el superbloque del archivo
    size_t bytes_leidos = fread(psup, sizeof(EXT_SIMPLE_SUPERBLOCK), 1, fich);
    if (bytes_leidos != 1) {
        printf("Error al leer el superbloque del archivo.\n");
    } else {
        printf("Superbloque leído exitosamente.\n");
    }
}

