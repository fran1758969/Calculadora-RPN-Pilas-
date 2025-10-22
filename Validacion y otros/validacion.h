#ifndef VALIDACION_H
#define VALIDACION_H

#define MAX_CARACTERES 20

#include <stdbool.h>


// VALIDACION DE ESTUDIANTES

// Verifica que el ingreso del usuario se una cedula de identidad
bool validar_cedula();



// VALIDACION DE USUARIOS

/* Valida que el nombre de usuario no tenga caracteres especiales, ni espacios, ni se mayor a el maximo de 
caracteres */
bool validar_nombre_usuario();
// Comprueba que la contraseña no tenga espacios ni sea mayor a el maximo de caracteres
bool validar_contrasena();



// LECTURA DE DATOS

// Lee una cadena de cualquier cantidad de caracteres, eliminando cualquier '\n' si hay algun fallo regresara NULL
char* leer_cadena();
// Lee la una cadena entrada del usuario, retorna true si es un numero entero mayor  0 y false si no lo es
bool leer_entero_validado(int* entero);



// VALIDACION DE TIPOS DE DATOS
bool validar_alphanumerico(const char *palabra); // Valida que una string solo sea alphanumerica
bool validar_entero(const char *palabra); // Valida que una cadena sea solo numeros enteros
// Valida que una cadena no sea mas larga que el maximo de caracteres permitido (100 ahora mismo) ni este vacia
bool validar_cadena(const char *cadena);



// Convierte cualquier caracter minuscula en mayuscula
void convertir_mayus(char *palabra);

// Comprueba si en la base de datos que se le especifique ya existe una cadena  igual a la buscada
bool ya_existe(void *base_de_datos, int cantidad, size_t size_estructura, size_t offset, 
              const char *str_buscada);



#endif