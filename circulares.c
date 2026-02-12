#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct nodo
{
    int dato;
    struct nodo *siguiente;
} NODO;

int solicitar_entero();

char eliminar_elemento(NODO **);
void agregar_elemento(NODO **);

void imprimir_lista(NODO *);
char liberar_lista(NODO **);

int main() 
{
    NODO *cabeza = NULL;
    int op = 0;

    system("cls");
    while (op != 4)
    {
        printf("LISTAS CIRCULARES\n"
               "1.Ingresar un dato.\n"
               "2.Eliminar un dato.\n"
               "3.Imprimir lista.\n"
               "4.Salir de programa\n\n"
               "OPCION\n");
        op = solicitar_entero();

        switch (op)
        {
        case 1:
            agregar_elemento(&cabeza);
            break;
        case 2:
            if  (eliminar_elemento(&cabeza) == '\0') {
                free(cabeza);
                cabeza = NULL;
            }
            break;
        case 3:
            imprimir_lista(cabeza);
            break;
        case 4:
            if (liberar_lista(&cabeza) == 'a') {
                free(cabeza);
                cabeza = NULL;
            }
            printf("\nSaliendo del programa...\n");
            break;
        default:
            printf("ERROR. Opcion incorrecta.\n");
            system("pause");
            system("cls");
            break;
        }
    }

    return 0;
}

int solicitar_entero()
{
    char Aux[' '];
    int i, p, y, num;
    do
    {
        printf("Introduzca un valor entero positivo: ");
        fflush(stdin);
        gets(Aux); // se lee los datos introducidos
        y = strlen(Aux);

        for (i = 0; i < y; i++)
        {
            if (isdigit(Aux[i]))
                p = 1;
            else
                p = 0;

            if (p == 0)
            {
                printf("\n\n Error, dato mal introducido\n\n ");
                break;
            }
        }
        if (y == 0)
            p = 0;
    } while (p == 0);

    num = atoi(Aux);
    return num;
}

// Se pasa como doble puntero en caso de que se quiera borrar el nodo al que apunta la cabeza
char eliminar_elemento(NODO **cabeza)
{
    system("cls");
    int dato;
    NODO *previo, *actual, *temp;
    temp = NULL;
    previo = *cabeza;
    actual = *cabeza;

    if (actual == NULL)
    {
        printf("ERROR. No existen nodos.\n");
    }
    else
    {
        printf("DATO A ELIMINAR\n");
        dato = solicitar_entero();

        // recorrer la lista y parar en el nodo hallado (o hasta el final)
        do 
        {
            if(actual->dato == dato) {
                temp = actual;
                actual = actual->siguiente;
                break;
            }
            actual = actual->siguiente;
        } while (actual != *cabeza);

        // Llego al final sin hallarlo
        if (temp == NULL)
        {
            printf("No se encontro nodo con el valor ingresado.\n");
        }

        // Si hallo el nodo a eliminar
        else
        {
            // El nodo encontrado fue el primero
            if (temp == (*cabeza))
            {
                // Era el UNICO nodo
                if (actual == (*cabeza))
                {
                    printf("Se ha vaciado la lista\n");
                    system("pause");
                    system("cls");
                    return '\0'; //Regresa un caracter indicando que queda un unico nodo, y se borrara desde donde se llamó
                    
                }
                // Habia mas nodos
                else
                {
                    while (previo->siguiente != *cabeza) 
                    {
                        previo = previo ->siguiente;
                    }
                    previo->siguiente = actual;
                    *cabeza = actual;
                }

                // el nodo hallado esta en medio o al final
            }
            else
            {
                while (previo->siguiente != temp) 
                {
                    previo = previo ->siguiente;
                }
                previo->siguiente = actual;

            }

            // Borrar el nodo
            free(temp);
            printf("Valor eliminado correctamente.\n");
        }
    }
    system("pause");
    system("cls");
    return 'a'; //Regresa un caracter de confirmacion para saber que se elimino con exito y aun quedan nodos
}

// Se pasa como doble puntero en caso de que se quiera agregar en el nodo al que apunta la cabeza
void agregar_elemento(NODO **cabeza)
{
    system("cls");
    // Apuntadores de trabajo
    NODO *previo = NULL, *actual = NULL, *ultimo = NULL;
    NODO *nuevo = malloc(sizeof(NODO));
    previo = NULL;
    actual = *cabeza;
    ultimo = *cabeza;

    // verificar que se haya reservado espacio en memoria
    if (nuevo != NULL)
    {
        // Asignacion inicial de valores del nodo nuevo
        printf("DATO A AGREGAR\n");
        nuevo->dato = solicitar_entero();
        nuevo->siguiente = NULL;

        // La lista esta vacia
        if (actual == NULL)
        {
            *cabeza = nuevo;
            nuevo->siguiente = nuevo;
            printf("Nueva lista creada.\n");
        }

        // La lista tiene uno o mas nodos
        else
        {
            // Ciclo para recorrer el arreglo y posicionar actual en el nodo con numero mayor siguiente al nodo a ingresar

            do
            {                
                if (actual->dato <= nuevo->dato)
                {
                    previo = actual;
                    actual = actual->siguiente;
                }
                else
                {
                    break;
                }
            } while (actual != *cabeza);

            //Insertar al inicio
            if (actual == *cabeza && (nuevo->dato <= (*cabeza)->dato))
            {
                while (ultimo->siguiente != *cabeza)
                {
                    ultimo = ultimo->siguiente;
                }
                nuevo->siguiente = *cabeza; 
                ultimo->siguiente = nuevo;
                *cabeza = nuevo;
            }
            //Insertar por el medio o por el final
            else
            {
                previo->siguiente = nuevo;
                nuevo->siguiente = actual;

            }

            printf("Se ingreso correctamente el nodo.\n");
        }
    }
    else
    {
        printf("No se logro alocar memoria para el nuevo nodo.\n");
    }

    system("pause");
    system("cls");
}

void imprimir_lista(NODO *cabeza)
{
    system("cls");
    printf("IMPRESION DE LISTA\n");
    NODO *actual = NULL;
    actual = cabeza;

    if (actual == NULL)
    {
        printf("Lista vacia.\n");
    }
    else if (actual->siguiente == NULL)
    {
        printf("%d --> %p\n", actual->dato, actual->siguiente);
    }
    else
    {  
        do {
            printf("%d --> %p\n", actual->dato, actual->siguiente);
            actual = actual->siguiente;
        } while (actual != cabeza);
    }
    system("pause");
    system("cls");
}

//Funcion para liberar la lista a la hora de finalizar el programa
char liberar_lista(NODO **cabeza)
{
    NODO *ptr = NULL, *temp = NULL;
    ptr = *cabeza;

    if (ptr == NULL) {
        return 'b'; //Regresa un caracter indicando que la lista era nula, para no liberar memoria que no esta asignada
    }

    ptr = ptr->siguiente;

    while (ptr != *cabeza) {
        temp = ptr;
        ptr = ptr->siguiente;
        free(temp);
    } 

    return 'a'; //Regresa un caracter indicando que se liberaron todos los nodos restantes, y que puede eliminar el nodo cabecera donde se llamó
}