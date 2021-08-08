#pragma once

#include "AthenaCore.h"
#include "Window.h"

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

	};

	App* CreateApp();

}