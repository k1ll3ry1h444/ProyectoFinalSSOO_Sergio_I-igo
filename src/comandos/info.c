//Iñigo
#include <stdio.h>
#include <stdlib.h>
#include "../super_bloque.h"
#include "../cabeceras.h"

int info(int argc, char *argv[]) {
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
    leeSuperBloque(&superbloque, archivo);

    // Cerrar el archivo
    fclose(archivo);

    // Mostrar la información del superbloque
    mostrar_info_superbloque(&superbloque);

    return 0;
}
