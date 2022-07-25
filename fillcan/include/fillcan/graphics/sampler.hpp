#pragma once

// vulkan
#include "vulkan/vulkan_core.h"

namespace fillcan {
    class LogicalDevice;
    class Sampler {
      private:
        VkSampler hSampler;
        LogicalDevice* pLogicalDevice;

      public:
        /**
         * @brief Create a Sampler object.
         *
         * @details When shaders read from images, they can do so in two ways. The first is to load the image raw, which reads formatted or
         * unformatted data directly from a specific location in the image. The second way is to sample the image using a sampler. Sampling can
         * include operations such as performing basic transformations on the image-coordinates or filtering texels to smooth out the image-data
         * returned to the shader. The sampler is a separate object that provides an interface to extract colors from a texture. It can be applied to
         * any image be it 1D, 2D or 3D.
         *
         * @param pLogicalDevice A pointer to the Logical Device the Image View should be associated with.
         * @param magFilter The filter mode to use when the image is magnified. This is a member of the VkFilter-enumerant.
         * @param minFilter The filter mode to use when the image is minified. This is a member of the VkFilter-enumerant.
         * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkFilter.html
         * @param mipmapMode How mipmaps are used in the image when it is sampled. This is a member of the VkSamplerMipmapMode-enumerant.
         * If the mipmap mode is VK_SAMPLER_MIPMAP_MODE_NEAREST, the selected mipmap level is rounded down to the next lowest integer, and then that
         * level is sampled as if it were a single-level image. When the mipmap mode is VK_SAMPLER_MIPMAP_MODE_LINEAR, a sample is taken from each of
         * the next-lower and next-higher levels using the filter mode selected by the {minFilter} field, and then those two samples are further
         * combined using a weighted average, similar to how the samples are combined during linear sampling, as previously described. Note that this
         * filter mode only applies to minification, which is the process of sampling from a different mipmap level than the base level.
         * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkSamplerMipmapMode.html
         * @param addressModeU Used to select the transformer applied to texture coordinates that would otherwise be sampled outside the image. This
         * is a member of the VkSamplerAddressMode-enumerant. U is the X within the convention of texture space coordinates.
         * @param addressModeV Used to select the transformer applied to texture coordinates that would otherwise be sampled outside the image. This
         * is a member of the VkSamplerAddressMode-enumerant. V is the Y within the convention of texture space coordinates.
         * @param addressModeW Used to select the transformer applied to texture coordinates that would otherwise be sampled outside the image. This
         * is a member of the VkSamplerAddressMode-enumerant. W is the Z within the convention of texture space coordinates.
         * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkSamplerAddressMode.html
         * @param mipLodBias A floating-point bias that is added to the computed level of detail before making mipmap selection. This can push the
         * level of detail up or down in the mipmap chain to make the resulting filtered texture look sharper or fainter than it would otherwise.
         * @param anisotropyEnable If anisotropic filtering is to be used, it can be set to VK_TRUE. If not, it can be set to VK_FALSE.
         * Anisotropic filtering generally works by considering a projected footprint of the area to be sampled (or "sampled") rather than using a
         * fixed 2×2 footprint. An approximation of a surface sample is formed by taking many samples within the footprint.
         * @param maxAnisotropy Because the number of samples taken can be quite large, anisotropic filtering can have a negative effect on
         * performance. Also, in extreme cases, the projected footprint can be quite large, and this can result in a large area and a correspondingly
         * blurry filter result. To mitigate these effects, the maximum amount of anisotropy can be locked by setting {maxAnisotropy} to a value
         * between 1.0f and the maximum value supported by the device. The maximum values can be determined by calling PhysicalDevice#getProperties
         * and inspecting the maxSamplerAnisotropy member of the embedded VkPhysicalDeviceLimits structure.
         * @param compareEnable When a sampler is used with a depth image, it can be configured to perform a compare operation and return the result
         * of the comparison instead of the raw values stored in the image. When this mode is enabled, the comparison is performed on each sample
         * taken from the image, and the resulting value is the fraction of the total number of samples taken that passed the test. This can be used
         * to implement a technique known as percentage closer filtering or PCF. To enable this mode, {compareEnable} must be set to VK_TRUE and the
         * compare operation must be set to {compareOp}.
         * @param compareOp A member of the VkCompareOp-enumeration, which is used in many places in Vulkan, including the graphical pipeline. This is
         * the enumeration used to specify the depth test operation.
         * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkSamplerAddressMode.html
         * @param minLod The lowest mipmaps (highest resolution) to sample from.
         * The sampler can be configured to limit sampling to a subset of the mip levels in an image with mipmaps. The range of mipmaps to sample from
         * is specified in {minLod} and {maxLod}.
         * @param maxLod The highest mipmaps (lowest resolution) to sample from.
         * @param borderColor The border color used in place of data from the image if {addressmodeU}, {addressmodeV} and/or {addressmodeW} is set to
         * VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_BORDER. This is a member of the VkBorderColor-enumerant.
         * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkBorderColor.html
         * @param unnormalizedCoordinates A flag that, when set to VK_TRUE, indicates that the coordinates used to extract from the image are in raw
         * texel units, rather than a value normalized between 0.0 and 1.0 for each dimension of the texture. This allows texels to be explicitly
         * extracted from the image. However, there are several limitations in this mode. When {unnormalizedCoordinates} is set to VK_TRUE,
         * {minFilter} and {magFilter} must be the same, {mipmapMode} must be set to VK_SAMPLER_MIPMAP_MODE_NEAREST and {anisotropyEnable} and
         * {compareEnable} must be set to VK_FALSE.
         *
         * @throws std::runtime_error if the Vulkan Sampler couldn't be created.
         * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkSampler.html
         *
         * @note It is recommended to not create a Sampler by it's Constructor, but to use a Sampler Builder.
         */
        Sampler(LogicalDevice* pLogicalDevice, VkFilter magFilter, VkFilter minFilter, VkSamplerMipmapMode mipmapMode,
                VkSamplerAddressMode addressModeU, VkSamplerAddressMode addressModeV, VkSamplerAddressMode addressModeW, float mipLodBias,
                VkBool32 anisotropyEnable, float maxAnisotropy, VkBool32 compareEnable, VkCompareOp compareOp, float minLod, float maxLod,
                VkBorderColor borderColor, VkBool32 unnormalizedCoordinates);
        ~Sampler();
        Sampler(const Sampler&) = delete;
        Sampler& operator=(const Sampler&) = delete;

        const VkSampler getSamplerHandle() const;
    };
} // namespace fillcan