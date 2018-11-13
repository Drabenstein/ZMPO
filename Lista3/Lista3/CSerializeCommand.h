#pragma once
#include "CCommand.h"
#include "CMenuItem.h"

namespace Commands
{
	class CSerializeCommand : public CCommand
	{
	public:
		CSerializeCommand(CMenuItem* pcRootMenuItem);

		bool bRunCommand(std::string* psResponseMsg) override;

	private:
		CMenuItem* pc_root_menu_item;
	};
}
