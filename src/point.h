/*
«аголовочный файл дл€ класса Point дл€ работы с точками на плоскости.
*/

#pragma once
#ifndef POINT_H
#define POINT_H


/**
 *  ласс дл€ точек на плоскости.
 */
class Point
{
public:
	double x; // координата x точки
	double y; // координата y точки

	//  онструктор по умолчанию
	Point();
	//  онструктор инициализирует точку
	Point(double, double);
};

#endif // !POINT_H
