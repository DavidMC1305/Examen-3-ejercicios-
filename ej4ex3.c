#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int buffer = 0;

void *producer(void *arg) {
    while (1) {
        if (buffer == 0) {
            int input;
            printf("Ingrese un número: ");
            scanf("%d", &input);
            buffer = input;
        }
    }
}

void *consumer(void *arg) {
    while (1) {
        if (buffer != 0) {
            if (buffer < 0) {
                printf("El número es negativo. Terminando...\n");
                exit(0);
            } else {
                int square = buffer * buffer;
                printf("%d al cuadrado es %d\n", buffer, square);
                buffer = 0;
            }
        }
    }
}

int main() {
    pthread_t tid_producer, tid_consumer;

    // Crea el hilo del productor
    if (pthread_create(&tid_producer, NULL, producer, NULL) != 0) {
        perror("Error al crear el hilo del productor");
        exit(1);
    }

    // Crea el hilo del consumidor
    if (pthread_create(&tid_consumer, NULL, consumer, NULL) != 0) {
        perror("Error al crear el hilo del consumidor");
        exit(1);
    }

    // Espera a que los hilos terminen (esto nunca sucede porque los hilos son infinitos)
    pthread_join(tid_producer, NULL);
    pthread_join(tid_consumer, NULL);

    return 0;
}
