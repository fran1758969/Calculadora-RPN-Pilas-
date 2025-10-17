#include <stdio.h>
#include <stdlib.h>
#include "pilas.h"

extern Pila *cabeza, *cola;

Pila* crear_nodo()
{
    // Reserva de memoria para el nuevo nodo
    Pila* nuevo_nodo = (Pila*) malloc(sizeof(Pila));
    if (nuevo_nodo == NULL) {
        printf("\nError al intentar reservar un espacio en memoria para el nuevo nodo\n");
        exit(1);
    }
    
    nuevo_nodo->sig = NULL; // Iniciamos el apuntador al siguiente nodo como nulo
    
    return nuevo_nodo; // Regresamos el apuntador al nuevo nodo
}