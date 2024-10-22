# Ejercicio 8

## a)
Suponiendo que se configura con 2 sectores por bloque, identificadores de bloque de 24 bits,
y hash de 16 bits. ¿Cuál es el tamaño que ocupa la FAT? ¿Cuál es el tamaño de la tabla de
archivos? ¿Cuál es el espacio que queda en disco para archivos?

- si cada sector es de 1KB, entonces ``|bloque| = 2KB``
- #bloques = 16 GB / 2 KB = 8 * 10^6
- ``|entrada FAT| = 24 bits = 3B``  ya que considero que la tabla (tipo array) solo alverga los valores, las claves son los propios indices.
- |FAT| = 3 B * 8 * 10^6 = 24 MB

- asumo que el tamanio maximo de un archivo es 16 GB = 16000000000 B,
y para representar este numero de Bytes, necesito 35 bits, asi que esa es la cantidad 
de bits del campo size de la hash table.   

- |entrada hash table| = 24 + 16 + 35 

- La cantidad de entradas de la hash table, son todos los posibles hashes, 
que se pueden armar con 16 bits (en binario), osea 2^16
- |hash table| = |entrada hash table| * #entradas hash table
            


