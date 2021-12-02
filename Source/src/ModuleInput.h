#pragma once
#include "Module.h"
#include "Globals.h"

using Uint8 = unsigned __int8;

class ModuleInput : public Module
{
public:
	ModuleInput();
	~ModuleInput() override;

	bool Init() override;
	update_status PreUpdate() override;
	bool CleanUp() override;

private:
	const Uint8* keyboard = nullptr;
};
