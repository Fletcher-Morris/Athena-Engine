#include "pch.h"
#include "App.h"

#include "Athena/Log.h"
#define GLW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace Athena
{
	Athena::App::App()
	{
		m_appWindow = std::unique_ptr<Window>(Window::Create());
		//return;
		CreateVulkanInstance();
		ATH_ENGINE_INFO("Created Vulkan instance!");
		SelectVulkanDevice();
	}

	Athena::App::~App()
	{
		vkDestroyInstance(m_vulkanInstance, nullptr);
	}

	void Athena::App::Run()
	{
		while (m_isRunning)
		{
			glfwPollEvents();

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
		VkResult enumerateDevicesResult = vkEnumeratePhysicalDevices(m_vulkanInstance, &vkDeviceCount, nullptr);
		ATH_ENGINE_ASSERT(vkDeviceCount != 0, "Failed to find GPU with Vulkan support!");

		std::vector<VkPhysicalDevice> foundVkDevices(vkDeviceCount);
		vkEnumeratePhysicalDevices(m_vulkanInstance, &vkDeviceCount, foundVkDevices.data());

		for (const auto& device : foundVkDevices)
		{
			if (IsVulkanDeviceSuitable(device))
			{
				m_vulkanDevice = device;
				break;
			}
		}
		bool gpuSuitable = m_vulkanDevice != VK_NULL_HANDLE;
		ATH_ENGINE_ASSERT(gpuSuitable, "Failed to find a suitable GPU!");
		if (gpuSuitable == false) return false;

		vkGetPhysicalDeviceProperties(m_vulkanDevice, &m_vulkanDeviceProperties);
		ATH_ENGINE_INFO("Selected GPU '{0}'", m_vulkanDeviceProperties.deviceName);

		return true;
	}
	bool App::IsVulkanDeviceSuitable(VkPhysicalDevice device)
	{
		return true;

		VkPhysicalDeviceProperties deviceProperties;
		VkPhysicalDeviceFeatures deviceFeatures;
		vkGetPhysicalDeviceProperties(device, &deviceProperties);
		vkGetPhysicalDeviceFeatures(device, &deviceFeatures);
		std::string deviceName = deviceProperties.deviceName;

		bool isDiscreteGpu = deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU;
		if (isDiscreteGpu == false)
		{
			ATH_ENGINE_WARN("GPU device '{0}' is not discrete!", deviceName);
			return false;
		}

		bool hasGeomShader = deviceFeatures.geometryShader;
		if (hasGeomShader == false)
		{
			ATH_ENGINE_WARN("GPU device '{0}' does not support geometry shaders!", deviceName);
			return false;
		}

		ATH_ENGINE_INFO("GPU device '{0}' is suitable!", deviceName);

		return true;
	}
}