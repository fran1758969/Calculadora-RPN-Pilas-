#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <stdbool.h>
#include <windows.h>
#include "menu_acceso.h"
#include "../Validacion y otros/variados.h"
#include "archivo_usuarios.h"
#include "../Validacion y otros/validacion.h"


extern int numUsuarios;

 /* Variable tipo struct que donde se guardaran los datos de los usuarios 
durante la ejecucion */
Usuarios* info_users;

// Contrasena y nombre que ingreso el usuario
char *contra_ingresada = NULL, *nombre_ingresado = NULL;

bool existen_usuarios;
 
/* Si el usuario se equivoca mas de una vez pasara a ser true para no imprimir un mensaje de error mas de una vez */
bool primer_error = false;




/*============================================================================================================*/

/* Una breve presentacion del programa y da a elegir al usuario entre inicio de sesion
y registro */
void menu_de_acceso()
{
    system("cls");

    // Se pasan todos los usuarios actuales a info_users
    existen_usuarios = lectura_archivo_users();
    // Si hay usuaurios la variable vale true sino vale false

    char eleccion; // Guarda la eleccion el usuario
    do
    {
        // Titulo
        printf("\nPrograma de registro de estudiantes\n");

        // Opciones de acceso
        printf("\n     Menu de acceso al programa\n");
        printf("---------------------------------------------");
        printf("\n1. Iniciar sesion\n");
        printf("2. Registrarse\n");
        printf("\nIngrese el numero correspondiente a la opcion que desea elegir\n\n");
        eleccion = getch();

        system("cls");

        switch (eleccion)
        {
            

        // INICIO DE SESION
        case '1':

            if (existen_usuarios) {
                inicio_de_sesion();
                return;
            }
            else {
                imprimir_mensaje_color("No existen usuarios guardados alctualmente, por favor registre un nuevo usuario", 6);
                break;
            }


        // REGISTRO
        case '2':

            registro(); 
            return; // Regresa al archivo main

        
        // Error
        default:
            system("cls");
            imprimir_mensaje_color("ERROR: Debe ingresar un numero entre 1 y 2", 12);
            continue;;
        }
    } while (1);
}

/*============================================================================================================*/

void inicio_de_sesion()
{
    do
    {
        for (int i = MAX_INTENTOS; i > 0; i--) 
        {
            printf("\n\t\tINICIO DE SESION\n");

            /* Pasamos al ingreso de los datos del usuario. En ese guardamos los datos que se compadaran con
            los que ya tenemos */
            ingreso_usuarios(&nombre_ingresado, &contra_ingresada);
        
            // Se verifica que los datos ingresados por el usuario coincidan con los almacenados
            for (int j = 0; j < numUsuarios; j++)
            {
                /* PARA DEBUGGEAR
                printf("\nComparando: [%s] con [%s]\n", info_users[j].nombreU, nombre_ingresado);
                printf("Comparando: [%s] con [%s]\n", info_users[j].contrasena, contra_ingresada); */

                if ((strcmp(info_users[j].nombreU, nombre_ingresado) == 0) && 
                (strcmp(info_users[j].contrasena, contra_ingresada) == 0))
                {
                    printf("-----------------------------------------");
                    printf("\nBienvenido %s", nombre_ingresado);
                    return;
                }
            }
            if (!validar_cadena(nombre_ingresado)  || !validar_cadena(contra_ingresada)) {
                i++;
            }
            else if (i == 1) 
            {
                system("cls");

                imprimir_mensaje_color("Ha excedido el numero de intentos permitidos. Acceso denegado", 4);

                getch();
                liberar_memoria();
                exit(1);
            }
            else
            {
                system("cls");


                printf("\nUsuario o contrase%ca incorrectas,  le quedan %d intentos. Intente de nuevo\n\n", 164, i - 1);
            }
        } 
    } while (terminar_o_continuar());  

    // Se libera la memoria reservada para info_users
    liberar_memoria();
}

/*============================================================================================================*/

void registro()
{

    bool validador_nombre, validador_contra;

    do
    {
        system("cls");

        do
        {

            printf("\n\t\tREGISTRO\n");

            /* Pasamos al ingreso de los datos del usuario. En ese guardamos los datos que se compadaran con
            los que ya tenemos */
            ingreso_usuarios(&nombre_ingresado, &contra_ingresada);

            // Se validan el nombre de usuario y contraseña
            validador_nombre = validar_nombre_usuario();
            validador_contra = validar_contrasena();

        } while (!validador_nombre || !validador_contra);

        
        // Se reserva un espacio mas para el nuevo usuario
        reservar_nuevo_usuario();

        // Impresion de la eleccion
        printf("----------------------------------------------");
        printf("\nNombre de usuario elegido: %s \n", nombre_ingresado);
        printf("Contrase%ca elegida: %s\n", 164, contra_ingresada);

    } while(terminar_o_continuar());

    // Se pasan el nombre contrasenas ingresados a info_users
    strcpy(info_users[numUsuarios - 1].nombreU, nombre_ingresado);
    strcpy(info_users[numUsuarios - 1].contrasena, contra_ingresada);
    // Se le da una ID al usuario
   info_users[numUsuarios - 1].ID = numUsuarios;
    
    // Se llama a la funcion que guarda la informacion en el archivo info_usuarios.bin
    escribir_archivo_usuarios();
    
    // Terminado el registro pasamos directamente al inicio de sesion
    inicio_de_sesion();
}

/*============================================================================================================*/

/* Funcion para tomar los datos del usuario */
void ingreso_usuarios(char** usuario, char** contrasena)
{
    *usuario = NULL;
    *contrasena = NULL;

    // Nombre de Usuario
    printf("----------------------------------------------");
    printf("\nIngrese el nombre de usuario\n");
    *usuario = leer_cadena();

    // Contraseña
    printf("----------------------------------------------");
    printf("\nIngrese la contrase%ca\n", 164);
    *contrasena = leer_cadena();

}

/*============================================================================================================*/

/* Permite liberar la memoria de los punteros utilizados (info_users, nombre_ingresado y contra_ingresada)*/
void liberar_memoria()
{
    free(info_users);
    free(nombre_ingresado);
    free(contra_ingresada);

}

/*============================================================================================================*/