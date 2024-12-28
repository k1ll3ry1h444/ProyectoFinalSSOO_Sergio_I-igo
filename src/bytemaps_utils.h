// bytemaps_utils.h

#include "cabeceras.h"

#ifndef BYTEMAPS_UTILS_H
#define BYTEMAPS_UTILS_H

void marcar_bloque_ocupado(EXT_BYTE_MAPS *ext_bytemaps, unsigned int bloque);
void marcar_bloque_libre(EXT_BYTE_MAPS *ext_bytemaps, unsigned int bloque);
int buscar_bloque_libre(EXT_BYTE_MAPS *ext_bytemaps);
void marcar_inodo_ocupado(EXT_BYTE_MAPS *ext_bytemaps, unsigned int inodo);
void marcar_inodo_libre(EXT_BYTE_MAPS *ext_bytemaps, unsigned int inodo);
int buscar_inodo_libre(EXT_BYTE_MAPS *ext_bytemaps);

#endif // BYTEMAPS_UTILS_H