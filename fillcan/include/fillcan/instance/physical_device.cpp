// fillcan
#include "vulkan/vulkan_core.h"
#include <fillcan/instance/physical_device.hpp>

// std
#include <array>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <memory>
#include <optional>
#include <stdexcept>

namespace fillcan {
    PhysicalDevice::PhysicalDevice(VkPhysicalDevice hPhysicalDevice, Window* pWindow, std::vector<const char*> requiredExtensions,
                                   VkPhysicalDeviceFeatures requiredFeatures)
        : hPhysicalDevice(hPhysicalDevice), pWindow(pWindow), requiredExtensions(requiredExtensions), requiredFeatures(requiredFeatures) {
        std::vector<VkQueueFamilyProperties> physicalDeviceQueueFamilyProperties = this->getQueueFamilyProperties();
        if (pWindow != nullptr) {
            this->findGraphicsQueueFamilyIndices(physicalDeviceQueueFamilyProperties);
            this->findPresentQueueFamilyIndices(physicalDeviceQueueFamilyProperties);
        }
        this->findComputeQueueFamilyIndices(physicalDeviceQueueFamilyProperties);
    }

    PhysicalDevice::~PhysicalDevice() {}

    const VkPhysicalDevice PhysicalDevice::getPhysicalDeviceHandle() const { return this->hPhysicalDevice; }

    const std::vector<const char*>& PhysicalDevice::getRequiredExtensions() const { return this->requiredExtensions; }

    bool PhysicalDevice::areExtensionsSupported() {
        unsigned int extensionCount;
        vkEnumerateDeviceExtensionProperties(this->hPhysicalDevice, nullptr, &extensionCount, nullptr);

        std::vector<VkExtensionProperties> allExtensions(extensionCount);
        vkEnumerateDeviceExtensionProperties(this->hPhysicalDevice, nullptr, &extensionCount, allExtensions.data());

        for (const char* extensionName : this->requiredExtensions) {
            bool extensionFound = false;
            for (const VkExtensionProperties& extensionProperties : allExtensions) {
                if (std::strcmp(extensionName, extensionProperties.extensionName) == 0) {
                    extensionFound = true;
                    break;
                }
            }

            if (!extensionFound) {
                return false;
            }
        }
        return true;
    }

    const VkPhysicalDeviceFeatures& PhysicalDevice::getRequiredFeatures() const { return this->requiredFeatures; }

