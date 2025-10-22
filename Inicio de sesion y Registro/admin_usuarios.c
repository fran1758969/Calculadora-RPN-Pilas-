#include <stdio.h>
#include <conio.h>
#include <stdbool.h>
#include <windows.h>
#include "menu_acceso.h"
#include "archivo_usuarios.h"
#include "../Validacion y otros/variados.h"
#include "../Validacion y otros/validacion.h"

// Cantidad usuarios traida dierectamente de archivo_usuarios.c
extern int numUsuarios;

// Usuario elegido
int eleccion;
// Eleccion en el menu de usuario
char subEleccion;

extern char *nombre_ingresado, *contra_ingresada; // Usuario o contrasena ingresada por el usuario

extern HANDLE consola;

/*============================================================================================================*/

/* Elimina el usuario elegido y guarda los cambios en el archivo info_usuarios.bin */
void eleminar_usuario()
{
    printf("\nSe ha elimnado al usuario: %s\n", info_users[eleccion - 1].nombreU);

    // Mover los usuarios posteriores una posición hacia arriba
    for (int i = eleccion - 1; i < numUsuarios - 1; i++) {
        strcpy(info_users[i].nombreU, info_users[i + 1].nombreU);
        strcpy(info_users[i].contrasena, info_users[i + 1].contrasena);
        info_users[i].ID = i + 1;
    }

    // Se disminuye la cantidad de usuarios
    numUsuarios--;
    // Se reasigna la memoria necesaria
    info_users = realloc(info_users, numUsuarios * sizeof(Usuarios));
}

/* ============================================================================================================ */

// Pequeño menu para modificar nombres de usuarios o contraseñas
void modificar_usuario()
{

    bool verificador; // Para verificar si el usuario ingresado ya existe
    bool veri_cadena_vacia;

    while(1)
    {


        char eleccion_modificar; // Almacena la eleccion del menu para modificar usuarios

        system("cls");
        printf("------------------------------------------------------------------------");
        printf("\n\t\tMenu para modificar usuarios\n");
        printf("------------------------------------------------------------------------\n");
        printf("\n1. Modificar nombre de usuario\n");
        printf("2. Modificar contrasena\n");
        printf("3. Regresar al menu de administracion de usuarios\n\n");
        printf("------------------------------------------------------------------------");
        printf("\nUsuario actual: %s\n", info_users[eleccion - 1].nombreU);
        printf("Contrase%ca actual: %s\n", 164, info_users[eleccion - 1].contrasena);
        printf("------------------------------------------------------------------------");
        printf("\nEliga un numero correspondiente a una opcion\n");
        printf("------------------------------------------------------------------------\n");

        eleccion_modificar = getch();

        switch (eleccion_modificar)
        {
            // MODIFICAR NOMBRE DE USUARIO
            case '1':

            system("cls");

            do
            {
                printf("\n\tNUEVO NOMBRE USUARIO\n");
                printf("---------------------------------------------------");
                printf("\nIngrese el nuevo nombre de usuario\n\n");
                nombre_ingresado = leer_cadena();

                 // Se verifica la contraseña ingresada
                verificador = validar_nombre_usuario();

                // Si verificador es true se podra realizar la eleccion s/n
                if (verificador) 
                {
                    imprimir_mensaje_color(";Seguro que quiere elegir este nombre de usuario Escriba S (Si) o N (No);", 6);
                    verificador = eleccionSN();
                }
                } while (!verificador);

            // Se guardan los cambios
            strcpy(info_users[eleccion - 1].nombreU, nombre_ingresado);
            break;


            // MODIFICAR CONTRASEÑA
            case '2':

            system("cls");

            do
            {    
 

                printf("\n\tNUEVA CONTRASE%cA\n", 165);
                printf("---------------------------------------------------");    
                printf("\nIngrese la nueva contrase%ca del usuario\n\n", 164);
                contra_ingresada = leer_cadena();

                if (verificador == false) {
                    system("cls");
                } 
                // Se verifica la contraseña ingresadaz
                verificador = validar_contrasena();

                // Si verificador es true se podra realizar la eleccion s/n
                if (verificador) 
                {
                    imprimir_mensaje_color(";Seguro que quiere elegir esta contrase*a Escriba S (Si) o N (No);", 6);
                    verificador = eleccionSN();
                }

            } while (!verificador);

            // Se guardan los cambios
            strcpy(info_users[eleccion - 1].contrasena, contra_ingresada);
            break;


            // REGRESAR AL MENU DE ADMINISTRACION DE USUARIOS
            case '3':
            return;

    
            default:
            break;
        }
    }

}

