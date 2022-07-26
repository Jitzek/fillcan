#pragma once

// vulkan
#include "vulkan/vulkan_core.h"

// std
#include <cstdint>
#include <memory>
#include <vector>

namespace fillcan {
    class RenderPass;
    class LogicalDevice;
    class RenderPassBuilder {
      private:
        LogicalDevice* pLogicalDevice = nullptr;

        std::vector<VkAttachmentDescription> attachmentDescriptions = {};

        std::vector<VkAttachmentReference> inputAttachments = {};
        std::vector<VkAttachmentReference> colorAttachments = {};
        std::unique_ptr<VkAttachmentReference> upDepthStencilAttachment = nullptr;
        std::vector<uint32_t> preserveAttachments = {};
        bool resolveCurrentBatch = false;

        std::vector<VkSubpassDescription> subpassDescriptions = {};
        std::vector<VkSubpassDependency> dependencyDescriptions = {};

      public:
        /**
         * @brief Create a new Render Pass Builder.
         *
         * @details The Render Pass Builder class is part of the creational design pattern to construct complex objects step by step.
         * The Builder pattern allows you to produce different types and representations of an object using the same construction code.
         *
         */
        RenderPassBuilder();
        ~RenderPassBuilder();

        /**
         * @brief Set the Logical Device for the Render Pass.
         *
         * @param pLogicalDevice A pointer to the Logical Device the render pass should be associated with.
         */
        void setLogicalDevice(LogicalDevice* pLogicalDevice);

        /**
         * @brief Add an attachment to be referenced as either input, color or depth-stencil.
         *
         * @param attachmentDescription A VkAttachmentDescription-structure. this structure defines a single image to be used as input,
         * output, or both within one or more of the subpasses in the render pass.
         * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkAttachmentDescription.html
         *
         * @return The index of the added attachment.
         */
        unsigned int addAttachment(VkAttachmentDescription attachmentDescription);

        /**
         * @brief Define a single input attachment, which is an attachment from which data can be read.
         *
         * @param attachmentDescriptionIndex The index of the attachment within the {attachmentDescriptions}-list. This index was returned when the
         * attachment was added using RenderPassBuilder#addAttachment.
         * @param layout The image layout which the attachment is expected to be in within this subpass.
         * @param preserve If there are attachments that should persist for the time in a subpass, but are not directly referenced by the subpass,
         * they should be referenced as preserved. This reference prevents Vulkan from performing optimizations that could disrupt
         * the content of those attachments.
         */
        void addInputAttachment(unsigned int attachmentDescriptionIndex, VkImageLayout layout, bool preserve);

        /**
         * @brief Define a single color attachment, which is an attachment to which the output of the subpass is written.
         *
         * @param attachmentDescriptionIndex The index of the attachment within the {attachmentDescriptions}-list. This index was returned when the
         * attachment was added using RenderPassBuilder#addAttachment.
         * @param layout The image layout which the attachment is expected to be in within this subpass.
         * @param preserve If there are attachments that should persist for the time in a subpass, but are not directly referenced by the subpass,
         * they should be referenced as preserved. This reference prevents Vulkan from performing optimizations that could disrupt
         * the content of those attachments.
         */
        void addColorAttachment(unsigned int attachmentDescriptionIndex, VkImageLayout layout, bool preserve);

        /**
         * @brief Define the depth and stencil buffer for this subpass.
         *
         * @param attachmentDescriptionIndex The index of the attachment within the {attachmentDescriptions}-list. This index was returned when the
         * attachment was added using RenderPassBuilder#addAttachment.
         * @param layout The image layout which the attachment is expected to be in within this subpass.
         * @param preserve If there are attachments that should persist for the time in a subpass, but are not directly referenced by the subpass,
         * they should be referenced as preserved. This reference prevents Vulkan from performing optimizations that could disrupt
         * the content of those attachments.
         */
        void setDepthStencilAttachment(unsigned int attachmentDescriptionIndex, VkImageLayout layout, bool preserve);

        /**
         * @brief Mark the current batch of color attachments as resolved, these are attachments to which multisample image data is converted.
         */
        void resolveCurrentAttachments();

        /**
         * @brief Construct a new subpass from the current batch of attachments. The current batch contains all the attachments added after the last
         * subpass construction or after the initialization of the builder.
         *
         * @return The index of the newly constructed subpass.
         */
        unsigned int constructSubpass();

        /**
         * @brief Add a subpass dependency.
         *
         * @details When there is more than one subpass in a render pass, Vulkan can figure out which subpasses are dependent on each other by
         * following the attachment references and looking for inputs and outputs that make subpasses dependent on each other. However, there are
         * cases where dependencies cannot be easily represented by a simple input-to-output relationship. This generally happens when a subpass
         * writes directly to a resource, such as an image or buffer, and a subsequent subpass reads that data back. Vulkan cannot figure this out
         * automatically, so it must explicitly indicate such dependency information.
         *
         * @param dependencyDescription A VkSubpassDependency-structure. The indices of both the source subpass and the destination subpass can be
         * determined using the index return by RenderPassBuilder#constructSubpass.
         */
        void addDependency(VkSubpassDependency dependencyDescription);

        /**
         * @brief Get the resulting Render Pass.
         *
         * @return A unique pointer to the Render Pass, it's ownership will be moved.
         *
         * @throws std::runtime_error if the Render Pass couldn't be created.
         */
        std::unique_ptr<RenderPass> getResult();

        /**
         * @brief Reset the Builder to it's default values.
         */
        void reset();
    };
} // namespace fillcan