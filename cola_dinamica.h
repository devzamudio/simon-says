#ifndef COLA_DINAMICA_H
#define COLA_DINAMICA_H

#include <stdbool.h>

typedef struct Nodo
{
    int dato;
    struct Nodo *siguiente;
} Nodo;

typedef struct Cola
{
    Nodo *frente;
    Nodo *final;
    int longitud;
} Cola;

Cola *crearCola();
void encolar(Cola *cola, int dato);
int desencolar(Cola *cola);
int frenteCola(Cola *cola);
bool colaVacia(Cola *cola);
void liberarCola(Cola *cola);

#include "cola_dinamica.c"

#endif