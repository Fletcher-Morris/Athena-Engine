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
}