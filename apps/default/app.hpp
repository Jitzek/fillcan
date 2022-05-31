#pragma once

// fillcan
// #include <fillcan/window.hpp>
#include <fillcan/fillcan.hpp>
#include <memory>

namespace app {
    class App {
      private:
        std::unique_ptr<fillcan::Fillcan> upFillcan;

      public:
        App();
        ~App();
        void run();
        void update();
    };
} // namespace app