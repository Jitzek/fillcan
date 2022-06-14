#pragma once

// vulkan
#include "vulkan/vulkan_core.h"

// fillcan
#include <cstddef>
#include <fillcan/commands/command_pool.hpp>
#include <fillcan/graphics/swapchain.hpp>
#include <fillcan/instance/device_pool.hpp>
#include <fillcan/instance/instance.hpp>
#include <fillcan/instance/physical_device.hpp>
#include <fillcan/shader/shader_module.hpp>
#include <fillcan/window.hpp>

// std
#include <functional>
#include <memory>
#include <shaderc/status.h>
#include <vector>

// shaderc
#include <shaderc/shaderc.hpp>
#include <shaderc/shaderc.h>

namespace fillcan {
    class Fillcan {
      protected:
        std::unique_ptr<Instance> upInstance{};
        std::unique_ptr<Window> upWindow{};
        std::unique_ptr<DevicePool> upDevicePool{};

        std::vector<char> readFile(std::string fileLocation, size_t* fileSize);
        shaderc::PreprocessedSourceCompilationResult preprocessGLSL(const std::string shaderDirectory, const std::string shaderFileName,
                                                                    shaderc_shader_kind shaderKind);

      public:
        Fillcan(const char* pApplicationName, uint32_t applicationVersion, unsigned int windowWidth, unsigned int windowHeight,
                VkPhysicalDeviceFeatures requiredDeviceFeatures = {});
        ~Fillcan();
        Fillcan(const Fillcan&) = delete;
        Fillcan& operator=(const Fillcan&) = delete;

        void MainLoop(std::function<void()> callback);

        const std::vector<PhysicalDevice> getSupportedPhysicalDevices() const;
        LogicalDevice* selectDevice(unsigned int deviceIndex = 0);

        LogicalDevice* getCurrentDevice();

        std::unique_ptr<ShaderModule> createShaderModule(const std::string shaderDirectory, const std::string shaderFileName,
                                                         shaderc_shader_kind shaderKind,
                                                         std::vector<std::unique_ptr<DescriptorSetLayout>> upDescriptorSetLayouts,
                                                         std::unique_ptr<DescriptorPool> upDescriptorPool /*, TODO: pushConstants*/,
                                                         bool preprocess = true, bool optimize = false);
    };
} // namespace fillcan