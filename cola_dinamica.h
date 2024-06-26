#ifndef COLA_DINAMICA_H
#define COLA_DINAMICA_H

#include <stdbool.h>

// Definición de la estructura Nodo
// Cada nodo contiene un dato entero y un puntero al siguiente nodo
typedef struct Nodo
{
    int dato;
    struct Nodo *siguiente;
} Nodo;

// Definición de la estructura Cola
// La cola tiene un puntero al nodo del frente, un puntero al nodo final, y un contador de la longitud de la cola
typedef struct Cola
{
    Nodo *frente; // Puntero al primer nodo de la cola
    Nodo *final;  // Puntero al último nodo de la cola
    int longitud; // Número de elementos en la cola
} Cola;

// Declaración de las funciones de la cola

// Función para crear una cola vacía
// Retorna un puntero a una estructura Cola
Cola *crearCola();

// Función para añadir un elemento al final de la cola
// Toma un puntero a una Cola y un dato entero
void encolar(Cola *cola, int dato);

// Función para eliminar un elemento del frente de la cola
// Toma un puntero a una Cola y retorna el dato entero del nodo eliminado
int desencolar(Cola *cola);

// Función para obtener el dato del nodo del frente de la cola sin eliminarlo
// Toma un puntero a una Cola y retorna el dato entero del nodo del frente
int frenteCola(Cola *cola);

// Función para verificar si la cola está vacía
// Toma un puntero a una Cola y retorna un valor booleano (true si está vacía, false si no lo está)
bool colaVacia(Cola *cola);

// Función para liberar la memoria utilizada por la cola
// Toma un puntero a una Cola y libera todos los nodos de la cola
void liberarCola(Cola *cola);

// Incluye la implementación de las funciones declaradas anteriormente
// Esto permite que las funciones declaradas en este archivo sean definidas en "cola_dinamica.c"
#include "cola_dinamica.c"

#endif // Fin de la condición del preprocesador COLA_DINAMICA_H
