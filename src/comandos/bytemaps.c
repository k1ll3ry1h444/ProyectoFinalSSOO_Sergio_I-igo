//Iñigo
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../cabeceras.h"

void printBytemaps(EXT_BYTE_MAPS *ext_bytemaps){
   printf("Bytemap de Inodos: ");
   for(int i = 0; i < MAX_INODOS; i++){
       printf("%d", ext_bytemaps -> bmap_inodos[i]);
   }
   printf("\nBytemap de Bloques: ");
   for(int i = 0; i < MAX_BLOQUES_PARTICION; i++){
       printf("%d", ext_bytemaps -> bmap_bloques[i]);
   }
   printf("\n");
}
