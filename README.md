# MonteCarloPi
[![Build Status](https://travis-ci.com/timerke/MonteCarloPi.svg?branch=main)](https://travis-ci.com/timerke/MonteCarloPi)

Calculation of `π` number by the Monte Carlo method. Multithreading is used

## Task
Write a program for the approximate calculation of the `π` number by the Monte Carlo method.

To do this, generate `M` pairs of random numbers in the range `[0, D]`. Use them like coordinates of points on the plane. Count how many points `N` fall into the circle inscribed in a square with side `D` (a circle centered in coordinates `(D/2, D/2)` and diameter `D`). The ratio of the areas of a circle and a square will tend to the ratio the number of points in the circle to the total number of points. The area of a circle is `S1 = πD^2/4`, the area of a square is `S2 = D^2`. So we can estimate the value of `π` as: `N/M = S1/S2 = π/4 -> π = 4N/M`.

Demonstrate results for different values of `M` and `D`. Use multithreaded implementation for different numbers of parallel threads.

## Задание
Написать программу для приближенного вычисления числа `π` методом Монте-Карло.

Для этого сгенерировать `M` пар случайных чисел в диапазоне `[0, D]`. Используя их как координаты точек на плоскости, посчитать сколько точек `N`, которые попадают в круг,
вписанный в квадрат со стороной `D` (круг с центром в координатах `(D/2, D/2)` и диаметром `D`). Отношение площадей круга и квадрата будет стремиться к отношению количества точек, попавших в круг, к общему количеству точек. Согласно формуле для площади круга `S1 = πD^2/4`, можно оценить значение `π` как `4N/M`.

Продемонстрировать результаты для разных значений `M` и `D`. При многопоточной реализации дополнительный параметр `T` — количество параллельных потоков. При выводе результата также указывать время вычислений. Показать значения времени для разного количества потоков.
