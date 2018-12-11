#include "pch.h"
#include "CRandomGenerator.h"

CRandomGenerator::CRandomGenerator(double dStart, double dEnd)
{
	std::random_device c_device;
	pc_generator = new std::mt19937(c_device());
	pc_distribution = new std::uniform_real_distribution<>(dStart, dEnd);
} // CRandomGenerator(double dStart, double dEnd)

CRandomGenerator::~CRandomGenerator()
{
	delete pc_generator;
	delete pc_distribution;
} // CRandomGenerator::~CRandomGenerator()

double CRandomGenerator::dNextDouble()
{
	return (*pc_distribution)(*pc_generator);
} // double dNextRandom()

int CRandomGenerator::iNextInt(int iMaxRange)
{
	return (*pc_generator)() % iMaxRange;
} // int CRandomGenerator::iNextInt(int iMaxRange)
