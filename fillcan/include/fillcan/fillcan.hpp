#pragma once
// vulkan
#include "vulkan/vulkan_core.h"

// fillcan
#include <fillcan/commands/command_pool.hpp>
#include <fillcan/commands/command_recording.hpp>
#include <fillcan/graphics/swapchain.hpp>
#include <fillcan/instance/device_pool.hpp>
#include <fillcan/instance/instance.hpp>
#include <fillcan/instance/physical_device.hpp>
#include <fillcan/shader/shader_module.hpp>
#include <fillcan/window.hpp>

// std
#include <chrono>
#include <cstddef>
#include <functional>
#include <memory>
#include <vector>

// shaderc
#include <shaderc/shaderc.h>
#include <shaderc/shaderc.hpp>
#include <shaderc/status.h>

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
        /**
         * @brief Intialize the Fillcan API.
         *
         * @details Initializes the Window, Instance, and Device Pool.
         *
         * @param pApplicationName The name of the application.
         * @param applicationVersion The version of the application.
         * @param windowWidth The initial width the window.
         * @param windowHeight The initial height the window.
         * @param requiredDeviceFeatures The features a Physical Device should have for the purposes of the application. This should be a
         * VkPhysicalDeviceFeatures-structure where each required feature should be set to true.
         * @param requiredDeviceExtensions The extensions a Physical Device should enable for the purposes of the application. This should be a list
         * of strings containing the names of the extensions to enable. The available extensions can be retrieved using
         * vkEnumerateInstanceExtensionProperties(). To be able to use a Swapchain this list should contain VK_KHR_SWAPCHAIN_EXTENSION_NAME (Fillcan
         * Graphics contains this by default).
         * In this version of Fillcan the window can not be detached from the application because the Instance might require certain extensions
         * requested by the window and the Physical Device requires a window to validate support for certain features.
         */
        Fillcan(const char* pApplicationName, uint32_t applicationVersion, unsigned int windowWidth, unsigned int windowHeight,
                VkPhysicalDeviceFeatures requiredDeviceFeatures = {}, std::vector<const char*> requiredDeviceExtensions = {});
        ~Fillcan();
        Fillcan(const Fillcan&) = delete;
        Fillcan& operator=(const Fillcan&) = delete;

        /**
         * @brief Get the supported Physical Devices.
         *
         * @return A list of all the Physical Devices that meet the requirements for the purposes of this implementation.
         */
        const std::vector<PhysicalDevice> getSupportedPhysicalDevices() const;

        /**
         * @brief Select a physical device by index to create a logical device of.
         *
         * @param deviceIndex The index of the physical device within the list of supported physical device.
         *
         * @see Fillcan#getSupportedPhysicalDevices
         *
         * @return A pointer to the created logical device.
         */
        LogicalDevice* selectDevice(unsigned int deviceIndex = 0);

        /**
         * @brief Get the currently selected Logical Device.
         *
         * @see Fillcan#selectDevice
         *
         * @return A pointer to the currently selected Logical Device.
         */
        LogicalDevice* getCurrentDevice();

        /**
         * @brief Get the Window.
         *
         * @return A pointer to the Window.
         */
        Window* getWindow();

        /**
         * @brief Create a Shader Module object.
         *
         * @details Uses Shaderc (https://github.com/google/shaderc) to compile the file (defined by @param shaderDirectory and @param shaderFileName)
         * from GLSL to SPIR-V.
         * Any resources the shader might need should be passed using the descriptor set layouts and the descriptor pool, both are unique pointers
         * which ownerships should be moved to the Shader Module using std::move.
         *
         * @param shaderDirectory The directory where the GLSL shader file is located.
         * @param shaderFileName The name of the GLSL shader file.
         * @param shaderKind The kind of shader (e.g. vertex, fragment, compute, etc.).
         * @param upDescriptorSetLayouts A unique pointer to a list of the descriptor set layouts describing the resources the shader should have
         * access to. Please use std::move to transfer ownership. @see DescriptorSetLayoutBuilder for creating descriptor set layouts.
         * @param upDescriptorPool A unique pointer to the descriptor pool where the descriptor sets can be retrieved from. Please use
         * std::move to transfer ownership. @see DescriptorPoolBuilder for creating descriptor set layouts.
         * @param preprocess Whether to preprocess the shader to validate the GLSL code. This will throw an exception if the shader failed to compile.
         * @param optimize Whether the optimize the shader.
         * @return A unique pointer of the created Shader Module (ownership will be transferred to the implementation).
         */
        std::unique_ptr<ShaderModule> createShaderModule(const std::string shaderDirectory, const std::string shaderFileName,
                                                         shaderc_shader_kind shaderKind,
                                                         std::vector<std::unique_ptr<DescriptorSetLayout>> upDescriptorSetLayouts,
                                                         std::unique_ptr<DescriptorPool> upDescriptorPool, bool preprocess = true,
                                                         bool optimize = false);

        /**
         * @brief Start a Command Recording with a given Queue.
         *
         * @details Creates a Command Recording using the given Queue pointer. This Command Recording will contain 1 (one) Primary Command Buffer and
         * 0 (zero) Secondary Command Buffers. To end the recording, call @see Fillcan#endSingleTimeRecording.
         *
         * @see CommandRecording
         * @see CommandBuffer
         *
         * @param pQueue A pointer to the Queue from which a Command Recording will be created from.
         * @return A pointer to the created Command Recording.
         */
        CommandRecording* beginSingleTimeRecording(Queue* pQueue);

        /**
         * @brief End a Command Recording.
         *
         * @details Ends a Command Recording (preferably created using @see Fillcan#beginSingleTimeRecording), submits the recording and waits for the
         * Queue to idle before returning.
         *
         * @param pCommandRecording The Command Recording to end.
         */
        void endSingleTimeRecording(CommandRecording* pCommandRecording);
    };
} // namespace fillcan