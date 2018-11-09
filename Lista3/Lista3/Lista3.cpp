// Lista3.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include "pch.h"
#include <iostream>
#include "CMenu.h"
#include "CMenuCommand.h"

int main()
{
	CMenu menu("main", "main", nullptr, nullptr);
	menu.bAddMenuItem(new CMenuCommand("Ala ma kota", "ala", "komenda ali", nullptr));
	menu.bAddMenuItem(new CMenuCommand("Ola ma kota", "ola", "komenda oli", nullptr));
	menu.bAddMenuItem(new CMenuCommand("Ania ma kota", "ania", "komenda ani", nullptr));
	menu.bAddMenuItem(new CMenuCommand("Aga ma kota", "aga", "komenda agi", nullptr));
	menu.bRun();
}
