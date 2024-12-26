//Sergio
#ifndef CABECERAS_H
#define CABECERAS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Definimos tamaños y limites

#define SIZE_BLOQUE 512 //Tamaño de bloque en bytes
#define MAX_BLOQUES_PARTICION 100 //Número máximo de bloques en la partición
#define MAX_INODOS 24 //Número total de inodos
#define LEN_NFICH 16 //Longitud máxima de nombre de fichero

//----------------------------------------------
//DEFINICION DE ESTRUCTURAS PRINCIPALES
//----------------------------------------------

//Estructura del superbloque

typedef struct{
    unsigned int s_inodes_count; //Número total de inodos
    unsigned int s_blocks_count; //Número total de bloques
    unsigned int s_free_blocks_count; //Número de bloques libres
    unsigned int s_free_inodes_count; //Número de inodos libres
    unsigned int s_first_data_block; //Primer bloque de datos
    unsigned char s_relleno[SIZE_BLOQUE - 6 * sizeof(unsigned int)]; //Relleno para completar el tamaño de bloque
}EXT_SIMPLE_SUPERBLOCK;

//Estructura de los bytemaps

typedef struct{
    unsigned char bmap_bloques[MAX_BLOQUES_PARTICION]; //Mapa de bits de bloques
    unsigned char bmap_inodos[MAX_INODOS]; //Mapa de bits de inodos
    unsigned char bmap_relleno[SIZE_BLOQUE - (MAX_BLOQUES_PARTICION + MAX_INODOS) * sizeof(unsigned char)]; //Relleno para completar el tamaño de bloque
}EXT_BYTE_MAPS;

//Estructura de un inodo

typedef struct{
    unsigned char size_fichero; //Tamaño en bytes del fichero
    unsigned short int i_nbloque[7]; //Bloques usados por el fichero
}EXT_SIMPLE_INODE;

//Estructura de entrada del directorio

typedef struct {
    char dir_nfich[LEN_NFICH];       // Nombre del archivo
    unsigned short int dir_inodo;   // Número de inodo asociado
} EXT_ENTRADA_DIR;

//----------------------------------------------
//PROTOTIPOS DE FUNCIONES
//----------------------------------------------

//Comandos
void comando_info(EXT_SIMPLE_SUPERBLOCK *superbloque);
void comando_bytemaps(EXT_BYTE_MAPS *bytemaps);
void comando_dir(EXT_ENTRADA_DIR *directorio, EXT_SIMPLE_INODE *lista_inodos);
void comando_rename(EXT_ENTRADA_DIR *directorio, const char *old_name, const char *new_name);
void comando_remove(EXT_BYTE_MAPS *bytemaps, EXT_SIMPLE_INODE *lista_inodos, EXT_ENTRADA_DIR *directorio, const char *file_name);
void comando_imprimir(EXT_SIMPLE_INODE *lista_inodos, EXT_BYTE_MAPS *bytemaps, const char *file_name);
void comando_copy(EXT_BYTE_MAPS *bytemaps, EXT_SIMPLE_INODE *lista_inodos, EXT_ENTRADA_DIR *directorio, const char *src_name, const char *dest_name);
void comando_salir();

//Utils (bytemaps_utils.c)
int buscar_bloque_libre(EXT_BYTE_MAPS *bytemaps);
int buscar_inodo_libre(EXT_BYTE_MAPS *bytemaps);
void marcar_bloque(EXT_BYTE_MAPS *bytemaps, int indice, int estado);
void marcar_inodo(EXT_BYTE_MAPS *bytemaps, int indice, int estado);
void imprimir_bytemap_bloques(EXT_BYTE_MAPS *bytemaps);
void imprimir_bytemap_inodos(EXT_BYTE_MAPS *bytemaps);

//Utils (helpers.c)
int buscar_archivo_por_nombre(EXT_ENTRADA_DIR *directorio, const char *file_name);
void inicializar_inodo(EXT_SIMPLE_INODE *inodo);
void limpiar_entrada_directorio(EXT_ENTRADA_DIR *entrada);

//Utils (super_bloque.c)
void imprimir_superbloque(EXT_SIMPLE_SUPERBLOCK *superbloque);

#endif