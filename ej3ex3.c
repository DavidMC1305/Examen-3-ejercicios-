#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

void sigusr1_handler(int sig) {
    printf("Señal 1 recibida\n");
}

void sigusr2_handler(int sig) {
    printf("Señal 2 recibida\n");
}

void print_id() {
    printf("ID del proceso: %d\n", getpid());
}

int main() {
    pid_t q_pid, v_pid, r_pid, p_pid;

    // Crea el proceso Q
    if ((q_pid = fork()) == 0) {
        sleep(4);
        kill(getppid(), SIGUSR2);
        exit(0);
    }

    // Crea el proceso V
    if ((v_pid = fork()) == 0) {
        sleep(8);
        kill(getppid(), SIGUSR1);
        exit(0);
    }

    // Crea el proceso R
    if ((r_pid = fork()) == 0) {
        while (1) {
            print_id();
            sleep(1);
        }
    }

    // Crea el proceso P
    if ((p_pid = fork()) == 0) {
        while (1) {
            print_id();
            sleep(1);
        }
    }

    // Establece los manejadores de señal
    signal(SIGUSR1, sigusr1_handler);
    signal(SIGUSR2, sigusr2_handler);

    // Espera a que los procesos Q y V terminen
    int status;
    waitpid(q_pid, &status, 0);
    waitpid(v_pid, &status, 0);

    // Espera dos segundos antes de terminar los procesos R y P
    sleep(2);
    kill(r_pid, SIGKILL);
    kill(p_pid, SIGKILL);

    return 0;
}
