#pragma once

#include "vulkan/vulkan_core.h"
#include <fillcan/graphics/sampler.hpp>
#include <fillcan/memory/buffer.hpp>
#include <fillcan/memory/image.hpp>
#include <fillcan/memory/memory.hpp>

// std
#include <memory>
#include <string>

// stb
#include <stb/stb_image.h>

namespace fillcan {
    class LogicalDevice;
    class CommandBuffer;
    class DescriptorSet;
    class Texture {
      private:
        Texture(int index, LogicalDevice* pLogicalDevice, std::string& filePath);
        int index = -1;
        LogicalDevice* pLogicalDevice;
        std::string filePath;
        int width;
        int height;
        int channels;

        std::unique_ptr<Image> upImage;
        std::unique_ptr<Memory> upImageMemory;
        std::unique_ptr<Sampler> upSampler;
        // DescriptorSet* pDescriptorSet;
        // VkDescriptorSetLayoutBinding descriptorSetBinding;

        void createImage(Buffer* pStagingBuffer);
        void createImageView();
        void createSampler();

      public:
        static Texture createTexture(LogicalDevice* pLogicalDevice, std::string& filePath) {
            static int currentIndex;
            return Texture(currentIndex++, pLogicalDevice, filePath);
        }
        ~Texture();

        Texture(const Texture&) = delete;
        Texture& operator=(const Texture&) = delete;
        Texture(Texture&&) = default;
        Texture& operator=(Texture&&) = default;

        int getIndex();

        Image* getImage();
        ImageView* getImageView();
        Sampler* getSampler();

        void write();
    };
} // namespace fillcan