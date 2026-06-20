# Tarea 2 Diseño y Análisis de Algoritmos: árboles AVL y "SplayTree"-s

El presente programa ejecuta pruebas de rendimiento para dos algoritmos de árboles de búsqueda binaria.
El objetivo del proyecto es la comparación en tiempo de construcción y de búsqueda de ambos algoritmos para una serie de números
aleatorios, ya sean a elección uniforme o sesgada, con tal de encontrar los casos en donde cada árbol funciona mejor.


## Requisitos

- Se requiere un sistema operativo basado en Unix que cuente con los siguientes comandos/librerias
    + gcc (version >= 16.1.1)
    + make

## Correr el programa
Para correr la tarea, basta con ir al directorio desde una terminal y correr

```bash
make run 
```

Esto producirá un archivo _resultados.csv_ con los tiempos obtenidos de la creación y búsqueda de los árboles,
mientras imprime en tiempo real en qué fase del experimento va. El archivo contiene los resultados
en una lista que indica el tamaño del dataset (N) y la cantidad de búsquedas (M).


Luego, se realizan los experimentos largos que buscan verificar los teoremas de acceso secuencial y grupo de trabajo.
Estos se guardarán en el archivo teoremas.csv.


La segunda fase del experimento es larga, por lo que se realiza en un paso separado. Es decir, si se interrumpe la
ejecución una vez comience el segundo experimento, para ese entonces el primero ya habrá generado sus resultados
en el archivo correspondiente.

### Experimento bonus
Finalmente, para correr el experimento de bonificación, se puede usar
``` bash
make run-bonus
```
Lo cual guardará los resultados en bonus.csv.

Y alternativamente, para correrlo en conjunto al resto:
``` bash
make run-all
```

El código está difícil de leer (principalmente en las rotaciones) por lo que si se necesita ayuda de confianza
en la implementación, se hicieron tests de rotaciones en src/main/test.cpp. Para correrlos, usar:

``` bash
make test
```
¡Eso es todo!



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


(además si la borras el código tomará $O(N^{67})$ en correr, o eso dicen.)