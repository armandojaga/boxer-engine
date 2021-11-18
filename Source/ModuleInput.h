#pragma once
#include "Module.h"
#include "Globals.h"

using Uint8 = unsigned __int8;

class ModuleInput : public Module
{
public:
	ModuleInput();
	~ModuleInput();

	bool Init() override;
	update_status Update() override;
	bool CleanUp() override;

private:
	const Uint8* keyboard = nullptr;
};
