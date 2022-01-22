# Base-T1-2021-2
Código base para tu tarea 2.

## Compilar y ejecutar
Compilar:
```make```

Compilar desde cero:
```make clean && make```

Ejecutar:
```./potterphoto <A/B> <input.png> <output.png>```

El parámetro ```<A/B>``` Indica si el test corresponde a de Hashing o Backtracking respectivamente. El codigo base incluye la deteccion de esto, sin embargo el resto de lectura de archivo lo tienes que realizar tu

Para optimizar el tiempo de ejecucion de tarea, puedes modificar el Makefile cambiando el -g por -O2

# Backtracking

Para la implementacion del codigo de backtracking, se uso como base un algoritmo para el problema de:
### The Knight’s tour problem
Esto se hizo para tomar la estructura base del algoritmo de backtracking, para luego de esto adapatarlo al problema especifico solicitado, esto se encuentra en el archivo de back_functions.c. El algoritmo, que de base fue sacado es el siguiente [link](https://www.codesdope.com/course/algorithms-knights-tour-problem/)