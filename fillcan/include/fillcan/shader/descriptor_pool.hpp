#pragma once

// vulkan
#include "vulkan/vulkan_core.h"

// fillcan
#include <fillcan/shader/descriptor_set.hpp>
#include <fillcan/shader/descriptor_set_layout.hpp>

// std
#include <memory>
#include <string>
#include <vector>

namespace fillcan {
    class LogicalDevice;
    class DescriptorPool {
      private:
        VkDescriptorPool hDescriptorPool;
        LogicalDevice* pLogicalDevice;
        VkDescriptorPoolCreateFlags flags;
        unsigned int maxSets;
        std::vector<VkDescriptorPoolSize> poolSizes;
        std::vector<std::unique_ptr<DescriptorSet>> upDescriptorSets = {};

      public:
        /**
         * @brief Create a new Descriptor Pool.
         *
         * @details The Descriptor Pool class takes a pointer to a Logical Device along with flags describing the supported operations and information
         * about the descriptor sets to be allocated and uses this information to construct a Vulkan Descriptor Pool from which it can allocate
         * descriptor sets.
         *
         * Resources are represented by descriptors and are bound to the pipeline by first binding their descriptors into sets and then binding those
         * descriptor sets to the pipeline. This allows a large number of resources to be bound with very little processing time, as the exact set of
         * resources used by a particular drawing command can be predetermined and the descriptor set containing them can be pre-created. The
         * descriptors are allocated from descriptor pools. Descriptors for different types of resources are likely to have similar data structures in
         * a given implementation. Pooling the mappings used to store descriptors allows drivers to make efficient use of memory.
         *
         * @param pLogicalDevice A pointer to the Logical Device the Descriptor Pool should be associated with.
         * @param flags A bitmask of VkDescriptorPoolCreateFlagBits that specify additional information about the allocation strategy to use to manage
         * the resources consumed by the pool.
         * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkDescriptorPoolCreateFlagBits.html
         * @param maxSets The maximum total number of descriptor sets that can be allocated from the pool.
         * @param poolSizes A list of VkDescriptorPoolSize-structures where each structure specifies the number of descriptors of a particular type
         * that can be allocated from the pool.
         * If no element in the list specifies a particular type of resource, then no descriptors of that type can be allocated from the resulting
         * pool. If a particular resource type appears twice in the array, the sum of all their descriptorCount fields (of the
         * VkDescriptorPoolSize-structure) is used to determine the pool for that resource type. The total number of resources in the pool is
         * distributed across the sets allocated from the pool.
         * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkDescriptorPoolSize.html
         *
         * @note It is recommended to not create a Descriptor Pool by it's Constructor, but to use a Descriptor Pool Builder instead.
         */
        DescriptorPool(LogicalDevice* pLogicalDevice, VkDescriptorPoolCreateFlags flags, unsigned int maxSets,
                       std::vector<VkDescriptorPoolSize> poolSizes);
        ~DescriptorPool();
        DescriptorPool(const DescriptorPool&) = delete;
        DescriptorPool& operator=(const DescriptorPool&) = delete;

        /**
         * @brief Get the handle to the Vulkan Descriptor Pool.
         *
         * @return The handle to the Vulkan Descriptor Pool.
         */
        const VkDescriptorPool getDescriptorPoolHandle() const;

        /**
         * @brief Allocate a single descriptor set.
         *
         * @details Assigns a block with descriptors from the pool by creating a new descriptor set. The given name can be used as an identifier to
         * retrieve the allocated descriptor set.
         *
         * @param pDescriptorSetLayout A pointer to the descriptor set layout describing the descriptor set.
         * @param name The identifying name of the descriptor set.
         * @return A pointer to the created descriptor set.
         *
         * @throws std::runtime_error if the Descriptor Set failed to be created.
         */
        DescriptorSet* allocateDescriptorSet(DescriptorSetLayout* pDescriptorSetLayout, std::string name);

        /**
         * @brief Get all the allocated descriptor sets.
         *
         * @return A list of pointers to the allocated descriptor sets.
         */
        std::vector<DescriptorSet*> getDescriptorSets();

        /**
         * @brief Get an allocated descriptor set by name.
         *
         * @param name The name of the descriptor set.
         * @return A pointer to the requested descriptor set or nullptr if no descriptor set with the given name was found.
         */
        DescriptorSet* getDescriptorSet(std::string name);

        /**
         * @brief Free all the allocated descriptor sets.
         *
         * @details If the descriptor pool was created with the flags field set to VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT, descriptor sets
         * can be returned to the pool by freeing them.
         *
         * @return true if all the descriptor sets were succesfully freed.
         * @return false if not all descriptor sets could be freed.
         */
        bool freeDescriptorSets();

        /**
         * @brief Free all the given allocated descriptor sets.
         *
         * @details If the descriptor pool was created with the flags field set to VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT, descriptor sets
         * can be returned to the pool by freeing them.
         *
         * @param pDescriptorSets A list of pointers to descriptor sets to be freed.
         *
         * @return true if all the descriptor sets were succesfully freed.
         * @return false if not all descriptor sets could be freed.
         */
        bool freeDescriptorSets(std::vector<DescriptorSet*> pDescriptorSets);

        /**
         * @brief Reset the descriptor pool.
         *
         * @return true if the descriptor pool was succesfully reset.
         * @return false if the descriptor pool failed to reset.
         */
        bool reset();
    };
} // namespace fillcan