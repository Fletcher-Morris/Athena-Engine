#pragma once

#include "AthenaCore.h"
#include "Window.h"

#include <vulkan/vulkan.h>

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
		VkPhysicalDevice m_vulkanDevice;
		bool SelectVulkanDevice();
		bool IsVulkanDeviceSuitable(VkPhysicalDevice device);
	};

	App* CreateApp();

}