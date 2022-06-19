#pragma once

#include <fillcan/memory/memory.hpp>
#include <fillcan/memory/image.hpp>
#include <fillcan/memory/buffer.hpp>

// std
#include <memory>
#include <string>

// stb
#include <stb/stb_image.h>

namespace fillcan {
    class LogicalDevice;
    class CommandBuffer;
    class Texture {
      private:
        LogicalDevice* pLogicalDevice;
        std::string filePath;
        int width;
        int height;
        int channels;

        std::unique_ptr<Buffer> upStagingBuffer;
        std::unique_ptr<Memory> upStagingBufferMemory;
        std::unique_ptr<Image> upImage;
        std::unique_ptr<Memory> upImageMemory;

      public:
        Texture(LogicalDevice* pLogicalDevice, std::string& filePath);
        ~Texture();

        void bind(CommandBuffer* pCommandBuffer);

        Image* getImage(); 
    };
} // namespace fillcan