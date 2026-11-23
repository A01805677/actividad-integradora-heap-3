# actividad-integradora-heap-3
En equipos hacer una aplicación que:

Abra el archivo de entrada resultado de la actividad integradora anterior (ordenado a partir de la IP destino).
Cuente el número de veces que aparece cada IP destino y almacene ambos datos (IP y número de accesos) en un vector de std::pair.
Considera que el archivo ya está ordenado por IP destino, por lo que todos los eventos con la misma IP destino deberán aparecer uno después de otro.
Convierta el vector en un heap, donde la prioridad sea determinada por el número de accesos (entre más accesos, más prioridad).
Utiliza la función make_heap de la librería algorithm.
La función determina la prioridad a través del uso del operador < o mediante una función de comparación provista.
Sobrecarga el operador < para objetos de tipo std::pair<ip, int>.
Pide al usuario un valor numérico N y despliega las N IPs con el mayor número de accesos.
Utiliza la función pop_heap de la librería algorithm.
Revisa bien la documentación de este método, pues su uso involucra también usar las funciones front y pop_back de vector.
