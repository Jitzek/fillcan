
// fillcan
#include <fillcan/graphics/sampler.hpp>
#include <fillcan/graphics/sampler_builder.hpp>
#include <fillcan/instance/logical_device.hpp>

// std
#include <memory>
#include <stdexcept>

namespace fillcan {
    SamplerBuilder::SamplerBuilder() {}
    SamplerBuilder::~SamplerBuilder() {}

    void SamplerBuilder::setLogicalDevice(LogicalDevice* pLogicalDevice) { this->pLogicalDevice = pLogicalDevice; }

    void SamplerBuilder::setFilters(VkFilter magFilter, VkFilter minFilter) {
        this->magFilter = magFilter;
        this->minFilter = minFilter;
    }

    void SamplerBuilder::setMipmapMode(VkSamplerMipmapMode mipmapMode) { this->mipmapMode = mipmapMode; }

    void SamplerBuilder::setAddressModes(VkSamplerAddressMode addressModeU, VkSamplerAddressMode addressModeV, VkSamplerAddressMode addressModeW) {
        this->addressModeU = addressModeU;
        this->addressModeV = addressModeV;
        this->addressModeW = addressModeW;
    }

    void SamplerBuilder::setMipLodBias(float mipLodBias) { this->mipLodBias = mipLodBias; }

    void SamplerBuilder::setMaxAnisotropy(float maxAnisotropy) {
        this->anisotropyEnable = VK_TRUE;
        this->maxAnisotropy = maxAnisotropy;
    }

    void SamplerBuilder::unsetMaxAnisotropy() {
        this->anisotropyEnable = VK_FALSE;
        this->maxAnisotropy = 1.f;
    }

    void SamplerBuilder::setCompareOp(VkCompareOp compareOp) {
        this->compareEnable = VK_TRUE;
        this->compareOp = compareOp;
    }

    void SamplerBuilder::unsetCompareOp() {
        this->compareEnable = VK_FALSE;
        this->compareOp = VK_COMPARE_OP_ALWAYS;
    }

    void SamplerBuilder::setLod(float minLod, float maxLod) {
        this->minLod = minLod;
        this->maxLod = maxLod;
    }

    void SamplerBuilder::setBorderColor(VkBorderColor borderColor) { this->borderColor = borderColor; }

    void SamplerBuilder::enableUnnormalizedCoordinates() { this->unnormalizedCoordinates = VK_TRUE; }

    void SamplerBuilder::disableUnnormalizedCoordinates() { this->unnormalizedCoordinates = VK_FALSE; }

    void SamplerBuilder::reset() {
        pLogicalDevice = nullptr;
        magFilter = VK_FILTER_LINEAR;
        minFilter = VK_FILTER_LINEAR;
        mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
        addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT;
        addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT;
        addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT;
        mipLodBias = 0.f;
        anisotropyEnable = VK_FALSE;
        maxAnisotropy = 1.0f;
        compareEnable = VK_FALSE;
        compareOp = VK_COMPARE_OP_ALWAYS;
        minLod = 0.f;
        maxLod = 0.f;
        borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
        unnormalizedCoordinates = VK_FALSE;
    }

    std::unique_ptr<Sampler> SamplerBuilder::getResult() {
        return std::move(std::make_unique<Sampler>(this->pLogicalDevice, this->magFilter, this->minFilter, this->mipmapMode, this->addressModeU,
                                                   this->addressModeV, this->addressModeW, this->mipLodBias, this->anisotropyEnable,
                                                   this->maxAnisotropy, this->compareEnable, this->compareOp, this->minLod, this->maxLod,
                                                   this->borderColor, this->unnormalizedCoordinates));
    }
} // namespace fillcan