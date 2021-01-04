/*
ћодуль содержит определени€ методов класса MonteCarlo.
*/

#include <cmath>
#include <random>
#include <time.h>
#include <thread>
#include "monte_carlo.h"


/**
 *  онструктор по умолчанию.
 */
MonteCarlo::MonteCarlo() {}

/**
 *  онструктор инициализирует вычисление числа ѕи.
 * @param points_number: количестов случайных точек;
 * @param d: ширина стороны квадрата, внутри которого будут генерироватьс€
 * случайные точки;
 * @param threads_number: количество потоков, в которых будет вычислено
 * число ѕи.
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
 * ћетод вычисл€ет число ѕи.
 * @return: вычисленное число ѕи.
 */
double MonteCarlo::calculate_pi()
{
	return 4.0 * points_number_inside / points_number;
}

/**
 * ћетод вычисл€ет долю случайных точек внутри круга.
 * @param n: общее количество точек, которые нужно сгенерировать.
 */
void MonteCarlo::calculate_points_inside(unsigned int n)
{
	// —оздаем случайные точки
	Point* points = create_points(n);
	// ¬ычисл€ем количество точек внутри круга
	unsigned int points_inside = 0; // количество точек внутри
	for (unsigned int i = 0; i < n; i++)
	{
		if (check_inside(points[i]))
			points_inside++;
	}
	// ƒополн€ем количество точек в общем счетчике
	number_mutex.lock();
	points_number_inside += points_inside;
	number_mutex.unlock();
}

/**
 * ћетод провер€ет, находитс€ ли точка внутри круга.
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
 * ћетод запускает вычисление числа ѕи.
 * @return: вычисленное число ѕи.
 */
double MonteCarlo::run()
{
	// ќпредел€ем, сколько точек должен создать каждый поток
	//  оличество точек во всех потоках, кроме последнего
	unsigned int points_num_for_thread = points_number / threads_number;
	//  оличество точек в последнем потоке
	unsigned int points_num_for_last = points_num_for_thread + points_number -
		points_num_for_thread * threads_number;
	// —оздаем массив потоков
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
	// ¬ыполн€ем потоки
	for (unsigned int i = 0; i < threads_number; i++)
		threads[i]->join();
	// ”дал€ем потоки
	delete[] threads;
	// ¬ычисл€ем число ѕи
	return calculate_pi();
}

/**
 * ћетод генерирует случайную точку.
 * @return: координаты точки.
 */
void MonteCarlo::create_point(Point& point)
{
	point.x = d * rand() / RAND_MAX;
	point.y = d * rand() / RAND_MAX;
}

/**
 * ћетод создает заданное количество случайных точек.
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