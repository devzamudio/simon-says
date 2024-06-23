# Simon Game

Este programa implementa el juego Simon, donde los jugadores deben repetir secuencias de colores generadas aleatoriamente.

## Funcionalidades

- **Registro de Jugadores:** Permite a los jugadores registrarse con un nombre de usuario único y una contraseña.
- **Inicio de Sesión:** Los jugadores pueden iniciar sesión con su nombre de usuario y contraseña.
- **Juego:** Los jugadores juegan Simon, repitiendo secuencias de colores generadas por el programa.
- **Historial de Jugadas:** Se guarda un historial de las partidas jugadas por cada jugador.
- **Mejor Puntaje:** Se muestra el mejor puntaje alcanzado por el jugador.

## Estructura del Código

- **cola_dinamica.h:** Contiene la definición de una cola dinámica utilizada en el juego.
- **simon.c:** Archivo principal que incluye las funciones para el juego, registro de jugadores, inicio de sesión, etc.

## Funciones Principales

- `registrarJugador(Jugador *jugador)`: Permite a un jugador registrarse con un nombre de usuario único.
- `iniciarSesion(Jugador *jugador)`: Inicia sesión para un jugador existente.
- `jugar(Cola *cola, const char *jugador)`: Función principal para jugar al juego Simon.
- `verHistorial(const char *jugador)`: Muestra el historial de partidas de un jugador.
- `verMejorPuntaje(const char *jugador)`: Muestra el mejor puntaje alcanzado por un jugador.

## Uso del Programa

1. Ejecutar el programa.
2. Seleccionar entre iniciar sesión, registrarse o salir.
3. Jugar al juego Simon y tratar de alcanzar la mayor puntuación.
4. Ver el historial de partidas y el mejor puntaje.

¡Diviértete jugando al Simon Game!
