/*
Заголовочный файл с классом MonteCarlo для вычисления числа Пи.
*/

#pragma once
#ifndef MONTE_CARLO_H
#define MONTE_CARLO_H

#include <mutex>
#include "point.h"


/**
 * Класс для вычисления числа Пи методом Монте-Карло.
 */
class MonteCarlo
{
private:
	double d; // ширина стороны квадрата
	unsigned int points_number; // количество случайных точек
	unsigned int points_number_inside; // количество точек внутри круга
	unsigned int threads_number; // количество потоков
	std::mutex number_mutex; // мьютекс для записи общего количества точек
	// внутри круга

	// Метод вычисляет число Пи
	double calculate_pi();
	// Метод вычисляет долю случайных точек внутри круга
	void calculate_points_inside(unsigned int);
	// Метод проверяет, находится ли точка внутри круга
	bool check_inside(Point&);
	// Метод генерирует случайную точку
	void create_point(Point&);
	// Метод создает заданное количество точек
	Point* create_points(unsigned int);

public:
	// Конструктор по умолчанию
	MonteCarlo();
	// Конструктор инициализирует вычисление числа Пи
	MonteCarlo(unsigned int, double, unsigned int);
	// Метод запускает вычисление числа Пи
	double run();
};

#endif // !MONTE_CARLO_H