    bool PhysicalDevice::areFeaturesSupported() {
        VkPhysicalDeviceFeatures supportedFeatures = getFeatures();
        VkPhysicalDeviceFeatures features = this->requiredFeatures;
        return (features.robustBufferAccess ? supportedFeatures.robustBufferAccess == VK_TRUE : true) &&
               (features.fullDrawIndexUint32 ? supportedFeatures.fullDrawIndexUint32 == VK_TRUE : true) &&
               (features.imageCubeArray ? supportedFeatures.imageCubeArray == VK_TRUE : true) &&
               (features.independentBlend ? supportedFeatures.independentBlend == VK_TRUE : true) &&
               (features.geometryShader ? supportedFeatures.geometryShader == VK_TRUE : true) &&
               (features.tessellationShader ? supportedFeatures.tessellationShader == VK_TRUE : true) &&
               (features.sampleRateShading ? supportedFeatures.tessellationShader == VK_TRUE : true) &&
               (features.logicOp ? supportedFeatures.logicOp == VK_TRUE : true) &&
               (features.multiDrawIndirect ? supportedFeatures.multiDrawIndirect == VK_TRUE : true) &&
               (features.drawIndirectFirstInstance ? supportedFeatures.drawIndirectFirstInstance == VK_TRUE : true) &&
               (features.depthClamp ? supportedFeatures.depthClamp == VK_TRUE : true) &&
               (features.depthBiasClamp ? supportedFeatures.depthBiasClamp == VK_TRUE : true) &&
               (features.fillModeNonSolid ? supportedFeatures.fillModeNonSolid == VK_TRUE : true) &&
               (features.depthBounds ? supportedFeatures.depthBounds == VK_TRUE : true) &&
               (features.wideLines ? supportedFeatures.wideLines == VK_TRUE : true) &&
               (features.largePoints ? supportedFeatures.largePoints == VK_TRUE : true) &&
               (features.alphaToOne ? supportedFeatures.alphaToOne == VK_TRUE : true) &&
               (features.multiViewport ? supportedFeatures.multiViewport == VK_TRUE : true) &&
               (features.samplerAnisotropy ? supportedFeatures.samplerAnisotropy == VK_TRUE : true) &&
               (features.textureCompressionETC2 ? supportedFeatures.textureCompressionETC2 == VK_TRUE : true) &&
               (features.textureCompressionASTC_LDR ? supportedFeatures.textureCompressionASTC_LDR == VK_TRUE : true) &&
               (features.textureCompressionBC ? supportedFeatures.textureCompressionBC == VK_TRUE : true) &&
               (features.occlusionQueryPrecise ? supportedFeatures.occlusionQueryPrecise == VK_TRUE : true) &&
               (features.pipelineStatisticsQuery ? supportedFeatures.pipelineStatisticsQuery == VK_TRUE : true) &&
               (features.vertexPipelineStoresAndAtomics ? supportedFeatures.vertexPipelineStoresAndAtomics == VK_TRUE : true) &&
               (features.fragmentStoresAndAtomics ? supportedFeatures.fragmentStoresAndAtomics == VK_TRUE : true) &&
               (features.shaderTessellationAndGeometryPointSize ? supportedFeatures.shaderTessellationAndGeometryPointSize == VK_TRUE : true) &&
               (features.shaderImageGatherExtended ? supportedFeatures.shaderImageGatherExtended == VK_TRUE : true) &&
               (features.shaderStorageImageExtendedFormats ? supportedFeatures.shaderStorageImageExtendedFormats == VK_TRUE : true) &&
               (features.shaderStorageImageMultisample ? supportedFeatures.shaderStorageImageMultisample == VK_TRUE : true) &&
               (features.shaderStorageImageReadWithoutFormat ? supportedFeatures.shaderStorageImageReadWithoutFormat == VK_TRUE : true) &&
               (features.shaderStorageImageWriteWithoutFormat ? supportedFeatures.shaderStorageImageWriteWithoutFormat == VK_TRUE : true) &&
               (features.shaderUniformBufferArrayDynamicIndexing ? supportedFeatures.shaderUniformBufferArrayDynamicIndexing == VK_TRUE : true) &&
               (features.shaderSampledImageArrayDynamicIndexing ? supportedFeatures.shaderSampledImageArrayDynamicIndexing == VK_TRUE : true) &&
               (features.shaderStorageBufferArrayDynamicIndexing ? supportedFeatures.shaderStorageBufferArrayDynamicIndexing == VK_TRUE : true) &&
               (features.shaderStorageImageArrayDynamicIndexing ? supportedFeatures.shaderStorageImageArrayDynamicIndexing == VK_TRUE : true) &&
               (features.shaderClipDistance ? supportedFeatures.shaderClipDistance == VK_TRUE : true) &&
               (features.shaderCullDistance ? supportedFeatures.shaderCullDistance == VK_TRUE : true) &&
               (features.shaderFloat64 ? supportedFeatures.shaderFloat64 == VK_TRUE : true) &&
               (features.shaderInt64 ? supportedFeatures.shaderInt64 == VK_TRUE : true) &&
               (features.shaderInt16 ? supportedFeatures.shaderInt16 == VK_TRUE : true) &&
               (features.shaderResourceResidency ? supportedFeatures.shaderResourceResidency == VK_TRUE : true) &&
               (features.shaderResourceMinLod ? supportedFeatures.shaderResourceMinLod == VK_TRUE : true) &&
               (features.sparseBinding ? supportedFeatures.sparseBinding == VK_TRUE : true) &&
               (features.sparseResidencyBuffer ? supportedFeatures.sparseResidencyBuffer == VK_TRUE : true) &&
               (features.sparseResidencyImage2D ? supportedFeatures.sparseResidencyImage2D == VK_TRUE : true) &&
               (features.sparseResidencyImage3D ? supportedFeatures.sparseResidencyImage3D == VK_TRUE : true) &&
               (features.sparseResidency2Samples ? supportedFeatures.sparseResidency2Samples == VK_TRUE : true) &&
               (features.sparseResidency4Samples ? supportedFeatures.sparseResidency4Samples == VK_TRUE : true) &&
               (features.sparseResidency8Samples ? supportedFeatures.sparseResidency8Samples == VK_TRUE : true) &&
               (features.sparseResidency16Samples ? supportedFeatures.sparseResidency16Samples == VK_TRUE : true) &&
               (features.sparseResidencyAliased ? supportedFeatures.sparseResidencyAliased == VK_TRUE : true) &&
               (features.variableMultisampleRate ? supportedFeatures.variableMultisampleRate == VK_TRUE : true) &&
               (features.inheritedQueries ? supportedFeatures.inheritedQueries == VK_TRUE : true);
    }

