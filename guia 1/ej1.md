## Ejercicio 1
¿Cuáles son los pasos que deben llevarse a cabo para realizar un cambio de contexto?

Para cambiar el programa que se ejecuta en la CPU, debemos:

- Guardar los registros.
- Guardar el IP.
- Si se trata de un programa nuevo, cargarlo en memoria.
- Cargar los registros del nuevo.
- Poner el valor del IP del nuevo.
- Otras cosas que veremos mas adelante.
- A esto se lo llama cambio de contexto o context switch


## Ejercicio 2

El PCB (Process Control Block) de un sistema operativo para una arquitectura de 16 bits es:

```C
struct PCB {

    int STAT; // valores posibles KE_RUNNING, KE_READY, KE_BLOCKED, KE_NEW
    int P_ID; // process ID
    int PC; // valor del PC del proceso al ser desalojado
    int RO; // valor del registro RO al ser desalojado
    ....
    int R15; // valor del registro R15 al ser desalojado
    int CPU_TIME // tiempo de ejecución del proceso
}
```
#### a)  
Implementar la rutina $\texttt{ Ke\textunderscore contextswitch(PCB* pcb\textunderscore0, PCB* pcb\textunderscore1) }$ , encargada de realizar el
cambio de contexto entre dos procesos (cuyos programas ya han sido cargados en memoria) debido
a que el primero ha consumido su quantum. pcb_0 es el puntero al PCB del proceso a ser desalojado
y pcb_1 al PCB del proceso a ser ejecutado a continuación. Para implementarla se cuenta con un
lenguaje que posee acceso a los registros del procesador R0, R1, ..., R15, y las siguientes operaciones:

```C
·=·; // asignación entre registros y memoria
int ke_current_user_time(); // devuelve el valor del cronómetro
void ke_reset_current_user_time(); // resetea el cronómetro
void ret(); // desapila el tope de la pila y reemplaza el PC
void set_current_process(int pid) // asigna al proceso con el pid como el siguiente a ejecutarse
```

```C
Ke_context_switch(PCB* pcb_0, PCB* pcb_1){

    // Guardar los registros del proceso a ser desalojados
    pcb_0.R1 = R1;
    pcb_0.R2 = R1;
    ...
    pcb_0.R15 = R15;

    // supongo que el PC (IP) ya esta actualizado en pcb_0

    // Cargar los registros del nuevo.
    R1 = pcb_1.R1
    R2 = pcb_2.R2
    ...
    R15 = pcb_1.R15

    // limpiamos la pila y reemplazamos el PC
    ret() 
    pcb_0.CPU_TIME = ke_current_user_time();
    ke_reset_current_user_time()

    // supongo que esta funcion setea automaticamente el campo de STAT
    set_current_process(pcb_1.PID)
}

```


## Ejercicio 3

Describir la diferencia entre un system call y una llamada a función de biblioteca.

Las syscalls son llamadas que un programa realiza al sistema operativo, para pedir que este realize alguna funcion o
tarea que el programa no tiene permiso/capacidad de realizar directamente. Estas requieren un cambio de contexto 
(pasamos a modo kernell), lo que conlleva un cierto overhead.

Las funciones provistas por bibliotecas, a priori no requieren cambio de contexto, por lo no tenemos ese overhead.
Por ejemplo: pow(), strcpy(), abs(), rand(), toUpper(), etc...

Sin embargo, tambien hay funciones de bibliotecas que hacen uso de syscalls, ej: printf(), malloc(), time(), ...


## Ejercicio 4



## Ejercicio 5

Un sistema operativo ofrece las siguientes funciones

```C
pid fork(); // Crea un proceso exactamente igual al actual y devuelve el nuevo process ID en el proceso padre y 0 en el proceso hijo.

void wait_for_child(pid child); // Espera hasta que el child indicado finalice su ejecución.

void exit(int exit_code); // Indica al sistema operativo que el proceso actual ha finalizado su ejecucion

void printf(const char *str); // Escribe un string en pantalla.

```
#### a)
Utilizando únicamente la llamada al sistema fork(), escribir un programa tal que construya un
árbol de procesos que represente la siguiente genealogía: Abraham es padre de Homero, Homero es
padre de Bart, Homero es padre de Lisa, Homero es padre de Maggie. Cada proceso debe imprimir
por pantalla el nombre de la persona que representa

```C


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
````

#### b)

Modificar el programa anterior para que cumpla con las siguientes condiciones: 1) Homero termine
sólo después que terminen Bart, Lisa y Maggie, y 2) Abraham termine sólo después que termine
Homero.

```C
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
````

### Ejericio 6 / 7


El sistema operativo del punto anterior es extendido con la llamada al sistema
$\texttt{ void exec(const char *arg) }$. Esta llamada al sistema reemplaza el programa actual por el código
localizado en el $\texttt{string (char *arg)}$ . Implementar una llamada al sistema que tenga el mismo comportamiento que la llamada $\texttt{void system(const char *arg)}$ , usando las llamadas al sistema ofrecidas
por el sistema operativo. Nota: Revisar man system, como ayuda.


```C

void system(const char *arg){
    pid_t pid = fork();
    if(pid == 0){
        execl("/dev/bin", "sh", arg, NULL);
        exit(0);
    }
}

```


## Ejercicio 8

Veamos el siguiente fragmento de código de un fork

```C
int main(int argc, char const *argv[]){
    int dato = 0;
    pid_t pid = fork();
    //si no hay error, pid vale 0 para el hijo
    //y el valor del process id del hijo para el padre
    if (pid == -1) exit(EXIT_FAILURE); //si es -1, hubo un error
    else if (pid == 0) {
        for (int i=0; i< 3; i++) {
            dato++;
            printf("Dato hijo: %d\n", dato);
        }
    }
    else {
        for (int i=0; i< 3; i++) {
            // dato nunca es actualizado en el padre, los procesos forkeados
            // no comparaten memoria
            printf("Dato padre: %d\n", dato);
        }
    }
    exit(EXIT_SUCCESS); //cada uno finaliza su proceso
}
```

¿Son iguales los resultados mostrados de la variable dato para el padre y para el hijo? ¿Qué está sucediendo?

El resultado printeado en consola es:

Dato padre: 0  
Dato padre: 0  
Dato padre: 0  
Dato hijo: 1  
Dato hijo: 2  
Dato hijo: 3  

Para el padre, la variable data nunca es actualizada, a pesar que el hijo si.
Esto ocurre porque los procesos forkeados, a pesar de ser identicos, no comparten memoria.


## Ejercicio 9

