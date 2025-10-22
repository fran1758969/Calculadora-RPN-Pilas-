#ifndef MENU_ACCESO_H
#define MENU_ACCESO_H

#define MAX_INTENTOS 3

#include <stdbool.h>
#include "../Validacion y otros/validacion.h"

// Estructura de las contrasenas y nombres de usuario
typedef struct
{
    char nombreU[MAX_CARACTERES]; // Nombres de usuario
    char contrasena[MAX_CARACTERES]; // Contraseñas
    int ID; // ID del usurio
} Usuarios;


/* Una breve presentacion del programa y da a elegir al usuario entre inicio de sesion
y registro */
void menu_de_acceso();

void inicio_de_sesion();

void registro();

/* Funcion para tomar los datos del usuario y abrir el archivo donde se guardaran o sacaran los datos */
void ingreso_usuarios(char** Usuario, char** contrsena);

/* Permite liberar la memoria de los punteros utilizados (info_users, nombre_ingresado y contra_ingresada)*/
void liberar_memoria();

#endif 