//Iñigo
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cabeceras.h"

void printBytemaps(EXT_BYTE_MAPS *ext_bytemaps) {
    if (ext_bytemaps == NULL) {
        printf("Error: El puntero a los mapas de bytes es nulo.\n");
        return;
    }

    // Imprimir el estado de los bloques
    printf("Estado de los bloques (primeros %d bloques):\n", MAX_BLOQUES_PARTICION);
    for (int i = 0; i < MAX_BLOQUES_PARTICION; i++) {
        printf("Bloque %d: %s\n", i, ext_bytemaps->bmap_bloques[i] ? "Ocupado" : "Libre");
    }

    // Imprimir el estado de los inodos
    printf("\nEstado de los inodos:\n");
    for (int i = 0; i < MAX_INODOS; i++) {
        printf("Inodo %d: %s\n", i, ext_bytemaps->bmap_inodos[i] ? "Ocupado" : "Libre");
    }
}




