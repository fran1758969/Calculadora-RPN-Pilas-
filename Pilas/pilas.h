#ifndef PILAS_H
#define PILAS_H

typedef struct pila 
{    
    int num;
    struct pila* sig;
    char nodo;
    
    
} Pila;

Pila* crear_nodo(Pila** cabeza);

#endif
