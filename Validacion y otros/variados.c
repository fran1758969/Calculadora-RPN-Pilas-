#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <conio.h>
#include "../Inicio de sesion y Registro/menu_acceso.h"




// Imprime un texto con una palabra de color
void imprimir_palabra_color(char pre[], char palabra[],char pos[] ,const int color)
{
    HANDLE consola = GetStdHandle(STD_OUTPUT_HANDLE);

    printf("%s", pre);
    SetConsoleTextAttribute(consola, color); // Color elegido
    printf("%s", palabra);
    SetConsoleTextAttribute(consola, 7); // Color elegido
    printf("%s\n", pos);
}
/*============================================================================================================*/

/* Permite imprimir un mensaje del color que quiera, para elegir un color debe pasar el numero correspondiente */
void imprimir_mensaje_color(char mensaje[], const int color)
{
    HANDLE consola = GetStdHandle(STD_OUTPUT_HANDLE);

    char copia[200];
    strcpy(copia, mensaje);

    SetConsoleTextAttribute(consola, color); // Color elegido

    int len = strlen(copia);
    char *posicion = strchr(copia, '*');
    // Colocar un punto y coma al principio y final del mesaje significa que quiere colocar signos de interrogacion
    if (copia[0] == ';' && copia[len - 1] == ';') 
    {
        copia[0] = 168;
        copia[len - 1] = 63;
    }
    if (posicion != NULL)
    {
        *posicion = 164;
    }
    

    printf("%s", copia);
    printf("\n");
    SetConsoleTextAttribute(consola, 7); // Regresa a blanco (color original)
}

/*============================================================================================================*/

// Una eleccion entre si o no (s = true, n = false)
bool eleccionSN()
{
    char eleccionSN;
        do
        {
        eleccionSN = getch();

        if (eleccionSN == 'S' || eleccionSN == 's')
        {
            system("cls");
            return true;
        }
        else if (eleccionSN == 'N' || eleccionSN == 'n')
        {
            system("cls");
            return false;
        }
    } while (1) ;

}

/*============================================================================================================*/

void terminar_programa()
{
    imprimir_mensaje_color(";Seguro que quiere salir del programa Escriba S (Si) o N (No);", 12);
    printf("\n");

    if (eleccionSN()) {
        liberar_memoria(); // Se libera la memoria reservada
        exit(0);
    }
}


/*============================================================================================================*/

 // Regresa true si  se quiere repetir y false si se quiere continuar
bool terminar_o_continuar()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); 
    bool primer_error = false;
    char sub_eleccion;

        // Menu de opciones
        // Color gris claro o blanco
        SetConsoleTextAttribute(hConsole, 7);
        printf("\n\n---------------------------------\n");
        printf("1. Continuar\n");
        printf("2. Realizar otra vez\n");
        printf("3. Apagar programa\n"); 
    do
    {
        // leer eleccion
        sub_eleccion = getch();

        // eleccion 1
        if (sub_eleccion == '1')
        {
            system("cls");
            return false;
        }
        // eleccion 2
        else if (sub_eleccion == '2')
        {
            system("cls");
            return true;
        // eleccion 3
        }
        else if (sub_eleccion == '3')
        {
            system("cls");
            terminar_programa();
        }
        // ERROR
        else if (!primer_error) // Si primero error es false imprime el mensaje de error
        {
             // color rojo para el error
            SetConsoleTextAttribute(hConsole, 4);
            printf("\nERROR: Debe elegir entre 1, 2 y 3\n\n");
            // regresamos al color original
            SetConsoleTextAttribute(hConsole, 7);
            primer_error = true; // Ya cometio el primer error, no se vuelve a imprimir el mensaje
        }
    } while (sub_eleccion != '1' && sub_eleccion != '2');  

    system("cls");
}

/*============================================================================================================*/

// Muestra los autores del programa
void autores()
{
    do
    {
       HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); 
    
        // Amarillo claro
        SetConsoleTextAttribute(hConsole, 14);
        printf("\n-------------------------------------------\n");
        printf("     Los autores de este programa son:");
        printf("\n-------------------------------------------\n");
    
        // Gris o Blanco
        SetConsoleTextAttribute(hConsole, 7);
        printf("Francisco Rodr%cguez  C.I: 32.179.150\n",161);
        printf("Geremy Tablante  C.I: 32.093.152\n");
        printf("Jos%c Padrino C.I: 31.684.264 \n", 130);
    } while (terminar_o_continuar());
}

/*============================================================================================================*/