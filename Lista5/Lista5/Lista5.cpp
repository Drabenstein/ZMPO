// Lista5.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include "pch.h"
#include "CExperimentManager.h"

int main()
{
	CExperimentManager* pc_manager = new CExperimentManager();
	pc_manager->vRun();
	delete pc_manager;
}
