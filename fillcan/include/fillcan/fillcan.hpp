#pragma once

// fillcan
#include <fillcan/window.hpp>
#include <fillcan/instance.hpp>

// std
#include <functional>

namespace fillcan
{
    class Fillcan
    {
    private:
        Instance instance;
        Window window;
    public:
        Fillcan(const char* pApplicationName, uint32_t applicationVersion);
        ~Fillcan();
        Fillcan(const Fillcan&) = delete;
        Fillcan &operator=(const Fillcan&) = delete;

        void MainLoop(std::function<void()> callback);
    };   
}