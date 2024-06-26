#include "cola_dinamica.h" // Incluir la definición de la cola dinámica
#include <stdio.h>         // Incluir la biblioteca estándar de entrada/salida
#include <stdlib.h>        // Incluir la biblioteca estándar de funciones generales
#include <time.h>          // Incluir la biblioteca para manejo de tiempo
#include <string.h>        // Incluir la biblioteca para manejo de cadenas
#include <unistd.h>        // Incluir la biblioteca para manipulación de archivos
#include <ctype.h>         // Incluir la biblioteca para manejo de caracteres

#define NUM_COLORES 4                                                   // Definir el número de colores
#define ANSI_COLOR_RED "\x1b[31m"                                       // Código de color rojo
#define ANSI_COLOR_GREEN "\x1b[32m"                                     // Código de color verde
#define ANSI_COLOR_BLUE "\x1b[34m"                                      // Código de color azul
#define ANSI_COLOR_PURPLE "\x1b[35m"                                    // Código de color morado
#define ANSI_COLOR_RESET "\x1b[0m"                                      // Código para resetear el color
const char *colores[NUM_COLORES] = {"Rojo", "Verde", "Azul", "Morado"}; // Definir nombres de colores

// Estructura para almacenar información del jugador
typedef struct
{
    char nombre[100];
    char contrasena[100];
} Jugador;

// Estructura para almacenar información de una partida
typedef struct
{
    char jugador[100];
    char fecha[20];
    int puntuacion;
    char secuenciaPrograma[100];
    char secuenciaUsuario[100];
} Partida;

// Función para limpiar la pantalla
void limpiarPantalla()
{
    const char *os = getenv("OS"); // Obtener el sistema operativo

    if (os != NULL && strcmp(os, "Windows_NT") == 0)
    {
        system("cls"); // Limpiar pantalla en Windows
    }
    else
    {
        system("clear"); // Limpiar pantalla en otros sistemas (Linux, macOS)
    }
}

// Función para registrar un nuevo jugador
void registrarJugador(Jugador *jugador)
{
    FILE *archivo;
    archivo = fopen("usuarios.txt", "a+"); // Abrir archivo en modo agregar

    if (archivo == NULL)
    {
        archivo = fopen("usuarios.txt", "w"); // Crear archivo si no existe
        if (archivo == NULL)
        {
            printf("Error al crear el archivo de usuarios.\n");
            return;
        }
    }

    char nombreUsuario[100];
    char contrasena[100];
    int usuarioRegistrado = 0;

    // Solicitar nombre de usuario
    printf("Ingresa tu nombre de usuario: ");
    fgets(nombreUsuario, sizeof(nombreUsuario), stdin);
    nombreUsuario[strcspn(nombreUsuario, "\n")] = 0;

    // Verificar si el usuario ya está registrado
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
        // Solicitar contraseña
        printf("Ingresa tu contraseña: ");
        fgets(contrasena, sizeof(contrasena), stdin);
        contrasena[strcspn(contrasena, "\n")] = 0;
        fprintf(archivo, "%s,%s\n", nombreUsuario, contrasena); // Guardar usuario y contraseña
        printf("Registro exitoso. Ahora puedes iniciar sesión.\n\n");
    }

    fclose(archivo);
}

