- Por prioridad: En caso que las prioridades sean estaticas, si llegaran continuamente y sin parar de prioridad 
alta, entonces los procesos de menos prioridad, nunca podrian acceder a la cpu.

- Colas de multinivel: De nuevo, si la prioridad es fija, entonces se puede dar el escenario que muchos procesos lleguen sin parar a las
colas de mayor prioridad, y de este modo las colas de menor prioridad quedarian sin acceso a la cpu.

- Shortest Remaining Time First / STF : Si hay un proceso con alto burst time (menor prioridad) y llegan muchos procesos sin parar que tienen un burst time menor (mayor prioridad), entonces el proceso con menor prioridad corre peligro de quedarse mucho tiempo sin acceso a la cpu.