#pragma once

// vulkan
#include "vulkan/vulkan_core.h"

// fillcan

// std
#include <string>

namespace fillcan {
    class LogicalDevice;
    class DescriptorPool;
    class DescriptorSetLayout;
    class ImageView;
    class Buffer;
    class BufferView;
    class Sampler;
    class DescriptorSet {
      private:
        VkDescriptorSet hDescriptorSet;
        LogicalDevice* pLogicalDevice;
        DescriptorSetLayout* pDescriptorSetLayout;
        std::string name = "undefined";

        void update(VkWriteDescriptorSet* pWrite, VkCopyDescriptorSet* pCopy);
        void write(VkDescriptorSetLayoutBinding binding, VkDescriptorImageInfo* pImageInfo, VkDescriptorBufferInfo* pBufferInfo,
                   VkBufferView* pTexelBufferView, unsigned int dstArrayElement = 0, unsigned int descriptorCount = 1);

      public:
        /**
         * @brief Create a new Descriptor Set.
         *
         * @details The Descriptor Set class takes a pointer to a Logical Device, a handle to the Vulkan Descriptor Set which it will wrap around and
         * the descriptor set layout which describes it's bindings The Descriptor Set class acts as a wrapper around the Vulkan Descriptor Set for
         * updating and copying it's contents.
         *
         * A descriptor is a special opaque shader variable used by shaders to indirectly access buffer and image resources. It can be seen as a
         * "pointer" to a resource. The Vulkan API allows these variables to be changed between drawing operations so that the shaders have access to
         * different resources for each rendering. A descriptor set is called a "set" because it can refer to a set of homogeneous resources that can
         * be described with the same layout binding.

         * A descriptor set is a set of resources tied to the pipeline as a group. Multiple sets can be tied to a pipeline at the same time. Each set
         * has a layout, which describes the order and types of resources in the set. Two sets with the same layout are considered compatible and
         * interchangeable. The layout of the descriptor set is represented by an object and sets are created with respect to this object.
         * Furthermore, the set of sets accessible to a pipeline is grouped together in another object: the pipeline layout. Pipelines are created in
         * relation to this pipeline layout object.
         *
         *
         * @param pLogicalDevice A pointer to the Logical Device the descriptor det should be associated with.
         * @param pDescriptorPool A pointer to the descriptor pool to allocate from.
         * @param pDescriptorSetLayout A pointer to the descriptor set layout describing the bindings.
         * @param name The identifying name of the descriptor set.
         *
         * @throws std::runtime_error if the Vulkan Descriptor Set failed to be allocated.
         * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkDescriptorSet.html
         *
         * @note It is recommended to not create a Descriptor Set by it's Constructor, but to use DescriptorPool#allocateDescriptorSet instead.
         */
        DescriptorSet(LogicalDevice* pLogicalDevice, DescriptorPool* pDescriptorPool, DescriptorSetLayout* pDescriptorSetLayout, std::string name);

        ~DescriptorSet();
        DescriptorSet(const DescriptorSet&) = delete;
        DescriptorSet& operator=(const DescriptorSet&) = delete;

        /**
         * @brief Get the handle to the Vulkan Descriptor Set.
         *
         * @return The handle to the Vulkan Descriptor Set.
         */
        const VkDescriptorSet getDescriptorSetHandle() const;

        /**
         * @brief Get the descriptor set layout.
         *
         * @return A pointer to the descriptor set layout.
         */
        DescriptorSetLayout* getLayout();

        /**
         * @brief Get the identifying name of the descriptor set.
         *
         * @return The identifying name of the descriptor set.
         */
        std::string getName();

        /**
         * @brief Bind an image to a given binding of the descriptor set.
         *
         * @param binding The binding-index of the descriptor set the resource should be bound to.
         * @param pImageView The image view of the image to be bound in the descriptor set.
         * @param imageLayout The layout in which the image is expected to be when used in the descriptor set. This is a member of the VkImageLayout
         * enumerant.
         * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkImageLayout.html
         * @param pSampler If the descriptor set was created with the descriptor type set to VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, a handle to
         * the corresponding image view's sampler (given in the pImageView field) is specified herein.
         * @param dstArrayElement If the binding in the set references an array of resources, dstArrayElement is used to specify the update start
         * index. If the target binding is not an array, it should be set to 0.
         * @param descriptorCount Used to specify the number of consecutive descriptors, after the specified index in the dstArrayElement field, to be
         * updated. If the target binding is not an array, it should be set to 1.
         */
        void writeImage(VkDescriptorSetLayoutBinding binding, ImageView* pImageView, VkImageLayout imageLayout, Sampler* pSampler,
                        unsigned int dstArrayElement = 0, unsigned int descriptorCount = 1);

        /**
         * @brief Bind a buffer to a given binding of the descriptor set.
         *
         * @param binding The binding-index of the descriptor set the resource should be bound to.
         * @param pBuffer The buffer to be bound in the descriptor set.
         * @param offset From which point in the buffer to bind. The offset of the binding in bytes.
         * @param range How much of the buffer to bind. The size of the binding in bytes. The bound range must be completely within the buffer object.
         * the corresponding image view's sampler (given in the pImageView field) is specified herein.
         * @param dstArrayElement If the binding in the set references an array of resources, dstArrayElement is used to specify the update start
         * index. If the target binding is not an array, it should be set to 0.
         * @param descriptorCount Used to specify the number of consecutive descriptors, after the specified index in the dstArrayElement field, to be
         * updated. If the target binding is not an array, it should be set to 1.
         */
        void writeBuffer(VkDescriptorSetLayoutBinding binding, Buffer* pBuffer, VkDeviceSize offset = 0, VkDeviceSize range = VK_WHOLE_SIZE,
                         unsigned int dstArrayElement = 0, unsigned int descriptorCount = 1);

        /**
         * @brief Bind a texel buffer view to a given binding of the descriptor set.
         *
         * @param binding The binding-index of the descriptor set the resource should be bound to.
         * @param pBufferView The texel buffer view to be bound in the descriptor set.
         * the corresponding image view's sampler (given in the pImageView field) is specified herein.
         * @param dstArrayElement If the binding in the set references an array of resources, dstArrayElement is used to specify the update start
         * index. If the target binding is not an array, it should be set to 0.
         * @param descriptorCount Used to specify the number of consecutive descriptors, after the specified index in the dstArrayElement field, to be
         * updated. If the target binding is not an array, it should be set to 1.
         */
        void writeTexelBufferView(VkDescriptorSetLayoutBinding binding, BufferView* pTexelBufferView, unsigned int dstArrayElement = 0,
                                  unsigned int descriptorCount = 1);

        /**
         * @brief Copy this descriptor set to another descriptor set.
         *
         * @param srcDescriptorSetBinding The binding index of the descriptor within the set to copy from.
         * @param pDstDescriptorSet A pointer to the descriptor set to copy to.
         * @param dstDescriptorSetBinding The binding index of the descriptor within the set to copy to.
         * @param dstArrayElement If the binding in the set references an array of resources, dstArrayElement is used to specify the update start
         * index. If the target binding is not an array, it should be set to 0.
         * @param descriptorCount Used to specify the number of consecutive descriptors, after the specified index in the dstArrayElement field, to be
         * updated. If the target binding is not an array, it should be set to 1.
         */
        void copy(VkDescriptorSetLayoutBinding srcDescriptorSetBinding, DescriptorSet* pDstDescriptorSet,
                  VkDescriptorSetLayoutBinding dstDescriptorSetBinding, unsigned int dstArrayElement = 0, unsigned int descriptorCount = 1);
    };
} // namespace fillcan