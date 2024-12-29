#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "cabeceras.h"
#include "bytemaps_utils.h"
#include "super_bloque.h"
#include "helpers.h"
#include "imprimir.h"
#include "remove.h"
#include "rename.h"
#include "dir.h"
#include "copy.h"
#include "info.h"

#define LONGITUD_COMANDO 100

// Declaración de funciones
void printBytemaps(EXT_BYTE_MAPS *ext_bytemaps);
int comprobarComando(char *strcomando, char *orden, char *argumento1, char *argumento2);
void leeSuperBloque(EXT_SIMPLE_SUPERBLOCK *psup, FILE *fich);
int buscaFich(EXT_ENTRADA_DIR *directorio, EXT_BLQ_INODOS *inodos, char *nombre);
void Directorio(EXT_ENTRADA_DIR *directorio, EXT_BLQ_INODOS *inodos);
int renombrar(EXT_ENTRADA_DIR *directorio, EXT_BLQ_INODOS *inodos, char *nombreantiguo, char *nombrenuevo);
int imprimir(EXT_ENTRADA_DIR *directorio, EXT_BLQ_INODOS *inodos, EXT_DATOS *memdatos, char *nombre);
int borrar(EXT_ENTRADA_DIR *directorio, EXT_BLQ_INODOS *inodos, EXT_BYTE_MAPS *ext_bytemaps, EXT_SIMPLE_SUPERBLOCK *ext_superblock, char *nombre, FILE *fich);
int copiar(EXT_ENTRADA_DIR *directorio, EXT_BLQ_INODOS *inodos, EXT_BYTE_MAPS *ext_bytemaps, EXT_SIMPLE_SUPERBLOCK *ext_superblock, EXT_DATOS *memdatos, char *nombreorigen, char *nombredestino, FILE *fich);
void grabarInodosyDirectorio(EXT_ENTRADA_DIR *directorio, EXT_BLQ_INODOS *inodos, FILE *fich);
void grabarByteMaps(EXT_BYTE_MAPS *ext_bytemaps, FILE *fich);
void grabarSuperBloque(EXT_SIMPLE_SUPERBLOCK *ext_superblock, FILE *fich);
void grabarDatos(EXT_DATOS *memdatos, FILE *fich);

// Función que comprueba el comando
int comprobarComando(char *strcomando, char *orden, char *argumento1, char *argumento2) {
    printf("Comprobando comando...\n");
    int count = sscanf(strcomando, "%s %s %s", orden, argumento1, argumento2);
    
    if (count == 1) { // Solo el comando, sin argumentos
        argumento1[0] = '\0';
        argumento2[0] = '\0';
    }
    return (count >= 1) ? 0 : -1; // Retorna 0 si el comando es válido, de lo contrario, -1
}

