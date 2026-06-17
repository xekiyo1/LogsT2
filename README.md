# Tarea 2 Diseño y Análisis de Algoritmos: árboles AVL y "SplayTree"-s

El presente programa ejecuta pruebas de rendimiento para dos algoritmos de árboles de búsqueda binaria.
El objetivo del proyecto es la comparación en tiempo de construcción y de búsqueda de ambos algoritmos para una serie de números
aleatorios, ya sean a elección uniforme o sesgada, con tal de encontrar los casos en donde cada árbol funciona mejor.


## Requisitos

- Se requiere un sistema operativo basado en Unix que cuente con los siguientes comandos/librerias
    + grep
    + ls
    + rm
    + gcc (version >= 11.4)
    + xargs (version >= 4.8.0)
    + chmod
    + make
    + test

## Correr el programa
Para correr la tarea, basta con ir al directorio desde una terminal y correr

```bash
make run 
```

Esto producirá un archivo .csv con los tiempos obtenidos de la creación y búsqueda de los árboles,
mientras imprime en tiempo real en qué fase del experimento va. El archivo contiene los resultados
en una lista que indica el tamaño del dataset (N) y la cantidad de búsquedas (M) por lo que se requiere
un


El código está difícil de leer (principalmente en las rotaciones) por lo que si se necesita ayuda de confianza
en la implementación, se hicieron tests de rotaciones en src/main/test.cpp. Para correrlos, usar:

``` bash
make test
```

```text
⣿⣿⣿⣿⣿⣿⠟⠁⠈⢻⣿⣿⣿⣿⣿⣿⣿⣿⡿⠿⣿⣿⣿⣿
⣿⣿⣿⣿⣿⡏⠂⠂⠂⠂⢙⠛⠙⠛⠻⢿⠟⠁⠂⠂⠸⣿⣿⣿
⣿⣿⣿⡿⠟⠂⠂⠂⠂⠂⠂⠂⠂⠂⠂⠂⠂⠂⠂⠂⠂⣿⣿⣿
⣿⡿⢋⣴⣤⣀⣀⣀⣀⣠⣤⣾⣷⣤⣀⠂⠂⠂⠂⠂⠂⢿⣿⣿
⣿⢁⣿⣿⣿⣿⣿⣿⣯⣽⣿⣿⣿⣿⣟⣿⣶⣦⣤⣤⣤⣦⠹⣿
⡇⣼⣿⣿⣿⣿⣿⢋⣭⠹⣿⣿⣿⣿⠟⡛⢿⣿⣿⣿⣿⣿⣇⢸
⠁⣿⣿⡟⡛⠛⢿⣄⣂⣴⣿⣿⣿⣿⡀⠉⢠⣿⣿⣿⣿⣿⣿⠂
⡇⢻⣿⣷⣿⣿⣾⣿⣿⣿⣙⠁⠛⣻⣿⣿⣣⣃⢉⢹⣿⣿⡟⢸
⣿⡌⢻⣿⣿⣿⣿⣿⣿⣿⣿⣍⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⢁⣾
⣿⡘⠦⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠟⣡⣾⣿
```
^ imagen increíble! (esta figura no es relevante a la ejecución y solo representa una bonificación de apoyo moral para terminar el semestre)