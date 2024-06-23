#include "cola_dinamica.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

#define NUM_COLORES 4
#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_PURPLE "\x1b[35m"
#define ANSI_COLOR_RESET "\x1b[0m"
const char *colores[NUM_COLORES] = {"Rojo", "Verde", "Azul", "Morado"};

typedef struct
{
    char nombre[100];
    char contrasena[100];
} Jugador;

typedef struct
{
    char jugador[100];
    char fecha[20];
    int puntuacion;
    char secuenciaPrograma[100];
    char secuenciaUsuario[100];
} Partida;

void limpiarPantalla()
{
    system("clear");
}

void registrarJugador(Jugador *jugador)
{
    FILE *archivo;
    archivo = fopen("usuarios.txt", "a+");

    if (archivo == NULL)
    {
        archivo = fopen("usuarios.txt", "w");
        if (archivo == NULL)
        {
            printf("Error al crear el archivo de usuarios.\n");
            return;
        }
    }

    char nombreUsuario[100];
    char contrasena[100];
    int usuarioRegistrado = 0;

    printf("Ingresa tu nombre de usuario: ");
    fgets(nombreUsuario, sizeof(nombreUsuario), stdin);
    nombreUsuario[strcspn(nombreUsuario, "\n")] = 0;

    char linea[256];
    rewind(archivo);
    while (fgets(linea, sizeof(linea), archivo) != NULL)
    {
        char nombreRegistrado[100];
        sscanf(linea, "%[^,],%*s", nombreRegistrado);
        if (strcmp(nombreUsuario, nombreRegistrado) == 0)
        {
            printf("El nombre de usuario ya está registrado. Por favor, elige otro nombre.\n\n");
            usuarioRegistrado = 1;
            break;
        }
    }

    if (!usuarioRegistrado)
    {
        printf("Ingresa tu contraseña: ");
        fgets(contrasena, sizeof(contrasena), stdin);
        contrasena[strcspn(contrasena, "\n")] = 0;
        fprintf(archivo, "%s,%s\n", nombreUsuario, contrasena);
        printf("Registro exitoso. Ahora puedes iniciar sesión.\n\n");
    }

    fclose(archivo);
}

int iniciarSesion(Jugador *jugador)
{
    FILE *archivo;
    archivo = fopen("usuarios.txt", "r");

    if (archivo == NULL)
    {
        printf("No se pudo abrir el archivo de usuarios.\n");
        return 0;
    }

    char nombreUsuario[100];
    char contrasena[100];
    int autenticado = 0;

    printf("Ingresa tu nombre de usuario: ");
    fgets(nombreUsuario, sizeof(nombreUsuario), stdin);
    nombreUsuario[strcspn(nombreUsuario, "\n")] = 0;

    printf("Ingresa tu contraseña: ");
    fgets(contrasena, sizeof(contrasena), stdin);
    contrasena[strcspn(contrasena, "\n")] = 0;

    char linea[256];
    while (fgets(linea, sizeof(linea), archivo) != NULL)
    {
        char nombreRegistrado[100];
        char contrasenaRegistrada[100];
        sscanf(linea, "%[^,],%s", nombreRegistrado, contrasenaRegistrada);

        if (strcmp(nombreUsuario, nombreRegistrado) == 0 && strcmp(contrasena, contrasenaRegistrada) == 0)
        {
            autenticado = 1;
            strcpy(jugador->nombre, nombreUsuario);
            strcpy(jugador->contrasena, contrasena);
            break;
        }
    }

    fclose(archivo);

    if (autenticado)
    {
        printf("Inicio de sesión exitoso.\n\n");
        return 1;
    }
    else
    {
        printf("Inicio de sesión fallido. Verifica tus credenciales e intenta de nuevo.\n\n");
        return 0;
    }
}

void generarColor(Cola *cola)
{
    srand(time(NULL));
    int indice = rand() % NUM_COLORES;
    encolar(cola, indice);
}

void mostrarSecuenciaColores(Cola *cola, const char *colores[])
{
    Nodo *actual = cola->frente;

    while (actual != NULL)
    {
        const char *color = colores[actual->dato];
        if (strcmp(color, "Rojo") == 0)
            printf("\033[41m  \033[0m ");
        else if (strcmp(color, "Verde") == 0)
            printf("\033[42m  \033[0m ");
        else if (strcmp(color, "Azul") == 0)
            printf("\033[44m  \033[0m ");
        else if (strcmp(color, "Morado") == 0)
            printf("\033[45m  \033[0m ");

        actual = actual->siguiente;
    }
    printf("\n");
}

int verificarSecuencia(Cola *cola)
{
    Nodo *actual = cola->frente;
    char input[100];

    printf("Ingresa la secuencia de colores separados por espacios (R V A M):\n");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0;

    char *inputPtr = strtok(input, " ");
    while (actual != NULL && inputPtr != NULL)
    {
        char colorInicial = toupper(inputPtr[0]);
        if (colorInicial != toupper(colores[actual->dato][0]))
        {
            return 0;
        }
        actual = actual->siguiente;
        inputPtr = strtok(NULL, " ");
    }

    if (actual != NULL || inputPtr != NULL)
    {
        return 0;
    }

    return 1;
}

