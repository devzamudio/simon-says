#include "cola_dinamica.h"
#include <stdlib.h>

// Función para crear una cola vacía
Cola *crearCola()
{
    Cola *c = (Cola *)malloc(sizeof(Cola)); // Asigna memoria para una nueva estructura Cola
    if (c == NULL)                          // Verifica si la asignación de memoria fue exitosa
    {
        return NULL; // Retorna NULL si no se pudo asignar memoria
    }
    c->frente = NULL; // Inicializa el frente de la cola a NULL
    c->final = NULL;  // Inicializa el final de la cola a NULL
    return c;         // Retorna el puntero a la nueva cola
}

// Función para añadir un elemento al final de la cola
void encolar(Cola *c, int valor)
{
    Nodo *nuevoNodo = (Nodo *)malloc(sizeof(Nodo)); // Asigna memoria para un nuevo nodo
    if (nuevoNodo == NULL)                          // Verifica si la asignación de memoria fue exitosa
    {
        return; // Sale de la función si no se pudo asignar memoria
    }
    nuevoNodo->dato = valor;     // Asigna el valor al nuevo nodo
    nuevoNodo->siguiente = NULL; // Inicializa el siguiente nodo como NULL

    if (c->final == NULL) // Verifica si la cola está vacía
    {
        c->frente = c->final = nuevoNodo; // El nuevo nodo es el único nodo, por lo que es tanto el frente como el final
    }
    else
    {
        c->final->siguiente = nuevoNodo; // Enlaza el último nodo actual con el nuevo nodo
        c->final = nuevoNodo;            // Actualiza el puntero final para que apunte al nuevo nodo
    }
}

// Función para eliminar un elemento del frente de la cola
int desencolar(Cola *c)
{
    if (colaVacia(c)) // Verifica si la cola está vacía
    {
        return -1; // Retorna -1 si la cola está vacía
    }
    Nodo *temp = c->frente;           // Guarda un puntero temporal al nodo del frente
    int valor = temp->dato;           // Guarda el dato del nodo del frente
    c->frente = c->frente->siguiente; // Actualiza el frente para que apunte al siguiente nodo

    if (c->frente == NULL) // Verifica si la cola quedó vacía
    {
        c->final = NULL; // Actualiza el final a NULL si la cola está vacía
    }

    free(temp);   // Libera la memoria del nodo eliminado
    return valor; // Retorna el dato del nodo eliminado
}

// Función para obtener el dato del nodo del frente de la cola sin eliminarlo
int frenteCola(Cola *c)
{
    if (colaVacia(c)) // Verifica si la cola está vacía
    {
        return -1; // Retorna -1 si la cola está vacía
    }
    return c->frente->dato; // Retorna el dato del nodo del frente
}

// Función para verificar si la cola está vacía
bool colaVacia(Cola *c)
{
    return c->frente == NULL; // Retorna true si el frente es NULL, false en caso contrario
}

// Función para liberar la memoria utilizada por la cola
void liberarCola(Cola *c)
{
    Nodo *temp;
    while (c->frente != NULL) // Itera sobre todos los nodos de la cola
    {
        temp = c->frente;                 // Guarda un puntero temporal al nodo del frente
        c->frente = c->frente->siguiente; // Actualiza el frente para que apunte al siguiente nodo
        free(temp);                       // Libera la memoria del nodo eliminado
    }
    c->final = NULL; // Asegura que el puntero final también sea NULL
}