    const VkPhysicalDeviceFeatures PhysicalDevice::getFeatures() const {
        VkPhysicalDeviceFeatures features;
        vkGetPhysicalDeviceFeatures(this->hPhysicalDevice, &features);
        return features;
    }

    const VkPhysicalDeviceProperties PhysicalDevice::getProperties() const {
        VkPhysicalDeviceProperties properties;
        vkGetPhysicalDeviceProperties(this->hPhysicalDevice, &properties);
        return properties;
    }

    const VkSurfaceCapabilitiesKHR PhysicalDevice::getSurfaceCapabilitiesKHR() const {
        if (!this->pWindow) {
            std::cerr << "Requested to query Surface Capabilities without a Window bound."
                      << "\n";
            return {};
        }
        VkSurfaceCapabilitiesKHR surfaceCapabilities;
        vkGetPhysicalDeviceSurfaceCapabilitiesKHR(this->hPhysicalDevice, this->pWindow->getSurface(), &surfaceCapabilities);
        return surfaceCapabilities;
    }

    const std::vector<VkSurfaceFormatKHR> PhysicalDevice::getSurfaceFormatsKHR() const {
        if (!this->pWindow) {
            std::cerr << "Requested to query Physical Device Surface Formats without a Window bound."
                      << "\n";
            return {};
        }
        uint32_t surfaceFormatCount = 0;
        vkGetPhysicalDeviceSurfaceFormatsKHR(this->hPhysicalDevice, this->pWindow->getSurface(), &surfaceFormatCount, nullptr);
        if (surfaceFormatCount == 0) {
            return {};
        }
        std::vector<VkSurfaceFormatKHR> surfaceFormats(surfaceFormatCount);
        vkGetPhysicalDeviceSurfaceFormatsKHR(this->hPhysicalDevice, this->pWindow->getSurface(), &surfaceFormatCount, surfaceFormats.data());
        return surfaceFormats;
    }

    const std::vector<VkPresentModeKHR> PhysicalDevice::getSurfacePresentModesKHR() const {
        if (!this->pWindow) {
            std::cerr << "Requested to query Present Modes without a Window bound."
                      << "\n";
            return {};
        }
        uint32_t presentModeCount;
        vkGetPhysicalDeviceSurfacePresentModesKHR(this->hPhysicalDevice, this->pWindow->getSurface(), &presentModeCount, nullptr);
        if (presentModeCount == 0) {
            return {};
        }
        std::vector<VkPresentModeKHR> presentModes(presentModeCount);
        vkGetPhysicalDeviceSurfacePresentModesKHR(this->hPhysicalDevice, this->pWindow->getSurface(), &presentModeCount, presentModes.data());
        return presentModes;
    }

