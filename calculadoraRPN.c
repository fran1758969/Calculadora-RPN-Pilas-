/*
    Autor: Francisco Rodriguez

    Materia: Algoritmica y Programacion
    Fecha de entrega: 20/10/25

    COMANDO PARA COMPILAR PROGRAMA:

    Descripcion: Calculadora RPN (Notacion Polaca Inversa) utilizando una pila o stack
*/

#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <windows.h>

typedef struct pila 
{    
    int num;
    struct pila* sig; // Puntero hacia el siguiente nodo
    
} Pila;

#define MAX_CARACTERES 12

// PILAS (STACK)
void insertar_nodo(Pila** cima, int valor); // Crea e inserta un nodo en la cima
int eliminar_nodo(Pila** cima); // Elimina el nodo en la cima

// CALCULADORA RPN
int es_entero(char *num);
int es_operador(char* op);
int resolver(Pila** cima, int *error,char* op);


int main()
{
    system("cls");
    Pila *cima = NULL; // Cima de la pila
    int error; // Determinara el flujo del programa segun si se realiza o no una divison entre 0
    int resultado = 0; 
    int tPila = 0; // Tamaño de la pila
    

    while (1)
    {
        // ENCABEZADO DE LA CALCULADORA
        printf("\n\t\t\t\tEJEMPLO DE PILA O STACK (Calculadora RPN)\n");
        printf("------------------------------------------------------------------------------------------------------------------------\n");
        printf("Como utilizar la calcuadora:\n\n");
        printf(" * Introduces un numero, pulsas ENTER, introduces el siguiente numero y asi sucesivamente, por ultimo el operador\n");
        printf(" * Para terminar el programa ingrese ENTER sin ingresar ningun numero u operador\n");
        printf("------------------------------------------------------------------------------------------------------------------------\n");
        printf("PILA: ");

        // Impresion de todos los nodos que hay en la pila
        Pila* pivote = cima;
        while (pivote != NULL) {
            printf("%d ", pivote->num);
            pivote = pivote->sig;
        }
        printf("\n------------------------------------------------------------------------------------------------------------------------\n");  

        // LECTURA DE LA ENTRADA
        printf("Ingrese un numero u operador (ENTER para salir): ");

        char token[MAX_CARACTERES];
        if (fgets(token, MAX_CARACTERES, stdin) == NULL) break;
        // Si no contiene '\n' la entrada fue truncada (queda resto en stdin)
        if (strchr(token, '\n') == NULL) 
        {
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF);

            system("cls");
            printf("\nERROR: Entrada demasiado larga (max %d caracteres). Intenta de nuevo.\n\n", MAX_CARACTERES - 2);
            continue; // volver a pedir entrada sin procesar token truncado
        }

        // OK: quitar el '\n' final y procesar normalmente
        token[strcspn(token, "\n")] = '\0';

        if (token[0] == '\0') break; // El programa termina si la entrada es un ENTER
        
        // CALCULADORA
        else if (es_entero(token))  // Si es un numero entero se apila
        {
            insertar_nodo(&cima ,atoi(token));
            tPila++;
            system("cls");
        }

        else if (es_operador(token)) // Si es un operador se resuelve la operacion
        {
            if (tPila < 2)  {
                system("cls");
                printf("\nERROR: Muy poco argumentos en la pila\n");
            }
            else {
                resultado = resolver(&cima , &error,token); // El resultado pasa a ser el nodo en la cima
                
                if (!error) {
                    insertar_nodo(&cima ,resultado);
                    tPila--; // Se resta un nodo al completar la operacion
                    
                }
                system("cls");
            }
        }
        else {
            system("cls");
            printf("\nERROR: Ingreso fuera de las reglas\n\n");
        }    
    }
    system("cls");

    printf("\nResultado: %d", resultado);
    printf("\n\nPRESIONE CUALQUIER TECLA PARA SALIR\n");

    getch();
    return 0;
}



void insertar_nodo(Pila** cima, int valor)
{
    // Reserva de memoria para el nuevo nodo
    Pila* nuevo_nodo = (Pila*) malloc(sizeof(Pila));
    if (nuevo_nodo == NULL) { // En caso de error al reservar memoria se acaba el programa
        printf("\nError al intentar reservar un espacio en memoria para el nuevo nodo\n");
        exit(1);
    }

    nuevo_nodo->num = valor;
    nuevo_nodo->sig = *cima; // Nuevo apunta hacia la anterior cima (Si no hay cima sera nulo)
    *cima = nuevo_nodo; // Nuevo ahora es la cima
}



int eliminar_nodo(Pila** cima)
{
    if (*cima == NULL) { // Si no hay cima no hay pila, asi que abortamos
        return 0;
    }

    Pila* aux = *cima; // Guardamos la direccion de la vieja cima en un auxiliar
    int valor = aux->num;

    *cima = aux->sig; // Puede quedar NULL si era el único
    free(aux);

    return valor; // Retorna el valor de la cima que se elimino para realizar las operaciones matematicas
}



int es_entero(char *num)
{
    while (*num != '\0')
    {
        if (*num == '+' || *num == '-') num++;
        if (!isdigit((unsigned char)*num)) {
            return 0;
        }
        num++;
    }
    return 1;
}



int es_operador(char* op)
{
    switch(*op)
    {
        case '+':
        case '-':
        case '/':
        case '*':
        return 1;

        default:
        return 0;
    }
}



int resolver(Pila** cima, int *error ,char* op)
{
    *error = 0; // resetear antes de intentar

    int a = eliminar_nodo(cima); // operando derecho (divisor)
    int b = eliminar_nodo(cima); // operando izquierdo (dividendo)

    switch(*op)
    {
        case '+': return b + a;
        case '*': return b * a;
        case '-': return b - a;
        case '/':
            if (a == 0) {
                printf("\nERROR: La division entre 0 es invalida\n");
                // Restauramos los nodos eliminados
                insertar_nodo(cima ,b);
                insertar_nodo(cima, a);
                *error = 1; // Error
                return 0;
            }
            *error = 0; // No hubo errores
            return b / a;
        default:
            *error = 1; // Error
            return 0;
    }
}