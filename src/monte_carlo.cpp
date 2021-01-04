/*
Модуль содержит определения методов класса MonteCarlo.
*/

#include <cmath>
#include <random>
#include <time.h>
#include <thread>
#include "monte_carlo.h"


/**
 * Конструктор по умолчанию.
 */
MonteCarlo::MonteCarlo() {}

/**
 * Конструктор инициализирует вычисление числа Пи.
 * @param points_number: количестов случайных точек;
 * @param d: ширина стороны квадрата, внутри которого будут генерироваться
 * случайные точки;
 * @param threads_number: количество потоков, в которых будет вычислено
 * число Пи.
 */
MonteCarlo::MonteCarlo(unsigned int points_number, double d,
	unsigned int threads_number = 1)
{
	srand((unsigned int)time(NULL));
	this->d = d;
	this->points_number = points_number;
	this->threads_number = threads_number;
	points_number_inside = 0;
}

/**
 * Метод вычисляет число Пи.
 * @return: вычисленное число Пи.
 */
double MonteCarlo::calculate_pi()
{
	return 4.0 * points_number_inside / points_number;
}

/**
 * Метод вычисляет долю случайных точек внутри круга.
 * @param n: общее количество точек, которые нужно сгенерировать.
 */
void MonteCarlo::calculate_points_inside(unsigned int n)
{
	// Создаем случайные точки
	Point* points = create_points(n);
	// Вычисляем количество точек внутри круга
	unsigned int points_inside = 0; // количество точек внутри
	for (unsigned int i = 0; i < n; i++)
	{
		if (check_inside(points[i]))
			points_inside++;
	}
	// Освобождаем память, выделенную для массива точек
	delete[] points;
	// Дополняем количество точек в общем счетчике
	number_mutex.lock();
	points_number_inside += points_inside;
	number_mutex.unlock();
}

/**
 * Метод проверяет, находится ли точка внутри круга.
 * @param point: точка.
 * @return: true, если точка внутри круга, иначе false.
 */
bool MonteCarlo::check_inside(Point& point)
{
	if (pow(point.x - d / 2, 2) + pow(point.y - d / 2, 2) > d * d / 4)
		return false;
	return true;
}

/**
 * Метод запускает вычисление числа Пи.
 * @return: вычисленное число Пи.
 */
double MonteCarlo::run()
{
	// Определяем, сколько точек должен создать каждый поток
	// Количество точек во всех потоках, кроме последнего
	unsigned int points_num_for_thread = points_number / threads_number;
	// Количество точек в последнем потоке
	unsigned int points_num_for_last = points_num_for_thread + points_number -
		points_num_for_thread * threads_number;
	// Создаем массив потоков
	std::thread** threads = new std::thread * [threads_number];
	for (unsigned int i = 0; i < threads_number; i++)
	{
		unsigned int n;
		if (i != threads_number - 1)
			n = points_num_for_thread;
		else
			n = points_num_for_last;
		threads[i] = new std::thread(&MonteCarlo::calculate_points_inside,
			this, n);
	}
	// Выполняем потоки
	for (unsigned int i = 0; i < threads_number; i++)
		threads[i]->join();
	// Удаляем потоки
	for (unsigned int i = 0; i < threads_number; i++)
		delete threads[i];
	delete[] threads;
	// Вычисляем число Пи
	return calculate_pi();
}

/**
 * Метод генерирует случайную точку.
 * @return: координаты точки.
 */
void MonteCarlo::create_point(Point& point)
{
	point.x = d * rand() / RAND_MAX;
	point.y = d * rand() / RAND_MAX;
}

/**
 * Метод создает заданное количество случайных точек.
 * @param n: требуемое количество точек.
 * @return: массив созданных точек.
 */
Point* MonteCarlo::create_points(unsigned int n)
{
	Point* points = new Point[n];
	for (unsigned int i = 0; i < n; i++)
		create_point(points[i]);
	return points;
}