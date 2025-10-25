#include <studio.h>
#include <stdlib.h>
#include <time.h>

//Variables globales 
int tablero[3][3];
int jugador = 1;
int computadora = 2;
int movimientos = 0;
int puntaje_humano = 0;
int puntaje_pc = 0;

//Funcion par empezar de cero
void reiniciar_juego() {
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            tablero[i][j] = 0;
        }
    }
    movimientos = 0;
}

// Dibujar el tablero actual 
void mostrar_tablero() {
    printf("\n  Tablero actual:\n");
    printf("   --- --- ---\n");
    for(int i = 0; i < 3; i++) {
        printf("  ");
        for(int j = 0; j < 3; j++) {
            if(tablero[i][j] == 0) printf("|   ");
            else if(tablero[i][j] == 1) printf("| X ");
            else printf("| O ");
        }
        printf("|\n");
        printf("   --- --- ---\n");
    }
    printf("\n");
}

//Verificar si alguien gano
int checar_ganador() {
    //Revisar filas
    for(int i = 0; i < 3; i++) {
        if(tablero[i][0] != 0 && tablero[i][0] == tablero[i][1] && tablero[i][1] == tablero[i][2]) {
            return tablero[i][0];
        }
    }

    //Revisar columnas
    for(int j = 0; j < 3; j++) {
        if(tablero[0][j] != 0 && tablero[0][j] == tablero[1][j] && tablero[1][j] == tablero[2][j]) {
            return tablero[0][j];
        }
    }

    //Rvisar diagonales
    if(tablero[0][0] != 0 && tablero[0][0] == tablero[1][1] && tablero[1][1] == tablero[2][2]) {
        return tablero[0][0];
    }
    if(tablero[0][2] != 0 && tablero[0][2] == tablero[1][1] && tablero[1][1] == tablero[2][0]) {
        return tablero[0][2];
    }

    return 0; //Nadie gano 
}

//Turno de la PC
void turno_computadora() {
    int fila, columna;

    //Buscar una casilla vacia aleatoria
    do {
        fila = rand() % 3;
        columna = rand() % 3;
    } while(tablero[fila][columna] != 0);

    tablero[fila][columna] = computadora;
    movimientos++;
    printf("La computadora juega en: %d,%d\n", fila + 1, columna + 1);
}

//Turno del jugador
void turno_jugador() {
    int fila, columna;
    int movimiento_valido = 0;

    while(!movimiento_valido) {
        printf("Tu turno! Ingresa fila y columna (ej: 1 2): ");
        scanf("%d %d", &fila, &columna);


        //Ajustar a indices de array
        fila--;
        columna--;

        if(fila < 0 || fila > 2 || columna < 0 || columna > 2) {
            printf("Coordenadas invalidas! Usa numeros del 1 al 3.\n");
        } else {
            tablero[fila][columna] = jugador;
            movimientos++;
            movimiento_valido = 1;
        }
    }
}

int main() {
    srand(time(NULL));
    int jugar_otra_vez = 1;

    printf("=== JUEGO DEL GATO ===\n");
    printf("Instrucciones:\n");
    printf("- Tu eres X, la computadora es O\n");
    printf("- Para jugar, Ingresa fila y columna (ej: 2 3)\n");
    printf("- Gana el que complete una linea de 3\n");
    printf("¡Buena suerte!\n\n");

    while(jugar_otra_vez) {
        reiniciar_juego();
        int ganador = 0;
        int turno_actual = rand() % 2; //0 = jugador, 1 = computadora

        if(turno_actual == 0) {
            printf("\nEmpiezas tú!\n");
        } else {
            printf("\nLa computadora empieza!\n");
        }

        // Loop principal del juego
        while(movimientos < 9 && ganador == 0) {
            mostrar_tablero();

            if(turno_actual == 0) {
                turno_jugador();
                turno_actual = 1;
            } else {
                turno_computadora();
                turno_actual = 0;
            }

            // Solor empezar a verificar ganador despues del 5to movimiento
            if(movimientos >= 5) {
                ganador = checar_ganador();
            }
        }

        //Mostrar resultado final
        mostrar_tablero();

        if(ganador == jugador) {
            printf("¡FELICIDADES! ¡GANASTE!\n");
            puntaje_humano++;
        } else if(ganador == computadora) {
            printf("La computadora gana. ¡Suerte para la próxima!\n");
            puntaje_pc++;
        } else {
            printf("¡EMPATE! Buen juego.\n");
        }

        printf("\n--- PUNTAJES ---\n");
        printf("Tú: %d  |  Computadora: %d\n", puntaje_humano, puntaje_pc);

        printf("\n¿Quieres jugar otra vez? (1 = Sí, 0 = No): ");
        scanf("%d", &jugar_otra_vez);
    }

    printf("\n¡Gracias por jugar! Hasta la próxima :)\n");
    return 0;
}