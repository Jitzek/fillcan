
// fillcan
#include "fillcan/fillcan.hpp"
#include "fillcan/graphics/render_pass.hpp"
#include "fillcan/graphics/render_pass_builder.hpp"
#include "fillcan/graphics/swapchain.hpp"
#include <fillcan/fillcan_graphics.hpp>
#include <iterator>
#include <vector>

namespace fillcan {
    FillcanGraphics::FillcanGraphics(const char* pApplicationName, uint32_t applicationVersion, unsigned int windowWidth, unsigned int windowHeight,
                                     VkPhysicalDeviceFeatures requiredDeviceFeatures)
        : Fillcan(pApplicationName, applicationVersion, windowWidth, windowHeight, requiredDeviceFeatures) {}

    FillcanGraphics::~FillcanGraphics() { Fillcan::~Fillcan(); }

    unsigned int FillcanGraphics::createSwapchain(BufferMode bufferMode, VkPresentModeKHR presentMode) {
        this->upSwapchains.push_back(std::move(std::make_unique<Swapchain>(
            this->getCurrentDevice(), this->upWindow.get(), this->getCurrentDevice()->getPresentQueue(), bufferMode, presentMode, nullptr)));
        return this->upSwapchains.size() - 1;
    }

    unsigned int FillcanGraphics::recreateSwapchain(BufferMode bufferMode, VkPresentModeKHR presentMode, unsigned int index) {
        if (this->upSwapchains[index] == nullptr) {
            return -1;
        }
        this->upSwapchains[index] =
            std::move(std::make_unique<Swapchain>(this->getCurrentDevice(), this->upWindow.get(), this->getCurrentDevice()->getPresentQueue(),
                                                  bufferMode, presentMode, this->upSwapchains[index].get()));
        return index;
    }

    Swapchain* FillcanGraphics::getSwapchain(unsigned int index) { return this->upSwapchains[index].get(); }

    std::vector<Swapchain*> FillcanGraphics::getSwapchains() {
        std::vector<Swapchain*> pSwapchains = {};
        pSwapchains.reserve(this->upSwapchains.size());
        std::transform(this->upSwapchains.begin(), this->upSwapchains.end(), std::back_inserter(pSwapchains),
                       [](const std::unique_ptr<Swapchain>& upSwapchain) { return upSwapchain.get(); });
        return pSwapchains;
    }

    void FillcanGraphics::destroySwapchain(unsigned int index) { this->upSwapchains.erase(this->upSwapchains.begin() + index); }

    unsigned int FillcanGraphics::createRenderPass(std::vector<Subpass>& subpasses) {
        RenderPassBuilder renderPassBuilder = RenderPassBuilder();
        renderPassBuilder.setLogicalDevice(this->getCurrentDevice());
        unsigned int i = 0;
        for (Subpass& subpass : subpasses) {
            subpass.id = i++;
        }
        for (Subpass& subpass : subpasses) {
            for (SubpassAttachment& inputAttachment : subpass.inputAttachments) {
                renderPassBuilder.addInputAttachment(inputAttachment.description, inputAttachment.layout, inputAttachment.preserve);
            }
            for (SubpassAttachment& colorAttachment : subpass.colorAttachments) {
                renderPassBuilder.addColorAttachment(colorAttachment.description, colorAttachment.layout, colorAttachment.preserve, subpass.resolve);
            }
            if (subpass.pDepthStencilAttachment != nullptr) {
                renderPassBuilder.setDepthStencilAttachment(subpass.pDepthStencilAttachment->description, subpass.pDepthStencilAttachment->layout,
                                                            subpass.pDepthStencilAttachment->preserve);
            }
            if (subpass.dependency != nullptr) {
                renderPassBuilder.addSubpassDependency(subpass.id, subpass.dependency->id, subpass.stageMask, subpass.dependency->stageMask,
                                                       subpass.accessMask, subpass.dependency->accessMask);
                renderPassBuilder.constructSubpassDependency(subpass.dependencyFlags);
            }
            renderPassBuilder.constructSubpass();
        }
        this->upRenderPasses.push_back(std::move(renderPassBuilder.getResult()));
        return this->upRenderPasses.size() - 1;
    }

    RenderPass* FillcanGraphics::getRenderPass(unsigned int index) { return this->upRenderPasses[index].get(); }

    std::vector<RenderPass*> FillcanGraphics::getRenderPasses() {
        std::vector<RenderPass*> pRenderPasses = {};
        pRenderPasses.reserve(this->upRenderPasses.size());
        std::transform(this->upRenderPasses.begin(), this->upRenderPasses.end(), std::back_inserter(pRenderPasses),
                       [](const std::unique_ptr<RenderPass>& upRenderPass) { return upRenderPass.get(); });
        return pRenderPasses;
    }

    void FillcanGraphics::destroyRenderPass(unsigned int index) { this->upRenderPasses.erase(this->upRenderPasses.begin() + index); }
} // namespace fillcan