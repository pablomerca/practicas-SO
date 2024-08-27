## Ejercicio 11

Un nuevo sistema operativo ofrece las siguientes llamadas al sistema para efectuar comunicación
entre procesos:

```C
void bsend(pid dst, int msg) // Envía el valor msg al proceso dst.
int breceive(pid src) // Recibe un mensaje del proceso src.
```

#### a)
Escribir un programa que cree un segundo proceso, para luego efectuar la siguiente secuencia de
mensajes entre ambos:

1. Padre envía a Hijo el valor 0
2. Hijo envía a Padre el valor 1,
3. Padre envía a Hijo el valor 2,
4. Hijo envía a Padre el valor 3,
etc...


```C

    int main(){

        int n;
        pid_t pid = fork();

        if(pid == 0){
            n = 1
        }
        else{
            n = 0
        }

        exit(0);
    }

```

