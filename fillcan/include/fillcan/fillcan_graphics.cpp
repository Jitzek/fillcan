
// fillcan
#include "fillcan/fillcan.hpp"
#include <fillcan/fillcan_graphics.hpp>
#include <fillcan/graphics/render_pass_builder.hpp>
#include <fillcan/graphics/swapchain.hpp>

// std
#include <algorithm>
#include <iterator>
#include <thread>
#include <vector>

namespace fillcan {
    FillcanGraphics::FillcanGraphics(const char* pApplicationName, uint32_t applicationVersion, unsigned int windowWidth, unsigned int windowHeight,
                                     VkPhysicalDeviceFeatures requiredDeviceFeatures, std::vector<const char*> requiredDeviceExtensions)
        : Fillcan() {
        // Initialize Window
        this->upWindow = std::make_unique<Window>(windowWidth, windowHeight, pApplicationName);

        std::vector<const char*> windowExtensions = upWindow->getRequiredExtensions();
        this->requiredInstanceExtensions.insert(requiredInstanceExtensions.begin(), windowExtensions.begin(), windowExtensions.end());

        // Initialize Instance
        this->upInstance = std::make_unique<Instance>(pApplicationName, applicationVersion, requiredInstanceLayers, requiredInstanceExtensions);

        // Create Window surface using Instance
        this->upWindow->createSurface(this->upInstance.get());

        // Initialize Device Pool
        this->upDevicePool =
            std::make_unique<DevicePool>(this->upInstance.get(), this->upWindow.get(), requiredDeviceExtensions, requiredDeviceFeatures);
    }

    FillcanGraphics::~FillcanGraphics() { this->upSwapchains.clear(); }

    Window* FillcanGraphics::getWindow() { return this->upWindow.get(); }

    void FillcanGraphics::mainLoop(std::function<void(double)> callback) {
        std::chrono::high_resolution_clock::time_point currentTime = std::chrono::high_resolution_clock::now();
        std::chrono::high_resolution_clock::time_point previousTime = currentTime;
        std::chrono::duration<double> deltaTime = previousTime - currentTime;

        while (!this->upWindow->shouldClose()) {
            this->upWindow->pollEvents();

            previousTime = currentTime;
            currentTime = std::chrono::high_resolution_clock::now();
            deltaTime = currentTime - previousTime;

            callback(deltaTime.count());
        }
        this->getCurrentDevice()->waitIdle();
    }

    unsigned int FillcanGraphics::createSwapchain(uint32_t imageCount, VkPresentModeKHR presentMode) {
        this->upSwapchains.emplace_back(std::move(std::make_unique<Swapchain>(
            this->getCurrentDevice(), this->upWindow.get(), this->getCurrentDevice()->getPresentQueue(), imageCount, presentMode, nullptr)));
        return this->upSwapchains.size() - 1;
    }

    unsigned int FillcanGraphics::recreateSwapchain(unsigned int index) {
        return this->recreateSwapchain(this->upSwapchains.at(index)->getImageCount(), this->upSwapchains.at(index)->getPresentMode(), index);
    }

    unsigned int FillcanGraphics::recreateSwapchain(uint32_t imageCount, VkPresentModeKHR presentMode, unsigned int index) {
        this->getCurrentDevice()->waitIdle();
        if (this->upSwapchains[index] == nullptr) {
            return -1;
        }
        this->upSwapchains.at(index) =
            std::move(std::make_unique<Swapchain>(this->getCurrentDevice(), this->upWindow.get(), this->getCurrentDevice()->getPresentQueue(),
                                                  imageCount, presentMode, this->upSwapchains.at(index).get()));
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

    // unsigned int FillcanGraphics::createRenderPass(RenderPassBuilder& builder) {
    //     this->upRenderPasses.push_back(std::move(builder.getResult()));
    //     return this->upRenderPasses.size() - 1;
    // }

    // RenderPass* FillcanGraphics::getRenderPass(unsigned int index) { return this->upRenderPasses[index].get(); }

    // std::vector<RenderPass*> FillcanGraphics::getRenderPasses() {
    //     std::vector<RenderPass*> pRenderPasses = {};
    //     pRenderPasses.reserve(this->upRenderPasses.size());
    //     std::transform(this->upRenderPasses.begin(), this->upRenderPasses.end(), std::back_inserter(pRenderPasses),
    //                    [](const std::unique_ptr<RenderPass>& upRenderPass) { return upRenderPass.get(); });
    //     return pRenderPasses;
    // }

    // void FillcanGraphics::destroyRenderPass(unsigned int index) { this->upRenderPasses.erase(this->upRenderPasses.begin() + index); }

    AssetManager* FillcanGraphics::getAssetManager() { return &this->assetManager; }
} // namespace fillcan