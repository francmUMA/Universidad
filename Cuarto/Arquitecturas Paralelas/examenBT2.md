## Ejercicio 1
````
# define NPOINTS 1000
# define MAXITER 1000
struct d_complex{ double r; double i; };
struct d_complex c;
int numoutside = 0;
int main(){
    int i, j;
    double area, error, eps = 1.0e-5;
    #pragma omp parallel for default(shared) private(c,eps)
    for (i=0; i<NPOINTS; i++) {
        for (j=0; j<NPOINTS; j++) {
        c.r = -2.0 + 2.5*(double)(i)/(double)(NPOINTS) + eps;
        c.i = 1.125*(double)(j)/(double)(NPOINTS) + eps;
        testpoint(); }
    }
}

void testpoint(void){
struct d_complex z = c;
int iter;
double temp;
for (iter=0; iter<MAXITER; iter++){
    temp = (z.r*z.r)-(z.i*z.i)+c.r;
    z.i = z.r*z.i*2+c.i;
    z.r = temp;
    if ((z.r*z.r+z.i*z.i)>4.0) {
        numoutside++;
        break; }
}
}

````
- Los hilos están compartiendo la variable i,j, por lo que está realizando mal el bucle y además eps no es necesario que sea privada. Se corrige mediante
```
    #pragma  omp parallel for private(i,j,c)
```
- En la función testpoint, hay inconsistencia en el acceso a numoutside ya que es global, por lo que es necesario lo siguiente
```
    #pragma omp atomic
    numoutside++;
```

## Ejercicio 2
````
int cnt = 0;
void *compute()
{
    for (i=1; i<10; i++){
        pthread_mutex_lock(&mtx);
        cnt += i;
        pthread_mutex_unlock(&mtx);}
}
int main(){
    pthread_t th;
    pthread_create(&th,NULL,compute,NULL);
    pthread_join(th,NULL)
    printf("cnt: %d\n",cnt);
}
````
- En primer lugar hay que inicializar el mutex
```
    pthread_mutex_t mtx;
    pthread_mutex_init(&mtx,NULL); //Dentro del main
```
- Además se podría mejorar con una variable privada donde acumular el la suma del hilo y realizar el mutex fuera.
```
    int cnt = 0;
    void *compute()
    {
        int cnt_local = 0;
        for (i=1; i<10; i++){
            cnt_local += i;}
        pthread_mutex_lock(&mtx);
        cnt += cnt_local;
        pthread_mutex_unlock(&mtx);
    }
```

## Ejercicio 3
````
void *compute()
{
}
int main()
{
pthread_t th1;
pthread_create(&th1,NULL,compute,NULL);
}
````
- Hay que añadir un pthread_join para que espere a que termine el hilo
```
    pthread_join(th1,NULL);
```

## Ejercicio 4
**Seleccionar respuesta correcta**
a. La asignación de las tareas a los threads NO tiene influencia en la intensidad aritmética
b. La comunicación de artefacto corresponde a los datos que necesariamente deben moverse entre los procesadores cuando se ejecuta una aplicación
c. La compartición falsa aumenta la comunicación inherente
d. La intensidad aritmética es la relación entre la cantidad de computación y la cantidad de datos que se transfieren como consecuencia

**Respuesta correcta:** d

## Ejercicio 5
**Seleccionar respuesta correcta**
a. El particionado estático por bloques siempre equilibra mejor la carga computacional que el entrelazado (cíclico)
b. La ley de Amdahl dice que una pequeña cantidad de desbalanceo de carga entre los procesadores tiene poco impacto en la aceleración (speedup)
conseguible
c. “Work-stealing” es un tipo de asignación dinámica de tareas que usa una cola de tareas centralizada
d. Con una asignación dinámica, lo mejor para conseguir un buen balanceo de carga es tener muchas más tareas que procesadores

**Respuesta correcta:** d

## Ejercicio 6
````
f = 2;
#pragma omp parallel for private(f,x)
for (i=1; i<N; i++)
{
    x = f * b[i];
    a[i] = x - 7;
}
a[0] = x;
````
- F no hace falta que sea privada y x tiene que devolver su último resultado:
```
    #pragma omp parallel for lastprivate(x)
```

## Ejercicio 7
**Seleccionar respuesta correcta**
a. La etapa de orquestación (orchestration) se encarga de asignar los threads a los procesadores
b. Un objetivo de la etapa de asignación (assignment) es el balanceo de la carga computacional entre los threads
c. Un objetivo de la descomposición (decomposition) es la explotación de la localidad de datos
d. Un objetivo de la proyección (mapping) es exponer suficiente paralelismo

**Respuesta correcta:** b

## Ejercicio 8
**Seleccionar respuesta correcta**
a. La asignación estática de tareas la realiza necesariamente el compilador
b. Cuando hay localidad de datos, es mejor un particionado estático entrelazado (cíclico) que por bloques.
c. La asignación dinámica requiere de un método de planificación de tareas en tiempo de ejecución
d. La asignación estática utiliza una cola compartida de tareas para distribuirlas entre los threads

**Respuesta correcta:** c

## Ejercicio 9
````
a[0] = 0;
#pragma omp parallel for
for (i=1; i<N; i++)
{
    a[i] = 2.0*i*(i-1);
    b[i] = a[i] - a[i-1];
}
````
- a[i-1] lo puede estar calculando otro hilo, por lo que si accedemos a él puede que no esté calculado. Por lo tanto, para solucionarlo hay que calcularlo en dos bucles:
```
    #pragma omp parallel for
    for (i=1; i<N; i++)
    {
        a[i] = 2.0*i*(i-1);
    }
    #pragma omp parallel for
    for (i=1; i<N; i++)
    {
        b[i] = a[i] - a[i-1];
    }
```

