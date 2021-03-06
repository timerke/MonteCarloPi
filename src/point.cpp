﻿/*
Модуль содержит определение методов класса Point.
*/

#include "point.h"


/**
 * Конструктор по умолчанию.
 */
Point::Point() {}

/**
 * Конструктор инициализирует точку.
 * @param x, y: координаты точки.
 */
Point::Point(double x, double y) : x(x), y(y) {}