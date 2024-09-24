Con esta modificacion, podriamos "extender" el cuantum que se le asigna a cada proceso arbitrariamente, solo tendriamos que
encolar el proceso tantas veces seguidas como cuantums desearamos, ademas que ganamos la flexibiliad de elegir,
cuan seguido le toca runnear a cada proceso.

Como desventaja, aunque tengamos un numero acotado de procesos, ahora no podemos acotar la longitud de la cola.
Ahora el scheduler podria no ser equitativo y mas propenso a starvation.

c) Cada proceso puede se encolado con un atributo que nos dice la longitud de su cuantum, el cual
puede ser customizado.

