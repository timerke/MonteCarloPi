/*
������������ ���� ��� ������ Point ��� ������ � ������� �� ���������.
*/

#pragma once
#ifndef POINT_H
#define POINT_H


/**
 * ����� ��� ����� �� ���������.
 */
class Point
{
public:
	double x; // ���������� x �����
	double y; // ���������� y �����

	// ����������� �� ���������
	Point();
	// ����������� �������������� �����
	Point(double, double);
};

#endif // !POINT_H
