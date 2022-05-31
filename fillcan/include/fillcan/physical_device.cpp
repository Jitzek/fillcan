#include "fillcan/physical_device.hpp"
#include "fillcan/window.hpp"
#include "vulkan/vulkan_core.h"
#include <array>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <fillcan/physical_device.hpp>
#include <vector>

namespace fillcan {
    PhysicalDevice::PhysicalDevice(VkPhysicalDevice hPhysicalDevice, Window* pWindow, std::vector<const char*> requiredExtensions,
                                   VkPhysicalDeviceFeatures requiredFeatures)
        : hPhysicalDevice(hPhysicalDevice), pWindow(pWindow), requiredExtensions(requiredExtensions), requiredFeatures(requiredFeatures) {
        std::vector<VkQueueFamilyProperties> physicalDeviceQueueFamilyProperties = this->getQueueFamilyProperties();
        this->findGraphicsAndPresentQueueFamilyIndex(physicalDeviceQueueFamilyProperties);
        this->findComputeQueueFamilyIndex(physicalDeviceQueueFamilyProperties);
    }

    PhysicalDevice::~PhysicalDevice() {}

    VkPhysicalDevice PhysicalDevice::getPhysicalDeviceHandle() { return this->hPhysicalDevice; }
    Window* PhysicalDevice::getWindow() { return this->pWindow; }

    std::vector<const char*> PhysicalDevice::getRequiredExtensions() { return this->requiredExtensions; }

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

    VkPhysicalDeviceFeatures PhysicalDevice::getRequiredFeatures() { return this->requiredFeatures; }

