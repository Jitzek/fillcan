#pragma once

// vulkan
#include "vulkan/vulkan_core.h"

// std
#include <memory>

namespace fillcan {
    class LogicalDevice;
    class Sampler;
    class SamplerBuilder {
      private:
        LogicalDevice* pLogicalDevice = nullptr;
        VkFilter magFilter = VK_FILTER_LINEAR;
        VkFilter minFilter = VK_FILTER_LINEAR;
        VkSamplerMipmapMode mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
        VkSamplerAddressMode addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT;
        VkSamplerAddressMode addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT;
        VkSamplerAddressMode addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT;
        float mipLodBias = 0.f;
        VkBool32 anisotropyEnable = VK_FALSE;
        float maxAnisotropy = 1.0f;
        VkBool32 compareEnable = VK_FALSE;
        VkCompareOp compareOp = VK_COMPARE_OP_ALWAYS;
        float minLod = 0.f;
        float maxLod = 0.f;
        VkBorderColor borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
        VkBool32 unnormalizedCoordinates = VK_FALSE;

      public:
        /**
         * @brief Create a new Sampler Builder.
         *
         * @details The Sampler Builder class is part of the creational design pattern to construct complex objects step by step.
         * The Builder pattern allows you to produce different types and representations of an object using the same construction code.
         */
        SamplerBuilder();
        ~SamplerBuilder();

        /**
         * @brief Set the Logical Device for the Sampler.
         *
         * @param pLogicalDevice A pointer to the Logical Device the Sampler should be associated with.
         */
        void setLogicalDevice(LogicalDevice* pLogicalDevice);

        /**
         * @brief Set the filter modes to use when the image is magnified or minified.
         *
         * @param magFilter The filter mode to use when the image is magnified. This is a member of the VkFilter-enumerant.
         * @param minFilter The filter mode to use when the image is minified. This is a member of the VkFilter-enumerant.
         * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkFilter.html
         */
        void setFilters(VkFilter magFilter, VkFilter minFilter);

        /**
         * @brief Set how mipmaps are used in the image when it is sampled.
         *
         * @param mipmapMode How mipmaps are used in the image when it is sampled. This is a member of the VkSamplerMipmapMode-enumerant.
         * If the mipmap mode is VK_SAMPLER_MIPMAP_MODE_NEAREST, the selected mipmap level is rounded down to the next lowest integer, and then that
         * level is sampled as if it were a single-level image. When the mipmap mode is VK_SAMPLER_MIPMAP_MODE_LINEAR, a sample is taken from each of
         * the next-lower and next-higher levels using the filter mode selected by the {minFilter} field, and then those two samples are further
         * combined using a weighted average, similar to how the samples are combined during linear sampling, as previously described. Note that this
         * filter mode only applies to minification, which is the process of sampling from a different mipmap level than the base level.
         * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkSamplerMipmapMode.html
         */
        void setMipmapMode(VkSamplerMipmapMode mipmapMode);

        /**
         * @brief Set the address modes which are used to select the transformer applied to texture coordinates that would otherwise be sampled
         * outside the image. These are members of the VkSamplerAddressMode-enumerant.
         * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkSamplerAddressMode.html
         *
         * @param addressModeU U is the X within the convention of texture space coordinates.
         * @param addressModeV V is the Y within the convention of texture space coordinates.
         * @param addressModeW W is the Z within the convention of texture space coordinates.
         */
        void setAddressModes(VkSamplerAddressMode addressModeU, VkSamplerAddressMode addressModeV, VkSamplerAddressMode addressModeW);

        /**
         * @brief Set the bias for the mip Lod.
         *
         * @param mipLodBias A floating-point bias that is added to the computed level of detail before making mipmap selection. This can push the
         * level of detail up or down in the mipmap chain to make the resulting filtered texture look sharper or fainter than it would otherwise.
         */
        void setMipLodBias(float mipLodBias);

        /**
         * @brief Set the max anisotropy if anisotropic filtering is to be used, also enables anisotropic filtering.
         *
         * @param maxAnisotropy If anisotropic filtering is to be used, it can be set to VK_TRUE. If not, it can be set to VK_FALSE.
         * Anisotropic filtering generally works by considering a projected footprint of the area to be sampled (or "sampled") rather than using a
         * fixed 2×2 footprint. An approximation of a surface sample is formed by taking many samples within the footprint.
         */
        void setMaxAnisotropy(float maxAnisotropy);

        /**
         * @brief Reset the max anisotropy to it's default value and disable anisotropic filtering.
         */
        void unsetMaxAnisotropy();

        /**
         * @brief When a sampler is used with a depth image, it can be configured to perform a compare operation and return the result
         * of the comparison instead of the raw values stored in the image. When this mode is enabled, the comparison is performed on each sample
         * taken from the image, and the resulting value is the fraction of the total number of samples taken that passed the test. This can be used
         * to implement a technique known as percentage closer filtering or PCF. This enables this mode.
         *
         * @param compareOp A member of the VkCompareOp-enumeration, which is used in many places in Vulkan, including the graphical pipeline. This is
         * the enumeration used to specify the depth test operation.
         */
        void setCompareOp(VkCompareOp compareOp);

        /**
         * @brief Reset the compare operation to it's default value and disable comparing.
         */
        void unsetCompareOp();

        /**
         * @brief The sampler can be configured to limit sampling to a subset of the mip levels in an image with mipmaps. The range of mipmaps to
         * sample from is specified in minLod and maxLod.
         *
         * @param minLod The lowest mipmaps (highest resolution) to sample from.
         * @param maxLod The highest mipmaps (lowest resolution) to sample from.
         */
        void setLod(float minLod, float maxLod);

        /**
         * @brief Set the border color.
         *
         * @param borderColor The border color used in place of data from the image if {addressmodeU}, {addressmodeV} and/or {addressmodeW} is set to
         * VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_BORDER. This is a member of the VkBorderColor-enumerant.
         */
        void setBorderColor(VkBorderColor borderColor);

        /**
         * @brief Enable unnormalized coordinates.
         *
         * @details A flag that, when enabled, indicates that the coordinates used to extract from the image are in raw texel units, rather
         * than a value normalized between 0.0 and 1.0 for each dimension of the texture. This allows texels to be explicitly extracted from the
         * image. However, there are several limitations in this mode. When unnormalizedCoordinates is enabled, minFilter and magFilter (see
         * setFilters) must be the same, mipmapMode (see SamplerBuilder#setMipmapMode) must be set to VK_SAMPLER_MIPMAP_MODE_NEAREST and
         * anisotropyEnable (see SamplerBuilder#setMaxAnisotropy and SamplerBuilder#unsetMaxAnisotropy) and compareEnable (see
         * SamplerBuilder#setCompareOp and SamplerBuilder#unsetCompareOp) must be set to VK_FALSE.
         */
        void enableUnnormalizedCoordinates();

        /**
         * @brief Disable unnormalized coordinates.
         * 
         */
        void disableUnnormalizedCoordinates();

        /**
         * @brief Get the resulting Sampler.
         *
         * @return A unique pointer to the Sampler, it's ownership will be moved.
         *
         * @throws std::runtime_error if the Sampler couldn't be created.
         */
        std::unique_ptr<Sampler> getResult();

        /**
         * @brief Reset the Builder to it's default values.
         */
        void reset();
    };
} // namespace fillcan