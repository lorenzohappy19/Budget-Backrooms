// By Jason Hoku Levien, Published 2022

#pragma once

#include "Modules/ModuleManager.h"

class FHashAndEncryptToolsPluginModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
