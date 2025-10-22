#ifndef ADMIN_USUARIOS_H
#define ADMIN_USUARIOS_H

#include <stdbool.h>

// Menu donde se encuentran las opciones para modificar y eliminar usuarios 
bool menu_usuarios();

// Muestra los usuarios cargados en el archivo info_usuarios.bin actualmente
void imprimir_usuarios();

void eleminar_usuario();

// Pequeño menu para modificar nombres de usuarios o contraseñas
void modificar_usuario();


#endif