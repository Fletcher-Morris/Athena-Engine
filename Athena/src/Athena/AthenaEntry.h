#pragma once

#include "Athena/App.h"
#include "Athena/Log.h"

#ifdef ATH_PLAT_WIN

extern Athena::App* Athena::CreateApp();

int main(int argc, char** argv)
{
	Athena::Log::Init();
	ATH_ENGINE_INFO("STARTING ENGINE");
	auto app = Athena::CreateApp();
	app->Run();
	delete app;
}

#endif // ATH_PLAT_WIN