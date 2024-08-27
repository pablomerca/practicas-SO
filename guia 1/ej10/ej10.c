#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(){

    // iniciamos en Juan

    pid_t pid = fork();

    if(pid == 0){
        printf("Soy Julieta\n");
        sleep(1);

        pid = fork();
        if(pid == 0){
            printf("Soy Jennifer\n");
            sleep(1);
        }
    }
    else {
        printf("Soy Juan\n");
        sleep(1);

        wait(NULL);

        pid = fork();
        if(pid == 0){
            printf("Soy Jorge\n");
            sleep(1);
        }
    }

    exit(0);
}