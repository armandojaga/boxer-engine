#pragma once

#include "Module.h"

class ModuleEditor : public Module
{
public:
	ModuleEditor();
	~ModuleEditor();

	bool Init() override;
	update_status Update() override;
	bool CleanUp() override;

private:
	void CreateMenu();
};
