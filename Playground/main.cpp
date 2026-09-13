#include <iostream>

// Playground
#include "playground.h"

int main(int argc, char** argv)
{
	ApplicationConfiguration appConfig;

	appConfig.title = "Sinter Engine Playground";
	appConfig.width = 800;
	appConfig.height = 600;

	PlaygroundApplication playgroundApp(appConfig);

	EngineConfiguration engineConfig;

	Engine::GetInstance().Initialize(engineConfig);
	Engine::GetInstance().Run(&playgroundApp);
	Engine::GetInstance().Shutdown();
}