void guardarPartida(const char *jugador, int puntuacion)
{
    FILE *archivo;
    char nombreArchivo[150];
    snprintf(nombreArchivo, sizeof(nombreArchivo), "%s_partida.txt", jugador);

    archivo = fopen(nombreArchivo, "a");
    if (archivo == NULL)
    {

        archivo = fopen(nombreArchivo, "w");
        if (archivo == NULL)
        {
            printf("Error al crear el archivo de usuarios.\n");
            return;
        }
    }

    time_t tiempoActual = time(NULL);
    struct tm *infoTiempo = localtime(&tiempoActual);
    char fecha[20];
    strftime(fecha, sizeof(fecha), "%Y-%m-%d %H:%M:%S", infoTiempo);

    fprintf(archivo, "%s,%d\n", fecha, puntuacion);
    fclose(archivo);
}

void verHistorial(const char *jugador)
{
    FILE *archivo;
    char nombreArchivo[150];
    snprintf(nombreArchivo, sizeof(nombreArchivo), "%s_partida.txt", jugador);

    archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL)
    {
        printf("No hay historial para este jugador.\n");
        return;
    }

    printf("Historial de jugadas de %s:\n", jugador);
    printf("Fecha\t\t\tPuntuación\n");

    char linea[256];
    while (fgets(linea, sizeof(linea), archivo) != NULL)
    {
        char fecha[20];
        int puntuacion;
        sscanf(linea, "%[^,],%d", fecha, &puntuacion);
        printf("%s\t%d\n", fecha, puntuacion);
    }
    printf("\n");

    fclose(archivo);
}

void verMejorPuntaje(const char *jugador)
{
    FILE *archivo;
    char nombreArchivo[150];
    snprintf(nombreArchivo, sizeof(nombreArchivo), "%s_partida.txt", jugador);

    archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL)
    {
        printf("No hay historial para este jugador.\n");
        return;
    }

    char linea[256];
    int mejorPuntaje = 0;
    char mejorFecha[20];

    while (fgets(linea, sizeof(linea), archivo) != NULL)
    {
        char fecha[20];
        int puntuacion;
        sscanf(linea, "%[^,],%d", fecha, &puntuacion);
        if (puntuacion > mejorPuntaje)
        {
            mejorPuntaje = puntuacion;
            strcpy(mejorFecha, fecha);
        }
    }

    if (mejorPuntaje > 0)
    {
        printf("Mejor puntaje de %s: %d (Fecha: %s)\n", jugador, mejorPuntaje, mejorFecha);
    }
    else
    {
        printf("No hay jugadas registradas para %s.\n", jugador);
    }
    fclose(archivo);
}

void jugar(Cola *cola, const char *jugador)
{
    int nivel = 1;
    int continuar = 1;

    while (continuar)
    {
        printf("Nivel %d\n", nivel);

        generarColor(cola);
        limpiarPantalla();
        mostrarSecuenciaColores(cola, colores);
        sleep(2);
        limpiarPantalla();

        if (!verificarSecuencia(cola))
        {
            printf("Juego terminado. Tu puntuación es: %d\n", nivel - 1);
            guardarPartida(jugador, nivel - 1);
            continuar = 0;
        }
        else
        {
            nivel++;
        }
    }
}

void menu(Jugador *jugador)
{
    int opcion;
    Cola *cola = crearCola();

    do
    {
        printf("Bienvenido, %s!\n", jugador->nombre);
        printf("1. Ver historial de jugadas\n");
        printf("2. Ver mejor puntaje\n");
        printf("3. Jugar\n");
        printf("4. Salir\n");
        printf("Selecciona una opción: ");
        scanf("%d", &opcion);
        getchar();

        switch (opcion)
        {
        case 1:
            verHistorial(jugador->nombre);
            break;
        case 2:
            verMejorPuntaje(jugador->nombre);
            break;
        case 3:
            jugar(cola, jugador->nombre);
            break;
        case 4:
            printf("Adiós, %s!\n", jugador->nombre);
            break;
        default:
            printf("Opción no válida. Intenta de nuevo.\n");
        }
    } while (opcion != 4);

    liberarCola(cola);
}

int main()
{
    Jugador jugador;

    int opcion;
    do
    {
        printf("Bienvenido a Simon Game\n");
        printf("1. Iniciar sesión\n");
        printf("2. Registrarse\n");
        printf("3. Salir\n");
        printf("Selecciona una opción: ");
        scanf("%d", &opcion);
        getchar();

        switch (opcion)
        {
        case 1:
            if (iniciarSesion(&jugador))
            {
                menu(&jugador);
            }
            break;
        case 2:
            registrarJugador(&jugador);
            break;
        case 3:
            printf("Gracias por jugar a Simon Game. ¡Hasta luego!\n");
            break;
        default:
            printf("Opción no válida. Por favor, selecciona una opción válida.\n");
        }
    } while (opcion != 3);

    return 0;
}