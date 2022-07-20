#pragma once

// vulkan
#include "vulkan/vulkan_core.h"

// fillcan
#include <fillcan/shader/descriptor_pool.hpp>
#include <fillcan/shader/descriptor_set_layout.hpp>
#include <fillcan/shader/descriptor_set_layout_builder.hpp>

// std
#include <memory>
#include <vector>

namespace fillcan {
    class LogicalDevice;
    class ShaderModule {
      private:
        VkShaderModule hShaderModule;
        LogicalDevice* pLogicalDevice;
        std::vector<std::unique_ptr<DescriptorSetLayout>> upDescriptorSetLayouts = {};
        std::unique_ptr<DescriptorPool> upDescriptorPool = nullptr;

      public:
        /**
         * @brief Create a new Shader Module.
         *
         * @details  The Shader Module class takes a pointer to a Logical Device along with a list of characters representing the GLSL code and a list
         * of unique pointers to the descriptor set layouts describing the descriptor sets that expose resources to the shader, and a unique pointer
         * to a descriptor pool from which the descriptor sets will be allocated. Note that the ownership of both the descriptor set layouts and the
         * descriptor pool needs to be transferred using std::move. Shaders are small programs that run directly on the device (like a GPU). Shaders
         * are the fundamental building blocks of the work to be done on the device.
         *
         * Vulkan shaders are represented by SPIR-V (Standard Portable Intermediate Representation), a binary intermediate representation of program
         * code. SPIR-V can be generated outside the application using a compiler, directly in the application or by passing a high-level language to
         * a library at run-time.
         *
         * The original shaders are written in GLSL using the Vulkan profile. This is a modified and extended version of the same shading language
         * used with OpenGL. Most examples therefore discuss Vulkan features in terms of their representation in GLSL.
         * Note that Vulkan itself knows nothing about GLSL and only cares about the compiled SPIR-V representation.

         * The Shader Module class compiles GLSL shaders at run-time using Shaderc.
         * @see https://github.com/google/shaderc
         *
         * @param pLogicalDevice The Logical Device that owns the Shader Module.
         * @param code The SPIR-V code.
         * @param upDescriptorSetLayouts A unique pointer to a list of the descriptor set layouts describing the descriptor sets that expose resources
         * to the shader. Ownerships needs to be transferred using std::move.
         * @see https://en.cppreference.com/w/cpp/utility/move
         * @param upDescriptorPool A unique pointer to a descriptor pool from which the descriptor sets will be allocated. Ownership needs to be
         * transferred using std::move.
         * @see https://en.cppreference.com/w/cpp/utility/move
         *
         * @note It is recommended to not create a Shader Module by it's Constructor, but to use Fillcan#createShaderModule instead.
         */
        ShaderModule(LogicalDevice* pLogicalDevice, std::vector<char>& code, std::vector<std::unique_ptr<DescriptorSetLayout>> upDescriptorSetLayouts,
                     std::unique_ptr<DescriptorPool> upDescriptorPool);

        /**
         * @brief Create a new Shader Module.
         *
         * @details  The Shader Module class takes a pointer to a Logical Device along with a list of characters representing the GLSL code and a list
         * of unique pointers to the descriptor set layouts describing the descriptor sets that expose resources to the shader, and a unique pointer
         * to a descriptor pool from which the descriptor sets will be allocated. Note that the ownership of both the descriptor set layouts and the
         * descriptor pool needs to be transferred using std::move. Shaders are small programs that run directly on the device (like a GPU). Shaders
         * are the fundamental building blocks of the work to be done on the device.
         *
         * Vulkan shaders are represented by SPIR-V (Standard Portable Intermediate Representation), a binary intermediate representation of program
         * code. SPIR-V can be generated outside the application using a compiler, directly in the application or by passing a high-level language to
         * a library at run-time.
         *
         * The original shaders are written in GLSL using the Vulkan profile. This is a modified and extended version of the same shading language
         * used with OpenGL. Most examples therefore discuss Vulkan features in terms of their representation in GLSL.
         * Note that Vulkan itself knows nothing about GLSL and only cares about the compiled SPIR-V representation.

         * The Shader Module class compiles GLSL shaders at run-time using Shaderc.
         * @see https://github.com/google/shaderc
         *
         * @param pLogicalDevice The Logical Device that owns the Shader Module.
         * @param code The SPIR-V code.
         * @param upDescriptorSetLayouts A unique pointer to a list of the descriptor set layouts describing the descriptor sets that expose resources
         * to the shader. Ownerships needs to be transferred using std::move.
         * @see https://en.cppreference.com/w/cpp/utility/move
         * @param upDescriptorPool A unique pointer to a descriptor pool from which the descriptor sets will be allocated. Ownership needs to be
         * transferred using std::move.
         * @see https://en.cppreference.com/w/cpp/utility/move
         *
         * @note It is recommended to not create a Shader Module by it's Constructor, but to use Fillcan#createShaderModule instead.
         */
        ShaderModule(LogicalDevice* pLogicalDevice, std::vector<uint32_t>& code,
                     std::vector<std::unique_ptr<DescriptorSetLayout>> upDescriptorSetLayouts, std::unique_ptr<DescriptorPool> upDescriptorPool);

        ~ShaderModule();
        ShaderModule(const ShaderModule&) = delete;
        ShaderModule& operator=(const ShaderModule&) = delete;


        /**
         * @brief Get the handle to the Vulkan Shader Module.
         *
         * @return The handle to the Vulkan Shader Module.
         * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkShaderModule.html
         */
        const VkShaderModule getShaderModuleHandle() const;

        /**
         * @brief Get the descriptor set layouts.
         * 
         * @return A list of pointers to the descriptor set layouts. 
         */
        std::vector<DescriptorSetLayout*> getDescriptorSetLayouts();

        /**
         * @brief Get the descriptor pool.
         * 
         * @return A pointer to the descriptor pool. 
         */
        DescriptorPool* getDescriptorPool();
    };
} // namespace fillcan