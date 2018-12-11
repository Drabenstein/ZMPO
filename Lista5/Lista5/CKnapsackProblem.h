#pragma once
#include "CProblem.h"
#include "CSubject.h"

class CKnapsackProblem : public CProblem
{
public:
	CKnapsackProblem(std::vector<CSubject*>& pvSubjects, int iPopSize, double dMutationProb, 
		double dCrossoverProb, double dMaxSize, int iIterations);

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
};