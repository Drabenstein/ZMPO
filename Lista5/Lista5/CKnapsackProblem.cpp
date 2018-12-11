#include "pch.h"
#include "CKnapsackProblem.h"

CKnapsackProblem::CKnapsackProblem(std::vector<CSubject*>& pvSubjects,
	int iPopSize, double dMutationProb, double dCrossoverProb, double dMaxSize, int iIterations)
	: CProblem(iPopSize)
{
	i_iterations = iIterations < NULL ? NULL : iIterations;
	d_max_size = dMaxSize < NULL ? NULL : dMaxSize;
	d_mutation_probability = dMutationProb;
	d_crossover_probability = dCrossoverProb;
	pc_algorithm = new CGeneticAlgorithm(this, dMutationProb, dCrossoverProb, iIterations);

	for(int i = 0; i < pvSubjects.size(); i++)
	{
		v_subjects.push_back(pvSubjects[i]);
	}
} // CKnapsackProblem::CKnapsackProblem(CGeneticAlgorithm* pcAlgorithm, std::vector<CSubject*>& pvSubjects, int iPopSize, double dMutationProb, double dCrossoverProb, double dMaxSize, int iIterations)	: CProblem(pcAlgorithm, iPopSize)

CKnapsackProblem::~CKnapsackProblem()
{
	delete pc_algorithm;
} // CKnapsackProblem::~CKnapsackProblem()

int CKnapsackProblem::iGetGenotypeLength()
{
	return v_subjects.size();
} // int CKnapsackProblem::iGetGenotypeLength()

bool CKnapsackProblem::bCalculateFitness(double& dResult, const std::vector<int>& rvGenotype)
{
	if (rvGenotype.size() != v_subjects.size())
	{
		dResult = 0.0;
		return false;
	}

	double d_fitness = 0.0;
	double d_size = 0.0;

	for (int i = 0; i < rvGenotype.size(); i++)
	{
		d_fitness += rvGenotype[i] * v_subjects[i]->dGetValue();
		d_size += rvGenotype[i] * v_subjects[i]->dGetSize();
	} // for (int i = 0; i < rvGenotype.size(); i++)

	dResult = d_size > d_max_size ? 0.0 : d_fitness;
	return true;
} // bool CKnapsackProblem::bCalculateFitness(double & dResult, const std::vector<int>& rvGenotype)

bool CKnapsackProblem::bStartAlgorithm()
{
	if (pc_algorithm == nullptr)
	{
		return false;
	}

	return pc_algorithm->bRun();
} // bool CKnapsackProblem::bStartAlgorithm()

void CKnapsackProblem::vSetAlgorithm(CGeneticAlgorithm * pcAlgorithm)
{
	delete pc_algorithm;
	pc_algorithm = pcAlgorithm;
} // void CKnapsackProblem::vSetAlgorithm(CGeneticAlgorithm * pcAlgorithm)

const std::vector<int>* CKnapsackProblem::pvGetBestResult()
{
	if(pc_algorithm != nullptr)
	{
		return pc_algorithm->pvGetBestResult();
	}
	else
	{
		return nullptr;
	}
} // const std::vector<int>* CKnapsackProblem::pvGetBestResult()
