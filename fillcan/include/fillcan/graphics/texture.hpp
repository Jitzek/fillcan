#pragma once

#include "vulkan/vulkan_core.h"
#include <fillcan/memory/memory.hpp>
#include <fillcan/memory/image.hpp>
#include <fillcan/memory/buffer.hpp>
#include <fillcan/graphics/sampler.hpp>

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
        LogicalDevice* pLogicalDevice;
        std::string filePath;
        int width;
        int height;
        int channels;

        std::unique_ptr<Image> upImage;
        std::unique_ptr<Memory> upImageMemory;
        std::unique_ptr<Sampler> upSampler;
        DescriptorSet* pDescriptorSet;
        VkDescriptorSetLayoutBinding descriptorSetBinding;

        void createImage(Buffer* pStagingBuffer);
        void createImageView();
        void createSampler();

      public:
        Texture(LogicalDevice* pLogicalDevice, std::string& filePath, DescriptorSet* pDescriptorSet, VkDescriptorSetLayoutBinding descriptorSetBinding);
        ~Texture();
        
        Image* getImage(); 

        void write();
    };
} // namespace fillcan