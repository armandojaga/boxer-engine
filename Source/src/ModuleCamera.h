#pragma once

#include "Module.h"

class ModuleCamera : public Module
{
public:
	ModuleCamera();
	~ModuleCamera() override;

	bool Init() override;
	update_status Update() override;
	bool CleanUp() override;

private:
};
