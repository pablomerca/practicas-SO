# Ejercicio 7

Una compañía que fabrica discos rígidos decide, como parte de cierta estrategia comercial, emprender la creación de un nuevo filesystem. Durante la fase de diseño preliminar el equipo de ingeniería a
cargo del proyecto discute acaloradamente la conveniencia de adoptar un enfoque inspirado en FAT o
la de uno basado en inodos. Indicar cuál de las dos opciones recomendaría, y por qué, para cada uno
de los siguientes requerimientos:


## 1. Es importante que puedan crearse enlaces simbólicos.
Para esto tenemos que usar inodos, ya que fat no permite usar links

## 2. Es importante que la cantidad de sectores utilizados para guardar estructuras auxiliares sea acotada, independientemente del tamaño del disco.  

En FAT, el tamanio de las estructuras (la FAT) no es independiente del tamanio del disco, sino que esta en funcion de este y de la cantidad de bloques que tiene el disco.  
Asi que de entrada FAT no cumple este requisito.

Por otro lado, en ext2, para cada archivo, tenenemos acceso a toda su data desde su inode. El problema es que los inodes tambien requieren espacio en el
disco para guardarlos (en la inode table). 

Se puede decir que la cantidad de sectores utilizados para guardar las inode  
tables es acotado, independientemente del tamanio del disco?

## 3. Es importante que el tamaño máximo de archivo sólo esté limitado por el tamaño del disco.

Suponiendo que el tamanio del disco no es exesivamete grande (solo algunos TB), esto lo podemos
conseguir con inodes, ya que en ext32, vimos que desde un inode podemos direccionar
hasta 40 TB.

## 4. Es importante que la cantidad de memoria principal ocupada por estructuras del filesystem en un instante dado sea (a lo sumo) lineal en la cantidad de archivos abiertos en ese momento.

Esto lo conseguimos facilmente con inodos, ya que solo necesitamos en memoria
un inodo por cada archivo que tengamos abierto.
En FAT tendriammos que tener si o si la FAT completa, asi que no conviene.

