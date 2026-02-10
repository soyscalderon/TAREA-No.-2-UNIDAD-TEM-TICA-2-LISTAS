#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
typedef struct nodo
{
    int dato;
    struct nodo *anterior;
    struct nodo *siguiente;
} NODO;

int solicitar_entero();
float solicitar_flotante();

void eliminar_elemento(NODO **);
void agregar_elemento(NODO **);
void imprimir_lista(NODO *);

int main()
{
    NODO *cabeza = NULL;
    int op = 0;

    system("cls");
    while (op != 4)
    {
        printf("LISTAS DOBLEMENTE ENCADENADAS\n"
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
            eliminar_elemento(&cabeza);
            break;
        case 3:
            imprimir_lista(cabeza);
            break;
        case 4:
            break;
        default:
            printf("ERROR. Opcion incorrecta.\n");
            system("pause");
            system("cls");
            break;
        }
    }

    free(cabeza);
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

float solicitar_flotante()
{
    char aux[' '];
    int p, y, i, c = 0, n = 0;
    double num;
    do
    {
        // system("cls");
        printf("Introduzca un valor flotante: ");
        fflush(stdin);
        gets(aux);
        y = strlen(aux);
        c = 0;
        n = 0;
        for (i = 0; i < y; i++)
        {
            if (isdigit(aux[i]) || aux[i] == '.' || aux[i] == '-')
            {
                p = 1;
                if (aux[i] == 46)
                    c++;
                if (aux[i] == '-')
                    n++;
            }
            else
                p = 0;

            // Linea modificada para que no pueda haber '-' que no sean en el principio
            if (p == 0 || c > 1 || n > 1 || ((n == 1) && aux[0] != '-'))
            {
                p = 0;
                printf("\n\n\t ERROR, DATO MAL INTRODUCIDO \n\n");
                break;
            }
        }
        if (y == 0)
            p = 0;
    } while (p == 0);

    num = atof(aux);
    return num;
}

// Se pasa como doble puntero en caso de que se quiera borrar el nodo al que apunta la cabeza
void eliminar_elemento(NODO **cabeza)
{
    system("cls");
    int dato;
    NODO *previo, *actual;
    previo = NULL;
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
        while (actual != NULL && actual->dato != dato)
        {
            previo = actual;
            actual = actual->siguiente;
        }

        // Llego al final sin hallarlo
        if (actual == NULL)
        {
            printf("No se encontro nodo con el valor ingresado.");
        }

        // Si hallo el nodo a eliminar
        else
        {
            // El nodo encontrado fue el primero
            if (previo == NULL)
            {
                // Era el UNICO nodo
                if (actual->siguiente == NULL)
                {
                    *cabeza = NULL;

                    // Habia mas nodos
                }
                else
                {
                    *cabeza = actual->siguiente;
                }

                // el nodo hallado esta en medio o al final
            }
            else
            {
                previo->siguiente = actual->siguiente;

                // el nodo hallado esta al final
                if (actual->siguiente != NULL)
                {
                    (actual->siguiente)->anterior = previo;
                }
            }

            // Borrar el nodo
            free(actual);
            printf("Valor eliminado correctamente.");
        }
    }
    system("pause");
    system("cls");
}

// Se pasa como doble puntero en caso de que se quiera agregar en el nodo al que apunta la cabeza
void agregar_elemento(NODO **cabeza)
{
    system("cls");
    // Apuntadores de trabajo
    NODO *previo = NULL, *actual = NULL;
    NODO *nuevo = malloc(sizeof(NODO));
    if (nuevo != NULL)
    {
        nuevo->anterior = NULL;
        printf("DATO A AGREGAR\n");
        nuevo->dato = solicitar_entero();
        nuevo->siguiente = NULL;

        if (*cabeza == NULL)
        {
            // La lista no tiene nodos
            *cabeza = nuevo;
        }
        else
        {
            // La lista tiene al menos un nodo
            previo = NULL;
            actual = *cabeza;

            // Ciclo para recorrer el arreglo y posicionar actual en el nodo con numero mayor siguiente al nodo a ingresar
            while (actual->dato < nuevo->dato && actual != NULL)
            {
                previo = actual;
                actual = actual->siguiente;
            }
            previo->siguiente = nuevo;
            nuevo->anterior = previo;
            nuevo->siguiente = actual;
            actual->anterior = nuevo;

            //
            //
            //
            //
            // Solo faltaria verificar que pueda insertar al inicio
            //
            //
            //
            //
        }
        printf("Se ingreso correctamente el nodo.\n");
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
    else
    {
        while (actual != NULL)
        {
            printf("%d --> ", actual->dato);
            actual = actual->siguiente;
        }
        printf("NULL\n");
    }
    system("pause");
    system("cls");
}