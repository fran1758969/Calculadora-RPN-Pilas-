#ifndef ARCHIVO_USUARIO_H
#define ARCHIVO_USUARIO_H

extern Usuarios* info_users;

#include "menu_acceso.h"
#include <stdbool.h>

// Lee la informacion guardada en el info_usuarios.bin
bool lectura_archivo_users();

// Guarda informacion en el archivo info_usuarios.bin
void escribir_archivo_usuarios();

// Dice cuantos usuarios hay guardados en el archivo info_users.bin
void usuarios_en_archivo();

// Reserva un bloque de memoria para un nuevo usuario
void reservar_nuevo_usuario();

#endif