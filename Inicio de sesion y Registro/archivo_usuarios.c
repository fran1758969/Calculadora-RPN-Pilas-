#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>
#include "menu_acceso.h"
#include "../Validacion y otros/variados.h"


// ARCHIVO INFO_USUARIOS
FILE *archivo_info_u; /* Puntero que guarda la direccion de memoria del archivo donde esta la info de los usuarios */
int tamano_archivo; // tamaño actual del archivo info_usuarios.bin
int veces_logradas = 0;  // Almacenara las veces que la funcion fwrite() y fread() escribio correctamente lo que se le pida

// INFORMACION DE LOS USUARIOS
extern Usuarios* info_users; // Extern declara una variable local que se definio en otro archivo
int numUsuarios; // Cantidad actual se usuarios

extern HANDLE consola;

/*============================================================================================================*/

// Reserva un bloque de memoria para un nuevo usuario
void reservar_nuevo_usuario()
{
    // Se le suma el nuevo usuario
    numUsuarios++;
    
    // Se reserva mas espacio para el nuevo usuarip
    info_users = realloc(info_users, numUsuarios * sizeof(Usuarios));
    if (info_users == NULL) {
    imprimir_mensaje_color("Error al reservar memoria para el nuevo usuario  (func: reservar_nuevo_usuario)", 4);
    }
}

/*============================================================================================================*/

// Dice cuantos usuarios hay guardados en el archivo info_users.bin
void usuarios_en_archivo()
{
    fseek(archivo_info_u, 0, SEEK_END);
    // Se calcula el tamno en bytes del archivo
    tamano_archivo = ftell(archivo_info_u);

    // Se calcula la cantidad de usuarios que hay en el archivo
    numUsuarios = tamano_archivo / sizeof(Usuarios);

    /* PARA DEBUGGEAR
    printf("\n\nTamano del Archivo: %d\n\n", tamano_archivo);
    printf("\n\nUsuarios en archivo: %d\n\n", numUsuarios);
    */
}

/*============================================================================================================*/


// Lee la informacion guardada en el info_usuarios.bin
bool lectura_archivo_users()
{
    // Apertura del archivo para lectura escritura
    archivo_info_u = fopen("Inicio de Sesion y Registro/info_usuarios.bin", "rb");

    // Se comprueba que no haya habido errores al momento de abrir el archivo
    if (archivo_info_u == NULL) {
        imprimir_mensaje_color("No se ha podido encontrar el archivo info_users.bin. Se ha creado un nuevo archivo", 4);
        // Si los llega a haber se crea un nuevo archivo info_usuarios.bin
        archivo_info_u = fopen("Inicio de Sesion y Registro/info_usuarios.bin", "wb");
    }

    // Se calculan cuantos usuarios ya hay en el archivo
    usuarios_en_archivo();
    rewind(archivo_info_u);

    if (numUsuarios > 0) {
        // Se reserva el espacio necesario para pasar todo lo que hay en el archivo hacia info_users
    info_users = calloc(numUsuarios, sizeof(Usuarios));
        // Comprobamos que no haya habido errores al momento de reservar memroia

        if (info_users == NULL) {
            imprimir_mensaje_color("Error al reservar memoria para info_users", 4);
        } 
        else 
        {
            // Se consigue la informacion de las cuentas almacenadas
            veces_logradas = fread(info_users, sizeof(Usuarios), numUsuarios, archivo_info_u);

            // Se comprueba que fread haya logrado leer la info del archivo la cantidad de veces seleccionada
            if (veces_logradas != numUsuarios) {
                imprimir_mensaje_color("Error al intentar leer la informacion de info_usuarios.bin (func: lectura_archivo_usuarios)", 4);
            } 

            /* PARA DE DEBUGGEAR
            else {
                printf("\n\nSe ha cargado la informacion correctamente\n\n");
            }

            printf("\nUsuarios cargados desde el archivo:\n");
            for (int i = 0; i < numUsuarios; i++) {
                printf("Usuario %d: %s | Contrase%ca: %s\n", i + 1, info_users[i].nombreU, 164, 
                    info_users[i].contrasena);
            } */
           
        }
    // Si la cantidad de usuarios es 0 regresa false
    } else {
        info_users = NULL;
        imprimir_mensaje_color("No hay usuarios guardados. Registre un nuevo usuario", 6);
        return false;
    }

    // Se cierra el archivo
    fclose(archivo_info_u);
    veces_logradas = 0; // Reinicio
    return true;
}

/*============================================================================================================*/

// Guarda informacion en el archivo info_usuarios.bin
void escribir_archivo_usuarios()
{
    // Apertura del archivo en modo escritura binaria
    archivo_info_u = fopen("Inicio de Sesion y Registro/info_usuarios.bin", "wb");
    if (archivo_info_u == NULL) {
        printf("\n\nError al intentar abrir el archivo info_usuarios.bin (func: escribir_archivo_usuarios)\n\n");
    }
    // Se pasa la informacion suministrada al archivo de la info de los usuarios
    veces_logradas = fwrite(info_users, sizeof(Usuarios), numUsuarios, archivo_info_u);

    // Se comprueba que fwrite haya logrado escribir el buffer la cantidad de veces seleccionada
    if (veces_logradas != numUsuarios) {
        imprimir_mensaje_color("Error al intentar escribir la informacion en info_usuarios.bin (func: escribir_archivo_usuarios)", 4);
    } else {
        imprimir_mensaje_color("Se ha guardado la informacion correctamente", 2);
    }

    // Se cierra el archivo
    fclose(archivo_info_u);
    veces_logradas = 0; // Se reinicia el contador
}

/*============================================================================================================*/