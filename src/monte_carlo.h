/*
������������ ���� � ������� MonteCarlo ��� ���������� ����� ��.
*/

#pragma once
#ifndef MONTE_CARLO_H
#define MONTE_CARLO_H

#include <mutex>
#include "point.h"


/**
 * ����� ��� ���������� ����� �� ������� �����-�����.
 */
class MonteCarlo
{
private:
	double d; // ������ ������� ��������
	unsigned int points_number; // ���������� ��������� �����
	unsigned int points_number_inside; // ���������� ����� ������ �����
	unsigned int threads_number; // ���������� �������
	std::mutex number_mutex; // ������� ��� ������ ������ ���������� �����
	// ������ �����

	// ����� ��������� ����� ��
	double calculate_pi();
	// ����� ��������� ���� ��������� ����� ������ �����
	void calculate_points_inside(unsigned int);
	// ����� ���������, ��������� �� ����� ������ �����
	bool check_inside(Point&);
	// ����� ���������� ��������� �����
	void create_point(Point&);
	// ����� ������� �������� ���������� �����
	Point* create_points(unsigned int);

public:
	// ����������� �� ���������
	MonteCarlo();
	// ����������� �������������� ���������� ����� ��
	MonteCarlo(unsigned int, double, unsigned int);
	// ����� ��������� ���������� ����� ��
	double run();
};

#endif // !MONTE_CARLO_H