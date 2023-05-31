# Задание 6: Каркасная модель
Во входном файле задано описание 3d-сцены в формате `.obj` необходимо построить проекции каркасной модели на координатные плоскости 
и получить три изображения заданного размера.

Размеры изображения и имя входного файла задаются аргументами командной строки. Например, 
```
wireframe width height input.obj
```
читает данные из файла *input.obj* и сохраняет три изображения в BMP-файлах *input.obj.Oxy.bmp*, *input.obj.Oxz.bmp*, *input.obj.Oyz.bmp*.

Описание модели содержит вершины и полигоны (из вершин). Необходимо отрисовать каждый полигон.

При отображении проекции необходимо учитывать, что пространственные координаты не соответствуют координатам на изображении и необходимо делать преобразование.
Например, для проекции на плоскость Oxy точка с координатами `(min(x), max(y))` соответствует точке на изображении с координатами `(10,10)`,
а точка с координатами `(max(x), min(y))` соответствует точке на изображении с координатами `(width-10, height-10)`.
Здесь `min(x)` — минимальная из координат x всех точек из 3d-сцены, `max(x)` — максимальная.


## Формат входного файла
Входной файл в формате .obj ([wavefront .obj file](https://en.wikipedia.org/wiki/Wavefront_.obj_file)).

Для данной задачи необъодимо использовать только часть объектов определенных в obj-файл: вершины и полигоны. Строки, соответствующие, другим объектам игнорировать.

Символ `#` используется для обозначения комментария (от символа до конца строки).

Строка вида `v x y z w` (то есть когда строка начинается с `v `) задает однородные координаты вершины x, y, z, w.

Строка вида `v x y z` задает декартовы координаты вершины x, y, z.

Все решины нумеруются по порядку, начиная с 1.

Строка вида `f v1 v2 v3 ....` (то есть когда строка начинается с `f `) задает полигон с вершинами v1, v2, v3 и т.д. Каждый полигон может быть задан тремя или более вершинами.

Другие строки в задании игнорировать. Например, строка вида `vn i j k` задает вектор нормали с координатами i, j, k. Все вектора нумеруются по порядку, начиная с 1. Но в данном задании эта информация не нужна.


## Подключаемые библиотеки
Необходимые конструкции вынесены в файл *rgbimage.h*

Класс `rgbImg` позволяет создавать переменные для работы с изображениями:
* конструктор зависит от двух аргументов `(unsigned int width, unsigned int height)` и позволяет задать изображение заданных размеров;
* метод `width()` позволяет определить ширину изображения;
* метод `height()` позволяет определить высоту изображения;
* метод `get(column, row)`, зависящий от двух аргументов типа unsigned int, позволяет получить значение цвета пикселя в заданном столбце (column) и строке (row), может использоваться как l-value и как r-value;
* метод `save(const char* filename)` позволяет сохранить изображение в файле формата BMP с заданным именем `filename`.

Цвет пикселя задан в модели RGB и определен как структура RGB с тремя полями: Red, Green, Blue.

## Тестирование
В папке tests приведены примеры входных файлов (\*.obj).