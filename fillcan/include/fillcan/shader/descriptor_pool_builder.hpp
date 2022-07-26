#pragma once

// vulkan
#include "vulkan/vulkan_core.h"

// fillcan

// std
#include <memory>
#include <utility>
#include <vector>

namespace fillcan {
    class LogicalDevice;
    class DescriptorPool;
    class DescriptorSetLayout;
    class DescriptorPoolBuilder {
      private:
        struct DescriptorSetInfo {
            std::string name = "undefined";
            DescriptorSetLayout* pLayout = nullptr;
            std::vector<VkDescriptorPoolSize> poolSizes = {};
        };
        LogicalDevice* pLogicalDevice = nullptr;
        VkDescriptorPoolCreateFlags flags = 0;
        unsigned int maxSets = 0;
        std::vector<DescriptorSetLayout*> pDescriptorSetLayouts = {};
        std::vector<DescriptorSetInfo> descriptorSetInfos = {};

      public:
        /**
         * @brief Create a new Descriptor Pool Builder.
         *
         * @details The Descriptor Pool Builder class is part of the creational design pattern to construct complex objects step by step.
         * The Builder pattern allows you to produce different types and representations of an object using the same construction code.
         */
        DescriptorPoolBuilder();

        ~DescriptorPoolBuilder();

        /**
         * @brief Set the Logical Device for the Descriptor Pool.
         *
         * @param pLogicalDevice A pointer to the Logical Device the descriptor pool should be associated with.
         */
        void setLogicalDevice(LogicalDevice* pLogicalDevice);

        /**
         * @brief Set the flags for the Descriptor Pool.
         *
         * @param flags A bitmask of VkDescriptorPoolCreateFlagBits that specify certain supported operations on the descriptor pool.
         * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkDescriptorPoolCreateFlagBits.html
         */
        void setFlags(VkDescriptorPoolCreateFlags flags);

        /**
         * @brief Specify a set of descriptors of a certain type that should be allocatable from the pool.
         *
         * @param pDescriptorSetLayout The descriptor set layout describing the order and types of resources in the set. Two sets with the same layout
         * are considered compatible and interchangeable.
         * @param name The identifying name of the descriptor set.
         */
        void addSet(DescriptorSetLayout* pDescriptorSetLayout, std::string name);

        /**
         * @brief Get the resulting Descriptor Pool.
         *
         * @param allocate Whether to automatically allocate the descriptor sets.
         *
         * @return A unique pointer to the Descriptor Pool, it's ownership will be moved.
         *
         * @throws std::runtime_error if the Descriptor Pool couldn't be created.
         * @throws std::runtime_error if {allocate} is true and the Descriptor Set(s) failed to be created.
         */
        std::unique_ptr<DescriptorPool> getResult(bool allocate = true);

        /**
         * @brief Reset the Builder to it's default values.
         */
        void reset();
    };
} // namespace fillcan