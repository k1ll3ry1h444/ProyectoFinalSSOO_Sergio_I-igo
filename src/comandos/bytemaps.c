//Iñigo
#include <stdio.h>

void printBytemaps(EXT_BYTE_MAPS *ext_bytemaps) {
    if (ext_bytemaps == NULL) {
        printf("Error: El puntero a los mapas de bytes es nulo.\n");
        return;
    }

    // Imprimir el estado de los bloques
    printf("Estado de los bloques (primeros %d bloques):\n", MAX_BLOCKS);
    for (int i = 0; i < MAX_BLOCKS; i++) {
        printf("Bloque %d: %s\n", i, ext_bytemaps->block_map[i] ? "Ocupado" : "Libre");
    }

    // Imprimir el estado de los inodos
    printf("\nEstado de los inodos:\n");
    for (int i = 0; i < 256; i++) { // Supongamos que hay 256 inodos
        printf("Inodo %d: %s\n", i, ext_bytemaps->inode_map[i] ? "Ocupado" : "Libre");
    }
}



