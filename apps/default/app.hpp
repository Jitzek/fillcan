#pragma once

// fillcan
#include <fillcan/window.hpp>

namespace app
{
    class App
    {
    private:
        fillcan::FillcanWindow window{960, 540, "Default Application"};
    public:
        App();
        ~App();
        void run();
    };
}