// Función main
int main() {
    char comando[LONGITUD_COMANDO];
    char orden[LONGITUD_COMANDO];
    char argumento1[LONGITUD_COMANDO];
    char argumento2[LONGITUD_COMANDO];

    EXT_SIMPLE_SUPERBLOCK ext_superblock;
    EXT_BYTE_MAPS ext_bytemaps;
    EXT_BLQ_INODOS ext_blq_inodos;
    EXT_ENTRADA_DIR directorio[MAX_FICHEROS];
    EXT_DATOS memdatos[MAX_BLOQUES_DATOS];
    EXT_DATOS datosfich[MAX_BLOQUES_PARTICION];
    int grabardatos = 0; // Inicialización correcta de grabardatos
    FILE *fent;

    // Lectura del fichero completo de una sola vez
    fent = fopen("particion.bin", "r+b"); // Abre el archivo en modo lectura y escritura binaria
    if (fent == NULL) {
        perror("Error al abrir el archivo"); // Si no se puede abrir el archivo, imprime un error
        return -1;
    }

    // Leer la partición en un solo paso
    if (fread(&datosfich, SIZE_BLOQUE, MAX_BLOQUES_PARTICION, fent) != MAX_BLOQUES_PARTICION) {
        perror("Error al leer el archivo de partición");
        fclose(fent);
        return -1;
    }

    memcpy(&ext_superblock, (EXT_SIMPLE_SUPERBLOCK *)&datosfich[0], SIZE_BLOQUE);
    memcpy(&directorio[0], (EXT_ENTRADA_DIR *)&datosfich[3], SIZE_BLOQUE);
    memcpy(&ext_bytemaps, (EXT_BLQ_INODOS *)&datosfich[1], SIZE_BLOQUE);
    memcpy(&ext_blq_inodos, (EXT_BLQ_INODOS *)&datosfich[2], SIZE_BLOQUE);
    memcpy(&memdatos[0], (EXT_DATOS *)&datosfich[4], MAX_BLOQUES_DATOS * SIZE_BLOQUE);

    // Bucle de tratamiento de comandos
    for (;;) {
        // Solicitar comando del usuario
        printf("Introduce un comando: [bytemaps, copy, dir, info, imprimir, rename, remove, salir]\n");
        printf(">> ");
        fgets(comando, LONGITUD_COMANDO, stdin);

        // Eliminar el salto de línea si está presente
        size_t len = strlen(comando);
        if (len > 0 && comando[len - 1] == '\n') {
            comando[len - 1] = '\0';
        }

        // Comprobar el comando y sus argumentos
        if (comprobarComando(comando, orden, argumento1, argumento2) == 0) {
            printf("Comando: %s.\n", orden);
            
            // Manejo de los comandos
            if (strcmp(orden, "dir") == 0) {
                Directorio(&directorio[0], &ext_blq_inodos);
            } else if (strcmp(orden, "bytemaps") == 0) {
                printBytemaps(&ext_bytemaps);
            } else if (strcmp(orden, "copy") == 0) {
                // Mostrar los archivos disponibles
                printf("Lista de archivos disponibles para copiar:\n");
                for (int i = 0; i < MAX_FICHEROS; i++) {
                    if (directorio[i].dir_inodo != NULL_INODO) {
                        printf("%d. %s\n", i + 1, directorio[i].dir_nfich);  // Mostrar nombre del archivo
                    }
                }

                // Elegir archivo origen
                printf("Introduce el número del archivo de origen: ");
                int origen;
                scanf("%d", &origen);
                while(getchar() != '\n');  // Limpiar el buffer del teclado

                if (origen < 1 || origen > MAX_FICHEROS || directorio[origen - 1].dir_inodo == NULL_INODO) {
                    printf("Archivo de origen no válido.\n");
                    return 1;
                }

                // Elegir archivo destino
                printf("Introduce el número del archivo de destino: ");
                int destino;
                scanf("%d", &destino);
                while(getchar() != '\n');  // Limpiar el buffer del teclado

                if (destino < 1 || destino > MAX_FICHEROS || directorio[destino - 1].dir_nfich[0] != '\0') {
                    printf("Archivo de destino no válido. Asegúrate de que el destino está libre.\n");
                    return 1;
                }

                // Copiar archivo
                strcpy(argumento1, directorio[origen - 1].dir_nfich);
                strcpy(argumento2, directorio[destino - 1].dir_nfich);
                copiar(&directorio[0], &ext_blq_inodos, &ext_bytemaps, &ext_superblock, &memdatos[0], argumento1, argumento2, fent);

            } else if (strcmp(orden, "info") == 0) {
                info(&ext_superblock);
            } else if (strcmp(orden, "rename") == 0) {
                // Mostrar los archivos disponibles
                printf("Lista de archivos disponibles para renombrar:\n");
                for (int i = 0; i < MAX_FICHEROS; i++) {
                    if (directorio[i].dir_inodo != NULL_INODO) {
                        printf("%d. %s\n", i + 1, directorio[i].dir_nfich);  // Mostrar nombre del archivo
                    }
                }

                // Elegir archivo a renombrar
                printf("Introduce el número del archivo a renombrar: ");
                int archivo_renombrar;
                scanf("%d", &archivo_renombrar);
                while(getchar() != '\n');  // Limpiar el buffer del teclado

                if (archivo_renombrar < 1 || archivo_renombrar > MAX_FICHEROS || directorio[archivo_renombrar - 1].dir_inodo == NULL_INODO) {
                    printf("Archivo no válido.\n");
                    return 1;
                }

                // Introducir nuevo nombre
                printf("Introduce el nuevo nombre del archivo: ");
                scanf("%s", argumento2);

                // Renombrar archivo
                strcpy(argumento1, directorio[archivo_renombrar - 1].dir_nfich);
                renombrar(&directorio[0], &ext_blq_inodos, argumento1, argumento2);

            } else if (strcmp(orden, "remove") == 0) {
                // Mostrar los archivos disponibles
                printf("Lista de archivos disponibles para eliminar:\n");
                for (int i = 0; i < MAX_FICHEROS; i++) {
                    if (directorio[i].dir_inodo != NULL_INODO) {
                        printf("%d. %s\n", i + 1, directorio[i].dir_nfich);  // Mostrar nombre del archivo
                    }
                }

                // Elegir archivo a eliminar
                printf("Introduce el número del archivo a eliminar: ");
                int archivo_eliminar;
                scanf("%d", &archivo_eliminar);
                while(getchar() != '\n');  // Limpiar el buffer del teclado

                if (archivo_eliminar < 1 || archivo_eliminar > MAX_FICHEROS || directorio[archivo_eliminar - 1].dir_inodo == NULL_INODO) {
                    printf("Archivo no válido.\n");
                    return 1;
                }

                // Eliminar archivo
                strcpy(argumento1, directorio[archivo_eliminar - 1].dir_nfich);
                borrar(&directorio[0], &ext_blq_inodos, &ext_bytemaps, &ext_superblock, argumento1, fent);
            } else if (strcmp(orden, "imprimir") == 0) {
                // Mostrar los archivos disponibles
                printf("Lista de archivos disponibles para imprimir:\n");
                for (int i = 0; i < MAX_FICHEROS; i++) {
                    if (directorio[i].dir_inodo != NULL_INODO) {
                        printf("%d. %s\n", i + 1, directorio[i].dir_nfich);  // Mostrar nombre del archivo
                    }
                }

                // Elegir archivo a imprimir
                printf("Introduce el número del archivo a imprimir: ");
                int archivo_imprimir;
                scanf("%d", &archivo_imprimir);
                while(getchar() != '\n');  // Limpiar el buffer del teclado

                if (archivo_imprimir < 1 || archivo_imprimir > MAX_FICHEROS || directorio[archivo_imprimir - 1].dir_inodo == NULL_INODO) {
                    printf("Archivo no válido.\n");
                    return 1;
                }

                // Imprimir archivo
                strcpy(argumento1, directorio[archivo_imprimir - 1].dir_nfich);
                imprimir(&directorio[0], &ext_blq_inodos, &memdatos[0], argumento1);

            } else if (strcmp(orden, "salir") == 0) {
                printf("Saliendo...\n");
                grabarDatos(&memdatos[0], fent);
                fclose(fent);
                return 0;  // Salir del programa
            } else {
                printf("ERROR: Comando ilegal [bytemaps, copy, dir, info, imprimir, rename, remove, salir]\n");
            }


            // Si el comando ejecutado requiere grabar datos
            if (grabardatos) {
                grabarDatos(&memdatos[0], fent);
            }
            grabardatos = 0;
        }
        else {
            // Si el comando no es válido
            printf("ERROR: Comando ilegal [bytemaps, copy, dir, info, imprimir, rename, remove, salir]\n");
        }
    }

    }