    const std::vector<VkQueueFamilyProperties> PhysicalDevice::getQueueFamilyProperties() const {
        uint32_t queueFamilyPropertyCount;
        vkGetPhysicalDeviceQueueFamilyProperties(this->hPhysicalDevice, &queueFamilyPropertyCount, nullptr);
        if (queueFamilyPropertyCount == 0) {
            return {};
        }
        std::vector<VkQueueFamilyProperties> queueFamilyProperties(queueFamilyPropertyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(this->hPhysicalDevice, &queueFamilyPropertyCount, queueFamilyProperties.data());
        return queueFamilyProperties;
    }

    const VkFormatProperties PhysicalDevice::getFormatProperties(VkFormat format) const {
        VkFormatProperties formatProperties;
        vkGetPhysicalDeviceFormatProperties(this->hPhysicalDevice, format, &formatProperties);
        return formatProperties;
    }

    const VkPhysicalDeviceMemoryProperties PhysicalDevice::getMemoryProperties() const {
        VkPhysicalDeviceMemoryProperties memoryProperties;
        vkGetPhysicalDeviceMemoryProperties(this->hPhysicalDevice, &memoryProperties);
        return memoryProperties;
    }

    const std::optional<VkFormat> PhysicalDevice::findSupportedFormat(std::vector<VkFormat> formats, VkImageTiling tiling,
                                                                      VkFormatFeatureFlags features) const {
        for (VkFormat format : formats) {
            VkFormatProperties formatProperties = this->getFormatProperties(format);
            if ((tiling == VK_IMAGE_TILING_LINEAR && (formatProperties.linearTilingFeatures & features)) ||
                (tiling == VK_IMAGE_TILING_OPTIMAL && (formatProperties.optimalTilingFeatures & features))) {
                return format;
            }
        }
        return std::nullopt;
    }

    void PhysicalDevice::findGraphicsQueueFamilyIndices(std::vector<VkQueueFamilyProperties> queueFamilyProperties) {
        if (!this->pWindow) {
            std::cerr << "Requested to find graphics queue family indices without a Window bound."
                      << "\n";
            return;
        }
        if (queueFamilyProperties.size() <= 0) {
            queueFamilyProperties = this->getQueueFamilyProperties();
        }
        for (size_t i = 0; i < queueFamilyProperties.size(); i++) {
            if (queueFamilyProperties[i].queueCount > 0 && queueFamilyProperties[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
                this->graphicsQueueFamilyIndices.push_back(i);
            }
        }
    }

    void PhysicalDevice::findPresentQueueFamilyIndices(std::vector<VkQueueFamilyProperties> queueFamilyProperties) {
        if (!this->pWindow) {
            std::cerr << "Requested to find present queue family indices without a Window bound."
                      << "\n";
            return;
        }
        if (queueFamilyProperties.size() <= 0) {
            queueFamilyProperties = this->getQueueFamilyProperties();
        }
        for (size_t i = 0; i < queueFamilyProperties.size(); i++) {
            VkBool32 presentSupported = VK_FALSE;
            vkGetPhysicalDeviceSurfaceSupportKHR(this->hPhysicalDevice, i, this->pWindow->getSurface(), &presentSupported);
            if (queueFamilyProperties[i].queueCount > 0 && presentSupported) {
                this->presentQueueFamilyIndices.push_back(i);
            }
        }
    }

    void PhysicalDevice::findComputeQueueFamilyIndices(std::vector<VkQueueFamilyProperties> queueFamilyProperties) {
        if (queueFamilyProperties.size() <= 0) {
            queueFamilyProperties = this->getQueueFamilyProperties();
        }
        for (size_t i = 0; i < queueFamilyProperties.size(); i++) {
            if (queueFamilyProperties[i].queueCount > 0 && queueFamilyProperties[i].queueFlags & VK_QUEUE_COMPUTE_BIT) {
                this->computeQueueFamilyIndices.push_back(i);
            }
        }
    }

    const std::vector<unsigned int>& PhysicalDevice::getGraphicsQueueFamilyIndices() const { return this->graphicsQueueFamilyIndices; }
    const std::vector<unsigned int>& PhysicalDevice::getPresentQueueFamilyIndices() const { return this->presentQueueFamilyIndices; }
    const std::vector<unsigned int>& PhysicalDevice::getComputeQueueFamilyIndices() const { return this->computeQueueFamilyIndices; }
} // namespace fillcan