#ifndef VARIADOS_H
#define VARIADOS_H

#include <stdbool.h>

// IMPRESION EN LA TERMINAL A COLOR

// Imprime un texto con una palabra de color
void imprimir_palabra_color(char pre[], char palabra[],char pos[] ,const int color);
/* Permite imprimir un mensaje del color que quiera, para elegir un color debe pasar el numero correspondiente */
void imprimir_mensaje_color(char mensaje[], const int color);



// MENUS PARA CONTROL DE FLUJO Y CONFIRMACION
bool eleccionSN(); // Le entre lo un caracter que deber ser entre s o n (s = true, n = false)
bool terminar_o_continuar();  // Regresa true si  se quiere repetir y false si se quiere continuar
void terminar_programa(); // Termina el programa

// Muestra los autores del programa
void autores();


#endif