
// vulkan
#include "fillcan/commands/command_buffer.hpp"
#include "fillcan/memory/image_director.hpp"
#include "vulkan/vulkan_core.h"

// fillcan
#include <cstring>
#include <fillcan/graphics/texture.hpp>
#include <fillcan/instance/logical_device.hpp>
#include <fillcan/memory/buffer.hpp>
#include <fillcan/memory/buffer_director.hpp>
#include <fillcan/memory/memory.hpp>

// std
#include <memory>
#include <stdexcept>

// stb
#include "stb/stb_image.h"

namespace fillcan {
    Texture::Texture(LogicalDevice* pLogicalDevice, std::string& filePath) : pLogicalDevice(pLogicalDevice), filePath(filePath) {
        stbi_uc* pixels = stbi_load(filePath.c_str(), &this->width, &this->height, &this->channels, STBI_rgb_alpha);
        if (pixels == nullptr) {
            throw std::runtime_error("Failed to load texture");
        }
        VkDeviceSize imageSize = (width * height * 4) /* 4 for RGBA */;
        this->upStagingBuffer = BufferDirector().makeStagingBuffer(this->pLogicalDevice, imageSize);

        this->upStagingBufferMemory = std::make_unique<Memory>(this->pLogicalDevice, this->upStagingBuffer.get(),
                                                               VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

        this->upStagingBuffer->bindMemory(upStagingBufferMemory.get());
        void** ppStagingBufferData = this->upStagingBuffer->getMemory()->map();
        memcpy(*ppStagingBufferData, pixels, static_cast<size_t>(imageSize));
        this->upStagingBuffer->getMemory()->unmap();

        stbi_image_free(pixels);

        this->upImage = ImageDirector().make2DTexture(this->pLogicalDevice, this->width, this->height, VK_SAMPLE_COUNT_1_BIT);
    }

    Texture::~Texture() {}

    void Texture::bind(CommandBuffer* pCommandBuffer) {
        // Transition Image Layout for buffer transfer // TODO: write function in {Image}
        VkImageMemoryBarrier stagingBarrier{};
        stagingBarrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
        stagingBarrier.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        stagingBarrier.newLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
        stagingBarrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
        stagingBarrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
        stagingBarrier.image = this->upImage->getImageHandle();
        stagingBarrier.subresourceRange = {
            .aspectMask = VK_IMAGE_ASPECT_COLOR_BIT, .baseMipLevel = 0, .levelCount = 1, .baseArrayLayer = 0, .layerCount = 1};
        stagingBarrier.srcAccessMask = 0;
        stagingBarrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;

        vkCmdPipelineBarrier(pCommandBuffer->getCommandBufferHandle(), VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT, 0, 0,
                             nullptr, 0, nullptr, 1, &stagingBarrier);

        // Copy Staging Buffer to Image // TODO: Write function in Buffer
        VkBufferImageCopy region{};
        region.bufferOffset = 0;
        region.bufferRowLength = 0;
        region.bufferImageHeight = 0;
        region.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        region.imageSubresource.mipLevel = 0;
        region.imageSubresource.baseArrayLayer = 0;
        region.imageSubresource.layerCount = 1;
        region.imageOffset = {0, 0, 0};
        region.imageExtent = {static_cast<uint32_t>(this->width), static_cast<uint32_t>(this->height), 1};

        vkCmdCopyBufferToImage(pCommandBuffer->getCommandBufferHandle(), this->upStagingBuffer->getBufferHandle(), this->upImage->getImageHandle(),
                               VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &region);

        // Transition Image Layout for shader access // TODO: write function in {Image}
        VkImageMemoryBarrier shaderBarrier{};
        shaderBarrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
        shaderBarrier.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
        shaderBarrier.newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
        shaderBarrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
        shaderBarrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
        shaderBarrier.image = this->upImage->getImageHandle();
        shaderBarrier.subresourceRange = {
            .aspectMask = VK_IMAGE_ASPECT_COLOR_BIT, .baseMipLevel = 0, .levelCount = 1, .baseArrayLayer = 0, .layerCount = 1};
        shaderBarrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
        shaderBarrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;

        vkCmdPipelineBarrier(pCommandBuffer->getCommandBufferHandle(), VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT, 0, 0,
                             nullptr, 0, nullptr, 1, &shaderBarrier);
    }

    Image* Texture::getImage() { return this->upImage.get(); }
} // namespace fillcan