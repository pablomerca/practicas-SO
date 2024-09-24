orden A B C.

```C
mutexA = sem(1)
mutexB = sem(0)
mutexC = sem(0)

// proceso A
while(1):
    mutexA.wait();
    f_A();
    mutexB.signal();

// proceso B
while(1):
    mutexB.wait();
    f_B();
    mutexC.signal();

// proceso C
while(1):
    mutexC.wait();
    f_C();
    mutexA.signal();

```

orden BBCA, BBCA , ...

```C

semA = sem(0)
semB = sem(1)
semC = sem(0)

// proceso A
while(1):
    semA.wait();
    f_A();
    semB.signal();

// proceso B
while(1):
    semB.wait();
    f_B();
    f_B();
    semC.signal();

// proceso C
while(1):
    semC.wait();
    f_C();
    semA.signal();

```

ej3:

```C
semA = sem(2)
prod = sem(0) // nos dice cuando hay productos disponibles
barrera = sem(0)

// proceso A
while(1):
    semA.wait();
    semA.wait();

    producir();
    producir();

    prod.singal();

    barrera.wait();

    prod.singal();

    barrera.wait(); // consume la signal que sobra, para que en la prox iter, barrera = 0

// proceso B
while(1):
    prod.wait();
    consumir();
    semA.signal();
    barrera.signal();

// proceso C
while(1):
    prod.wait();
    consumir();
    semA.signal();
    barrera.signal();

```


ej 4:
ABB, AC, ABB, AC, ABB, AC...

```C

semA = sem(1)
semB = sem(0)
semC = sem(0)

// proceso A
int consumer = C // indica quien fue el ultimo en consumir
while(1):
    if(consumer == B):
        semA.wait()
        produce();
        consumer = C
        semC.signal();
    else: // consumer == C
        semA.wait()
        produce();
        produce();
        consumer = B
        semB.signal();


// proceso B
while(1):
    semB.wait();
    consumir();
    consumir();
    semA.signal();

// proceso C
while(1):
    semC.wait();
    consumir();
    semA.signal();
```

