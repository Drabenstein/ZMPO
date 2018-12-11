#include "pch.h"
#include "CIndividual.h"

CIndividual::CIndividual(CProblem* pcProblem, const std::vector<int>& rvGenotype) : pc_problem(pcProblem)
{
	for (int i = 0; i < rvGenotype.size(); i++)
	{
		v_genotype.push_back(rvGenotype.at(i));
	} // for (int i = 0; i < rvGenotype.size(); i++)
} // CIndividual::CIndividual(CProblem& rcProblem, const std::vector<int>& rvGenotype)

CIndividual::CIndividual(const CIndividual& rcOther) : pc_problem(rcOther.pc_problem)
{
	for (int i = 0; i < rcOther.v_genotype.size(); i++)
	{
		v_genotype.push_back(rcOther.v_genotype[i]);
	} // for (int i = 0; i < rcOther.v_genotype.size(); i++)
} // CIndividual::CIndividual(const CIndividual & rcOther)

bool CIndividual::bCalculateFitness(double& dResult)
{
	if (pc_problem != nullptr)
	{
		return pc_problem->bCalculateFitness(dResult, v_genotype);
	}
	else
	{
		dResult = 0.0;
		return false;
	}
} // bool CIndividual::bCalculateFitness(double& dResult)

bool CIndividual::bMutate(int iGenToMutateIndex)
{
	if (iGenToMutateIndex < 0 || iGenToMutateIndex >= v_genotype.size())
	{
		return false;
	}

	v_genotype[iGenToMutateIndex] = !v_genotype[iGenToMutateIndex];
	return true;
} // bool CIndividual::bMutate(int iGenToMutateIndex)s

bool CIndividual::bCrossover(CIndividual& rcOtherParent, int iSplitPoint, std::vector<CIndividual*>& rvResult)
{
	if (v_genotype.size() != rcOtherParent.v_genotype.size())
	{
		return false;
	}

	if (iSplitPoint < 0 || iSplitPoint >= v_genotype.size())
	{
		return false;
	}

	std::vector<int> v_first_child_genotype;
	std::vector<int> v_second_child_genotype;

	for (int i = 0; i < iSplitPoint; i++)
	{
		v_first_child_genotype.push_back(v_genotype[i]);
		v_second_child_genotype.push_back(rcOtherParent.v_genotype[i]);
	} // for (int i = 0; i < iSplitPoint; i++)

	for (int i = iSplitPoint; i < v_genotype.size(); i++)
	{
		v_first_child_genotype.push_back(rcOtherParent.v_genotype[i]);
		v_second_child_genotype.push_back(v_genotype[i]);
	} // for (int i = iSplitPoint; i < v_genotype.size(); i++)
	
	rvResult.push_back(new CIndividual(pc_problem, v_first_child_genotype));
	rvResult.push_back(new CIndividual(pc_problem, v_second_child_genotype));
	return true;
} // void CIndividual::vCrossover(CIndividual & rcOtherParent, std::vector<CIndividual*>* pvResult)

std::vector<int>& CIndividual::rvGetGenotype()
{
	return v_genotype;
} // std::vector<int>& CIndividual::rvGetGenotype()
