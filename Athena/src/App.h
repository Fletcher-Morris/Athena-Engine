#pragma once

#include "AthenaCore.h"

namespace Athena
{
	class ATH_API App
	{
	public:
		App();
		virtual ~App();
		void Run();
	};

	App* CreateApp();
}