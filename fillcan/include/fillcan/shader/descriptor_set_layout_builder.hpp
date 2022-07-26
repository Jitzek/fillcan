#pragma once

// vulkan
#include "vulkan/vulkan_core.h"

// fillcan

// std
#include <memory>
#include <vector>

namespace fillcan {
    class LogicalDevice;
    class DescriptorSetLayout;
    class DescriptorSetLayoutBuilder {
      private:
        LogicalDevice* pLogicalDevice = nullptr;
        std::vector<VkDescriptorSetLayoutBinding> bindings = {};

      public:
        /**
         * @brief Create a new Descriptor Set Layout Builder.
         *
         * @details The Descriptor Set Layout Builder class is part of the creational design pattern to construct complex objects step by step.
         * The Builder pattern allows you to produce different types and representations of an object using the same construction code.
         */
        DescriptorSetLayoutBuilder();
        ~DescriptorSetLayoutBuilder();

        /**
         * @brief Set the Logical Device for the Descriptor Set Layout.
         *
         * @param pLogicalDevice A pointer to the Logical Device the descriptor set layout should be associated with.
         */
        void setLogicalDevice(LogicalDevice* pLogicalDevice);

        /**
         * @brief Add a descriptor set layout binding. Resources are bound by binding points in the descriptor set.
         * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkDescriptorSetLayoutBinding.html
         *
         * @param binding Each resource accessible to a shader is assigned a binding number. The bindings used in a descriptor set do not have to be
         * contiguous and there may be gaps (unused binding numbers) in a set. However, it is recommended that sparsely populated sets are not created
         * as this can waste resources in the device.
         * @param descriptorType The type descriptor on this binding point. This is a member of the VkDescriptorType-enumerator.
         * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkDescriptorType.html
         * @param descriptorCount The number of descriptors in the binding, accessible in a shader as an array, unless descriptorType is
         * VK_DESCRIPTOR_TYPE_INLINE_UNIFORM_BLOCK. In that case, descriptorCount is the size in bytes of the inline uniform block. If descriptorCount
         * is 0, this binding entry is reserved and the resource should not be accessed from any stage through this binding within a pipeline with the
         * layout set.
         * @param stageFlags A bitmask of the VkShaderStageFlagBits-enumerant that specifies which pipeline shader stages can access a resource for
         * this binding.
         * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkShaderStageFlagBits.html
         * @param immutableSamplers Affects sampler initialization. If descriptorType specifies a VK_DESCRIPTOR_TYPE_SAMPLER or
         * VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER type descriptor, then pImmutableSamplers can be used to initialize a set of immutable samplers.
         * Immutable samplers are permanently embedded in the set layout and should not be modified; updating a VK_DESCRIPTOR_TYPE_SAMPLER descriptor
         * with immutable samplers is not allowed and updates of a VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER descriptor with immutable samplers do not
         * change the samplers (the image views are updated, but the sampler updates are ignored).
         */
        void addBinding(unsigned int binding, VkDescriptorType descriptorType, unsigned int descriptorCount, VkShaderStageFlags stageFlags,
                        std::vector<VkSampler> immutableSamplers = {});

        /**
         * @brief Get the resulting Descriptor Set Layout.
         *
         * @return A unique pointer to the Descriptor Set Layout, it's ownership will be moved.
         */
        std::unique_ptr<DescriptorSetLayout> getResult();

        /**
         * @brief Reset the Builder to it's default values.
         */
        void reset();
    };
} // namespace fillcan