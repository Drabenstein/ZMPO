#pragma once
#include "CProblem.h"
#include <vector>

class CProblem;

class CIndividual
{
public:
	CIndividual(CProblem* pcProblem, const std::vector<int>& rvGenotype);
	CIndividual(const CIndividual& rcOther);

	bool bCalculateFitness(double& dResult);
	bool bMutate(int iGenToMutateIndex);
	bool bCrossover(CIndividual& rcOtherParent, int iSplitPoint, std::vector<CIndividual*>& rvResult);
	std::vector<int>& rvGetGenotype();

private:
	std::vector<int> v_genotype;
	CProblem* pc_problem;
};
