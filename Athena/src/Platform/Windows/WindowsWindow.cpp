#include "pch.h"

#include "WindowsWindow.h"

void Athena::WindowsWindow::Init(const WindowProperties& properties)
{
	m_glfwWindowData.Title = properties.WindowTitle;
	m_glfwWindowData.Width = properties.WindowWidth;
	m_glfwWindowData.Height = properties.WindowHeight;

	ATH_ENGINE_INFO("Creating glfw window {0} ({1} X {2})", properties.WindowTitle, properties.WindowWidth, properties.WindowHeight);
}

unsigned int Athena::WindowsWindow::GetWidth() const
{
	return 0;
}

unsigned int Athena::WindowsWindow::GetHeight() const
{
	return 0;
}