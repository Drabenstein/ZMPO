// Lista5.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include "pch.h"
#include <iostream>
#include <string>
#include "CKnapsackProblem.h"
#include "ExperimentConstants.h"
#include "KnapsackProblemErrorCodes.h"

int main()
{
	std::vector<CSubject*> v_subjects;
	CRandomGenerator* pc_values_generator = new CRandomGenerator(MIN_ITEM_VALUE, MAX_ITEM_VALUE);
	CRandomGenerator* pc_sizes_generator = new CRandomGenerator(MIN_ITEM_SIZE, MAX_ITEM_SIZE);

	for(int i = 0; i < KNAPSACK_ITEMS_COUNT; i++)
	{
		CSubject* pc_new_subject = new CSubject(pc_values_generator->dNextDouble(), pc_sizes_generator->dNextDouble());
		v_subjects.push_back(pc_new_subject);
		std::cout << pc_new_subject->sToString() << std::endl;
	} // for(int i = 0; i < KNAPSACK_ITEMS_COUNT; i++)

	delete pc_values_generator;
	delete pc_sizes_generator;

	int i_error_code;
	CKnapsackProblem* pc_problem = new CKnapsackProblem(v_subjects, POP_SIZE, MUTATION_PROBABILITY,
		CROSSOVER_PROBABILITY, KNAPSACK_CAPACITY, ITERATIONS_NUM, i_error_code);
	if (i_error_code == ERR_NO_ERROR)
	{
		pc_problem->bStartAlgorithm();
		const std::vector<int>* pv_result = pc_problem->pvGetBestResult();

		if (pv_result != nullptr)
		{
			for (int i = 0; i < pv_result->size(); i++)
			{
				std::cout << (*pv_result)[i];
			} // for(int i = 0; i < pv_result->size(); i++) 
		}
	}
	else
	{
		std::string s_error_msg;

		switch(i_error_code)
		{
		case ERR_INVALID_CROSSOVER_PROB:
			s_error_msg = ERR_MSG_INVALID_CROSSOVER_PROBABILITY;
			break;
		case ERR_INVALID_ITERATIONS_NUM:
			s_error_msg = ERR_MSG_INVALID_ITERATIONS_NUM;
			break;
		case ERR_INVALID_MAX_SIZE:
			s_error_msg = ERR_MSG_INVALID_MAX_SIZE;
			break;
		case ERR_INVALID_MUTATION_PROB:
			s_error_msg = ERR_INVALID_MUTATION_PROB;
			break;
		case ERR_INVALID_POP_SIZE:
			s_error_msg = ERR_INVALID_POP_SIZE;
			break;
		case ERR_INVALID_SUBJECT_SIZE:
			s_error_msg = ERR_MSG_INVALID_SUBJECT_SIZE;
			break;
		case ERR_INVALID_SUBJECT_VALUE:
			s_error_msg = ERR_MSG_INVALID_SUBJECT_VALUE;
			break;
		default:
			s_error_msg = ERR_MSG_UNKNOWN_ERROR;
			break;
		}

		std::cout << s_error_msg << std::endl;
	}

	std::cout << std::endl;

	delete pc_problem;

	for(int i = 0; i < v_subjects.size(); i++)
	{
		delete v_subjects[i];
	}
}
