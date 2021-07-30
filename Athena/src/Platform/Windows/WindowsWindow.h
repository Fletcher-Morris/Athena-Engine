#pragma once

#include <Athena/Window.h>
#include <GLFW/glfw3.h>

namespace Athena
{
    class WindowsWindow : public Window
    {
    public:
        WindowsWindow(const WindowProperties& properties);
        virtual ~WindowsWindow();
        virtual unsigned int GetWidth() const override;
        virtual unsigned int GetHeight() const override;

    private:
        virtual void Init(const WindowProperties& properties);

        GLFWwindow* m_glfwWindow;
        struct GlfwWindowData
        {
            std::string Title;
            unsigned int Width, Height;
            bool VSync;
        };
        GlfwWindowData m_glfwWindowData;
        virtual void OnUpdate() override;
    };
}