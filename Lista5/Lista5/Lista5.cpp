// Lista5.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include "pch.h"
#include <iostream>
#include "CKnapsackProblem.h"

int main()
{
	std::vector<CSubject*> v_subjects;
	v_subjects.push_back(new CSubject(12.0, 1.0));
	v_subjects.push_back(new CSubject(4.0, 2.0));
	v_subjects.push_back(new CSubject(7.0, 3.0));
	v_subjects.push_back(new CSubject(8.0, 4.0));
	CKnapsackProblem* pc_problem = new CKnapsackProblem(v_subjects, 20, 0.2, 0.6, 7.0, 10000);
	pc_problem->bStartAlgorithm();
	const std::vector<int>* pv_result = pc_problem->pvGetBestResult();
	
	for(int i = 0; i < pv_result->size(); i++)
	{
		std::cout << (*pv_result)[i];
	} // for(int i = 0; i < pv_result->size(); i++)

	std::cout << std::endl;
}
