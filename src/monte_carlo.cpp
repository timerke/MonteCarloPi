/*
������ �������� ����������� ������� ������ MonteCarlo.
*/

#include <cmath>
#include <random>
#include <time.h>
#include <thread>
#include "monte_carlo.h"


/**
 * ����������� �� ���������.
 */
MonteCarlo::MonteCarlo() {}

/**
 * ����������� �������������� ���������� ����� ��.
 * @param points_number: ���������� ��������� �����;
 * @param d: ������ ������� ��������, ������ �������� ����� ��������������
 * ��������� �����;
 * @param threads_number: ���������� �������, � ������� ����� ���������
 * ����� ��.
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
 * ����� ��������� ����� ��.
 * @return: ����������� ����� ��.
 */
double MonteCarlo::calculate_pi()
{
	return 4.0 * points_number_inside / points_number;
}

/**
 * ����� ��������� ���� ��������� ����� ������ �����.
 * @param n: ����� ���������� �����, ������� ����� �������������.
 */
void MonteCarlo::calculate_points_inside(unsigned int n)
{
	// ������� ��������� �����
	Point* points = create_points(n);
	// ��������� ���������� ����� ������ �����
	unsigned int points_inside = 0; // ���������� ����� ������
	for (unsigned int i = 0; i < n; i++)
	{
		if (check_inside(points[i]))
			points_inside++;
	}
	// ��������� ���������� ����� � ����� ��������
	number_mutex.lock();
	points_number_inside += points_inside;
	number_mutex.unlock();
}

/**
 * ����� ���������, ��������� �� ����� ������ �����.
 * @param point: �����.
 * @return: true, ���� ����� ������ �����, ����� false.
 */
bool MonteCarlo::check_inside(Point& point)
{
	if (pow(point.x - d / 2, 2) + pow(point.y - d / 2, 2) > d * d / 4)
		return false;
	return true;
}

/**
 * ����� ��������� ���������� ����� ��.
 * @return: ����������� ����� ��.
 */
double MonteCarlo::run()
{
	// ����������, ������� ����� ������ ������� ������ �����
	// ���������� ����� �� ���� �������, ����� ����������
	unsigned int points_num_for_thread = points_number / threads_number;
	// ���������� ����� � ��������� ������
	unsigned int points_num_for_last = points_num_for_thread + points_number -
		points_num_for_thread * threads_number;
	// ������� ������ �������
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
	// ��������� ������
	for (unsigned int i = 0; i < threads_number; i++)
		threads[i]->join();
	// ������� ������
	delete[] threads;
	// ��������� ����� ��
	return calculate_pi();
}

/**
 * ����� ���������� ��������� �����.
 * @return: ���������� �����.
 */
void MonteCarlo::create_point(Point& point)
{
	point.x = d * rand() / RAND_MAX;
	point.y = d * rand() / RAND_MAX;
}

/**
 * ����� ������� �������� ���������� ��������� �����.
 * @param n: ��������� ���������� �����.
 * @return: ������ ��������� �����.
 */
Point* MonteCarlo::create_points(unsigned int n)
{
	Point* points = new Point[n];
	for (unsigned int i = 0; i < n; i++)
		create_point(points[i]);
	return points;
}