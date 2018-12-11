#pragma once
#include <random>

class CRandomGenerator
{
public:
	CRandomGenerator(double dStart, double dEnd);

	~CRandomGenerator();

	double dNextDouble();
	int iNextInt(int iMaxRange);

private:
	std::mt19937* pc_generator;
	std::uniform_real_distribution<>* pc_distribution;
};