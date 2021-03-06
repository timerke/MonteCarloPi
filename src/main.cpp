﻿/*
Задача 3.
Написать программу для приближенного вычисления числа «Пи» методом Монте-Карло.
Для этого сгенерировать M пар случайных чисел в диапазоне [0; D]. Используя их
как координаты точек на плоскости, посчитать сколько точек N, которые попадают
в круг, вписанный в квадрат со стороной D (круг с центром в координатах
(D/2, D/2) и диаметром D). Отношение площадей круга и квадрата будет стремиться
к отношению количества точек, попавших в круг, к общему количеству точек.
Согласно формуле для площади круга SΟ = πD^2/4, можно оценить значение π как
4N/M. Продемонстрировать результаты для разных значений M и D. При
многопоточной реализации дополнительный параметр T — количество параллельных
потоков. При выводе результата также указывать время вычислений. Показать
значения времени для разного количества потоков. Сделать выводы.
*/

#include <iostream>
#include "monte_carlo.h"


int main()
{
	setlocale(LC_ALL, "Rus");
	// Количество случайных точек, которые нужно сгенерировать
	const unsigned int POINTS_NUMBER = 10000000;
	// Сторона квадрата, внутри которого будут генерироваться точки
	double D = 5.0;

	// Вычисляем число Пи с разным количеством потоков
	for (unsigned int threads_number = 1; threads_number < 6; threads_number++)
	{
		MonteCarlo monte_carlo(POINTS_NUMBER, D, threads_number);
		clock_t t_start = clock();
		std::cout << "Число Пи с " << threads_number << " потоками: " <<
			monte_carlo.run() << "\n";
		clock_t t = clock() - t_start;
		std::cout << "Время выполнения: " << 1.0 * t / CLOCKS_PER_SEC <<
			"\n\n";
	}
	return 0;
}
