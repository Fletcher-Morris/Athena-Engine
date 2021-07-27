#pragma once

#include <Athena/Window.h>
#include <GLFW/glfw3.h>

namespace Athena
{
    class WindowsWindow : public Window
    {
    public:
        virtual void Init(const WindowProperties& properties);

        // Inherited via Window
        virtual unsigned int GetWidth() const override;
        virtual unsigned int GetHeight() const override;

    private:
        GLFWwindow* m_glfwWindow;

        struct GlfwWindowData
        {
            std::string Title;
            unsigned int Width, Height;
            bool VSync;
        };
        GlfwWindowData m_glfwWindowData;
    };
}