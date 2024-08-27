
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

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


void homero(){
    printf("hola, soy Homero\n");

    pid_t pid;
    pid = fork();

    if(pid == 0) bart();

    // cada hijo de Homero tiene que estar en su propio if(pid != 0), si llamaramos a 
    // todos los hijos desde el mismo if(pid != 0), podria pasar que homero tenga a Lisa y a Maggie
    // y que luego Lisa tambien tenga a Maggie.

    pid = fork();
    if(pid == 0) lisa();

    pid = fork();
    if(pid == 0) maggie();

    // esto tiene el problema que los hijos no siempre se imprimen en orden
}


int main(){
    // Empezamos en Abraham

    pid_t pid;
    pid = fork();

    if(pid == 0){
        homero();
    }
    else{
        printf("hola soy Abraham\n");
    }
    return 0;
}