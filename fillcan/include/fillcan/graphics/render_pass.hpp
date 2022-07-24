#pragma once

// vulkan
#include "vulkan/vulkan_core.h"

// fillcan
#include <fillcan/graphics/framebuffer.hpp>

// std
#include <memory>
#include <vector>

namespace fillcan {
    class LogicalDevice;
    class CommandBuffer;
    class ImageView;

    class RenderPass {
      private:
        VkRenderPass hRenderPass;
        LogicalDevice* pLogicalDevice;
        CommandBuffer* pCommandBuffer = nullptr;
        std::vector<VkAttachmentDescription> attachments;
        std::vector<VkSubpassDescription> subpasses;
        std::vector<VkSubpassDependency> dependencies;

      public:
        /**
         * @brief Create a new Render Pass.
         *
         * @details One of the things that distinguishes a Vulkan graphics pipeline from a compute pipeline is that the graphics pipeline is usually
         * used to convert pixels into images that can be further processed or presented to the user. In complex graphics applications, the image is
         * built over many passes with each pass responsible for producing a different part of the scene, applying full-frame effects such as
         * post-processing or compositing, rendering user interface elements, and so on. These passages can be rendered in Vulkan using a renderpass
         * object.
         *
         * A single renderpass object spans multiple passes or render stages over a single set of output images. Each pass within the render pass is
         * known as a subpass. Renderpass objects can contain many subpasses, but even in simple applications with only a single pass over a single
         * output image, the renderpass object contains information about that output image.
         *
         * All drawings must be in a render pass. Furthermore, graphical pipelines need to know where they are being rendered; therefore it is
         * necessary to create a renderpass object before creating a graphics pipeline so that the pipeline can be told about the images it will
         * produce.
         *
         * @param pLogicalDevice A pointer to the Logical Device the render pass should be associated with.
         * @param attachments A list of VkAttachmentDescription-structures. Each of these structures defines a single image to be used as input,
         * output, or both within one or more of the subpasses in the render pass.
         * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkAttachmentDescription.html
         * @param subpasses A list of VkSubpassDescription-structures. Each of these structures defines a single subpass. Each subpass refers to a
         * number of attachments (from the list given in the attachments field) as input or output.
         * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkSubpassDescription.html
         * @param dependencies A list of VkSubpassDependency-structures.
         * When there is more than one subpass in a render pass, Vulkan can figure out which subpasses are dependent on each other by following the
         * attachment references and looking for inputs and outputs that make subpasses dependent on each other. However, there are cases where
         * dependencies cannot be easily represented by a simple input-to-output relationship. This generally happens when a subpass writes directly
         * to a resource, such as an image or buffer, and a subsequent subpass reads that data back. Vulkan cannot figure this out automatically, so
         * it must explicitly indicate such dependency information.
         * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkSubpassDependency.html
         *
         * @throws std::runtime_error if the Vulkan Render Pass couldn't be created.
         * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkRenderPass.html
         */
        RenderPass(LogicalDevice* pLogicalDevice, std::vector<VkAttachmentDescription> attachments, std::vector<VkSubpassDescription> subpasses,
                   std::vector<VkSubpassDependency> dependencies);
        ~RenderPass();
        RenderPass(const RenderPass&) = delete;
        RenderPass& operator=(const RenderPass&) = delete;

        /**
         * @brief Get the handle to the Vulkan Render Pass.
         *
         * @return The handle to the Vulkan Render Pass.
         */
        const VkRenderPass getRenderPassHandle() const;

        /**
         * @brief Get all the attachments.
         *
         * @return A list of VkAttachmentDescription-structures describing the attachments.
         * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkAttachmentDescription.html
         */
        const std::vector<VkAttachmentDescription>& getAttachments() const;

        /**
         * @brief Get all the subpasses.
         *
         * @return A list of VkSubpassDescription-structures describing the subpasses.
         * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkSubpassDescription.html
         */
        const std::vector<VkSubpassDescription>& getSubpasses() const;

        /**
         * @brief Get all the dependencies.
         *
         * @return A list of VkSubpassDependency-structures describing the dependencies.
         * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkSubpassDependency.html
         */
        const std::vector<VkSubpassDependency>& getDependencies() const;

        /**
         * @brief Prepare to render.
         *
         * @details All drawings are in a render pass. While renderpass objects can encapsulate many subpasses, even a simple rendering that is
         * included in a single output image must be part of a renderpass.
         *
         * @param pCommandBuffer The command buffer that contains the commands specified in the render pass.
         * @param pFramebuffer The frame buffer in which to render. The framebuffer is the collection of images rendered to by graphics commands.
         * @param pClearValues A list of VkClearValue associations. If one of the attachments in the render pass has a load of
         * VK_ATTACHMENT_LOAD_OP_CLEAR, then the colors or values to which they are cleared are specified in this array.
         * The index of each attachment of the {attachments} field given in the constructor is used to index into the
         * array of VkClearValue associations. This means that if only some of the attachments have a load of VK_ATTACHMENT_LOAD_OP_CLEAR, there may
         * be unused items in the array. There must be at least as many items in the pClearValues array as the highest indexed attachment with a load
         * of VK_ATTACHMENT_LOAD_OP_CLEAR
         * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkClearValue.html
         *
         * @param pRenderArea With each specific use of a render pass, we can choose to render only a small portion of the attached images.
         */
        void begin(CommandBuffer* pCommandBuffer, Framebuffer* pFramebuffer, std::vector<VkClearValue>* pClearValues = nullptr,
                   VkRect2D* pRenderArea = nullptr);

        void end();
    };
} // namespace fillcan