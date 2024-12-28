//Iñigo
#include <stdio.h>
#include <stdlib.h>
#include "../super_bloque.h"
#include "../cabeceras.h"

// Función para mostrar la información del superbloque
void info(EXT_SIMPLE_SUPERBLOCK *superbloque) {
    printf("Información del Superbloque:\n");
    printf("Número de inodos en la partición: %u\n", superbloque->s_inodes_count);
    printf("Número de bloques en la partición: %u\n", superbloque->s_blocks_count);
    printf("Número de bloques libres: %u\n", superbloque->s_free_blocks_count);
    printf("Número de inodos libres: %u\n", superbloque->s_free_inodes_count);
    printf("Primer bloque de datos: %u\n", superbloque->s_first_data_block);
    printf("Tamaño del bloque: %u bytes\n", superbloque->s_block_size);
}

// Función principal para leer y procesar la información del archivo del superbloque
int info_func(int argc, char *argv[]) {
    // Verificar si se pasó el nombre del archivo como argumento
    if (argc != 2) {
        printf("Uso: %s <archivo_superbloque>\n", argv[0]);
        return 1;
    }

    // Abrir el archivo binario proporcionado
    FILE *archivo = fopen(argv[1], "rb");
    if (archivo == NULL) {
        perror("Error al abrir el archivo");
        return 1;
    }

    // Leer el superbloque desde el archivo
    EXT_SIMPLE_SUPERBLOCK superbloque;
    leeSuperBloque(&superbloque, archivo);  // Asegúrate de que esta función carga correctamente los datos

    // Cerrar el archivo
    fclose(archivo);

    // Ahora llamar a info() para mostrar la información del superbloque
    info(&superbloque);

    return 0;
}
