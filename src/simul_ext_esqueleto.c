#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "cabeceras.h"

#define LONGITUD_COMANDO 100

void printBytemaps(EXT_BYTE_MAPS *ext_bytemaps);
int comprobarComando(char *strcomando, char *orden, char *argumento1, char *argumento2);
void leeSuperBloque(EXT_SIMPLE_SUPERBLOCK *psup);
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

int main(){
   char *comando[LONGITUD_COMANDO];
   char *orden[LONGITUD_COMANDO];
   char *argumento1[LONGITUD_COMANDO];
   char *argumento2[LONGITUD_COMANDO];

   int i, j;
   unsigned long int m;
   EXT_SIMPLE_SUPERBLOCK ext_superblock;
   EXT_BYTE_MAPS ext_bytemaps;
   EXT_BLQ_INODOS ext_blq_inodos;
   EXT_ENTRADA_DIR directorio[MAX_FICHEROS];
   EXT_DATOS memdatos[MAX_BLOQUES_DATOS];
   EXT_DATOS datosfich[MAX_BLOQUES_PARTICION];
   int entradadir;
   int grabardatos;
   FILE *fent;

   // Lectura del fichero completo de una sola vez
   fent = fopen("particion.bin", "r+b"); // Abre el archivo en modo lectura y escritura binaria
   if (fent == NULL){
      perror("Error al abrir el archivo"); // Si no se puede abrir el archivo, imprime un error
      return -1;
   }

   fent = fopen("particion.bin", "r+b");
   fread(&datosfich, SIZE_BLOQUE, MAX_BLOQUES_PARTICION, fent);

   memcpy(&ext_superblock, (EXT_SIMPLE_SUPERBLOCK *)&datosfich[0], SIZE_BLOQUE);
   memcpy(&directorio, (EXT_ENTRADA_DIR *)&datosfich[3], SIZE_BLOQUE);
   memcpy(&ext_bytemaps, (EXT_BLQ_INODOS *)&datosfich[1], SIZE_BLOQUE);
   memcpy(&ext_blq_inodos, (EXT_BLQ_INODOS *)&datosfich[2], SIZE_BLOQUE);
   memcpy(&memdatos, (EXT_DATOS *)&datosfich[4], MAX_BLOQUES_DATOS * SIZE_BLOQUE);

   // Bucle de tratamiento de comandos
   for (;;){
      do{
         printf(">> ");
         fflush(stdin);
         fgets(comando, LONGITUD_COMANDO, stdin);
      } while (comprobarComando(comando, orden, argumento1, argumento2) != 0);
      if (strcmp(orden, "dir") == 0){
         Directorio(&directorio, &ext_blq_inodos);
         continue;
      } else if (strcmp(orden,"rename") == 0) {
         renombrar(&directorio, &ext_blq_inodos, argumento1, argumento2);
         continue;
      } else if (strcmp(orden,"remove") == 0) {
         borrar(&directorio, &ext_blq_inodos, &ext_bytemaps, &ext_superblock, argumento1, fent);
         continue;
      } else if (strcmp(orden,"imprimir") == 0) {
         imprimir(&directorio, &ext_blq_inodos, &memdatos, argumento1);
         continue;
      } else if (strcmp(orden,"copiar") == 0) {
         copiar(&directorio, &ext_blq_inodos, &ext_bytemaps, &ext_superblock, &memdatos, argumento1, argumento2, fent);
         continue;
      } else if (strcmp(orden,"salir") == 0) {
         grabarDatos(&memdatos, fent);
         fclose(fent);
         return 0;
      } else {
         printf("ERROR: Comando ilegal [bytemaps, copy, dir, info, imprimir, rename, remove, salir]\n");
      }
      // Escritura de metadatos en comandos rename, remove, copy
      grabarInodosyDirectorio(&directorio, &ext_blq_inodos, fent);
      grabarByteMaps(&ext_bytemaps, fent);
      grabarSuperBloque(&ext_superblock, fent);
      if (grabardatos)
         grabarDatos(&memdatos, fent);
      grabardatos = 0;
      // Si el comando es salir se habrán escrito todos los metadatos
      // faltan los datos y cerrar
      if (strcmp(orden, "salir") == 0){
         grabarDatos(&memdatos, fent);
         fclose(fent);
         return 0;
      }
   }
}

//void grabarInodosyDirectorio(EXT_ENTRADA_DIR *directorio, EXT_BLQ_INODOS *inodos, FILE *fich);
//void grabarDatos(EXT_DATOS *memdatos, FILE *fich);
