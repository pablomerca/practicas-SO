# Ejercicio 6

Considerar la siguiente ruta a un archivo: /home/aprobar.txt.

## b)
En un sistema basado en ext2, se quiere leer el archivo /pepe.txt, que es un enlace simbólico
al archivo mencionado arriba. El enlace no está cargado en memoria. ¿Cuántos bloques de
disco se deben acceder para llegar a los bloques de datos del archivo referenciado?

---

Sabemos que un enlace simbolico (foo -> bar) tiene un inodo para foo y uno  
para bar, en el que la data de foo, contiene una referencia a la dir entry  
de bar. 

Entonces, si tenemos pepe.txt -> aprobar.txt, para acceder a aprobar.txt, podemos hacerlo desde su referencia.

Para este ej, asumo que cada vez que busco un archivo, este esta en la primera entrada del primer bloque de su directorio padre. Si busco mas de un archivo,
entonces todos estan en el primer bloque.  

Empiezo en el root, cargo su primer bloque de datos (+1) para acceder a la dir entry
de pepe.txt. Una vez en la dir entry, voy a la inode table, al bloque (+1) en donde esta el numero de inode de pepe.txt. Una vez en su inode, accedo a su primer bloque de datos (+1) para entontrar el link a la dir entry de aprobar.txt.
Luego tengo que ir otra vez al bloque de la inode table (+0 ya que asumo que ya quedo cargado de la vez anterior) para agarrar el inode de aprobar.txt y ya con su inode, tengo acceso a sus bloques de datos. 

En total 3 accesos a bloques de disco.
