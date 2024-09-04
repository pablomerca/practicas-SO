
#include <stdio.h>   // printf()
#include <stdlib.h>  // exit()
#include <unistd.h>  // fork() pipe() execlp() dup2() close()
#include <sys/wait.h>

enum {CH1, CH2};
enum {READ, WRITE};
int pipes_fd[2][2];

void child_process_1(){
    printf("HIJO 1\n");
    
    for(int i=1; i<50; i+=3){
        int val;

        read(pipes_fd[CH1][READ], &val, sizeof(val));
        printf("hijo 1 recibe de padre: %d\n", val);

        write(pipes_fd[CH2][WRITE], &i, sizeof(i));
        printf("hijo 1 envia a hijo 2: %d\n", i);   
    }       
    exit(0);
}

void child_process_2(){
    printf("HIJO 2\n");
    
    for(int i=2; i<50; i+=3){
        int val;
        read(pipes_fd[CH1][READ], &val, sizeof(val));
        printf("hijo 2 recibe de hijo 1: %d\n", val);   

        write(pipes_fd[CH2][WRITE], &i, sizeof(i));
        printf("hijo 2 envia a padre: %d\n", i);   
    }       
    exit(0);
}

int main(int argc, int *argv[]){

    // creamos los pipes
    for(int i=0; i<2; i++) pipe(pipes_fd[i]);

    pid_t pid_child_1 = fork();
    if(pid_child_1 < 0) exit(EXIT_FAILURE);
    if(pid_child_1 == 0) child_process_1();
    

    pid_t pid_child_2 = fork();
    if(pid_child_2 < 0) exit(EXIT_FAILURE);
    if(pid_child_2 == 0) child_process_2();


    // de aca para abajo es el codigo del padre
    for(int i=0; i<50; i+=3){
        int val;

        write(pipes_fd[CH1][WRITE], &i, sizeof(i));
        printf("padre envia a hijo 1: %d\n", i);   

        read(pipes_fd[CH2][READ], &val, sizeof(val));
        printf("padre recibe de hijo 2: %d\n", val);   
    }       

    wait(NULL);
    wait(NULL);

    return 0;
}