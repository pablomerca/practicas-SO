# Ejercicio 4

Suponer que se cuenta con un sistema de archivos basado en inodos como ext2 y bloques de 4 KB

## a)
a) Si se tiene un archivo de 40 KB, ¿cuántos bloques es necesario leer para procesarlo completamente?

Supongo que ya contamos con el inodo correspondiente al archivo.

Sabemos que en ext2, cada inodo puede direccionar de manera directa, 12 bloques de datos,
Osea ``12 * 4 KB = 48 KB``. Esto es suficiente para procesar todo el contenido de un   
archivo de ``40 KB``. Se necesitan ``10 bloques`` para procesar ``40 KB`` .


## b)

b) ¿Cuántos bloques es necesario leer si el archivo tiene 80 KB?

Los primeros ``48 KB``, los leo de los ``12 bloques`` directos, luego tengo que leer un bloque
extra para acceder  
a la tabla de indireccion simple, de la cual leo 8 bloques para completar  los ``32 KB`` restantes.

Total = 12 + 1 + 8 = ``21 bloques``




