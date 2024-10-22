# Ejercicio 3

Un sistema de archivos de UNIX, similar a ext2, tiene bloques de tamaño
4 KB y el direccionamiento a bloques de disco (LBA) es de 8 B. A su
vez, cada inodo cuenta con 5 entradas directas, dos indirectas y una
doblemente indirecta


## a)
Cual es el tamanio maximo de archivo que soporta

Para esto hay que calcular la cantidad de bloques que podemos direccionar desde un inodo (contando todas las indirecciones) y multiplicar por el size de un bloque.

El dato del LBA nos sirve para saber cuantas direcciones de bloque podemos guardar en un bloque.


#direcciones de bloques x bloque = |bloque| / 8 B 
                                 = 4 KB / 8 B   
                                 = 4 * 10^3 B / 8 B = 0.5 * 10^3  

#bloques direccion directa = 5
#bloques simple indireccion = 2 * #direcciones de bloques x bloque  
                            = 2 * 0.5 * 10^3  
                            = 10^3  
#bloques doble indireccion = (#direcciones de bloques x bloque)^2  
                           = (0.5 * 10^3)^2 = 0.25 * 10^6  

#total bloques direccionales = 5 + 10^3 + 0.25 * 10^6 = 
                             = 5 + 10^3 + 250 * 10^3
                             = 255 * 10^3

#maxima de bytes por archivo = #total bloques direccionales * |bloque|  
                             = (255 * 10^3) * (4KB)  
                             = (255 * 10^3) * (4 * 10^3 B)  
                             = 1020 * 10^6 B  
                             = 1020 MB  


## b)
Si el 50 % del espacio en disco está ocupado por archivos de 2 KB, el 25 % por archivos de 4  
KB y el 25 % restante por archivos de 8 KB, ¿qué porcentaje del espacio en disco está siendo  
desperdiciado? (Considerar sólo el espacio utilizado en los bloques de datos)  

Hay que ver cuanto espacio vacio queda en los bloques:

Los archivos de 2KB, usan la mitad de un bloque, por lo que la otra mitad se desperdicia,   
los archivos de 4KB y 8KB usan bloques completos ya que son multiplos del block size (4KB).  
Por lo tanto el espacio desperdiciado se atribuye enteramente a los archivos de 2KB, y ya  
que estos ocupan el 50% del disco, concluimos que el 25% del disco es desperdiciado.  


## c)
¿Cuántos bloques es necesario acceder para procesar completo un archivo de 5 MB?

#bloques necesarios = 5MB / 4KB = 5000 KB / 4 KB = 1250

^^^ esta respuesta no esta bien, para almacenar los 5MB, aparte de los bloques de data,
hay que considerar los bloques que guardan direcciones a otros bloques en el inodo.

Cuantos bloques usamos para direccionar 1250 bloques?

los primero 5 bloques los tenemos directo desde el inodo, nos quedan 1245 bloques por direccionar. Luego con los 2 bloques de simple indireccion (los sumamos), tenemos 1000 bloques mas cubiertos, nos quedan 245 por cubrir, estos los cubro con 1 bloque del doble indireccion del cual uso 1 bloque de simple indireccion (sumo esos 2).

5 + 1000 + 2 + 1 + 1 + 245 = 1254 bloques

Entonces a los 1250 bloques, les tengo que sumar 4.
En total uso 1254 bloques.















