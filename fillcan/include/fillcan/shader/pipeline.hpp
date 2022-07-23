#pragma once

// vulkan
#include "vulkan/vulkan_core.h"

// fillcan
#include <fillcan/shader/pipeline_layout.hpp>

// std
#include <memory>
#include <string>
#include <vector>

namespace fillcan {
    class CommandBuffer;
    class LogicalDevice;
    class PipelineLayout;
    class ShaderModule;
    class DescriptorSetLayout;
    class DescriptorSet;

    struct PipelineShaderStage {
        VkShaderStageFlagBits stage;
        ShaderModule* pShaderModule;
        std::string name;
        // TODO: Specialization Constants
    };

    class Pipeline {
      protected:
        VkPipeline hPipeline;
        LogicalDevice* pLogicalDevice;
        VkPipelineCreateFlags flags;
        std::vector<PipelineShaderStage> shaderStages;
        std::vector<DescriptorSetLayout*> pDescriptorSetLayouts = {};
        std::vector<DescriptorSet*> pDescriptorSets = {};
        std::unique_ptr<PipelineLayout> layout;
        CommandBuffer* pCommandBuffer = nullptr;
        VkPipelineBindPoint bindPoint = VK_PIPELINE_BIND_POINT_MAX_ENUM;

      protected:
        void setBindPoint(VkPipelineBindPoint pipelineBindPoint);

      public:
        /**
         * @brief Create a new Pipeline.
         *
         * @details The Pipeline class takes a pointer to a Logical Device along a pointer to a command buffer, flags controlling how the pipeline is
         * created, a list of shader stages, a list of push constants and a optionally pipeline cache and a base pipeline, and uses this information
         * to construct a Vulkan Pipeline and it's pipeline layout describing it's bound resources.
         *
         * Before shader modules can be used to do useful work on the device, you must create a pipeline. There are two types of pipelines in Vulkan:
         * "compute" and "graphics". The graphics pipeline is quite complex and contains many phases that have nothing to do with shaders. However, a
         * compute pipeline is conceptually much simpler and essentially contains nothing but just the shader code.
         *
         * @param pLogicalDevice A pointer to the Logical Device the Pipeline should be associated with.
         * @param flags A bitmask of VkPipelineCreateFlagBits controlling how the pipeline is created.
         * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkPipelineCreateFlags.html
         * @param shaderStages A list of PipelineShaderStage-structures each of which defining a shader stage of the pipeline.
         * @param pushConstants A list of push constants to be bound to the pipeline.
         * @param pipelineCache A handle to a Vulkan Pipeline Cache object.
         * Allows the result of pipeline construction to be reused between pipelines and between runs of an application. Reuse between pipelines is
         * achieved by passing the same pipeline cache object when creating multiple related pipelines. Reuse across runs of an application is
         * achieved by retrieving pipeline cache contents in one run of an application, saving the contents, and using them to preinitialize a
         * pipeline cache on a subsequent run.
         * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkPipelineCache.html
         * @param pBasePipeline A pointer to the pipeline to derive from.
         * A pipeline derivative is a child pipeline created from a parent pipeline, where the child and parent pipeline are expected to have a lot of
         * commonality. The purpose of derived pipelines is that they can be made cheaper with the parent in mind, and that it is more efficient (on
         * host or device) to switch/bind between.
         *
         * @throws std::runtime_error if the pipeline layout couldn't be created.
         */
        Pipeline(LogicalDevice* pLogicalDevice, VkPipelineCreateFlags flags, std::vector<PipelineShaderStage> shaderStages,
                 std::vector<PushConstant> pushConstants, VkPipelineCache pipelineCache = VK_NULL_HANDLE, Pipeline* pBasePipeline = nullptr);

        virtual ~Pipeline();
        Pipeline(const Pipeline&) = delete;
        Pipeline& operator=(const Pipeline&) = delete;

        /**
         * @brief Get the handle to the Vulkan Pipeline.
         * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkPipeline.html
         *
         * @return The handle to the Vulkan Pipeline.
         */
        const VkPipeline getPipelineHandle() const;

        /**
         * @brief Get the the pipeline layout.
         *
         * @return A pointer to the pipeline layout.
         */
        PipelineLayout* getPipelineLayout();

