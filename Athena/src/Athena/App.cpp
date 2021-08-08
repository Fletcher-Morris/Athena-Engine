#include "pch.h"
#include "Athena/Graphics/Backend.h"

#include "App.h"

namespace Athena
{
	Athena::App::App()
	{
		m_appWindow = std::unique_ptr<Window>(Window::Create());
		if (!GraphicsBackend::VulkanInit()) return;
	}

	Athena::App::~App()
	{
		GraphicsBackend::VulkanCleanup();
	}

	void Athena::App::Run()
	{
		while (m_isRunning)
		{
			glfwPollEvents();

			m_appWindow->OnUpdate();
		}
	}
}