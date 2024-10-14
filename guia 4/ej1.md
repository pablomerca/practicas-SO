# Ejercicio 1

Suponer una computadora cuyo disco se accede sin memoria cache y un sistema de archivos FAT.
Además, en este sistema, la FAT no queda almacenada en la memoria (recordar que lo normal es que
la FAT se cargue en memoria). ¿Cuántos accesos al disco son necesarios para llegar hasta el último
bloque de un archivo de N bloques?

---

Supongo que conozco la entrada de la FAT correspondiente al 1er bloque.

Ya que dice que la FAT no queda alamacenada en memoria, voy a tener que acceder al disco cada vez que quiera consultarla.
Para llegar al N-esimo bloque, hay que acceder la FAT N veces.

En realidad, si de ante mano, ya se que ocupa N bloques, solo necesito consultar N - 1 veces el "siguiente" bloque, hasta 
llegar al N-esimo.
