# Actividad 02 - Maching Learning
- Christian Marroquin
- Julian Medina Rosero
# Actividad
- Calcular la diferencia entre dos imagenes similares y encontrar cuales son sus diferencias.
## resultado

|imagen izquierda|imagen derecha|diferencia|
|-|-|-|
|![left](res/left.png)|![rigth](res/right.png)|![diff](res/difference.png)|

- Calcular la convolucion de la imagen de la izquierda con los diferentes objetos.

|kernel|convolucion|
|-|-|
|![kernel 1](res/Object-1.png)|![convolucion 1](res/convolution-1.png)|
|![kernel 2](res/Object-2.png)|![convolucion 2](res/convolution-2.png)|
|![kernel 3](res/Object-3.png)|![convolucion 3](res/convolution-3.png)|
|![kernel 4](res/Object-4.png)|![convolucion 4](res/convolution-4.png)|
|![kernel 5](res/Object-5.png)|![convolucion 5](res/convolution-5.png)|

Ademas de la tarea se hizo un metodo para encontrar los objetos en la imagen de la izquierda usando la desviacion estandar.

|kernel|desviacion estandar|lugar|
|-|-|-|
|![kernel 1](res/Object-1.png)|![search 1](res/search-1.png)|248,367|
|![kernel 2](res/Object-2.png)|![search 2](res/search-2.png)|285,248|
|![kernel 3](res/Object-3.png)|![search 3](res/search-3.png)|415,806|
|![kernel 4](res/Object-4.png)|![search 4](res/search-4.png)|624,275|
|![kernel 5](res/Object-5.png)|![search 5](res/search-5.png)|365,511|

Para la imagen a color el resultado de la busqueda es la siguiente:
![busqueda color](res/places_image.png)

y para la imagen en escala de grises es la siguiente:
![busqueda color](res/places_image_gray.png)

- Realizar un mapa conceptual.

- El [codigo](src/main.c).
