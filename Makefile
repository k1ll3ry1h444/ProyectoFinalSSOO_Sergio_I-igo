# Nombre del ejecutable
TARGET = main

# Carpetas del proyecto
SRC_DIR = src
CMD_DIR = $(SRC_DIR)/comandos
UTIL_DIR = $(SRC_DIR)/utils

# Archivos fuente y objetos
SRCS = $(CMD_DIR)/bytemaps.c $(CMD_DIR)/copy.c $(CMD_DIR)/dir.c $(CMD_DIR)/imprimir.c \
       $(CMD_DIR)/info.c $(CMD_DIR)/remove.c $(CMD_DIR)/rename.c $(CMD_DIR)/salir.c \
       $(UTIL_DIR)/bytemaps_utils.c $(UTIL_DIR)/helpers.c $(UTIL_DIR)/super_bloque.c \
       $(SRC_DIR)/simul_ext_esqueleto.c
OBJS = $(SRCS:.c=.o)

# Opciones del compilador
CC = gcc
CFLAGS = -Wall -g
LDFLAGS =

# Regla principal
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Regla para compilar los objetos
%.o: %.c $(SRC_DIR)/cabeceras.h
	$(CC) $(CFLAGS) -c -o $@ $<

# Limpiar archivos generados
clean:
	rm -f $(OBJS) $(TARGET)

# Regla para ejecutar el archivo después de compilarlo, abriendo particion.bin como argumento
run: $(TARGET)
	./$(TARGET) particion.bin

# Phony targets
.PHONY: all clean run

# Regla de compilación por defecto
all: $(TARGET)
