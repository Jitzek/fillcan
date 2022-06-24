
// fillcan
#include "fillcan/fillcan.hpp"
#include "fillcan/graphics/render_pass.hpp"
#include "fillcan/graphics/render_pass_builder.hpp"
#include "fillcan/graphics/swapchain.hpp"
#include <algorithm>
#include <fillcan/fillcan_graphics.hpp>
#include <iterator>
#include <thread>
#include <vector>

namespace fillcan {
    FillcanGraphics::FillcanGraphics(const char* pApplicationName, uint32_t applicationVersion, unsigned int windowWidth, unsigned int windowHeight,
                                     VkPhysicalDeviceFeatures requiredDeviceFeatures)
        : Fillcan(pApplicationName, applicationVersion, windowWidth, windowHeight, requiredDeviceFeatures) {}

    FillcanGraphics::~FillcanGraphics() {
        this->upRenderPasses.clear();
        this->upSwapchains.clear();
    }

    void FillcanGraphics::MainLoop(std::function<void(double)> callback) {
        std::chrono::high_resolution_clock::time_point currentTime = std::chrono::high_resolution_clock::now();
        std::chrono::high_resolution_clock::time_point previousTime = currentTime;
        std::chrono::duration<double> deltaTime = previousTime - currentTime;

        while (!this->upWindow->shouldClose()) {
            this->upWindow->pollEvents();

            previousTime = currentTime;
            currentTime = std::chrono::high_resolution_clock::now();
            deltaTime = currentTime - previousTime;
            this->_deltaTime = deltaTime.count();

            callback(this->deltaTime());
            // std::this_thread::sleep_for(std::chrono::milliseconds(100));
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

    unsigned int FillcanGraphics::createRenderPass(RenderPassBuilder& builder) {
        this->upRenderPasses.push_back(std::move(builder.getResult()));
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

    AssetManager* FillcanGraphics::getAssetManager() { return &this->assetManager; }
} // namespace fillcan