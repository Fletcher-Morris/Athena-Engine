#pragma once
#include "Athena.h"

#include "entt.hpp"

namespace Athena
{
	class ATH_API Scene
	{
	public:
		Scene();
		~Scene();
	private:
		entt::registry m_entRegistry;
	};
}