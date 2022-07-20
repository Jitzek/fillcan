#pragma once

// vulkan
#include "vulkan/vulkan_core.h"

// fillcan

// std
#include <vector>

namespace fillcan {
    class LogicalDevice;
    class DescriptorSetLayout {
      private:
        VkDescriptorSetLayout hDescriptorSetLayout;
        LogicalDevice* pLogicalDevice;
        std::vector<VkDescriptorSetLayoutBinding> bindings;

      public:
        /**
         * @brief Create a new Descriptor Set Layout.
         *
         * @details The Descriptor Set Layout class takes a pointer to a Logical Device along a list of Vulkan Descriptor Set Layout Bindings and uses
         * this information to construct a Vulkan Descriptor Set Layout.
         *
         * @param pLogicalDevice A pointer to the Logical Device the Descriptor Set Layout should be associated with.
         * @param bindings A list of VkDescriptorSetLayoutBinding-structures. Resources are bound by binding points in the descriptor set. Each member
         * of the supplied list provides a description of a descriptor set layout binding.
         * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkDescriptorSetLayoutBinding.html
         *
         * @throws std::runtime_error if the Vulkan Descriptor Set Layout couldn't be created.
         *
         * @note It is recommended to not create a Descriptor Set Layout by it's Constructor, but to use a Descriptor Set Layout Builder instead.
         */
        DescriptorSetLayout(LogicalDevice* pLogicalDevice, std::vector<VkDescriptorSetLayoutBinding> bindings);
        ~DescriptorSetLayout();
        DescriptorSetLayout(const DescriptorSetLayout&) = delete;
        DescriptorSetLayout& operator=(const DescriptorSetLayout&) = delete;

        /**
         * @brief Get the handle to the Vulkan Descriptor Set Layout.
         *
         * @return The handle to the Vulkan Descriptor Set Layout.
         */
        const VkDescriptorSetLayout getDescriptorSetLayoutHandle() const;

        /**
         * @brief Get a list of the Descriptor Set Layout Bindings.
         *
         * @return A list of the Descriptor Set Layout Bindings.
         */
        const std::vector<VkDescriptorSetLayoutBinding>& getBindings() const;
    };
} // namespace fillcan