/*============================================================================================================*/

// Menu donde se encuentran las opciones para modificar y eliminar usuario
bool menu_usuarios()
{
    do
    {
        system("cls");

        // MENU DE OPCIONES
        printf("--------------------------------------------------------------------------------");
        printf("\n\t%cQue que quiere realizar con este usuario%c\n", 168, 63);
        printf("--------------------------------------------------------------------------------\n");
        printf("\n1. Eliminar usuario\n"); 
        printf("2. Modificar usuario\n");
        printf("3. Elegir otro usuario\n");
        printf("4. Regresar al menu principal\n\n");
        printf("--------------------------------------------------------------------------------");
        printf("\nHa elegido al usuario: %s\n", info_users[eleccion - 1].nombreU);
        printf("--------------------------------------------------------------------------------\n");
        
        // Lectura de la eleccion
        subEleccion = getch();

        switch (subEleccion)
        {

        // ELIMINAR USUARIO
        case '1':
            imprimir_mensaje_color(";Seguro que quieres eliminar este usuario. Escriba S (Si) o N (No);", 12);
            if (eleccionSN()) {
                 // Eliminamos el usuario
                eleminar_usuario();
            }
            else {
            return false; // Regresa al administrador de usuarios
            }
            return false;   
            
    
        // MODIFICAR USUARIO
        case '2':
            modificar_usuario();
            break; // No quiere regresar


        // ELEGIR OTRO USUARIO
        case '3':
        system("cls");
        return false; // Regresa al menu de administracion de usuarios


        // REGRESAR AL MENU PRINCIPAL
        case '4':
        return true; // Sale al menu principal
        
        // ERROR
        default:
            system("cls");
            imprimir_mensaje_color("ERROR: Debe ingresar un numero  que corresponda a una de las opciones", 12);
            break;
        }
    } while (1);
}

/*============================================================================================================*/

// Muestra los usuarios cargados en el archivo info_usuarios.bin actualmente
void imprimir_usuarios()
{
    bool validador; // Para validar el ingreso del usuario

    // Se cargan todos lo usuarios en info_users nuevamente
    lectura_archivo_users();

    system("cls");

    do
    {

        // Impresion de todos los usuarios
        printf("---------------------------------------------------------------\n");
        printf("\t\tAministrar usuarios guardados\n\n");
        printf("---------------------------------------------------------------\n");
        printf("%-5s | %-20s | %-20s\n", "ID", "USUARIO", "CONTRASENA");
        printf("---------------------------------------------------------------\n");      
    for (int i = 0; i < numUsuarios; i++) {
            printf("%-5d | %-20s | %-20s\n", info_users[i].ID, info_users[i].nombreU, info_users[i].contrasena);
        }

        // ELEGIR USUARIO
        printf("---------------------------------------------------------------\n");
        printf("Ingrese el numero de ID del usuario que quiere elegir (0 = salir)\n");
        // Lectura de la eleccion
        if (!leer_entero_validado(&eleccion)) {
        }
    else if (eleccion > numUsuarios) {
            system("cls");
            imprimir_mensaje_color("ERROR: Debe ingresar un numero correspondiente al ID de un usario", 12);
            validador = false;
        }
        else if (eleccion == 0) {
            system("cls");
            validador = true;
        }
        else {
            // Entramos al menu para administrar usuarios
            validador = menu_usuarios();
            /* Si el usuario elige regresar  al menu principla validador sera true, si no sera false*/
        }
    } while (!validador); /* Si validador es true se regresa al menu principal, sino nos quedamos en el menu de 
    administracion de usuarios */
    system("cls");

    // Se guardan los cambios en el archivo info_usuarios.bin
    escribir_archivo_usuarios();

}

/*============================================================================================================*/