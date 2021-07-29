#include "pch.h"

#include "WindowsWindow.h"

namespace Athena
{
	Window* Window::Create(const WindowProperties& properties)
	{
		return new WindowsWindow(properties);
	}

	void Athena::WindowsWindow::Init(const WindowProperties& properties)
	{
		m_glfwWindowData.Title = properties.WindowTitle;
		m_glfwWindowData.Width = properties.WindowWidth;
		m_glfwWindowData.Height = properties.WindowHeight;

		ATH_ENGINE_INFO("Creating GLFW window '{0}' ({1} X {2})", properties.WindowTitle, properties.WindowWidth, properties.WindowHeight);

		ATH_ENGINE_INFO("Initialising Vulkan");
		bool vulkanSupported = glfwVulkanSupported();
		ATH_ENGINE_ASSERT(vulkanSupported, "Vulkan is not supported on this system!");

		//	Create Vulkan Instance
		PFN_vkCreateInstance pfnCreateInstance = (PFN_vkCreateInstance)glfwGetInstanceProcAddress(NULL, "vkCreateInstance");
		uint32_t extensionsCount;
		const char** extensions = glfwGetRequiredInstanceExtensions(&extensionsCount);
		VkInstanceCreateInfo ici;
		memset(&ici, 0, sizeof(ici));
		ici.enabledExtensionCount = extensionsCount;
		ici.ppEnabledExtensionNames = extensions;

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		m_glfwWindow = glfwCreateWindow(m_glfwWindowData.Width, m_glfwWindowData.Height, m_glfwWindowData.Title.c_str(), NULL, NULL);

		/*VkSurfaceKHR vkSurface;
		VkResult err = glfwCreateWindowSurface(instance, m_glfwWindow, NULL, &vkSurface);
		if (err)
		{
			ATH_ENGINE_ERROR("Failed to create vulkan window surface!");
		}*/
	}

	WindowsWindow::WindowsWindow(const WindowProperties& properties)
	{
		Init(properties);
	}

	WindowsWindow::~WindowsWindow()
	{
		glfwDestroyWindow(m_glfwWindow);
	}

	unsigned int Athena::WindowsWindow::GetWidth() const
	{
		return 0;
	}

	unsigned int Athena::WindowsWindow::GetHeight() const
	{
		return 0;
	}

	void Athena::WindowsWindow::OnUpdate()
	{
	}

}