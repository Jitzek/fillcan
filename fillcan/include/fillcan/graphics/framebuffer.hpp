#pragma once

// vulkan
#include "vulkan/vulkan_core.h"

// std
#include <vector>

namespace fillcan {
    class LogicalDevice;
    class RenderPass;
    class ImageView;
    class Framebuffer {
      private:
        VkFramebuffer hFramebuffer;
        LogicalDevice* pLogicalDevice;
        std::vector<ImageView*> pAttachments;
        VkExtent2D extent;
        unsigned int layers;

      public:
        /**
         * @brief Create a new Framebuffer.
         *
         * @details The Frambuffer class takes a pointer to a Logical Device, a pointer to a Render Pass along with lists of attachments, the width,
         * the height and a number of array layers. It uses this information to create a Vulkan Framebuffer.
         *
         * A Render Pass renders to a Framebuffer. The framebuffer links to the images being rendered to and is used when starting a render pass to
         * set the target images for rendering. Once the render pass is created, it can be used to create the framebuffers. Frame buffers are created
         * based on a particular render pass and they act as a link between the render pass attachments and the real images to be rendered to.
         *
         * The framebuffer is an object that represents the set of images into which graphics pipelines render. These affect the last few stages in
         * the pipeline: depth- and stencil testing, blending, logical operations, multisampling, and so on. A framebuffer object is created by using
         * a reference to a render pass and can be used with any render pass that has a similar arrangement of attachments.
         *
         * @param pLogicalDevice A pointer to the Logical Device the render pass should be associated with.
         * @param pRenderPass A pointer to a render pass that defines which render pass the framebuffer will be compatible with. Two render
         * passes are compatible with the same framebuffer if their attachment references are the same.
         * @param pAttachments The set of images to be bound into the framebuffer object. Each image (/attachment) will be used as the corresponding
         * attachment in the {attachments} list of the Render Pass Constructor of a render pass instance.
         * @param width The width of the framebuffer.
         * @param height The height of the framebuffer.
         * @param layers The number of layers of the framebuffer.
         *
         * @throws std::runtime_error if the Vulkan Framebuffer couldn't be created.
         * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkFramebuffer.html
         */
        Framebuffer(LogicalDevice* pLogicalDevice, RenderPass* pRenderPass, std::vector<ImageView*> pAttachments, unsigned int width,
                    unsigned int height, unsigned int layers);
        ~Framebuffer();
        Framebuffer(const Framebuffer&) = delete;
        Framebuffer& operator=(const Framebuffer&) = delete;

        /**
         * @brief Get the handle to the Vulkan Framebuffer.
         *
         * @return The handle to the Vulkan Framebuffer.
         */
        const VkFramebuffer getFramebufferHandle() const;

        /**
         * @brief Get the extent of the framebuffer.
         *
         * @return The extent of the framebuffer, this is a VkExtent2D-structure.
         * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkExtent2D.html
         */
        VkExtent2D getExtent();

        /**
         * @brief Get the number of layers of the framebuffer.
         *
         * @return The number of layers of the framebuffer.
         */
        unsigned int getLayers();
    };
} // namespace fillcan