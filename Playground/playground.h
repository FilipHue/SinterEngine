#pragma once

// Sinter Engine
#include <sinter/sinter.h>

using namespace sinter;
using namespace core;
using namespace engine;

class PlaygroundApplication : public Application
{
public:
	PlaygroundApplication(const ApplicationConfiguration& p_refConfiguration);
	virtual ~PlaygroundApplication() = default;

	void Init() override;
	void Shutdown() override;

	void  OnProcessUpdate() override;

private:
};