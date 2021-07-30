#include "pch.h"
#include "App.h"

#include "Athena/Log.h"
#include <GLFW/glfw3.h>

namespace Athena
{
	Athena::App::App()
	{
		//s_instance = this;
		m_appWindow = std::unique_ptr<Window>(Window::Create());
	}

	Athena::App::~App()
	{
		vkDestroyInstance(m_vulkanInstance, nullptr);
	}

	void Athena::App::Run()
	{
		while (m_isRunning)
		{
			m_appWindow->OnUpdate();
		}
	}

	bool App::CreateVulkanInstance()
	{
		VkApplicationInfo appInfo{};
		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pApplicationName = "Athena Engine";
		appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.pEngineName = "Athena";
		appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.apiVersion = VK_API_VERSION_1_0;

		VkInstanceCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		createInfo.pApplicationInfo = &appInfo;

		uint32_t glfwExtensionCount = 0;
		const char** glfwExtensions;
		glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
		createInfo.enabledExtensionCount = glfwExtensionCount;
		createInfo.ppEnabledExtensionNames = glfwExtensions;

		createInfo.enabledLayerCount = 0;

		VkResult result = vkCreateInstance(&createInfo, nullptr, &m_vulkanInstance);
		bool success = result == VK_SUCCESS;
		ATH_ENGINE_ASSERT(success, "Failed to create Vulkan instance!");
		return success;
	}
}