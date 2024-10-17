#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

// Función que manejará la señal
void handle_sigint(int sig) {
    printf("Señal SIGINT recibida\n");
}
void handle_sigquit(int sig) {
    printf("Señal SIGQUIT recibida\n");
}
void handle_sigign(int sig) {
    printf("Señal SIGIGN recibida\n");
}
int main() {
    // Registrar la señal SIGINT con la función de manejo
    signal(SIGINT, handle_sigint);
    signal(SIGQUIT, handle_sigquit);
    //signal(SIG_IGN, handle_sigign);

    // Bucle infinito para mantener el programa corriendo
    while (1) {
        printf("Programa en ejecución...\n");
        sleep(1);
    }

    return 0;
}