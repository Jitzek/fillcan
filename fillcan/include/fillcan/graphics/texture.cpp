
// vulkan
#include "fillcan/commands/command_buffer.hpp"
#include "fillcan/commands/command_recording.hpp"
#include "fillcan/graphics/sampler_builder.hpp"
#include "fillcan/memory/image_director.hpp"
#include "vulkan/vulkan_core.h"

// fillcan
#include <fillcan/graphics/texture.hpp>
#include <fillcan/instance/logical_device.hpp>
#include <fillcan/memory/buffer.hpp>
#include <fillcan/memory/buffer_director.hpp>
#include <fillcan/memory/memory.hpp>
#include <fillcan/shader/descriptor_set.hpp>

// std
#include <cstring>
#include <memory>
#include <stdexcept>
#include <vector>

// stb
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

namespace fillcan {
    Texture::Texture(int index, LogicalDevice* pLogicalDevice, std::string& filePath)
        : index(index), pLogicalDevice(pLogicalDevice), filePath(filePath) {
        stbi_uc* pixels = stbi_load(filePath.c_str(), &this->width, &this->height, &this->channels, STBI_rgb_alpha);
        if (pixels == nullptr) {
            throw std::runtime_error("Failed to load texture");
        }
        VkDeviceSize imageSize = (width * height * 4) /* 4 for RGBA */;

        std::unique_ptr<Buffer> upStagingBuffer = BufferDirector().makeStagingBuffer(this->pLogicalDevice, imageSize);
        std::unique_ptr<Memory> upStagingBufferMemory = std::make_unique<Memory>(
            this->pLogicalDevice, upStagingBuffer.get(), VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
        upStagingBuffer->bindMemory(upStagingBufferMemory.get());
        void** ppStagingBufferData = upStagingBuffer->getMemory()->map();
        memcpy(*ppStagingBufferData, pixels, static_cast<size_t>(imageSize));
        upStagingBuffer->getMemory()->unmap();

        stbi_image_free(pixels);

        this->createImage(upStagingBuffer.get());
        this->createImageView();
        this->createSampler();
    }

    Texture::~Texture() {}

    void Texture::createImage(Buffer* pStagingBuffer) {
        this->upImage = ImageDirector().make2DTexture(this->pLogicalDevice, this->width, this->height, VK_SAMPLE_COUNT_1_BIT);
        this->upImageMemory = std::make_unique<Memory>(this->pLogicalDevice, this->upImage.get(), VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
        this->upImage->bindMemory(this->upImageMemory.get());

        CommandRecording* pCommandRecording = this->pLogicalDevice->beginSingleTimeCommandRecording(this->pLogicalDevice->getGraphicsQueue());
        // Transition Image Layout for buffer transfer
        this->upImage->transitionImageLayout(pCommandRecording->pPrimaryCommandBuffers[0], VK_IMAGE_LAYOUT_UNDEFINED,
                                             VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 0, VK_ACCESS_TRANSFER_WRITE_BIT, VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT,
                                             VK_PIPELINE_STAGE_TRANSFER_BIT);

        // Copy staging buffer to image
        std::vector<VkBufferImageCopy> regions = {{.bufferOffset = 0,
                                                   .bufferRowLength = 0,
                                                   .bufferImageHeight = 0,
                                                   .imageSubresource =
                                                       {
                                                           .aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
                                                           .mipLevel = 0,
                                                           .baseArrayLayer = 0,
                                                           .layerCount = 1,
                                                       },
                                                   .imageOffset = {0, 0, 0},
                                                   .imageExtent = {static_cast<uint32_t>(this->width), static_cast<uint32_t>(this->height), 1}}};
        pStagingBuffer->copyTo(pCommandRecording->pPrimaryCommandBuffers[0], this->upImage.get(), VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, regions);

        // Transition Image Layout for shader access
        this->upImage->transitionImageLayout(pCommandRecording->pPrimaryCommandBuffers[0], VK_IMAGE_LAYOUT_UNDEFINED,
                                             VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_ACCESS_TRANSFER_WRITE_BIT, VK_ACCESS_SHADER_READ_BIT,
                                             VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT);
        this->pLogicalDevice->endSingleTimeCommandRecording(pCommandRecording);
    }

    void Texture::createImageView() { this->upImage->createImageView(VK_IMAGE_VIEW_TYPE_2D, VK_FORMAT_R8G8B8A8_SRGB); }

    void Texture::createSampler() {
        SamplerBuilder samplerBuilder = SamplerBuilder();
        samplerBuilder.setLogicalDevice(this->pLogicalDevice);
        samplerBuilder.setFilters(VK_FILTER_LINEAR, VK_FILTER_LINEAR);
        samplerBuilder.setMipmapMode(VK_SAMPLER_MIPMAP_MODE_LINEAR);
        samplerBuilder.setAddressModes(VK_SAMPLER_ADDRESS_MODE_REPEAT, VK_SAMPLER_ADDRESS_MODE_REPEAT, VK_SAMPLER_ADDRESS_MODE_REPEAT);
        samplerBuilder.setMipLodBias(0.0f);
        samplerBuilder.setMaxAnisotropy(1.0f);
        samplerBuilder.setCompareOp(VK_COMPARE_OP_ALWAYS);
        samplerBuilder.setLod(0.0f, 0.0f);
        samplerBuilder.setBorderColor(VK_BORDER_COLOR_INT_OPAQUE_BLACK);
        this->upSampler = samplerBuilder.getResult();
    }

    int Texture::getIndex() { return this->index; }

    Image* Texture::getImage() { return this->upImage.get(); }

    ImageView* Texture::getImageView() { return this->upImage->getImageView(0); }

    Sampler* Texture::getSampler() { return this->upSampler.get(); }
} // namespace fillcan