    bool PhysicalDevice::areFeaturesSupported() {
        VkPhysicalDeviceFeatures supportedFeatures = getFeatures();
        VkPhysicalDeviceFeatures features = this->requiredFeatures;
        return (features.robustBufferAccess ? supportedFeatures.robustBufferAccess == true : true) &&
               (features.fullDrawIndexUint32 ? supportedFeatures.fullDrawIndexUint32 == true : true) &&
               (features.imageCubeArray ? supportedFeatures.imageCubeArray == true : true) &&
               (features.independentBlend ? supportedFeatures.independentBlend == true : true) &&
               (features.geometryShader ? supportedFeatures.geometryShader == true : true) &&
               (features.tessellationShader ? supportedFeatures.tessellationShader == true : true) &&
               (features.sampleRateShading ? supportedFeatures.tessellationShader == true : true) &&
               (features.logicOp ? supportedFeatures.logicOp == true : true) &&
               (features.multiDrawIndirect ? supportedFeatures.multiDrawIndirect == true : true) &&
               (features.drawIndirectFirstInstance ? supportedFeatures.drawIndirectFirstInstance == true : true) &&
               (features.depthClamp ? supportedFeatures.depthClamp == true : true) &&
               (features.depthBiasClamp ? supportedFeatures.depthBiasClamp == true : true) &&
               (features.fillModeNonSolid ? supportedFeatures.fillModeNonSolid == true : true) &&
               (features.depthBounds ? supportedFeatures.depthBounds == true : true) &&
               (features.wideLines ? supportedFeatures.wideLines == true : true) &&
               (features.largePoints ? supportedFeatures.largePoints == true : true) &&
               (features.alphaToOne ? supportedFeatures.alphaToOne == true : true) &&
               (features.multiViewport ? supportedFeatures.multiViewport == true : true) &&
               (features.samplerAnisotropy ? supportedFeatures.samplerAnisotropy == true : true) &&
               (features.textureCompressionETC2 ? supportedFeatures.textureCompressionETC2 == true : true) &&
               (features.textureCompressionASTC_LDR ? supportedFeatures.textureCompressionASTC_LDR == true : true) &&
               (features.textureCompressionBC ? supportedFeatures.textureCompressionBC == true : true) &&
               (features.occlusionQueryPrecise ? supportedFeatures.occlusionQueryPrecise == true : true) &&
               (features.pipelineStatisticsQuery ? supportedFeatures.pipelineStatisticsQuery == true : true) &&
               (features.vertexPipelineStoresAndAtomics ? supportedFeatures.vertexPipelineStoresAndAtomics == true : true) &&
               (features.fragmentStoresAndAtomics ? supportedFeatures.fragmentStoresAndAtomics == true : true) &&
               (features.shaderTessellationAndGeometryPointSize ? supportedFeatures.shaderTessellationAndGeometryPointSize == true : true) &&
               (features.shaderImageGatherExtended ? supportedFeatures.shaderImageGatherExtended == true : true) &&
               (features.shaderStorageImageExtendedFormats ? supportedFeatures.shaderStorageImageExtendedFormats == true : true) &&
               (features.shaderStorageImageMultisample ? supportedFeatures.shaderStorageImageMultisample == true : true) &&
               (features.shaderStorageImageReadWithoutFormat ? supportedFeatures.shaderStorageImageReadWithoutFormat == true : true) &&
               (features.shaderStorageImageWriteWithoutFormat ? supportedFeatures.shaderStorageImageWriteWithoutFormat == true : true) &&
               (features.shaderUniformBufferArrayDynamicIndexing ? supportedFeatures.shaderUniformBufferArrayDynamicIndexing == true : true) &&
               (features.shaderSampledImageArrayDynamicIndexing ? supportedFeatures.shaderSampledImageArrayDynamicIndexing == true : true) &&
               (features.shaderStorageBufferArrayDynamicIndexing ? supportedFeatures.shaderStorageBufferArrayDynamicIndexing == true : true) &&
               (features.shaderStorageImageArrayDynamicIndexing ? supportedFeatures.shaderStorageImageArrayDynamicIndexing == true : true) &&
               (features.shaderClipDistance ? supportedFeatures.shaderClipDistance == true : true) &&
               (features.shaderCullDistance ? supportedFeatures.shaderCullDistance == true : true) &&
               (features.shaderFloat64 ? supportedFeatures.shaderFloat64 == true : true) &&
               (features.shaderInt64 ? supportedFeatures.shaderInt64 == true : true) &&
               (features.shaderInt16 ? supportedFeatures.shaderInt16 == true : true) &&
               (features.shaderResourceResidency ? supportedFeatures.shaderResourceResidency == true : true) &&
               (features.shaderResourceMinLod ? supportedFeatures.shaderResourceMinLod == true : true) &&
               (features.sparseBinding ? supportedFeatures.sparseBinding == true : true) &&
               (features.sparseResidencyBuffer ? supportedFeatures.sparseResidencyBuffer == true : true) &&
               (features.sparseResidencyImage2D ? supportedFeatures.sparseResidencyImage2D == true : true) &&
               (features.sparseResidencyImage3D ? supportedFeatures.sparseResidencyImage3D == true : true) &&
               (features.sparseResidency2Samples ? supportedFeatures.sparseResidency2Samples == true : true) &&
               (features.sparseResidency4Samples ? supportedFeatures.sparseResidency4Samples == true : true) &&
               (features.sparseResidency8Samples ? supportedFeatures.sparseResidency8Samples == true : true) &&
               (features.sparseResidency16Samples ? supportedFeatures.sparseResidency16Samples == true : true) &&
               (features.sparseResidencyAliased ? supportedFeatures.sparseResidencyAliased == true : true) &&
               (features.variableMultisampleRate ? supportedFeatures.variableMultisampleRate == true : true) &&
               (features.inheritedQueries ? supportedFeatures.inheritedQueries == true : true);
    }

