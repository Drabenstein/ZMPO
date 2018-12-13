#pragma once
#include "CProblem.h"
#include "CIndividual.h"
#include "CRandomGenerator.h"

class CIndividual;
class CProblem;

class CGeneticAlgorithm
{
public:
	static const double MIN_PROBABILITY;
	static const double MAX_PROBABILITY;
	static const double DEFAULT_MUTATION_PROBABILITY;
	static const double DEFAULT_CROSSOVER_PROBABILITY;
	static const int GEN_TYPES_COUNT;
	static const int MIN_ITERATIONS;

	CGeneticAlgorithm(CProblem* pcProblem, double dMutationProb, double dCrossoverProb, int iIterationNum);

	~CGeneticAlgorithm();

	bool bRun();
	const std::vector<int>* pvGetBestResult();
	bool bSetMutationProbability(double dProbability);
	bool bSetCrossoverProbability(double dProbability);
	bool bSetIterations(int iIterations);

private:
	CProblem* pc_problem;
	double d_mutation_probability;
	double d_crossover_probability;
	int i_iterations_max;
	std::vector<CIndividual*> v_population;
	CRandomGenerator* pc_random;

	CIndividual* pc_create_individual();
	bool b_crossover(std::vector<CIndividual*>& rvNewPopulation);
	CIndividual* pc_run_tournament();
	void v_mutatation();
	void v_clear_population(std::vector<CIndividual*>& rvPopulationToDel);
	bool b_is_probability_correct(double dProbability);

	void v_mutation_inversion();
};