// Función para iniciar sesión
int iniciarSesion(Jugador *jugador)
{
    FILE *archivo;
    archivo = fopen("usuarios.txt", "r"); // Abrir archivo en modo lectura

    if (archivo == NULL)
    {
        printf("No se pudo abrir el archivo de usuarios.\n");
        return 0;
    }

    char nombreUsuario[100];
    char contrasena[100];
    int autenticado = 0;

    // Solicitar nombre de usuario y contraseña
    printf("Ingresa tu nombre de usuario: ");
    fgets(nombreUsuario, sizeof(nombreUsuario), stdin);
    nombreUsuario[strcspn(nombreUsuario, "\n")] = 0;

    printf("Ingresa tu contraseña: ");
    fgets(contrasena, sizeof(contrasena), stdin);
    contrasena[strcspn(contrasena, "\n")] = 0;

    // Verificar credenciales
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

// Función para generar un color aleatorio y agregarlo a la cola
void generarColor(Cola *cola)
{
    srand(time(NULL));                 // Inicializar generador de números aleatorios
    int indice = rand() % NUM_COLORES; // Generar índice aleatorio
    encolar(cola, indice);             // Agregar color a la cola
}

// Función para mostrar la secuencia de colores en la cola
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

// Función para verificar la secuencia ingresada por el usuario
int verificarSecuencia(Cola *cola)
{
    Nodo *actual = cola->frente;
    char input[100];

    // Solicitar secuencia de colores al usuario
    printf("Ingresa la secuencia de colores separados por espacios (R V A M):\n");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0;

    // Comparar la secuencia ingresada con la secuencia en la cola
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

// Función para guardar una partida en un archivo
void guardarPartida(const char *jugador, int puntuacion)
{
    FILE *archivo;
    char nombreArchivo[150];
    snprintf(nombreArchivo, sizeof(nombreArchivo), "%s_partida.txt", jugador); // Generar nombre del archivo

    archivo = fopen(nombreArchivo, "a"); // Abrir archivo en modo agregar
    if (archivo == NULL)
    {
        archivo = fopen(nombreArchivo, "w"); // Crear archivo si no existe
        if (archivo == NULL)
        {
            printf("Error al crear el archivo de usuarios.\n");
            return;
        }
    }

    // Obtener la fecha y hora actual
    time_t tiempoActual = time(NULL);
    struct tm *infoTiempo = localtime(&tiempoActual);
    char fecha[20];
    strftime(fecha, sizeof(fecha), "%Y-%m-%d %H:%M:%S", infoTiempo);

    // Guardar fecha y puntuación en el archivo
    fprintf(archivo, "%s,%d\n", fecha, puntuacion);
    fclose(archivo);
}

// Función para ver el historial de partidas de un jugador
void verHistorial(const char *jugador)
{
    FILE *archivo;
    char nombreArchivo[150];
    snprintf(nombreArchivo, sizeof(nombreArchivo), "%s_partida.txt", jugador); // Generar nombre del archivo

    archivo = fopen(nombreArchivo, "r"); // Abrir archivo en modo lectura
    if (archivo == NULL)
    {
        printf("No hay historial para este jugador.\n");
        return;
    }

    printf("Historial de jugadas de %s:\n", jugador);
    printf("Fecha\t\t\tPuntuación\n");

    // Leer y mostrar cada línea del archivo
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

// Función para ver el mejor puntaje de un jugador
void verMejorPuntaje(const char *jugador)
{
    FILE *archivo;
    char nombreArchivo[150];
    snprintf(nombreArchivo, sizeof(nombreArchivo), "%s_partida.txt", jugador); // Generar nombre del archivo

    archivo = fopen(nombreArchivo, "r"); // Abrir archivo en modo lectura
    if (archivo == NULL)
    {
        printf("No hay historial para este jugador.\n");
        return;
    }

    char linea[256];
    int mejorPuntaje = 0;
    char mejorFecha[20];

    // Leer y comparar cada línea del archivo para encontrar el mejor puntaje
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

// Función para iniciar el juego
void jugar(Cola *cola, const char *jugador)
{
    int nivel = 1;
    int continuar = 1;

    while (continuar)
    {
        printf("Nivel %d\n", nivel);

        generarColor(cola);                     // Generar un color aleatorio
        limpiarPantalla();                      // Limpiar pantalla
        mostrarSecuenciaColores(cola, colores); // Mostrar secuencia de colores
        sleep(2);                               // Pausar por 2 segundos
        limpiarPantalla();                      // Limpiar pantalla

        if (!verificarSecuencia(cola)) // Verificar secuencia ingresada por el usuario
        {
            printf("Juego terminado. Tu puntuación es: %d\n", nivel - 1);
            guardarPartida(jugador, nivel - 1); // Guardar la partida
            continuar = 0;
        }
        else
        {
            nivel++;
        }
    }
}

// Función para mostrar el menú principal
void menu(Jugador *jugador)
{
    int opcion;
    Cola *cola = crearCola(); // Crear una cola para el juego

    do
    {
        printf("Bienvenido, %s!\n", jugador->nombre);
        printf("1. Ver historial de jugadas\n");
        printf("2. Ver mejor puntaje\n");
        printf("3. Jugar\n");
        printf("4. Salir\n");
        printf("Selecciona una opción: ");
        scanf("%d", &opcion); // Leer opción seleccionada
        getchar();            // Limpiar buffer de entrada

        switch (opcion)
        {
        case 1:
            verHistorial(jugador->nombre); // Ver historial de jugadas
            break;
        case 2:
            verMejorPuntaje(jugador->nombre); // Ver mejor puntaje
            break;
        case 3:
            jugar(cola, jugador->nombre); // Iniciar juego
            break;
        case 4:
            printf("Adiós, %s!\n", jugador->nombre); // Salir del menú
            break;
        default:
            printf("Opción no válida. Intenta de nuevo.\n"); // Manejar opción inválida
        }
    } while (opcion != 4);

    liberarCola(cola); // Liberar memoria de la cola
}

// Función principal
int main()
{
    Jugador jugador; // Crear un jugador

    int opcion;
    do
    {
        printf("Bienvenido a Simon Game\n");
        printf("1. Iniciar sesión\n");
        printf("2. Registrarse\n");
        printf("3. Salir\n");
        printf("Selecciona una opción: ");
        scanf("%d", &opcion); // Leer opción seleccionada
        getchar();            // Limpiar buffer de entrada

        switch (opcion)
        {
        case 1:
            if (iniciarSesion(&jugador)) // Iniciar sesión
            {
                menu(&jugador); // Mostrar menú si el inicio de sesión es exitoso
            }
            break;
        case 2:
            registrarJugador(&jugador); // Registrar nuevo jugador
            break;
        case 3:
            printf("Gracias por jugar a Simon Game. ¡Hasta luego!\n"); // Salir del programa
            break;
        default:
            printf("Opción no válida. Por favor, selecciona una opción válida.\n"); // Manejar opción inválida
        }
    } while (opcion != 3);

    return 0;
}
