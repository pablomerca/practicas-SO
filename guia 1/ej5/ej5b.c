#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

void maggie(){
    printf("hola, soy Maggie\n");
    exit(0);
}
void lisa(){
    printf("hola, soy Lisa\n");
    exit(0);
}
void bart(){
    printf("hola, soy Bart\n");
    exit(0);
}

// When exit() is called, it does not just return from the function or the block of code where it's called.
// Instead, it stops the execution of the entire process, regardless of where in the code the exit() function is called.

void homero(){

    pid_t pid;
    pid = fork();

    if(pid == 0) bart();
    // esto solo de abajo solo lo ejecuta homero, bart ya termino.
    int status;
    if(wait(&status) < 0){perror("wait");exit(-1);}

    // cada hijo de Homero tiene que estar en su propio if(pid != 0), si llamaramos a 
    // todos los hijos desde el mismo if(pid != 0), podria pasar que homero tenga a Lisa y a Maggie
    // y que luego Lisa tambien tenga a Maggie.

    pid = fork();
    if(pid == 0) lisa();
    // esto solo de abajo solo lo ejecuta homero, lisa ya termino.
    if(wait(&status) < 0){perror("wait");exit(-1);}

    pid = fork();
    if(pid == 0) maggie();
    // esto solo de abajo solo lo ejecuta homero, maggie ya termino.
    if(wait(&status) < 0){perror("wait");exit(-1);}

    // al poner los wait justo despues de la creacion de un hijo, conseguimos que los hijos
    // sean creados por el padre de manera secuencial, cada hijo es creado luego que el anterior muere.
    // si quisieramos que los 3 hijos pudiesen correr de manera concurrente, tendriamos que llamar a wait()
    // desde homero, tras crear a los 3 hijos.

    printf("hola, soy Homero\n");
    exit(0);
}


int main(){
    // Empezamos en Abraham

    pid_t pid;
    pid = fork();

    if(pid == 0) homero();
    else{
        int status;
        if(wait(&status) < 0){perror("wait");exit(-1);}
        printf("hola soy Abraham\n");
    }
    return 0;
}