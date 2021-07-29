#include "pch.h"
#include "App.h"

#include "Athena/Log.h"

namespace Athena
{
	Athena::App::App()
	{
		//s_instance = this;
		m_appWindow = std::unique_ptr<Window>(Window::Create());
	}

	Athena::App::~App()
	{
	}

	void Athena::App::Run()
	{
		while (m_isRunning)
		{
			m_appWindow->OnUpdate();
		}
	}
}