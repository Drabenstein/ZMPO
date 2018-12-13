#pragma once
#include <vector>
#include "CSubject.h"
#include "CKnapsackProblem.h"

class CExperimentManager
{
public:
	CExperimentManager();

	~CExperimentManager();

	void vRun();

private:
	std::vector<CSubject*> v_subjects;
	CKnapsackProblem* pc_problem;

	void v_prepare_testable_data();
	void v_initialize_subjects();
	void v_clear_instance();
};
