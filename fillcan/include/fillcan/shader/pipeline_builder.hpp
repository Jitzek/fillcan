#pragma once
// vulkan
#include "vulkan/vulkan_core.h"

// fillcan
#include <fillcan/shader/pipeline_layout.hpp>

// std
#include <string>
#include <vector>

namespace fillcan {
    class LogicalDevice;
    class Pipeline;
    class CommandBuffer;
    class PipelineBuilder {
      protected:
        LogicalDevice* pLogicalDevice = nullptr;
        VkPipelineCreateFlags flags = 0;
        std::vector<PushConstant> pushConstants = {};
        VkPipelineCache pipelineCache = VK_NULL_HANDLE;
        Pipeline* pBasePipeline = nullptr;

      public:
        /**
         * @brief Create a new Pipeline Builder.
         *
         * @details The Pipeline Builder class is part of the creational design pattern to construct complex objects step by step.
         * The Builder pattern allows you to produce different types and representations of an object using the same construction code.
         *
         * @note The Pipeline Builder class is meant to be extended as it only asks for the generic information shared by all pipelines.
         */
        PipelineBuilder();
        virtual ~PipelineBuilder();

        /**
         * @brief Set the Logical Device for the Pipeline.
         *
         * @param pLogicalDevice A pointer to the Logical Device the Pipeline should be associated with.
         */
        void setLogicalDevice(LogicalDevice* pLogicalDevice);

        /**
         * @brief Set the flags for the Pipeline.
         *
         * @param flags A bitmask of VkPipelineCreateFlagBits controlling how the pipeline is created.
         * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkPipelineCreateFlags.html
         */
        void setFlags(VkPipelineCreateFlags flags);

        /**
         * @brief Set the push constants for the pipeline.
         *
         * @param name The identifying name for the push constant.
         * @param pushConstantRange A VkPushConstantRange-structure defining the size and offset of the push constant.
         * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkPushConstantRange.html
         */
        void addPushConstant(std::string name, VkPushConstantRange pushConstantRange);

        /**
         * @brief Set the pipeline cache for the pipeline.
         *
         * @param pipelineCache A handle to a Vulkan Pipeline Cache object.
         * Allows the result of pipeline construction to be reused between pipelines and between runs of an application. Reuse between pipelines is
         * achieved by passing the same pipeline cache object when creating multiple related pipelines. Reuse across runs of an application is
         * achieved by retrieving pipeline cache contents in one run of an application, saving the contents, and using them to preinitialize a
         * pipeline cache on a subsequent run.
         * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkPipelineCache.html
         */
        void setPipelineCache(VkPipelineCache pipelineCache);

        /**
         * @brief Set the base pipeline for the pipeline.
         *
         * @param pBasePipeline  A pointer to the pipeline to derive from.
         * A pipeline derivative is a child pipeline created from a parent pipeline, where the child and parent pipeline are expected to have a lot of
         * commonality. The purpose of derived pipelines is that they can be made cheaper with the parent in mind, and that it is more efficient (on
         * host or device) to switch/bind between.
         */
        void setBasePipeline(Pipeline* pBasePipeline);

        /**
         * @brief Reset the Builder to it's default values.
         */
        virtual void reset();
    };
} // namespace fillcan