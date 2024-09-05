#include <stdio.h>   // printf()
#include <stdlib.h>  // exit()
#include <unistd.h>  // fork() pipe() execlp() dup2() close()
#include <sys/wait.h>

#define N 50
#define END_SIGNAL -1  // Señal para indicar fin de transmisión

enum {P_CH1, CH1_CH2, CH2_P};
enum {READ, WRITE};
int pipes_fd[3][2];

void child_process_1(){
    printf("HIJO 1\n");
    
    while (1) {
        int val;
        read(pipes_fd[P_CH1][READ], &val, sizeof(val));
        if (val == END_SIGNAL) break;  // Fin de transmisión
        printf("hijo 1 recibe de padre: %d\n", val);

        int i = val + 1;  // Avanza en su rango (simulación)
        write(pipes_fd[CH1_CH2][WRITE], &i, sizeof(i));
        printf("hijo 1 envia a hijo 2: %d\n", i);
    }
    int temp = END_SIGNAL;
    write(pipes_fd[CH1_CH2][WRITE], &temp, sizeof(temp));  // Enviar señal de fin a hijo 2
    printf("hijo 1 termino con su rango\n\n");
    exit(0);
}

void child_process_2(){
    printf("HIJO 2\n");

    while (1) {
        int val;
        read(pipes_fd[CH1_CH2][READ], &val, sizeof(val));
        if (val == END_SIGNAL) break;  // Fin de transmisión
        printf("hijo 2 recibe de hijo 1: %d\n", val);

        int i = val + 1;  // Avanza en su rango (simulación)
        write(pipes_fd[CH2_P][WRITE], &i, sizeof(i));
        printf("hijo 2 envia a padre: %d\n", i);
    }

    int temp = END_SIGNAL;
    write(pipes_fd[CH2_P][WRITE], &temp, sizeof(temp));  // Enviar señal de fin al padre
    printf("hijo 2 termino con su rango\n\n");
    exit(0);
}

int main(int argc, char *argv[]){

    // Crear los pipes
    for(int i=0; i<3; i++) pipe(pipes_fd[i]);

    pid_t pid_child_1 = fork();
    if(pid_child_1 < 0) exit(EXIT_FAILURE);
    if(pid_child_1 == 0) child_process_1();
    

    pid_t pid_child_2 = fork();
    if(pid_child_2 < 0) exit(EXIT_FAILURE);
    if(pid_child_2 == 0) child_process_2();

    // Código del padre
    for(int i=0; i<=N; i+=3){
        write(pipes_fd[P_CH1][WRITE], &i, sizeof(i));
        printf("padre envia a hijo 1: %d\n", i);   

        int val;
        read(pipes_fd[CH2_P][READ], &val, sizeof(val));
        printf("padre recibe de hijo 2: %d\n", val);   
    }

    // Enviar señal de fin a hijo 1
    int temp = END_SIGNAL;
    write(pipes_fd[P_CH1][WRITE], &temp, sizeof(temp));

    // Leer señal de fin del hijo 2
    int val;
    read(pipes_fd[CH2_P][READ], &val, sizeof(val));

    printf("padre termino con su rango\n\n");

    pid_t pid1 = wait(NULL);
    printf("termino el hijo con pid: %d\n", pid1);
    pid_t pid2 = wait(NULL);
    printf("termino el hijo con pid: %d\n", pid2);

    return 0;
}


    /*
    ojo, que el padre salga del loop y luego le envie las END_SIGNAL a AMBOS hijo, seria un error,
    ya que podria pasar que el padre termine su rango, pero los hijo tengan que seguir por 1 o 2 valores mas.
    Luego padre envia a los 2 hijos la END_SIGNAL, pero el hijo2 lee la END_SIGNAL, antes que el mensaje del hijo 1, luego el hijo 2 
    lee la END_SIGNAL y termina. Pero entonces el hijo2 no va a poder leer el ultimo valor que envio el hijo1 y el hijo1 se va a 
    quedar bloqueado

    Ademas, por como esta codeado el hijo 2, este lee siempre del hijo 1, x lo que no va a leer la END_SIGNAL del padre.
    La solucion es hacer que la END_SIGNAL se propague a los hijos, en el sentido de la "ronda":
    padre -> hijo1 -> hijo2.
    */