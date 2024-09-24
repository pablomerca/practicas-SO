```C
barrera = sem(0);
mutex = sem(1);

counter = 0;
a(i)

mutex.wait();

counter++
if(counter == N) barrera.signal();

mutex.signal();

// molinete / turnstile
barrera.wait();
b(i)
barrera.signal();

```