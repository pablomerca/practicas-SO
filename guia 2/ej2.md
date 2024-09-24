a) Para planificar estos procesos, ¿convendría usar un algoritmo de Round Robin? ¿convendría
usar uno de prioridades? Justifique su respuesta.

Si usaramos Round Robin (preemptive), estariamos haciendo esperar de mas a los procesos P0 o P1, al distribuir de forma
equitativa los quantums, el proceso P2 estaria acaparando la CPU mas de lo necesario. 
Los procesos P0 y P1, podrian incluso bloquearse antes de cumplir su cuantum, por lo que es conveniente darles prioridad, 
para no aumentar su waiting time.

Entonces la opcion que conviene es usar un algoritmo de prioridades, que priorize a P0 y P1 por sobre P2.