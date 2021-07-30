#include "pch.h"
#include "App.h"

#include "Athena/Log.h"
#include <GLFW/glfw3.h>

namespace Athena
{
	Athena::App::App()
	{
		m_appWindow = std::unique_ptr<Window>(Window::Create());
		CreateVulkanInstance();
		ATH_ENGINE_INFO("Created Vulkan instance!");
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
		ATH_ENGINE_INFO("Initialising Vulkan");

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

		uint32_t vkExtensionCount = 0;
		vkEnumerateInstanceExtensionProperties(nullptr, &vkExtensionCount, nullptr);
		std::vector<VkExtensionProperties> extensions(vkExtensionCount);
		vkEnumerateInstanceExtensionProperties(nullptr, &vkExtensionCount, extensions.data());
		std::string vkExtensionsString = "Vulkan extensions: ";
		for (const auto& extension : extensions)
		{
			vkExtensionsString += extension.extensionName;
			vkExtensionsString += ", ";
		}
		ATH_ENGINE_INFO(vkExtensionsString);

		return success;
	}
	bool App::SelectVulkanDevice()
	{
		m_vulkanDevice = VK_NULL_HANDLE;
		uint32_t vkDeviceCount = 0;
		vkEnumeratePhysicalDevices(m_vulkanInstance, &vkDeviceCount, nullptr);
		ATH_ENGINE_ASSERT(vkDeviceCount == 0, "Failed to find GPU with Vulkan support!");

		std::vector<VkPhysicalDevice> foundVkDevices(vkDeviceCount);
		for (const auto& device : foundVkDevices)
		{
			if (IsVulkanDeviceSuitable(device))
			{
				m_vulkanDevice = device;
				break;
			}
		}
		bool gpuSuitable = m_vulkanDevice == VK_NULL_HANDLE;
		ATH_ENGINE_ASSERT(gpuSuitable, "Failed to find a suitable GPU!");
		if (gpuSuitable == false) return false;

		return false;
	}
	bool App::IsVulkanDeviceSuitable(VkPhysicalDevice device)
	{
		return true;
	}
}