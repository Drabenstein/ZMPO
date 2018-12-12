#include "pch.h"
#include "CGeneticAlgorithm.h"

const double CGeneticAlgorithm::MIN_PROBABILITY = 0.0;
const double CGeneticAlgorithm::MAX_PROBABILITY = 1.0;
const double CGeneticAlgorithm::DEFAULT_MUTATION_PROBABILITY = 0.1;
const double CGeneticAlgorithm::DEFAULT_CROSSOVER_PROBABILITY = 0.6;
const int CGeneticAlgorithm::GEN_TYPES_COUNT = 2;
const int CGeneticAlgorithm::MIN_ITERATIONS = 1;

CGeneticAlgorithm::CGeneticAlgorithm(CProblem* pcProblem, double dMutationProb, double dCrossoverProb, int iIterationNum)
{
	pc_problem = pcProblem;

	if (!bSetMutationProbability(dMutationProb))
	{
		d_mutation_probability = DEFAULT_MUTATION_PROBABILITY;
	}

	if (!bSetCrossoverProbability(dCrossoverProb))
	{
		d_crossover_probability = DEFAULT_CROSSOVER_PROBABILITY;
	}

	if (!bSetIterations(iIterationNum))
	{
		i_iterations_max = MIN_ITERATIONS;
	}

	pc_random = new CRandomGenerator(MIN_PROBABILITY, MAX_PROBABILITY);
} // CGeneticAlgorithm::CGeneticAlgorithm(CProblem & rcProblem, double dMutationProb, double dCrossoverProb, int iIterationsNum)

CGeneticAlgorithm::~CGeneticAlgorithm()
{
	delete pc_random;
	v_clear_population(v_population);
} // CGeneticAlgorithm::~CGeneticAlgorithm()

bool CGeneticAlgorithm::bRun()
{
	if(pc_problem == nullptr)
	{
		return false;
	}

	while (v_population.size() < pc_problem->iGetPopulationSize())
	{
		v_population.push_back(pc_create_individual());
	} // while (v_population.size() < pc_problem.iGetPopulationSize())

	for (int i = 0; i < i_iterations_max; i++)
	{
		std::vector<CIndividual*> v_new_population;
		bool b_success = b_crossover(v_new_population);
		if (!b_success)
		{
			v_clear_population(v_population);
			v_clear_population(v_new_population);
			return false;
		}

		v_clear_population(v_population);
		v_population = v_new_population;
		v_mutatation();
	} // for (int i = 0; i < i_iterations_max; i++)

	return true;
} // bool CGeneticAlgorithm::vRun()

const std::vector<int>* CGeneticAlgorithm::pvGetBestResult()
{
	CIndividual* pc_best_individual = nullptr;
	double d_best_individual_fitness = 0.0;

	for (int i = 0; i < v_population.size(); i++)
	{
		double d_current_fitness;
		v_population[i]->bCalculateFitness(d_current_fitness);
		if (pc_best_individual == nullptr || d_best_individual_fitness < d_current_fitness)
		{
			pc_best_individual = v_population[i];
			d_best_individual_fitness = d_current_fitness;
		}
	} // for (int i = 0; i < v_population.size(); i++)

	if (pc_best_individual != nullptr)
	{
		return &pc_best_individual->rvGetGenotype();
	}
	else
	{
		return nullptr;
	}
} // const std::vector<int>* CGeneticAlgorithm::pvGetBestResult()

bool CGeneticAlgorithm::bSetMutationProbability(double dProbability)
{
	bool b_is_value_correct = b_is_probability_correct(dProbability);
	if (b_is_value_correct)
	{
		d_mutation_probability = dProbability;
	}
	return b_is_value_correct;
} // bool CGeneticAlgorithm::bSetMutationProbability(double dProbability)

bool CGeneticAlgorithm::bSetCrossoverProbability(double dProbability)
{
	bool b_is_value_correct = b_is_probability_correct(dProbability);
	if (b_is_value_correct)
	{
		d_crossover_probability = dProbability;
	}
	return b_is_value_correct;
} // bool CGeneticAlgorithm::bSetCrossoverProbability(double dProbability)

