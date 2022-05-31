#pragma once

// fillcan
// #include <fillcan/window.hpp>
#include <fillcan/fillcan.hpp>

namespace app {
    class App {
      private:
        // fillcan::Window window{960, 540, "Default Application"};
        fillcan::Fillcan fillcan{"Default Application", 1, 800, 600, {.samplerAnisotropy = true}};

      public:
        App();
        ~App();
        void run();
        void update();
    };
} // namespace app