    void PhysicalDevice::findGraphicsAndPresentQueueFamilyIndex(std::vector<VkQueueFamilyProperties> queueFamilyProperties) {
        if (queueFamilyProperties.size() <= 0) {
            queueFamilyProperties = this->getQueueFamilyProperties();
        }
        for (size_t i = 0; i < queueFamilyProperties.size(); i++) {
            if (queueFamilyProperties[i].queueCount > 0 && queueFamilyProperties[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
                graphicsQueueFamilyIndex = i;
            }
            VkBool32 presentSupported = VK_FALSE;
            vkGetPhysicalDeviceSurfaceSupportKHR(this->hPhysicalDevice, i, this->pWindow->getSurface(), &presentSupported);
            if (queueFamilyProperties[i].queueCount > 0 && presentSupported) {
                presentQueueFamilyIndex = i;
            }
            // Prefer that the graphics and present use the same queue
            if (graphicsQueueFamilyIndex != -1 && graphicsQueueFamilyIndex == presentQueueFamilyIndex) {
                break;
            }
        }
    }

    void PhysicalDevice::findComputeQueueFamilyIndex(std::vector<VkQueueFamilyProperties> queueFamilyProperties) {
        if (queueFamilyProperties.size() <= 0) {
            queueFamilyProperties = this->getQueueFamilyProperties();
        }
        for (size_t i = 0; i < queueFamilyProperties.size(); i++) {
            if (queueFamilyProperties[i].queueCount > 0 && queueFamilyProperties[i].queueFlags & VK_QUEUE_COMPUTE_BIT) {
                computeQueueFamilyIndex = i;
                break;
            }
        }
    }

    VkPhysicalDeviceFeatures PhysicalDevice::getFeatures() {
        VkPhysicalDeviceFeatures features;
        vkGetPhysicalDeviceFeatures(this->hPhysicalDevice, &features);
        return features;
    }

    VkPhysicalDeviceProperties PhysicalDevice::getProperties() {
        VkPhysicalDeviceProperties properties;
        vkGetPhysicalDeviceProperties(this->hPhysicalDevice, &properties);
        return properties;
    }

    VkSurfaceCapabilitiesKHR PhysicalDevice::getSurfaceCapabilitiesKHR() {
        VkSurfaceCapabilitiesKHR surfaceCapabilities;
        vkGetPhysicalDeviceSurfaceCapabilitiesKHR(this->hPhysicalDevice, this->pWindow->getSurface(), &surfaceCapabilities);
        return surfaceCapabilities;
    }

    std::vector<VkSurfaceFormatKHR> PhysicalDevice::getSurfaceFormatsKHR() {
        uint32_t surfaceFormatCount = 0;
        vkGetPhysicalDeviceSurfaceFormatsKHR(this->hPhysicalDevice, this->pWindow->getSurface(), &surfaceFormatCount, nullptr);
        if (surfaceFormatCount == 0) {
            return {};
        }
        std::vector<VkSurfaceFormatKHR> surfaceFormats(surfaceFormatCount);
        vkGetPhysicalDeviceSurfaceFormatsKHR(this->hPhysicalDevice, this->pWindow->getSurface(), &surfaceFormatCount, surfaceFormats.data());
        return surfaceFormats;
    }

    std::vector<VkPresentModeKHR> PhysicalDevice::getSurfacePresentModesKHR() {
        uint32_t presentModeCount;
        vkGetPhysicalDeviceSurfacePresentModesKHR(this->hPhysicalDevice, this->pWindow->getSurface(), &presentModeCount, nullptr);
        if (presentModeCount == 0) {
            return {};
        }
        std::vector<VkPresentModeKHR> presentModes(presentModeCount);
        vkGetPhysicalDeviceSurfacePresentModesKHR(this->hPhysicalDevice, this->pWindow->getSurface(), &presentModeCount, presentModes.data());
        return presentModes;
    }

    std::vector<VkQueueFamilyProperties> PhysicalDevice::getQueueFamilyProperties() {
        uint32_t queueFamilyPropertyCount;
        vkGetPhysicalDeviceQueueFamilyProperties(this->hPhysicalDevice, &queueFamilyPropertyCount, nullptr);
        if (queueFamilyPropertyCount == 0) {
            return {};
        }
        std::vector<VkQueueFamilyProperties> queueFamilyProperties(queueFamilyPropertyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(this->hPhysicalDevice, &queueFamilyPropertyCount, queueFamilyProperties.data());
        return queueFamilyProperties;
    }

    int PhysicalDevice::getGraphicsQueueFamilyIndex() { return this->graphicsQueueFamilyIndex; }
    int PhysicalDevice::getPresentQueueFamilyIndex() { return this->presentQueueFamilyIndex; }
    int PhysicalDevice::getComputeQueueFamilyIndex() { return this->computeQueueFamilyIndex; }
} // namespace fillcan