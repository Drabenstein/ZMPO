#pragma once
#include "CProblem.h"
#include "CSubject.h"

class CKnapsackProblem : public CProblem
{
public:
	static const double MIN_PROBABILITY;
	static const double MAX_PROBABILITY;
	static const double DEFAULT_MUTATION_PROBABILITY;
	static const double DEFAULT_CROSSOVER_PROBABILITY;
	static const double MIN_MAX_SIZE;
	static const int MIN_POP_SIZE;
	static const int MIN_ITERATIONS;
	static const int MIN_TOURNAMENT_SIZE;

	CKnapsackProblem(std::vector<CSubject*>& pvSubjects, int iPopSize, int iTournamentSize, 
		double dMutationProb, double dCrossoverProb, double dMaxSize, int iIterations, int& riErrorCode);

	~CKnapsackProblem();

	int iGetGenotypeLength() override;
	bool bCalculateFitness(double& dResult, const std::vector<int>& rvGenotype) override;
	bool bStartAlgorithm();

	void vSetAlgorithm(CGeneticAlgorithm* pcAlgorithm);
	const std::vector<int>* pvGetBestResult();

private:
	double d_mutation_probability;
	double d_crossover_probability;
	double d_max_size;
	int i_iterations;
	std::vector<CSubject*> v_subjects;
	CGeneticAlgorithm* pc_algorithm;

	bool b_is_probability_correct(double dProbability);
	int i_validate_parameters();
};