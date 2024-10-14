# Ejercicio 2

Se tiene un disco con capacidad de 128 GB, y bloques de 8 KB. Supongamos un sistema de archivos
similar a FAT, donde la tabla se ubica desde la posición 0, y cada entrada de la tabla es de 24 B.

a) ¿Qué tamaño ocupa la tabla?  
b) ¿Cuántos archivos de 10 MB es posible almacenar?  
c) Se sabe que un archivo comienza en el bloque 20. Dada la siguiente FAT, indicar el   
tamaño de dicho archivo.

$$\begin{array}{|c|c|c|c|c|c|c|c|c|c|c|c|c|c|c|c|c|}\hline\text{Bloque}&0&1&2&3&4&5&6&...&20&21&22&...\\\hline\text{Siguiente}&\text{EOF}&2&23&4&5&0&7&...&21&22&3&...\\\hline\end{array}$$

---

a) |tabla| = #bloques * |entrada de tabla| = (|almacenamiento|/|bloque|)*|entrada de tabla|

|bloques| = 128 GB / 8 KB = (128 * 10^9) B / (8 * 10^3) B = 16 * 10^6 

|tabla| = 16 * 10^6 * 24 B = 384 * 10^6 B = 384 MB  

b) |memoria disponible| = 128 GB - 384 MB = 128 * 10^9 - 384 * 10^6 = 128000 * 10^6 - 384 * 10^6
                        = 127616 * 10^6 = 127616 MB

Entonces podemos almacenar 12761 archivos de 10 MB

c) 20 -> 21 -> 22 -> 3 -> 4 -> 5 -> 0
El archivo ocupa 7 bloques de 8 KB, osea 56 KB.









