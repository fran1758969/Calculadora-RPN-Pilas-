#include <stdio.h>
#include <ctype.h>
#include <windows.h>
#include <string.h>
#include <stdbool.h>
#include <stddef.h>
#include "variados.h"
#include "validacion.h"
#include "../Inicio de sesion y Registro/menu_acceso.h"


// USUARIOS
extern char *nombre_ingresado, *contra_ingresada;
extern Usuarios* info_users;
extern int numUsuarios;









// Comprueba que la contraseña no tenga espacios ni sea mayor a el maximo de caracteres
bool validar_contrasena()
{
    if (strchr(contra_ingresada, ' ') != NULL || !validar_cadena(contra_ingresada)) 
    {
        imprimir_mensaje_color("ERROR: La contrase*a no debe tener espacios ni mas de 100 caracteres", 12);
        return false; // Invalido
    }
    else {
     return true; // Valido
    }

}





/* Valida que el nombre de usuario no tenga caracteres especiales, ni espacios, ni se mayor a el maximo de 
caracteres */
bool validar_nombre_usuario()
{
    // Se comprueba si ya existe otro usuario con el mismo nombre
    if (ya_existe(info_users, numUsuarios, sizeof(Usuarios), offsetof(Usuarios, nombreU), nombre_ingresado)) 
    {
        system("cls");
        imprimir_mensaje_color("ERROR: Ya existe un usuario, intente nuevamento con otro nombre", 12);
        return false; // Invalido
    }
    // Se comprueba que el nombre de usuario sea alfanumerico
    else if (!validar_alphanumerico(nombre_ingresado) || !validar_cadena(nombre_ingresado)) 
    {
        return false; // Invalido
    }
    else {
        return true; // Valido
    }
}





// Valida que una cadena no sea mas larga que el maximo de caracteres permitido (20 ahora mismo)
bool validar_cadena(const char *cadena)
{
    int len = strlen(cadena);

    if (len > MAX_CARACTERES - 1 || cadena[0] == '\0')
    {       system("cls");
            imprimir_mensaje_color("ERROR: El texto no puede estar vacio ni exceder los 20 caracteres", 12);
        return false; // Invalido
    }
    else {
        return true; // Valido
    }
}





/* 
    EXPLICACION ENCABEZADO
    base_de_datos: El arreglo de estructuras en el que se guarda toda la informacion
    cantidad: cantidad de usuarios o estudiantes guardados 
    size_base_datos: La cantidad de bytes que pesa la estructura Estudiantes o Usuarios
    offset: Los bytes que hay entre el comienzo de la estructura y el campo que queremos comparar (cedulas o nombresE)
    str_buscada: La cadena de la que buscamos coincidencias (Cedulas o Nombre)
*/
bool ya_existe(void *base_de_datos, int cantidad, size_t size_estructura, size_t offset, 
              const char *str_buscada)
/* Verifica que el dato ingresado por el usuario no conincida con los que estan guardados en el struct elegido */
{
    for (int i = 0; i < cantidad; i++) 
    {
        // el puntero *campo apuntara hacia la cadena que toca comparar
        char *campo = (char *)(char *) base_de_datos + i * size_estructura + offset;
        
        if (strcmp(campo, str_buscada) == 0) {
            return true; // Existe
        }
    }
    return false; // No existe
}






// Lee una cadena de cualquier cantidad de caracteres, eliminando cualquier '\n' si hay algun fallo regresara NULL
char* leer_cadena()
{
    int i = 0; // Acumulador
    int capacida = 100; // capacidad que soporta la variable buffer
    int longitud = 0; // longitud de la cadena ingresada
    char c;

    // Reserva del tamano del buffer
    char* buffer = malloc(capacida);
    if (buffer == NULL) {
        printf("\n\nFallo al reservar memoria (funcion leer_cadena) (malloc)\n\n");
        return NULL;
    }
    do
    {
        // Lectura de la cadena
        c = getchar(); 
        buffer[i] = c;

        i++, longitud++; // Se le suma uno a los acumuladores

        if (longitud + 1 > capacida) // + 1 porque queremos dejar un espacio para el caracter nulo
        {
            // Se le da el doble de capacidad a buffer y se reserva mas espacio en memoria
            capacida *= 2;
            buffer = realloc(buffer, capacida);
            if (buffer == NULL)  {
                printf("\n\nFallo al reservar memoria, intente ingresar una cadena mas corta (funcion leer_cadena) (realloc)\n\n");
                return NULL;
            }
            
        }
    } while (c != '\n' && c != EOF);
    
    // Se intercambia el bajar de linea final por un caracter nulo
    if (longitud > 0) {
    buffer[longitud - 1] = '\0';
    }
    else {
    buffer[0] = '\0';
    }

    return buffer;
}





// Lee la una cadena entrada del usuario, retorna true si es un numero entero mayor  0 y false si no lo es
bool leer_entero_validado(int* entero)
{
    // Lectura de entrada
    char* buffer = leer_cadena();
    if (buffer == NULL) {
        printf("\n\nError funcion leer_cadena()\n\n");
        return false;
    }

    // longitud de la entrada
    int longitud = strlen(buffer);

    // Validacion de que sea un entero
    for (int i = 0; i < longitud; i++)
    {
        if (isdigit(buffer[i]) == 0) {

            free(buffer);
            system("cls");
            imprimir_mensaje_color("ERROR: El texto solo puede tener numeros enteros", 12);
            return false; // Invalido
        }
    }
    if (!validar_cadena(buffer)) {
        free(buffer);
        return false;
    }
    // Una vez validado se le regresa el entero
    *entero = atoi(buffer);

    free(buffer);
    return true; // Valido
}





// Valida si una string sea alphanumerica
bool validar_alphanumerico(const char *palabra) 
{
    while (*palabra) 
    {
        if (!isalnum((unsigned char)*palabra))
        {
            system("cls");
            imprimir_mensaje_color("ERROR: El  texto no puede incluir caracteres especiales o espacios en blanco", 12);
            return false; // Invalido
        }
        palabra++;
    }
    return true; // Valido
}






// Valida que una cadena sea solo numeros enteros
bool validar_entero(const char *palabra)
{
    int len_palabra = strlen(palabra);

    for (int i = 0; i < len_palabra; i++)
    {
        if (!isdigit(palabra[i]))
        {
            system("cls");
            imprimir_mensaje_color("ERROR: El texto solo debe incluir numeros", 12);
            return false; // Invalido
        }
    }

    int valor = atoi(palabra); // Se convierte la cadena a numeros
    // Se valida que no pase los limites
    if (valor <= 0 || len_palabra >= 9)
    {
        system("cls");
        imprimir_mensaje_color("ERROR: El numero no puede tener mas de 9 digitos  ni ser menor a 0", 12);
        return false; // Invalido
    }
    

    return true; // Valido
}






// Convierte cualquier palabra minuscula en mayuscula
void convertir_mayus(char *palabra)
{
    while (*palabra) 
    {
        *palabra = toupper((unsigned char)*palabra);
        palabra++;
    }
}
