#pragma once

#include <optional>
#include <vector>

#include "Athena/AthenaCore.h"
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>



namespace Athena
{
	struct ATH_API QueueFamilyIndices
	{
		std::optional<uint32_t> graphicsFamily;

		bool IsComplete()
		{
			return graphicsFamily.has_value();
		}
	};

	class ATH_API GraphicsBackend
	{
	public:
		inline static std::shared_ptr<GraphicsBackend>& Singleton()
		{
			if (s_instance == 0) s_instance = std::make_shared<GraphicsBackend>(GraphicsBackend());
			return s_instance;
		}
		static bool VulkanInit();

		static void VulkanCleanup();
	private:
		static std::shared_ptr<GraphicsBackend> s_instance;
		GraphicsBackend();
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
}