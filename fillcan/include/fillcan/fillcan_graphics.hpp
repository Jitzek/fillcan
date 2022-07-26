#pragma once

// vulkan
#include "vulkan/vulkan_core.h"

// fillcan
#include <fillcan/fillcan.hpp>
#include <fillcan/graphics/asset_manager.hpp>
#include <fillcan/graphics/framebuffer.hpp>
#include <fillcan/graphics/render_pass.hpp>
#include <fillcan/graphics/render_pass_builder.hpp>

// std
#include <memory>
#include <vector>

namespace fillcan {
    class FillcanGraphics : public Fillcan {
      private:
        std::unique_ptr<Window> upWindow{};
        std::vector<std::unique_ptr<Swapchain>> upSwapchains = {};
        AssetManager assetManager{};

      public:
        /**
         * @brief Intialize the Fillcan Graphics API.
         *
         * @details Initializes the Window, Instance, and Device Pool.
         *
         * @param pApplicationName The name of the application.
         * @param applicationVersion he version of the application.
         * @param windowWidth The initial width the Window.
         * @param windowHeight The initial height the Window.
         * @param requiredDeviceFeatures The features a Physical Device should have for the purposes of the application. This should be a
         * VkPhysicalDeviceFeatures-structure where each required feature should be set to true.
         * @param requiredDeviceExtensions The extensions a Physical Device should enable for the purposes of the application. This should be a list
         * of strings containing the names of the extensions to enable. The available extensions can be retrieved using
         * vkEnumerateInstanceExtensionProperties(). To be able to use a Swapchain this list should contain VK_KHR_SWAPCHAIN_EXTENSION_NAME (Fillcan
         * Graphics contains this by default).
         *
         * @throws std::runtime_error if the Instance couldn't be created.
         * @throws std::runtime_error if the Device Pool couldn't be created.
         */
        FillcanGraphics(const char* pApplicationName, uint32_t applicationVersion, unsigned int windowWidth, unsigned int windowHeight,
                        VkPhysicalDeviceFeatures requiredDeviceFeatures = {},
                        std::vector<const char*> requiredDeviceExtensions = {VK_KHR_SWAPCHAIN_EXTENSION_NAME});
        ~FillcanGraphics();
        FillcanGraphics(const FillcanGraphics&) = delete;
        FillcanGraphics& operator=(const FillcanGraphics&) = delete;

        /**
         * @brief Get the Window.
         *
         * @return A pointer to the Window.
         */
        Window* getWindow();

        /**
         * @brief The main loop of the Fillcan Graphics API.
         *
         * @details The main loop of the Fillcan Graphics API gives access to a callback function with the deltaTime. The main loop calls this
         * callback every frame.
         *
         * @param callback The callback with the deltaTime which will be called every frame.
         */
        void mainLoop(std::function<void(double)> callback);

        /**
         * @brief Create a Swapchain.
         *
         * @param imageCount The amount of images the Swapchain should have.
         * @param presentMode The present mode of the Swapchain. This should be member of the VkPresentModeKHR-struct (@see
         * https://www.khronos.org/registry/vulkan/specs/1.3-extensions/man/html/VkPresentModeKHR.html).
         *
         * @return The index of the created Swapchain.
         *
         * @throws std::runtime_error if the Swapchain couldn't be created.
         */
        unsigned int createSwapchain(uint32_t imageCount = 3, VkPresentModeKHR presentMode = VK_PRESENT_MODE_FIFO_KHR);

        /**
         * @brief Recreate a Swapchain.
         *
         * @param imageCount The amount of images the recreated Swapchain should have.
         * @param presentMode The present mode of the recreated Swapchain. This should be member of the VkPresentModeKHR-struct (@see
         * https://www.khronos.org/registry/vulkan/specs/1.3-extensions/man/html/VkPresentModeKHR.html).
         * @param index The index of the Swapchain to be recreated. @see FillcanGraphics#createSwapchain.
         *
         * @return The index of the recreated Swapchain.
         *
         * @throws std::runtime_error if the Swapchain couldn't be recreated.
         */
        unsigned int recreateSwapchain(uint32_t imageCount, VkPresentModeKHR presentMode, unsigned int index = 0);

        /**
         * @brief Recreate a Swapchain using it's original values.
         *
         * @param index The index of the Swapchain. @see FillcanGraphics#createSwapchain.
         *
         * @return The index of the recreated Swapchain.
         *
         * @throws std::runtime_error if the Swapchain couldn't be recreated.
         */
        unsigned int recreateSwapchain(unsigned int index = 0);

        /**
         * @brief Get a Swapchain at a given index.
         *
         * @param index The index of the Swapchain. @see FillcanGraphics#createSwapchain.
         *
         * @return A pointer to the Swapchain at the given index.
         */
        Swapchain* getSwapchain(unsigned int index = 0);

        /**
         * @brief Get all created Swapchains.
         *
         * @return A list of pointers to the created Swapchains.
         */
        std::vector<Swapchain*> getSwapchains();

        /**
         * @brief Destroy a Swapchain at a given index.
         *
         * @param index The index of the Swapchain to destroy. @see FillcanGraphics#createSwapchain.
         */
        void destroySwapchain(unsigned int index = 0);

        /**
         * @brief Get the Asset Manager.
         *
         * @return A pointer to the Asset Manager.
         */
        AssetManager* getAssetManager();
    };
} // namespace fillcan