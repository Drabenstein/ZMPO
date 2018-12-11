#pragma once
#include "CGeneticAlgorithm.h"
#include <vector>

class CProblem
{
public:
	virtual ~CProblem() {};

	virtual bool bCalculateFitness(double& dResult, const std::vector<int>& rvGenotype) = 0;
	int iGetPopulationSize() { return i_population_size; };
	virtual int iGetGenotypeLength() = 0;

protected:
	int i_population_size;

	CProblem(int iPopulationSize)
		: i_population_size(iPopulationSize) {}
};