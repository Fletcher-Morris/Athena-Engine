#pragma once

namespace Athena
{
	struct WindowProperties
	{
		std::string WindowTitle;
		unsigned int WindowWidth;
		unsigned int WindowHeight;

		WindowProperties(const std::string& name = "Athena Engine", unsigned int width = 1600, unsigned int height = 900) : WindowTitle(name), WindowWidth(width), WindowHeight(height)
		{

		}
	};

	class ATH_API Window
	{
	public:
		virtual ~Window() {}
		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;
		static Window* Create(const WindowProperties& properties = WindowProperties());
	};
}