#pragma once

#include "Athena/Window.h"
namespace Athena
{
    class WindowsWindow : public Window
    {
    public:

        // Inherited via Window
        virtual unsigned int GetWidth() const override;
        virtual unsigned int GetHeight() const override;
    };
}