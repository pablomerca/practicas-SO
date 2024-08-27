#include <stdio.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

volatile sig_atomic_t me_toca = 0;

void handler(){
    // cuando un proceso recive esta senial, sabe que es su turno.
    me_toca = 1;
}

void pingPong(pid_t pid){

    for(int i=0; i<3; i++){

        // esperamos a que nos toque de nuevo
        while(!me_toca);
        // si salio del loop, es xq es nuestro turno, vamos a la sig iteracion
        me_toca = 0;

        if(pid == 0){ // estamos en el hijo
            printf("PONG - pid: %d\n", getpid());
            // le avisamos al padre que ya printeamos
            kill(getppid(), SIGUSR1);
        }
        else{ // estamos en el padre
            printf("PING - pid: %d\n", getpid());
            // le avisamos al hijo que ya printeamos
            kill(pid, SIGUSR1);
        }
    }
}


int main(){

    signal(SIGUSR1, handler);
    pid_t pid = fork();

    while(1){

        // nos aseguramos que el padre siempre el 1ro en printear
        if(pid != 0){
            me_toca = 1;
        }

        pingPong(pid);

        // desde el padre preguntamos si queremos terminar
        if(pid != 0){
            // esperamos al hijo
            while(!me_toca);

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
    }

    return 0;
}