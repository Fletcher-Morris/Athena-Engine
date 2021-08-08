#include "pch.h"

#include "Backend.h"

namespace Athena
{
	std::shared_ptr<GraphicsBackend> GraphicsBackend::s_instance;

	GraphicsBackend::GraphicsBackend()
	{
	}

	bool GraphicsBackend::VulkanInit()
	{
		if (!Singleton()->CreateVulkanInstance()) return false;
		if (!Singleton()->SelectVulkanDevice()) return false;
		if (!Singleton()->CreateVulkanLogcialDevice()) return false;
		return true;
	}

	void GraphicsBackend::VulkanCleanup()
	{
		vkDestroyInstance(Singleton()->m_vulkanInstance, nullptr);
		vkDestroyDevice(Singleton()->m_vulkanLogicalDevice, nullptr);
	}

	bool Athena::GraphicsBackend::CreateVulkanInstance()
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

	bool Athena::GraphicsBackend::SelectVulkanDevice()
	{
		m_vulkanPhysicalDevice = VK_NULL_HANDLE;
		uint32_t vkDeviceCount = 0;
		VkResult enumerateDevicesResult = vkEnumeratePhysicalDevices(m_vulkanInstance, &vkDeviceCount, nullptr);
		ATH_ENGINE_ASSERT(vkDeviceCount != 0, "Failed to find GPU with Vulkan support!");

		std::vector<VkPhysicalDevice> foundVkDevices(vkDeviceCount);
		vkEnumeratePhysicalDevices(m_vulkanInstance, &vkDeviceCount, foundVkDevices.data());

		for (const auto& device : foundVkDevices)
		{
			if (IsVulkanDeviceSuitable(device))
			{
				m_vulkanPhysicalDevice = device;
				break;
			}
		}
		bool gpuSuitable = m_vulkanPhysicalDevice != VK_NULL_HANDLE;
		ATH_ENGINE_ASSERT(gpuSuitable, "Failed to find a suitable GPU!");
		if (gpuSuitable == false) return false;

		vkGetPhysicalDeviceProperties(m_vulkanPhysicalDevice, &m_vulkanPhysicalDeviceProperties);
		ATH_ENGINE_INFO("Selected GPU '{0}'", m_vulkanPhysicalDeviceProperties.deviceName);

		return true;
	}

	bool Athena::GraphicsBackend::IsVulkanDeviceSuitable(VkPhysicalDevice device)
	{
		//return true;

		VkPhysicalDeviceProperties deviceProperties;
		VkPhysicalDeviceFeatures deviceFeatures;
		vkGetPhysicalDeviceProperties(device, &deviceProperties);
		vkGetPhysicalDeviceFeatures(device, &deviceFeatures);
		std::string deviceName = deviceProperties.deviceName;

		QueueFamilyIndices indices = FindQueueFamilies(device);
		if (indices.graphicsFamily.has_value() == false)
		{
			ATH_ENGINE_WARN("GPU device '{0}' has no graphics family!", deviceName);
			return false;
		}

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

	bool Athena::GraphicsBackend::CreateVulkanLogcialDevice()
	{
		QueueFamilyIndices indices = FindQueueFamilies(m_vulkanPhysicalDevice);
		VkDeviceQueueCreateInfo createQueueInfo{};
		createQueueInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		createQueueInfo.queueFamilyIndex = indices.graphicsFamily.value();
		createQueueInfo.queueCount = 1;
		float queuePriority = 1.0f;
		createQueueInfo.pQueuePriorities = &queuePriority;

		VkPhysicalDeviceFeatures physicalDeviceFeatures;
		vkGetPhysicalDeviceFeatures(m_vulkanPhysicalDevice, &physicalDeviceFeatures);

		VkDeviceCreateInfo createDeviceInfo{};
		createDeviceInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		createDeviceInfo.pQueueCreateInfos = &createQueueInfo;
		createDeviceInfo.queueCreateInfoCount = 1;
		createDeviceInfo.pEnabledFeatures = &physicalDeviceFeatures;
		createDeviceInfo.enabledExtensionCount = 0;

		const std::vector<const char*> validationLayers = { "VK_LAYER_KHRONOS_validation" };
		bool enableValidationLayers = true;

		if (enableValidationLayers)
		{
			createDeviceInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
			createDeviceInfo.ppEnabledLayerNames = validationLayers.data();
		}
		else
		{
			createDeviceInfo.enabledLayerCount = 0;
		}

		VkResult createLogicalDeviceResult = vkCreateDevice(m_vulkanPhysicalDevice, &createDeviceInfo, nullptr, &m_vulkanLogicalDevice);
		ATH_ENGINE_ASSERT(createLogicalDeviceResult == VK_SUCCESS, "Failed to create logical device!");
		if (createLogicalDeviceResult != VK_SUCCESS) return false;

		return true;
	}

	QueueFamilyIndices Athena::GraphicsBackend::FindQueueFamilies(VkPhysicalDevice device)
	{
		QueueFamilyIndices indices;

		uint32_t queueFamilyCount = 0;
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);
		std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

		int i = 0;
		for (const auto& queueFamily : queueFamilies)
		{
			if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
			{
				indices.graphicsFamily = 1;
			}


			if (indices.IsComplete())
			{
				break;
			}

			i++;
		}

		return indices;
	}
}