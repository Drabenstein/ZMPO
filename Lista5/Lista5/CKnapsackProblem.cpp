#include "pch.h"
#include "CKnapsackProblem.h"
#include "KnapsackProblemErrorCodes.h"

const double CKnapsackProblem::MIN_PROBABILITY = 0.0;
const double CKnapsackProblem::MAX_PROBABILITY = 1.0;
const double CKnapsackProblem::DEFAULT_MUTATION_PROBABILITY = 0.1;
const double CKnapsackProblem::DEFAULT_CROSSOVER_PROBABILITY = 0.6;
const double CKnapsackProblem::MIN_MAX_SIZE = 0.0;
const int CKnapsackProblem::MIN_POP_SIZE = 4;
const int CKnapsackProblem::MIN_ITERATIONS = 1;
const int CKnapsackProblem::MIN_TOURNAMENT_SIZE = 2;

CKnapsackProblem::CKnapsackProblem(std::vector<CSubject*>& pvSubjects, int iPopSize, int iTournamentSize,
	double dMutationProb, double dCrossoverProb, double dMaxSize, int iIterations, int& riErrorCode)
	: CProblem(iPopSize, iTournamentSize)
{
	i_iterations = iIterations;
	d_max_size = dMaxSize;
	d_mutation_probability = dMutationProb;
	d_crossover_probability = dCrossoverProb;
	pc_algorithm = nullptr;

	riErrorCode = i_validate_parameters();

	for(int i = 0; i < pvSubjects.size(); i++)
	{
		v_subjects.push_back(pvSubjects[i]);
	} // for(int i = 0; i < pvSubjects.size(); i++)
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
	if(i_validate_parameters() != ERR_NO_ERROR)
	{
		return false;
	}

	vSetAlgorithm(new CGeneticAlgorithm(this, d_mutation_probability, d_crossover_probability, i_iterations));
	
	return pc_algorithm->bRun();
} // bool CKnapsackProblem::bStartAlgorithm()

void CKnapsackProblem::vSetAlgorithm(CGeneticAlgorithm* pcAlgorithm)
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

bool CKnapsackProblem::b_is_probability_correct(double dProbability)
{
	 return dProbability < MIN_PROBABILITY || dProbability > MAX_PROBABILITY;
} // bool CKnapsackProblem::b_is_probability_correct(double dProbability

int CKnapsackProblem::i_validate_parameters()
{
	int i_error_code = ERR_NO_ERROR;

	if (b_is_probability_correct(d_mutation_probability))
	{
		i_error_code = ERR_INVALID_MUTATION_PROB;
	}
	else if (b_is_probability_correct(d_crossover_probability))
	{
		i_error_code = ERR_INVALID_CROSSOVER_PROB;
	}
	else if (i_iterations < MIN_ITERATIONS)
	{
		i_error_code = ERR_INVALID_ITERATIONS_NUM;
	}
	else if (d_max_size < MIN_MAX_SIZE)
	{
		i_error_code = ERR_INVALID_MAX_SIZE;
	}
	else if(i_population_size < MIN_POP_SIZE || i_population_size % 2 != 0)
	{
		i_error_code = ERR_INVALID_POP_SIZE;
	}
	else if(i_tournament_size < MIN_TOURNAMENT_SIZE)
	{
		i_error_code = ERR_INVALID_TOURNAMENT_SIZE;
	}
	else
	{
		for (int i = 0; i < v_subjects.size(); i++)
		{
			if (i_error_code == ERR_NO_ERROR)
			{
				if (v_subjects[i]->dGetSize() < 0.0)
				{
					i_error_code = ERR_INVALID_SUBJECT_SIZE;
				}
				else if (v_subjects[i]->dGetValue() < 0.0)
				{
					i_error_code = ERR_INVALID_SUBJECT_VALUE;
				}
			}
		} // for (int i = 0; i < v_subjects.size(); i++)
	}

	return i_error_code;
} // int CKnapsackProblem::i_validate_parameters()
