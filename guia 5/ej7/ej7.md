![alt text](image.png)

```C
int write(int sector, void* data){

    sema_wait(&mutex);

    // check motor encendido
    if(IN(DOR_STATUS == 0)) OUT(DOR_IO, 1);
    sleep(50ms);

    // seleccionamos pista y sector
    int pista = sector / cant_sectores_por_pista();
    OUT(ARM, pista);
    while(IN(ARM_STATUS) =! 1);
    OUT(SEEK_SECTOR, sector);

    // escribimos en el ultimo sector seleccionado
    int* kdata;
    copy_form_user(kdata, data, sizeof(data));
    escribir_datos(kdata);

    // esperamos a que termine la escritura
    while(IN(DATA_READY) != 1);

    // al final, apagamos el motor
    OUT(DOR_IO, 0);
    sleep(200ms);

    sema_signal(&mutex);

    return IO_OK;
}

int driver_init(){
    sema_init(&mutex, 1);
    return IO_OK;
}

```

![alt text](image-1.png)


```C
bool timer;
int tick_counter;
semaphore mutex, sem_arm, sem_status;

int write(int sector, void* data){

    sema_wait(&mutex);

    if(IN(DOR_STATUS == 0)) OUT(DOR_IO, 1);

    tick_counter = 2;
    timer = true
    while(tick_counter) sema_wait(&sem_timer);


    // seleccionamos pista y sector
    int pista = sector / cant_sectores_por_pista();
    OUT(ARM, pista);

    // esperamos a que se posicione
    sema_wait(&sem_ready);

    OUT(SEEK_SECTOR, sector);

    // escribimos en el ultimo sector seleccionado
    int* kdata;
    copy_form_user(kdata, data, sizeof(data));
    escribir_datos(kdata);

    // esperamos a que termine la escritura
    sema_wait(&sem_ready);

    // al final, apagamos el motor
    OUT(DOR_IO, 0);
    
    tick_counter = 5;
    timer = true
    while(tick_counter) sema_wait(&sem_timer);

    sema_signal(&mutex);

    return IO_OK;
}

int driver_init(){
    skip_timer = true;

    sema_init(&mutex, 1);
    sema_init(&sem_ready, 0);
    sema_init(&sem_timer, 0);

    request_irq(IRQ6, handler_status);
    request_irq(IRQ7, handler_timer);

    return IO_OK;
}

void handler_timer(){
    if(timer)
        if(tick_counter--)
            sema_signal(&sem_timer);
        else timer = false;
}

void handler_status(){
    // no puede haber 2 instancias write tratando de escribir al mismo tiempo,
    // asi que esto no tiene problemas.
    sema_signal(&sem_ready);
}


int driver_close(){
    free_irq(IRQ6);
    free_irq(IRQ7);
}


```