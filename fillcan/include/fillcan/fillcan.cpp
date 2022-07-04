
// vulkan
#include "vulkan/vulkan_core.h"

// fillcan
#include <fillcan/commands/command_buffer.hpp>
#include <fillcan/fillcan.hpp>
#include <fillcan/instance/logical_device.hpp>
#include <fillcan/shader/shader_module.hpp>

// std
#include <chrono>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <thread>
#include <vector>

// shaderc
#include <shaderc/status.h>

namespace fillcan {

    std::vector<const char*> requiredInstanceLayers = {
#ifndef NDEBUG
        "VK_LAYER_KHRONOS_validation"
#endif
    };

    std::vector<const char*> requiredInstanceExtensions = {
#ifndef NDEBUG
        VK_EXT_DEBUG_UTILS_EXTENSION_NAME
#endif
    };

    Fillcan::Fillcan(const char* pApplicationName, uint32_t applicationVersion, unsigned int windowWidth, unsigned int windowHeight,
                     VkPhysicalDeviceFeatures requiredDeviceFeatures, std::vector<const char*> requiredDeviceExtensions) {
        // Initialize Window
        this->upWindow = std::make_unique<Window>(windowWidth, windowHeight, pApplicationName);

        // Initialize Instance
        std::vector<const char*> windowExtensions = upWindow->getRequiredExtensions();
        requiredInstanceExtensions.insert(requiredInstanceExtensions.begin(), windowExtensions.begin(), windowExtensions.end());
        this->upInstance = std::make_unique<Instance>(pApplicationName, applicationVersion, requiredInstanceLayers, requiredInstanceExtensions);

        // Create surface of Window using Instance
        this->upWindow->createSurface(this->upInstance.get());

        // Initialize Device Pool
        this->upDevicePool =
            std::make_unique<DevicePool>(this->upInstance.get(), this->upWindow.get(), requiredDeviceExtensions, requiredDeviceFeatures);
    }

    Fillcan::~Fillcan() {
        vkDestroySurfaceKHR(this->upInstance->getInstanceHandle(), this->upWindow->getSurface(), nullptr);
        this->upDevicePool.reset();
        this->upInstance.reset();
    }

    const std::vector<PhysicalDevice> Fillcan::getSupportedPhysicalDevices() const { return this->upDevicePool->getSupportedPhysicalDevices(); }

    LogicalDevice* Fillcan::selectDevice(unsigned int deviceIndex) { return this->upDevicePool->selectDevice(deviceIndex); }

    LogicalDevice* Fillcan::getCurrentDevice() { return this->upDevicePool->getCurrentDevice(); }

    Window* Fillcan::getWindow() { return this->upWindow.get(); }

    std::vector<char> Fillcan::readFile(std::string fileLocation, size_t* fileSize) {
        std::ifstream fileStream(fileLocation, std::ios::ate | std::ios::binary);
        if (!fileStream.is_open()) {
            throw std::runtime_error("Failed to open file");
        }
        // std::ios::ate brought us to the end so we can use tellg to get the position (size) of the file
        *fileSize = static_cast<size_t>(fileStream.tellg());
        std::vector<char> sourceText(*fileSize);

        // Go to the start of the file and put all data in buffer
        fileStream.seekg(0);
        fileStream.read(sourceText.data(), *fileSize);
        fileStream.close();
        return sourceText;
    }

    std::unique_ptr<ShaderModule> Fillcan::createShaderModule(const std::string shaderDirectory, const std::string shaderFileName,
                                                              shaderc_shader_kind shaderKind,
                                                              std::vector<std::unique_ptr<DescriptorSetLayout>> upDescriptorSetLayouts,
                                                              std::unique_ptr<DescriptorPool> upDescriptorPool, bool preprocess, bool optimize) {
        shaderc::Compiler compiler;
        shaderc::CompileOptions options;

        // options.AddMacroDefinition("MY_DEFINE", "1");

        size_t shaderFileSize;
        std::vector<char> shaderSourceText = readFile(shaderDirectory + "/" + shaderFileName, &shaderFileSize);

        if (preprocess) {
            shaderc::PreprocessedSourceCompilationResult preProcessResult =
                compiler.PreprocessGlsl(shaderSourceText.data(), shaderFileSize, shaderKind, shaderFileName.c_str(), options);
            if (preProcessResult.GetCompilationStatus() != shaderc_compilation_status_success) {
                throw preProcessResult.GetErrorMessage();
            }
        }

        if (optimize) {
            options.SetOptimizationLevel(shaderc_optimization_level_performance);
        }

        shaderc::SpvCompilationResult spvResult =
            compiler.CompileGlslToSpv(shaderSourceText.data(), shaderFileSize, shaderKind, shaderFileName.c_str(), options);

        if (spvResult.GetCompilationStatus() != shaderc_compilation_status_success) {
            throw spvResult.GetErrorMessage();
        }

        std::vector<uint32_t> spirvCode = {spvResult.begin(), spvResult.end()};

        return std::move(
            std::make_unique<ShaderModule>(this->getCurrentDevice(), spirvCode, std::move(upDescriptorSetLayouts), std::move(upDescriptorPool)));
    }

    CommandRecording* Fillcan::beginSingleTimeCommands(Queue* pQueue) {
        fillcan::CommandRecording* singleTimeRecording = pQueue->createRecording(1, 0);
        for (CommandBuffer* pCommandBuffer : singleTimeRecording->pPrimaryCommandBuffers) {
            pCommandBuffer->begin();
        }
        return singleTimeRecording;
    }

    void Fillcan::endSingleTimeCommands(CommandRecording* pCommandRecording) {
        pCommandRecording->endAll();
        pCommandRecording->submit();
        pCommandRecording->pQueue->waitIdle();
        pCommandRecording->free();
    }
} // namespace fillcan