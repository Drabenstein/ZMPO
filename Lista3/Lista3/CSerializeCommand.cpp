#include "pch.h"
#include "CSerializeCommand.h"
#include <iostream>

Commands::CSerializeCommand::CSerializeCommand(CMenuItem * pcRootMenuItem)
{
	pc_root_menu_item = pcRootMenuItem;
} // Commands::CSerializeCommand::CSerializeCommand(CMenuItem * pcRootMenuItem)

bool Commands::CSerializeCommand::bRunCommand(std::string * psResponseMsg)
{
	std::cout << std::endl << pc_root_menu_item->sSerialize() << std::endl << std::endl;
	return true;
} // bool Commands::CSerializeCommand::bRunCommand(std::string * psResponseMsg)