bool CGeneticAlgorithm::bSetIterations(int iIterations)
{
	if (iIterations < MIN_ITERATIONS)
	{
		return false;
	}

	i_iterations_max = iIterations;
	return true;
} // bool CGeneticAlgorithm::bSetIterations(int iIterations)

CIndividual* CGeneticAlgorithm::pc_create_individual()
{
	std::vector<int> v_genotype;

	for (int i = 0; i < pc_problem->iGetGenotypeLength(); i++)
	{
		v_genotype.push_back(pc_random->iNextInt(GEN_TYPES_COUNT));
	} // for (int i = 0; i < pc_problem.iGetGenotypeLength(); i++)

	return new CIndividual(pc_problem, v_genotype);
} // CIndividual * CGeneticAlgorithm::pc_create_individual()

bool CGeneticAlgorithm::b_crossover(std::vector<CIndividual*>& rvNewPopulation)
{
	bool b_success = true;

	while (rvNewPopulation.size() < pc_problem->iGetPopulationSize() && b_success)
	{
		CIndividual* pc_first_parent = pc_run_tournament();
		CIndividual* pc_second_parent = pc_run_tournament();
		double d_crossover_random = pc_random->dNextDouble();
		if (d_crossover_random < d_crossover_probability)
		{
			int i_split_point = pc_random->iNextInt(pc_first_parent->rvGetGenotype().size() - 1) + 1;
			b_success = pc_first_parent->bCrossover(*pc_second_parent, i_split_point, rvNewPopulation);
		}
		else
		{
			rvNewPopulation.push_back(new CIndividual(*pc_first_parent));
			rvNewPopulation.push_back(new CIndividual(*pc_second_parent));
		}
	} // while (rvNewPopulation.size() < pc_problem.iGetPopulationSize())

	return b_success;
} // void CGeneticAlgorithm::v_crossover(std::vector<CIndividual*>& rvNewPopulation)

CIndividual * CGeneticAlgorithm::pc_run_tournament()
{
	CIndividual* pc_best_participant = nullptr;
	double d_best_participant_fitness = 0.0;

	for(int i = 0; i < pc_problem->iGetTournamentSize(); i++)
	{
		int i_random_index = pc_random->iNextInt(v_population.size());
		double d_current_fitness = 0.0;
		bool b_calculate_success = v_population.at(i_random_index)->bCalculateFitness(d_current_fitness);

		if(pc_best_participant == nullptr || (b_calculate_success && d_best_participant_fitness < d_current_fitness))
		{
			pc_best_participant = v_population.at(i_random_index);
			d_best_participant_fitness = d_current_fitness;
		}
	} // for(int i = 0; i < pc_problem->iGetTournamentSize(); i++)

	return pc_best_participant;
} // CIndividual * CGeneticAlgorithm::pc_run_tournament()

void CGeneticAlgorithm::v_mutatation()
{
	for (int i = 0; i < v_population.size(); i++)
	{
		int i_genotype_length = v_population[i]->rvGetGenotype().size();
		for (int j = 0; j < i_genotype_length; j++)
		{
			double d_mutation_random = pc_random->dNextDouble();
			if (d_mutation_random < d_mutation_probability)
			{
				v_population[i]->bMutate(j);
			}
		} // for (int j = 0; j < i_genotype_length; j++)
	} // for (int i = 0; i < v_population.size(); i++)
} // void CGeneticAlgorithm::v_mutatation()

void CGeneticAlgorithm::v_clear_population(std::vector<CIndividual*>& rvPopulationToDel)
{
	for (int i = 0; i < rvPopulationToDel.size(); i++)
	{
		delete rvPopulationToDel[i];
	} // for (int i = 0; i < rvPopulationToDel.size(); i++)
} // void CGeneticAlgorithm::v_clear_population(std::vector<CIndividual*>& rvPopulationToDel)

bool CGeneticAlgorithm::b_is_probability_correct(double dProbability)
{
	return dProbability < MIN_PROBABILITY || dProbability > MAX_PROBABILITY;
} // bool CGeneticAlgorithm::b_is_probability_correct(double dProbability)