        /**
         * @brief Bind the pipeline to a command buffer.
         *
         * @details Before a pipeline can be used, it must be bound to a command buffer that executes draw or send commands. This can be done with a
         * command. When this command is executed, the current pipeline (and all shaders in it) is used to process the commands.
         *
         * @param pCommandBuffer A pointer to the command buffer to bind to.
         */
        void bindToCommandBuffer(CommandBuffer* pCommandBuffer);

        /**
         * @brief Get the bound command buffer.
         *
         * @return A pointer to the bound command buffer, or nullptr if no command buffer is bound.
         */
        CommandBuffer* getCommandBuffer();

        /**
         * @brief Bind all the descriptor sets defined within the shader modules of the shader stages to the bound command buffer.
         *
         * @details To access the resources associated with a descriptor set, the descriptor set must be bound to the command
         * buffer that executes the commands that access those descriptors. There are two binding points for descriptor sets — one for compute
         * and one for graphics — these are the sets that can be accessed by the appropriate pipelines.
         *
         * @throws std::runtime_error if the pipeline bindpoint is not set, this should be done by the class that extends the pipeline, @see
         * Pipeline#setBindPoint.
         * @throws std::runtime_error if there is no command buffer bound, @see Pipeline#bindToCommandBuffer.
         */
        void bindDescriptorSets();

        /**
         * @brief Bind the given descriptor sets to the bound command buffer.
         *
         * @details To access the resources associated with a descriptor set, the descriptor set must be bound to the command
         * buffer that executes the commands that access those descriptors. There are two binding points for descriptor sets — one for compute
         * and one for graphics — these are the sets that can be accessed by the appropriate pipelines.
         *
         * @param pDescriptorSets A list of pointers to the descriptor sets to bind to the bound command buffer.
         * @param firstSet The set number of the first descriptor set to bind. This is used to bind a subset of the sets accessible to the pipeline
         * layout.
         *
         * @throws std::runtime_error if the pipeline bindpoint is not set, this should be done by the class that extends the pipeline, @see
         * Pipeline#setBindPoint.
         * @throws std::runtime_error if there is no command buffer bound, @see Pipeline#bindToCommandBuffer.
         */
        void bindDescriptorSets(std::vector<DescriptorSet*> pDescriptorSets, unsigned int firstSet);

        /**
         * @brief Bind the given descriptor sets by name to the bound command buffer.
         *
         * @details To access the resources associated with a descriptor set, the descriptor set must be bound to the command
         * buffer that executes the commands that access those descriptors. There are two binding points for descriptor sets — one for compute
         * and one for graphics — these are the sets that can be accessed by the appropriate pipelines.
         *
         * @param names A list of names of the descriptor sets to bind to the bound command buffer.
         * @param firstSet The set number of the first descriptor set to bind. This is used to bind a subset of the sets accessible to the pipeline
         * layout.
         *
         * @throws std::runtime_error if the pipeline bindpoint is not set, this should be done by the class that extends the pipeline, @see
         * Pipeline#setBindPoint.
         * @throws std::runtime_error if there is no command buffer bound, @see Pipeline#bindToCommandBuffer.
         */
        void bindDescriptorSets(std::vector<std::string> names, unsigned int firstSet);

        /**
         * @brief Get all the descriptor sets of this pipeline.
         *
         * @return A list of pointers to all the descriptor sets of this pipeline.
         */
        std::vector<DescriptorSet*>& getDescriptorSets();

        /**
         * @brief Get a descriptor set by name.
         *
         * @param name The name of the descriptor set to get.
         * @return The descriptor set with the given name, or nullptr if no descriptor set with the given name was found.
         */
        DescriptorSet* getDescriptorSet(std::string name);

        /**
         * @brief Update the value of a push constant using the bound command buffer.
         *
         * @param name The name of the push constant to update.
         * @param upPushConstantData A unique pointer to the new value of the push constant, please use std::move to transfer ownership.
         * @see https://en.cppreference.com/w/cpp/memory/unique_ptr
         * @see https://en.cppreference.com/w/cpp/utility/move
         *
         * @throws std::runtime_error if no push constant with the requested name could be found.
         * @throws std::runtime_error if there is no command buffer bound, @see Pipeline#bindToCommandBuffer.
         */
        void pushConstantData(std::string name, std::unique_ptr<PushConstantData> upPushConstantData);
    };
} // namespace fillcan