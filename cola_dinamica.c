#include "cola_dinamica.h"
#include <stdlib.h>

Cola *crearCola()
{
    Cola *c = (Cola *)malloc(sizeof(Cola));
    if (c == NULL)
    {
        return NULL;
    }
    c->frente = NULL;
    c->final = NULL;
    return c;
}

void encolar(Cola *c, int valor)
{
    Nodo *nuevoNodo = (Nodo *)malloc(sizeof(Nodo));
    if (nuevoNodo == NULL)
    {
        return;
    }
    nuevoNodo->dato = valor;
    nuevoNodo->siguiente = NULL;

    if (c->final == NULL)
    {
        c->frente = c->final = nuevoNodo;
    }
    else
    {
        c->final->siguiente = nuevoNodo;
        c->final = nuevoNodo;
    }
}

int desencolar(Cola *c)
{
    if (colaVacia(c))
    {
        return -1;
    }
    Nodo *temp = c->frente;
    int valor = temp->dato;
    c->frente = c->frente->siguiente;

    if (c->frente == NULL)
    {
        c->final = NULL;
    }

    free(temp);
    return valor;
}

int frenteCola(Cola *c)
{
    if (colaVacia(c))
    {
        return -1;
    }
    return c->frente->dato;
}

bool colaVacia(Cola *c)
{
    return c->frente == NULL;
}

void liberarCola(Cola *c)
{
    Nodo *temp;
    while (c->frente != NULL)
    {
        temp = c->frente;
        c->frente = c->frente->siguiente;
        free(temp);
    }
    c->final = NULL;
}