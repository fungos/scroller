#include "app.h"

ISceneNode *pScene;
ISceneNode *pSceneStatic;

int main(int argc, char **argv)
{
	App app;

	Seed::SetGameApp(&app, argc, argv);
	if (Seed::Initialize())
	{
		while (!pSystem->IsShuttingDown())
		{
			if (!app.HasError())
			{
				Seed::Update();
			}
			pTimer->Sleep(1);
		}
	}
	Seed::Shutdown();

	return EXIT_SUCCESS;
}
