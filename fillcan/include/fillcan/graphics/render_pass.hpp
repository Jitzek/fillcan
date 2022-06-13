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

    struct SubpassAttachment {
        VkAttachmentDescription description;
        VkImageLayout layout;
        bool preserve;
    };

    struct Subpass {
        // Automatically set
        unsigned int id = 0;

        std::vector<SubpassAttachment> inputAttachments = {};
        std::vector<SubpassAttachment> colorAttachments = {};
        SubpassAttachment* pDepthStencilAttachment = nullptr;
        bool resolve = false;

        // Only required if this subpass is dependent on another subpass, or another subpass is dependentn on this subpass
        Subpass* dependency = nullptr;
        VkPipelineStageFlags stageMask = 0;
        VkAccessFlags accessMask = 0;
        VkDependencyFlags dependencyFlags = 0;
    };

    class RenderPass {
      private:
        VkRenderPass hRenderPass;
        LogicalDevice* pLogicalDevice;
        CommandBuffer* pCommandBuffer = nullptr;
        std::vector<VkAttachmentDescription> attachments;
        // std::vector<VkAttachmentReference> inputAttachmentReferences;
        // std::vector<VkAttachmentReference> colorAttachmentReferences;
        // std::vector<VkAttachmentReference> resolveAttachmentReferences;
        // std::vector<VkAttachmentReference> depthStencilAttachmentReferences;
        // std::vector<uint32_t> preserveAttachmentReferences;
        std::vector<VkSubpassDescription> subpasses;
        std::vector<VkSubpassDependency> dependencies;
        std::vector<std::unique_ptr<Framebuffer>> upFramebuffers = {};

      public:
        RenderPass(LogicalDevice* pLogicalDevice, std::vector<VkAttachmentDescription> attachments, std::vector<VkSubpassDescription> subpasses,
                   std::vector<VkSubpassDependency> dependencies);
        ~RenderPass();

        VkRenderPass getRenderPassHandle();

        std::vector<VkAttachmentDescription>& getAttachments();
        std::vector<VkSubpassDescription>& getSubpasses();
        std::vector<VkSubpassDependency>& getDependencies();

        void begin(CommandBuffer* pCommandBuffer, Framebuffer* pFramebuffer, std::vector<VkClearValue>* pClearValues = nullptr,
                   VkRect2D* pRenderArea = nullptr);
        void end();

        unsigned int createFramebuffer(std::vector<ImageView*> pAttachments, unsigned int width, unsigned int height, unsigned int layers);
        Framebuffer* getFramebuffer(unsigned int index = 0);
        std::vector<Framebuffer*> getFramebuffers();
        void destroyFramebuffer(unsigned int index = 0);
    };
} // namespace fillcan