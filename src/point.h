/*
Заголовочный файл для класса Point для работы с точками на плоскости.
*/

#pragma once
#ifndef POINT_H
#define POINT_H


/**
 * Класс для точек на плоскости.
 */
class Point
{
public:
	double x; // координата x точки
	double y; // координата y точки

	// Конструктор по умолчанию
	Point();
	// Конструктор инициализирует точку
	Point(double, double);
};

#endif // !POINT_H
