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

|kernel|desviacion estandar|lugar|
|-|-|-|
|![kernel 1](res/Object-1.png)|![search 1](res/search-1.png)|248,367|
|![kernel 2](res/Object-2.png)|![search 2](res/search-2.png)|285,248|
|![kernel 3](res/Object-3.png)|![search 3](res/search-3.png)|415,806|
|![kernel 4](res/Object-4.png)|![search 4](res/search-4.png)|624,275|
|![kernel 5](res/Object-5.png)|![search 5](res/search-5.png)|365,511|

- Realizar un mapa conceptual.

```mermaid
graph TD
    %% Estilos de los nodos
    classDef main fill:#2b5c8f,stroke:#1e3f63,stroke-width:2px,color:#fff,font-weight:bold
    classDef section fill:#38761d,stroke:#275214,stroke-width:2px,color:#fff,font-weight:bold
    classDef concept fill:#444,stroke:#222,stroke-width:1px,color:#fff
    classDef detail fill:#222,stroke:#444,stroke-width:1px,color:#ddd

    A[Manejo de Imágenes mediante Matrices] :::main

    %% Rama 1: Representación
    A --> B[1. Representación Matricial] :::section
    B --> B1[Estructura bidimensional: M x N] :::concept
    B --> B2[Canales de Color] :::concept
    
    B1 --> B1a[Filas = Alto / Columnas = Ancho] :::detail
    B1 --> B1b[Píxel = Elemento A_ij] :::detail
    
    B2 --> B2a[Escala de Grises: 1 canal (0-255)] :::detail
    B2 --> B2b[RGB: 3 canales (R, G, B)] :::detail
    B2 --> B2c[RGBA: 4 canales (+ Transparencia)] :::detail

    %% Rama 2: Operaciones
    A --> C[2. Operaciones Matriciales] :::section
    C --> C1[Transformaciones Puntuales] :::concept
    C --> C2[Filtros y Convolución] :::concept
    C --> C3[Transformaciones Geométricas] :::concept

    C1 --> C1a[Brillo: Suma de constante] :::detail
    C1 --> C1b[Contraste: Multiplicación escalar] :::detail
    C1 --> C1c[Inversión: 255 - Píxel] :::detail

    C2 --> C2a[Kernel/Máscara: Matriz pequeña K] :::detail
    C2 --> C2b[Operación: Suma de productos locales] :::detail
    C2 --> C2c[Ejemplos: Detección de bordes, Desenfoque] :::detail

    C3 --> C3a[Matrices de Transformación Afín] :::detail
    C3 --> C3b[Rotación, Escalado, Traslación] :::detail

    %% Rama 3: Procesamiento
    A --> D[3. Procesamiento y Análisis] :::section
    D --> D1[Dominio Frecuencial] :::concept
    D --> D2[Álgebra Lineal Aplicada] :::concept

    D1 --> D1a[Transformada Discreta de Fourier - DFT] :::detail
    D1 --> D1b[Compresión y Filtrado de Ruido] :::detail

    D2 --> D2a[SVD / Descomposición en Valores Singulares] :::detail
    D2 --> D2b[Reducción de Dimensionalidad y Compresión] :::detail
```


- El [codigo](src/main.c).
