//Iñigo
#include <stdio.h>
#include <stdlib.h>
#include "../cabeceras.h"

void salir(int codigo) {
    printf("\nLiberando recursos...\n");
    printf("Cerrando el programa...\n");

    // Mensaje según el código de salida
    if (codigo == 0) {
        printf("El programa terminó exitosamente.\n");
    } else {
        printf("El programa terminó con errores. Código de salida: %d\n", codigo);
    }

    // Salir del programa
    exit(codigo);
}
