#pragma once

// vulkan
#include "vulkan/vulkan_core.h"

// fillcan
#include <fillcan/shader/pipeline.hpp>
#include <fillcan/shader/pipeline_layout.hpp>

// std
#include <memory>

namespace fillcan {
    class LogicalDevice;
    class CommandBuffer;
    class ComputePipeline : public Pipeline {
      private:
      public:
        /**
         * @brief Create a new Compute Pipeline.
         *
         * @details The Compute Pipeline class extends the Pipeline class.
         *
         * The compute shader provides direct access to the computing capabilities of the Vulkan device. The device can be thought of as a collection
         * of broad vector processing units operating on related data. A compute shader is written as if it were a serial, single run track. However,
         * many of these run tracks can run simultaneously. This is how most Vulkan devices are built. Each track of execution is called an
         * invocation. When a compute shader is running, many calls are made at once. The invocations are grouped into fixed size local workgroups,
         * then one or more of these groups are run together in what is sometimes known as a global workgroup. Logically, both the local and global
         * workgroups are three-dimensional. However, if the size of one of the three dimensions is set to one, the dimensionality of the group is
         * reduced.
         *
         * @param pLogicalDevice A pointer to the Logical Device the pipeline should be associated with.
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
         * @throws std::runtime_error if the Vulkan Compute Pipeline couldn't be created.
         * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkPipeline.html
         */
        ComputePipeline(LogicalDevice* pLogicalDevice, VkPipelineCreateFlags flags, std::vector<PipelineShaderStage> shaderStages,
                        std::vector<PushConstant> pushConstants, VkPipelineCache pipelineCache = VK_NULL_HANDLE, Pipeline* pBasePipeline = nullptr);
        ~ComputePipeline();

        ComputePipeline(const ComputePipeline&) = delete;
        ComputePipeline& operator=(const ComputePipeline&) = delete;
    };
} // namespace fillcan