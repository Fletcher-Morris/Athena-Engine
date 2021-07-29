#pragma once

#include <Athena/Window.h>

#include <vulkan/vulkan.h>
#define GLFW_INCLDUE_VULKAN 
#include <GLFW/glfw3.h>

namespace Athena
{
    class WindowsWindow : public Window
    {
    public:
        WindowsWindow(const WindowProperties& properties);
        virtual ~WindowsWindow();


        // Inherited via Window
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

        // Inherited via Window
        virtual void OnUpdate() override;
    };
}