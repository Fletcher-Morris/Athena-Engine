#pragma once

#ifdef ATH_PLAT_WIN

extern Athena::App* Athena::CreateApp();

int main(int argc, char** argv)
{
	Athena::Log::Init();
	auto app = Athena::CreateApp();
	app->Run();
	delete app;
}

#endif // ATH_PLAT_WIN