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
        // Solicitando al usuario que ingrese un comando
        do {
            printf(">> ");
            while (getchar() != '\n');  // Limpiar el buffer de entrada
            fgets(comando, LONGITUD_COMANDO, stdin);
        } while (comprobarComando(comando, orden, argumento1, argumento2) != 0);
        
        // Manejo de los diferentes comandos
        if (strcmp(orden, "dir") == 0) {
            Directorio(&directorio[0], &ext_blq_inodos);
        } 
        else if (strcmp(orden, "rename") == 0) {
            renombrar(&directorio[0], &ext_blq_inodos, argumento1, argumento2);
        } 
        else if (strcmp(orden, "remove") == 0) {
            borrar(&directorio[0], &ext_blq_inodos, &ext_bytemaps, &ext_superblock, argumento1, fent);
        } 
        else if (strcmp(orden, "imprimir") == 0) {
            imprimir(&directorio[0], &ext_blq_inodos, &memdatos[0], argumento1);
        } 
        else if (strcmp(orden, "copiar") == 0) {
            copiar(&directorio[0], &ext_blq_inodos, &ext_bytemaps, &ext_superblock, &memdatos[0], argumento1, argumento2, fent);
        } 
        else if (strcmp(orden, "salir") == 0) {
            grabarDatos(&memdatos[0], fent);
            fclose(fent);
            return 0;
        } 
        else {
            printf("ERROR: Comando ilegal [bytemaps, copy, dir, info, imprimir, rename, remove, salir]\n");
        }
        
        if (grabardatos) {
            grabarDatos(&memdatos[0], fent);
        }
        grabardatos = 0;

        // Si el comando es salir, se habrán escrito todos los metadatos
        // faltan los datos y cerrar
        if (strcmp(orden, "salir") == 0) {
            grabarDatos(&memdatos[0], fent);
            fclose(fent);
            return 0;
        }
    }
}
