#include <stdio.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

volatile sig_atomic_t padre_listo = 0;

void handler(){padre_listo = 1;} 

void pingPong(pid_t pid){

    for(int i=0; i<3; i++){

        if(pid == 0){ // estamos en el hijo
            printf("PONG - pid: %d\n", getpid());
            sleep(1);
        }
        else{ // estamos en el padre
            printf("PING - pid: %d\n", getpid());
            sleep(1);
        }
    }
}


int main(){

    pid_t pid = fork();
    // asignamos el custom handler para el hijo
    if(pid == 0) signal(SIGUSR1, handler);

    while(1){

        // el hijo no debe empezar antes que el padre
        if(pid == 0)
            if(!padre_listo) continue;
        else kill(pid, SIGUSR1);

        pingPong(pid);

        // desde el padre preguntamos si queremos terminar
        if(pid != 0){

            char ch;
            printf("Desea continuar? s/n\n");
            scanf("%c", &ch);
            if(ch == 's') continue;
            if(ch == 'n') break;
            else{
                printf("opcion invalida, terminando el programa\n");
                kill(pid, SIGTERM);
                wait(NULL);
                break;
            } 
        }

        padre_listo = 0;
    }

    return 0;
}