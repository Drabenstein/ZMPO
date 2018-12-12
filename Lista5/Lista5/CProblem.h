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
	virtual int iGetTournamentSize() { return i_tournament_size; }

protected:
	int i_population_size;
	int i_tournament_size;

	CProblem(int iPopulationSize, int iTournamentSize)
		: i_population_size(iPopulationSize), i_tournament_size(iTournamentSize) {}
};