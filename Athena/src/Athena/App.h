#pragma once

#include "AthenaCore.h"
#include "Window.h"

#include "Athena/Graphics/Backend.h"

namespace Athena
{
	class ATH_API App
	{
	public:
		App();
		virtual ~App();
		void Run();
	private:
		std::unique_ptr<Window> m_appWindow;
		bool m_isRunning = true;

		//	VULKAN
		VkInstance m_vulkanInstance;
		bool CreateVulkanInstance();
		VkPhysicalDevice m_vulkanPhysicalDevice;
		VkPhysicalDeviceProperties m_vulkanPhysicalDeviceProperties;
		VkDevice m_vulkanLogicalDevice;
		bool SelectVulkanDevice();
		bool IsVulkanDeviceSuitable(VkPhysicalDevice device);
		bool CreateVulkanLogcialDevice();
		QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);
	};

	App* CreateApp();

}