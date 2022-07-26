<script lang="ts">
    import { fly } from "svelte/transition";
    import Anchor from "$components/Documentation/Anchor.svelte";
    import { DisplayType } from "$objects/State";
    import { getState, stateStore } from "$stores/StateStore";

    import Highlight from "svelte-highlight";
    import cppHighlight from "svelte-highlight/languages/cpp";
    import cmakeHighlight from "svelte-highlight/languages/cmake";
    import jsonHighlight from "svelte-highlight/languages/json";
    import nord from "svelte-highlight/styles/nord";
    import {
        SectionID,
        type Section as SectionObject,
    } from "$objects/Documentation/Section";
    import GettingStarted from "$components/Documentation/Sections/Getting_Started/GettingStarted.svelte";
    import Section from "$components/Documentation/Section.svelte";
    import CMake from "$components/Documentation/Sections/Getting_Started/CMake.svelte";
    import Fillcan from "$components/Documentation/Sections/Fillcan/Fillcan.svelte";
    import FillcanConstructor from "$components/Documentation/Sections/Fillcan/FillcanConstructor.svelte";
    import GetSupportedPhysicalDevices from "$components/Documentation/Sections/Fillcan/getSupportedPhysicalDevices.svelte";
    import SelectDevice from "$components/Documentation/Sections/Fillcan/selectDevice.svelte";
    import GetCurrentDevice from "$components/Documentation/Sections/Fillcan/getCurrentDevice.svelte";
    import GetWindow from "$components/Documentation/Sections/Fillcan_Graphics/getWindow.svelte";
    import CreateShaderModule from "$components/Documentation/Sections/Fillcan/createShaderModule.svelte";
    import HamburgerMenuIcon from "$components/NavBar/HamburgerMenuIcon.svelte";
    import FillcanGraphics from "$components/Documentation/Sections/Fillcan_Graphics/FillcanGraphics.svelte";
    import FillcanGraphicsConstructor from "$components/Documentation/Sections/Fillcan_Graphics/FillcanGraphicsConstructor.svelte";
    import MainLoop from "$components/Documentation/Sections/Fillcan_Graphics/mainLoop.svelte";
    import CreateSwapchain from "$components/Documentation/Sections/Fillcan_Graphics/createSwapchain.svelte";
    import RecreateSwapchain from "$components/Documentation/Sections/Fillcan_Graphics/recreateSwapchain.svelte";
    import GetSwapchain from "$components/Documentation/Sections/Fillcan_Graphics/getSwapchain.svelte";
    import GetSwapchains from "$components/Documentation/Sections/Fillcan_Graphics/getSwapchains.svelte";
    import DestroySwapchain from "$components/Documentation/Sections/Fillcan_Graphics/destroySwapchain.svelte";
    import GetAssetManager from "$components/Documentation/Sections/Fillcan_Graphics/getAssetManager.svelte";
    import Window from "$components/Documentation/Sections/Window/Window.svelte";
    import WindowConstructor from "$components/Documentation/Sections/Window/WindowConstructor.svelte";
    import ShouldClose from "$components/Documentation/Sections/Window/shouldClose.svelte";
    import WasResized from "$components/Documentation/Sections/Window/wasResized.svelte";
    import PollEvents from "$components/Documentation/Sections/Window/pollEvents.svelte";
    import WindowGetRequiredExtensions from "$components/Documentation/Sections/Window/WindowGetRequiredExtensions.svelte";
    import CreateSurface from "$components/Documentation/Sections/Window/createSurface.svelte";
    import GetSurface from "$components/Documentation/Sections/Window/getSurface.svelte";
    import GetExtent from "$components/Documentation/Sections/Window/getExtent.svelte";
    import Instance from "$components/Documentation/Sections/Instance/Instance.svelte";
    import InstanceConstructor from "$components/Documentation/Sections/Instance/InstanceConstructor.svelte";
    import GetInstanceHandle from "$components/Documentation/Sections/Instance/getInstanceHandle.svelte";
    import DevicePool from "$components/Documentation/Sections/Device_Pool/DevicePool.svelte";
    import DevicePoolConstructor from "$components/Documentation/Sections/Device_Pool/DevicePoolConstructor.svelte";
    import DevicePoolgetSupportedPhysicalDevices from "$components/Documentation/Sections/Device_Pool/DevicePoolgetSupportedPhysicalDevices.svelte";
    import DevicePoolselectDevice from "$components/Documentation/Sections/Device_Pool/DevicePoolselectDevice.svelte";
    import DevicePoolgetCurrentDevice from "$components/Documentation/Sections/Device_Pool/DevicePoolgetCurrentDevice.svelte";
    import PhysicalDevice from "$components/Documentation/Sections/Physical_Device/PhysicalDevice.svelte";
    import PhysicalDeviceConstructor from "$components/Documentation/Sections/Physical_Device/PhysicalDeviceConstructor.svelte";
    import GetPhysicalDeviceHandle from "$components/Documentation/Sections/Physical_Device/getPhysicalDeviceHandle.svelte";
    import GetRequiredExtensions from "$components/Documentation/Sections/Physical_Device/getRequiredExtensions.svelte";
    import AreExtensionsSupported from "$components/Documentation/Sections/Physical_Device/areExtensionsSupported.svelte";
    import DocumentationSectionList from "$components/Documentation/DocumentationSectionList.svelte";
    import GetRequiredFeatures from "$components/Documentation/Sections/Physical_Device/getRequiredFeatures.svelte";
    import AreFeaturesSupported from "$components/Documentation/Sections/Physical_Device/areFeaturesSupported.svelte";
    import GetFeatures from "$components/Documentation/Sections/Physical_Device/getFeatures.svelte";
    import GetProperties from "$components/Documentation/Sections/Physical_Device/getProperties.svelte";
    import GetSurfaceCapabilitiesKhr from "$components/Documentation/Sections/Physical_Device/getSurfaceCapabilitiesKHR.svelte";
    import GetSurfaceFormatsKhr from "$components/Documentation/Sections/Physical_Device/getSurfaceFormatsKHR.svelte";
    import GetSurfacePresentModesKhr from "$components/Documentation/Sections/Physical_Device/getSurfacePresentModesKHR.svelte";
    import GetQueueFamilyProperties from "$components/Documentation/Sections/Physical_Device/getQueueFamilyProperties.svelte";
    import GetFormatProperties from "$components/Documentation/Sections/Physical_Device/getFormatProperties.svelte";
    import FindSupportedFormat from "$components/Documentation/Sections/Physical_Device/findSupportedFormat.svelte";
    import GetGraphicsQueueFamilyIndices from "$components/Documentation/Sections/Physical_Device/getGraphicsQueueFamilyIndices.svelte";
    import GetPresentQueueFamilyIndices from "$components/Documentation/Sections/Physical_Device/getPresentQueueFamilyIndices.svelte";
    import GetComputeQueueFamilyIndices from "$components/Documentation/Sections/Physical_Device/getComputeQueueFamilyIndices.svelte";
    import LogicalDevice from "$components/Documentation/Sections/Logical_Device/LogicalDevice.svelte";
    import LogicalDeviceConstructor from "$components/Documentation/Sections/Logical_Device/LogicalDeviceConstructor.svelte";
    import GetLogicalDeviceHandle from "$components/Documentation/Sections/Logical_Device/getLogicalDeviceHandle.svelte";
    import GetPhysicalDevice from "$components/Documentation/Sections/Logical_Device/getPhysicalDevice.svelte";
    import WaitIdle from "$components/Documentation/Sections/Logical_Device/waitIdle.svelte";
    import GetGraphicsQueue from "$components/Documentation/Sections/Logical_Device/getGraphicsQueue.svelte";
    import GetComputeQueue from "$components/Documentation/Sections/Logical_Device/getComputeQueue.svelte";
    import GetPresentQueue from "$components/Documentation/Sections/Logical_Device/getPresentQueue.svelte";
    import BeginSingleTimeCommandRecording from "$components/Documentation/Sections/Logical_Device/beginSingleTimeCommandRecording.svelte";
    import EndSingleTimeCommandRecording from "$components/Documentation/Sections/Logical_Device/endSingleTimeCommandRecording.svelte";
    import Queue from "$components/Documentation/Sections/Queue/Queue.svelte";
    import QueueConstructor from "$components/Documentation/Sections/Queue/QueueConstructor.svelte";
    import GetQueueHandle from "$components/Documentation/Sections/Queue/getQueueHandle.svelte";
    import CreateRecording from "$components/Documentation/Sections/Queue/createRecording.svelte";
    import SubmitRecordings from "$components/Documentation/Sections/Queue/submitRecordings.svelte";
    import ResetRecording from "$components/Documentation/Sections/Queue/resetRecording.svelte";
    import FreeRecording from "$components/Documentation/Sections/Queue/freeRecording.svelte";
    import QueueWaitIdle from "$components/Documentation/Sections/Queue/QueueWaitIdle.svelte";
    import CommandPool from "$components/Documentation/Sections/Command_Pool/CommandPool.svelte";
    import CommandPoolConstructor from "$components/Documentation/Sections/Command_Pool/CommandPoolConstructor.svelte";
    import AllocateCommandBuffers from "$components/Documentation/Sections/Command_Pool/allocateCommandBuffers.svelte";
    import FreeCommandBuffers from "$components/Documentation/Sections/Command_Pool/freeCommandBuffers.svelte";
    import CommandPoolReset from "$components/Documentation/Sections/Command_Pool/CommandPoolReset.svelte";
    import GetCommandPoolHandle from "$components/Documentation/Sections/Command_Pool/getCommandPoolHandle.svelte";
    import GetCommandBufferHandle from "$components/Documentation/Sections/Command_Buffer/getCommandBufferHandle.svelte";
    import GetLevel from "$components/Documentation/Sections/Command_Buffer/getLevel.svelte";
    import CommandBufferBegin from "$components/Documentation/Sections/Command_Buffer/CommandBufferBegin.svelte";
    import CommandBufferEnd from "$components/Documentation/Sections/Command_Buffer/CommandBufferEnd.svelte";
    import CommandBufferReset from "$components/Documentation/Sections/Command_Buffer/CommandBufferReset.svelte";
    import CommandBuffer from "$components/Documentation/Sections/Command_Buffer/CommandBuffer.svelte";
    import CreateCommandPool from "$components/Documentation/Sections/Queue/createCommandPool.svelte";
    import GetCommandPool from "$components/Documentation/Sections/Queue/getCommandPool.svelte";
    import DestroyCommandPool from "$components/Documentation/Sections/Queue/destroyCommandPool.svelte";
    import CommandBufferConstructor from "$components/Documentation/Sections/Command_Buffer/CommandBufferConstructor.svelte";
    import GetCommandPools from "$components/Documentation/Sections/Queue/getCommandPools.svelte";
    import CommandRecording from "$components/Documentation/Sections/Command_Recording/CommandRecording.svelte";
    import CommandRecordingEndAll from "$components/Documentation/Sections/Command_Recording/CommandRecordingEndAll.svelte";
    import CommandRecordingSubmit from "$components/Documentation/Sections/Command_Recording/CommandRecordingSubmit.svelte";
    import CommandRecordingReset from "$components/Documentation/Sections/Command_Recording/CommandRecordingReset.svelte";
    import CommandRecordingFree from "$components/Documentation/Sections/Command_Recording/CommandRecordingFree.svelte";
    import CommandRecordingCreateFence from "$components/Documentation/Sections/Command_Recording/CommandRecordingCreateFence.svelte";
    import CommandRecordingWaitForFence from "$components/Documentation/Sections/Command_Recording/CommandRecordingWaitForFence.svelte";
    import Swapchain from "$components/Documentation/Sections/Swapchain/Swapchain.svelte";
    import SwapchainConstructor from "$components/Documentation/Sections/Swapchain/SwapchainConstructor.svelte";
    import GetSwapchainHandle from "$components/Documentation/Sections/Swapchain/getSwapchainHandle.svelte";
    import SwapchaingetNextImage from "$components/Documentation/Sections/Swapchain/SwapchaingetNextImage.svelte";
    import SwapchainGetSurfaceFormat from "$components/Documentation/Sections/Swapchain/SwapchainGetSurfaceFormat.svelte";
    import SwapchainGetImageCount from "$components/Documentation/Sections/Swapchain/SwapchainGetImageCount.svelte";
    import SwapchainGetImageArrayLayers from "$components/Documentation/Sections/Swapchain/SwapchainGetImageArrayLayers.svelte";
    import SwapchainGetImageUsage from "$components/Documentation/Sections/Swapchain/SwapchainGetImageUsage.svelte";
    import SwapchainGetImageSharingMode from "$components/Documentation/Sections/Swapchain/SwapchainGetImageSharingMode.svelte";
    import SwapchainGetPresentMode from "$components/Documentation/Sections/Swapchain/SwapchainGetPresentMode.svelte";
    import SwapchainGetImageExtent from "$components/Documentation/Sections/Swapchain/SwapchainGetImageExtent.svelte";
    import SwapchainGetQueueFamilyIndices from "$components/Documentation/Sections/Swapchain/SwapchainGetQueueFamilyIndices.svelte";
    import SwapchainPresent from "$components/Documentation/Sections/Swapchain/SwapchainPresent.svelte";
    import SwapchainImage from "$components/Documentation/Sections/Swapchain/SwapchainImage.svelte";
    import Buffer from "$components/Documentation/Sections/Buffer/Buffer.svelte";
    import BufferConstructor from "$components/Documentation/Sections/Buffer/BufferConstructor.svelte";
    import GetBufferHandle from "$components/Documentation/Sections/Buffer/getBufferHandle.svelte";
    import BufferGetFlags from "$components/Documentation/Sections/Buffer/BufferGetFlags.svelte";
    import BufferGetSize from "$components/Documentation/Sections/Buffer/BufferGetSize.svelte";
    import BufferGetUsage from "$components/Documentation/Sections/Buffer/BufferGetUsage.svelte";
    import BufferGetSharingMode from "$components/Documentation/Sections/Buffer/BufferGetSharingMode.svelte";
    import BufferGetQueueFamilyIndices from "$components/Documentation/Sections/Buffer/BufferGetQueueFamilyIndices.svelte";
    import BufferBindMemory from "$components/Documentation/Sections/Buffer/BufferBindMemory.svelte";
    import BufferGetMemory from "$components/Documentation/Sections/Buffer/BufferGetMemory.svelte";
    import BufferCreateBufferView from "$components/Documentation/Sections/Buffer/BufferCreateBufferView.svelte";
    import BufferGetBufferView from "$components/Documentation/Sections/Buffer/BufferGetBufferView.svelte";
    import BufferGetBufferViews from "$components/Documentation/Sections/Buffer/BufferGetBufferViews.svelte";
    import BufferDestroyBufferView from "$components/Documentation/Sections/Buffer/BufferDestroyBufferView.svelte";
    import BufferDestroyBufferViews from "$components/Documentation/Sections/Buffer/BufferDestroyBufferViews.svelte";
    import BufferCopyTo from "$components/Documentation/Sections/Buffer/BufferCopyTo.svelte";
    import Image from "$components/Documentation/Sections/Image/Image.svelte";
    import ImageConstructor from "$components/Documentation/Sections/Image/ImageConstructor.svelte";
    import GetImageHandle from "$components/Documentation/Sections/Image/getImageHandle.svelte";
    import ImageGetFlags from "$components/Documentation/Sections/Image/ImageGetFlags.svelte";
    import ImageGetUsage from "$components/Documentation/Sections/Image/ImageGetUsage.svelte";
    import ImageGetSharingMode from "$components/Documentation/Sections/Image/ImageGetSharingMode.svelte";
    import ImageGetQueueFamilyIndices from "$components/Documentation/Sections/Image/ImageGetQueueFamilyIndices.svelte";
    import ImageBindMemory from "$components/Documentation/Sections/Image/ImageBindMemory.svelte";
    import ImageGetMemory from "$components/Documentation/Sections/Image/ImageGetMemory.svelte";
    import ImageCreateImageView from "$components/Documentation/Sections/Image/ImageCreateImageView.svelte";
    import ImageGetImageView from "$components/Documentation/Sections/Image/ImageGetImageView.svelte";
    import ImageDestroyImageViews from "$components/Documentation/Sections/Image/ImageDestroyImageViews.svelte";
    import ImageDestroyImageView from "$components/Documentation/Sections/Image/ImageDestroyImageView.svelte";
    import ImageCopyTo from "$components/Documentation/Sections/Image/ImageCopyTo.svelte";
    import ImageGetType from "$components/Documentation/Sections/Image/ImageGetType.svelte";
    import ImageGetFormat from "$components/Documentation/Sections/Image/ImageGetFormat.svelte";
    import ImageGetExtent from "$components/Documentation/Sections/Image/ImageGetExtent.svelte";
    import ImageGetMipLevels from "$components/Documentation/Sections/Image/ImageGetMipLevels.svelte";
    import ImageGetArrayLayers from "$components/Documentation/Sections/Image/ImageGetArrayLayers.svelte";
    import ImageGetSamples from "$components/Documentation/Sections/Image/ImageGetSamples.svelte";
    import ImageGetTiling from "$components/Documentation/Sections/Image/ImageGetTiling.svelte";
    import ImageGetInitialLayout from "$components/Documentation/Sections/Image/ImageGetInitialLayout.svelte";
    import ImageTransitionImageLayout from "$components/Documentation/Sections/Image/ImageTransitionImageLayout.svelte";
    import ImageGetImageViews from "$components/Documentation/Sections/Image/ImageGetImageViews.svelte";
    import GetQueueFamilyIndex from "$components/Documentation/Sections/Queue/getQueueFamilyIndex.svelte";
    import GetQueueIndex from "$components/Documentation/Sections/Queue/getQueueIndex.svelte";
    import GetBufferViewHandle from "$components/Documentation/Sections/Buffer_View/getBufferViewHandle.svelte";
    import BufferViewConstructor from "$components/Documentation/Sections/Buffer_View/BufferViewConstructor.svelte";
    import BufferView from "$components/Documentation/Sections/Buffer_View/BufferView.svelte";
    import ImageView from "$components/Documentation/Sections/Image_View/ImageView.svelte";
    import ImageViewConstructor from "$components/Documentation/Sections/Image_View/ImageViewConstructor.svelte";
    import GetImageViewHandle from "$components/Documentation/Sections/Image_View/getImageViewHandle.svelte";
    import Memory from "$components/Documentation/Sections/Memory/Memory.svelte";
    import MemoryConstructor from "$components/Documentation/Sections/Memory/MemoryConstructor.svelte";
    import GetMemoryHandle from "$components/Documentation/Sections/Memory/getMemoryHandle.svelte";
    import MemoryMap from "$components/Documentation/Sections/Memory/MemoryMap.svelte";
    import MemoryUnmap from "$components/Documentation/Sections/Memory/MemoryUnmap.svelte";
    import MemoryGetData from "$components/Documentation/Sections/Memory/MemoryGetData.svelte";
    import MemoryFlush from "$components/Documentation/Sections/Memory/MemoryFlush.svelte";
    import MemoryInvalidate from "$components/Documentation/Sections/Memory/MemoryInvalidate.svelte";
    import BufferDirector from "$components/Documentation/Sections/Buffer_Director/BufferDirector.svelte";
    import BufferDirectorConstructor from "$components/Documentation/Sections/Buffer_Director/BufferDirectorConstructor.svelte";
    import BufferDirectorMakeVertexBuffer from "$components/Documentation/Sections/Buffer_Director/BufferDirectorMakeVertexBuffer.svelte";
    import BufferDirectorMakeVertexTransferDestinationBuffer from "$components/Documentation/Sections/Buffer_Director/BufferDirectorMakeVertexTransferDestinationBuffer.svelte";
    import BufferDirectorMakeUniformBuffer from "$components/Documentation/Sections/Buffer_Director/BufferDirectorMakeUniformBuffer.svelte";
    import BufferDirectorMakeStorageBuffer from "$components/Documentation/Sections/Buffer_Director/BufferDirectorMakeStorageBuffer.svelte";
    import BufferDirectorMakeUniformTexelBuffer from "$components/Documentation/Sections/Buffer_Director/BufferDirectorMakeUniformTexelBuffer.svelte";
    import BufferDirectorMakeStorageTexelBuffer from "$components/Documentation/Sections/Buffer_Director/BufferDirectorMakeStorageTexelBuffer.svelte";
    import BufferDirectorMakeIndexBuffer from "$components/Documentation/Sections/Buffer_Director/BufferDirectorMakeIndexBuffer.svelte";
    import BufferDirectorMakeIndexTransferDestinationBuffer from "$components/Documentation/Sections/Buffer_Director/BufferDirectorMakeIndexTransferDestinationBuffer.svelte";
    import BufferDirectorMakeIndirectBuffer from "$components/Documentation/Sections/Buffer_Director/BufferDirectorMakeIndirectBuffer.svelte";
    import BufferDirectorMakeStagingBuffer from "$components/Documentation/Sections/Buffer_Director/BufferDirectorMakeStagingBuffer.svelte";
    import BufferBuilder from "$components/Documentation/Sections/Buffer_Builder/BufferBuilder.svelte";
    import BufferBuilderConstructor from "$components/Documentation/Sections/Buffer_Builder/BufferBuilderConstructor.svelte";
    import BufferBuilderSetLogicalDevice from "$components/Documentation/Sections/Buffer_Builder/BufferBuilderSetLogicalDevice.svelte";
    import BufferBuilderSetFlags from "$components/Documentation/Sections/Buffer_Builder/BufferBuilderSetFlags.svelte";
    import BufferBuilderSetSize from "$components/Documentation/Sections/Buffer_Builder/BufferBuilderSetSize.svelte";
    import BufferBuilderSetUsage from "$components/Documentation/Sections/Buffer_Builder/BufferBuilderSetUsage.svelte";
    import BufferBuilderSetSharingMode from "$components/Documentation/Sections/Buffer_Builder/BufferBuilderSetSharingMode.svelte";
    import BufferBuilderSetQueueFamilyIndices from "$components/Documentation/Sections/Buffer_Builder/BufferBuilderSetQueueFamilyIndices.svelte";
    import BufferBuilderReset from "$components/Documentation/Sections/Buffer_Builder/BufferBuilderReset.svelte";
    import BufferBuilderGetResult from "$components/Documentation/Sections/Buffer_Builder/BufferBuilderGetResult.svelte";
    import ImageDirectorConstructor from "$components/Documentation/Sections/Image_Director/ImageDirectorConstructor.svelte";
    import ImageDirector from "$components/Documentation/Sections/Image_Director/ImageDirector.svelte";
    import ImageDirectorMake2DTexture from "$components/Documentation/Sections/Image_Director/ImageDirectorMake2DTexture.svelte";
    import ImageDirectorMakeDepthImage from "$components/Documentation/Sections/Image_Director/ImageDirectorMakeDepthImage.svelte";
    import ImageBuilder from "$components/Documentation/Sections/Image_Builder/ImageBuilder.svelte";
    import ImageBuilderConstructor from "$components/Documentation/Sections/Image_Builder/ImageBuilderConstructor.svelte";
    import ImageBuilderSetLogicalDevice from "$components/Documentation/Sections/Image_Builder/ImageBuilderSetLogicalDevice.svelte";
    import ImageBuilderSetFlags from "$components/Documentation/Sections/Image_Builder/ImageBuilderSetFlags.svelte";
    import ImageBuilderSetImageType from "$components/Documentation/Sections/Image_Builder/ImageBuilderSetImageType.svelte";
    import ImageBuilderSetFormat from "$components/Documentation/Sections/Image_Builder/ImageBuilderSetFormat.svelte";
    import ImageBuilderSetExtent from "$components/Documentation/Sections/Image_Builder/ImageBuilderSetExtent.svelte";
    import ImageBuilderSetMipLevels from "$components/Documentation/Sections/Image_Builder/ImageBuilderSetMipLevels.svelte";
    import ImageBuilderSetArrayLayers from "$components/Documentation/Sections/Image_Builder/ImageBuilderSetArrayLayers.svelte";
    import ImageBuilderSetSamples from "$components/Documentation/Sections/Image_Builder/ImageBuilderSetSamples.svelte";
    import ImageBuilderSetImageTiling from "$components/Documentation/Sections/Image_Builder/ImageBuilderSetImageTiling.svelte";
    import ImageBuilderSetImageUsage from "$components/Documentation/Sections/Image_Builder/ImageBuilderSetImageUsage.svelte";
    import ImageBuilderSetSharingMode from "$components/Documentation/Sections/Image_Builder/ImageBuilderSetSharingMode.svelte";
    import ImageBuilderSetQueueFamilyIndices from "$components/Documentation/Sections/Image_Builder/ImageBuilderSetQueueFamilyIndices.svelte";
    import ImageBuilderSetInitialLayout from "$components/Documentation/Sections/Image_Builder/ImageBuilderSetInitialLayout.svelte";
    import ImageBuilderReset from "$components/Documentation/Sections/Image_Builder/ImageBuilderReset.svelte";
    import ImageBuilderGetResult from "$components/Documentation/Sections/Image_Builder/ImageBuilderGetResult.svelte";
    import Fence from "$components/Documentation/Sections/Fence/Fence.svelte";
    import FenceConstructor from "$components/Documentation/Sections/Fence/FenceConstructor.svelte";
    import GetFenceHandle from "$components/Documentation/Sections/Fence/getFenceHandle.svelte";
    import FenceWaitFor from "$components/Documentation/Sections/Fence/FenceWaitFor.svelte";
    import FenceSWaitForAll from "$components/Documentation/Sections/Fence/FenceS_WaitForAll.svelte";
    import FenceSResetAll from "$components/Documentation/Sections/Fence/FenceS_ResetAll.svelte";
    import FenceReset from "$components/Documentation/Sections/Fence/FenceReset.svelte";
    import Semaphore from "$components/Documentation/Sections/Semaphore/Semaphore.svelte";
    import SemaphoreConstructor from "$components/Documentation/Sections/Semaphore/SemaphoreConstructor.svelte";
    import GetSemaphoreHandle from "$components/Documentation/Sections/Semaphore/getSemaphoreHandle.svelte";
    import ShaderModule from "$components/Documentation/Sections/Shader_Module/ShaderModule.svelte";
    import ShaderModuleConstructor from "$components/Documentation/Sections/Shader_Module/ShaderModuleConstructor.svelte";
    import GetShaderModuleHandle from "$components/Documentation/Sections/Shader_Module/getShaderModuleHandle.svelte";
    import ShaderModuleGetDescriptorSetLayouts from "$components/Documentation/Sections/Shader_Module/ShaderModuleGetDescriptorSetLayouts.svelte";
    import ShaderModuleGetDescriptorPool from "$components/Documentation/Sections/Shader_Module/ShaderModuleGetDescriptorPool.svelte";
    import DescriptorSetLayout from "$components/Documentation/Sections/Descriptor_Set_Layout/DescriptorSetLayout.svelte";
    import DescriptorSetLayoutConstructor from "$components/Documentation/Sections/Descriptor_Set_Layout/DescriptorSetLayoutConstructor.svelte";
    import GetDescriptorSetLayoutHandle from "$components/Documentation/Sections/Descriptor_Set_Layout/getDescriptorSetLayoutHandle.svelte";
    import DescriptorSetLayoutGetBindings from "$components/Documentation/Sections/Descriptor_Set_Layout/DescriptorSetLayoutGetBindings.svelte";
    import DescriptorSetLayoutBuilder from "$components/Documentation/Sections/Descriptor_Set_Layout_Builder/DescriptorSetLayoutBuilder.svelte";
    import DescriptorSetLayoutBuilderConstructor from "$components/Documentation/Sections/Descriptor_Set_Layout_Builder/DescriptorSetLayoutBuilderConstructor.svelte";
    import DescriptorSetLayoutBuilderSetLogicalDevice from "$components/Documentation/Sections/Descriptor_Set_Layout_Builder/DescriptorSetLayoutBuilderSetLogicalDevice.svelte";
    import DescriptorSetLayoutBuilderAddBinding from "$components/Documentation/Sections/Descriptor_Set_Layout_Builder/DescriptorSetLayoutBuilderAddBinding.svelte";
    import DescriptorSetLayoutBuilderGetResult from "$components/Documentation/Sections/Descriptor_Set_Layout_Builder/DescriptorSetLayoutBuilderGetResult.svelte";
    import DescriptorSetLayoutBuilderReset from "$components/Documentation/Sections/Descriptor_Set_Layout_Builder/DescriptorSetLayoutBuilderReset.svelte";
    import DescriptorPool from "$components/Documentation/Sections/Descriptor_Pool/DescriptorPool.svelte";
    import DescriptorPoolConstructor from "$components/Documentation/Sections/Descriptor_Pool/DescriptorPoolConstructor.svelte";
    import GetDescriptorPoolHandle from "$components/Documentation/Sections/Descriptor_Pool/getDescriptorPoolHandle.svelte";
    import DescriptorPoolAllocateDescriptorSet from "$components/Documentation/Sections/Descriptor_Pool/DescriptorPoolAllocateDescriptorSet.svelte";
    import DescriptorPoolGetDescriptorSets from "$components/Documentation/Sections/Descriptor_Pool/DescriptorPoolGetDescriptorSets.svelte";
    import DescriptorPoolGetDescriptorSet from "$components/Documentation/Sections/Descriptor_Pool/DescriptorPoolGetDescriptorSet.svelte";
    import DescriptorPoolFreeDescriptorSets from "$components/Documentation/Sections/Descriptor_Pool/DescriptorPoolFreeDescriptorSets.svelte";
    import DescriptorPoolReset from "$components/Documentation/Sections/Descriptor_Pool/DescriptorPoolReset.svelte";
    import DescriptorPoolBuilder from "$components/Documentation/Sections/Descriptor_Pool_Builder/DescriptorPoolBuilder.svelte";
    import DescriptorPoolBuilderConstructor from "$components/Documentation/Sections/Descriptor_Pool_Builder/DescriptorPoolBuilderConstructor.svelte";
    import DescriptorPoolBuilderSetLogicalDevice from "$components/Documentation/Sections/Descriptor_Pool_Builder/DescriptorPoolBuilderSetLogicalDevice.svelte";
    import DescriptorPoolBuilderSetFlags from "$components/Documentation/Sections/Descriptor_Pool_Builder/DescriptorPoolBuilderSetFlags.svelte";
    import DescriptorPoolBuilderAddSet from "$components/Documentation/Sections/Descriptor_Pool_Builder/DescriptorPoolBuilderAddSet.svelte";
    import DescriptorPoolBuilderGetResult from "$components/Documentation/Sections/Descriptor_Pool_Builder/DescriptorPoolBuilderGetResult.svelte";
    import DescriptorPoolBuilderReset from "$components/Documentation/Sections/Descriptor_Pool_Builder/DescriptorPoolBuilderReset.svelte";
    import DescriptorSet from "$components/Documentation/Sections/Descriptor_Set/DescriptorSet.svelte";
    import DescriptorSetConstructor from "$components/Documentation/Sections/Descriptor_Set/DescriptorSetConstructor.svelte";
    import GetDescriptorSetHandle from "$components/Documentation/Sections/Descriptor_Set/getDescriptorSetHandle.svelte";
    import DescriptorSetGetLayout from "$components/Documentation/Sections/Descriptor_Set/DescriptorSetGetLayout.svelte";
    import DescriptorSetGetName from "$components/Documentation/Sections/Descriptor_Set/DescriptorSetGetName.svelte";
    import DescriptorSetWriteImage from "$components/Documentation/Sections/Descriptor_Set/DescriptorSetWriteImage.svelte";
    import DescriptorSetWriteBuffer from "$components/Documentation/Sections/Descriptor_Set/DescriptorSetWriteBuffer.svelte";
    import DescriptorSetWriteTexelBufferView from "$components/Documentation/Sections/Descriptor_Set/DescriptorSetWriteTexelBufferView.svelte";
    import DescriptorSetCopy from "$components/Documentation/Sections/Descriptor_Set/DescriptorSetCopy.svelte";
    import PipelineLayout from "$components/Documentation/Sections/Pipeline_Layout/PipelineLayout.svelte";
    import PipelineLayoutConstructor from "$components/Documentation/Sections/Pipeline_Layout/PipelineLayoutConstructor.svelte";
    import GetPipelineLayoutHandle from "$components/Documentation/Sections/Pipeline_Layout/getPipelineLayoutHandle.svelte";
    import PipelineLayoutPushConstantData from "$components/Documentation/Sections/Pipeline_Layout/PipelineLayoutPushConstantData.svelte";
    import PushConstant from "$components/Documentation/Sections/Pipeline_Layout/PushConstant.svelte";
    import Pipeline from "$components/Documentation/Sections/Pipeline/Pipeline.svelte";
    import PipelineConstructor from "$components/Documentation/Sections/Pipeline/PipelineConstructor.svelte";
    import GetPipelineHandle from "$components/Documentation/Sections/Pipeline/getPipelineHandle.svelte";
    import PipelineGetPipelineLayout from "$components/Documentation/Sections/Pipeline/PipelineGetPipelineLayout.svelte";
    import PipelineBindToCommandBuffer from "$components/Documentation/Sections/Pipeline/PipelineBindToCommandBuffer.svelte";
    import PipelineGetCommandBuffer from "$components/Documentation/Sections/Pipeline/PipelineGetCommandBuffer.svelte";
    import PipelineBindDescriptorSets from "$components/Documentation/Sections/Pipeline/PipelineBindDescriptorSets.svelte";
    import PipelineGetDescriptorSets from "$components/Documentation/Sections/Pipeline/PipelineGetDescriptorSets.svelte";
    import PipelineGetDescriptorSet from "$components/Documentation/Sections/Pipeline/PipelineGetDescriptorSet.svelte";
    import PipelineShaderStage from "$components/Documentation/Sections/Pipeline/PipelineShaderStage.svelte";
    import PipelinePushConstantData from "$components/Documentation/Sections/Pipeline/PipelinePushConstantData.svelte";
    import PipelineBuilder from "$components/Documentation/Sections/Pipeline_Builder/PipelineBuilder.svelte";
    import PipelineBuilderConstructor from "$components/Documentation/Sections/Pipeline_Builder/PipelineBuilderConstructor.svelte";
    import PipelineBuilderSetLogicalDevice from "$components/Documentation/Sections/Pipeline_Builder/PipelineBuilderSetLogicalDevice.svelte";
    import PipelineBuilderSetFlags from "$components/Documentation/Sections/Pipeline_Builder/PipelineBuilderSetFlags.svelte";
    import PipelineBuilderAddPushConstant from "$components/Documentation/Sections/Pipeline_Builder/PipelineBuilderAddPushConstant.svelte";
    import PipelineBuilderSetPipelineCache from "$components/Documentation/Sections/Pipeline_Builder/PipelineBuilderSetPipelineCache.svelte";
    import PipelineBuilderReset from "$components/Documentation/Sections/Pipeline_Builder/PipelineBuilderReset.svelte";
    import PipelineBuilderSetBasePipeline from "$components/Documentation/Sections/Pipeline_Builder/PipelineBuilderSetBasePipeline.svelte";
    import ComputePipeline from "$components/Documentation/Sections/Compute_Pipeline/ComputePipeline.svelte";
    import ComputePipelineConstructor from "$components/Documentation/Sections/Compute_Pipeline/ComputePipelineConstructor.svelte";
    import ComputePipelineBuilder from "$components/Documentation/Sections/Compute_Pipeline_Builder/ComputePipelineBuilder.svelte";
    import ComputePipelineBuilderConstructor from "$components/Documentation/Sections/Compute_Pipeline_Builder/ComputePipelineBuilderConstructor.svelte";
    import ComputePipelineBuilderSetShaderStage from "$components/Documentation/Sections/Compute_Pipeline_Builder/ComputePipelineBuilderSetShaderStage.svelte";
    import ComputePipelineBuilderGetResult from "$components/Documentation/Sections/Compute_Pipeline_Builder/ComputePipelineBuilderGetResult.svelte";
    import ComputePipelineBuilderReset from "$components/Documentation/Sections/Compute_Pipeline_Builder/ComputePipelineBuilderReset.svelte";
    import RenderPass from "$components/Documentation/Sections/Render_Pass/RenderPass.svelte";
    import RenderPassConstructor from "$components/Documentation/Sections/Render_Pass/RenderPassConstructor.svelte";
    import GetRenderPassHandle from "$components/Documentation/Sections/Render_Pass/getRenderPassHandle.svelte";
    import RenderPassGetAttachments from "$components/Documentation/Sections/Render_Pass/RenderPassGetAttachments.svelte";
    import RenderPassGetSubpasses from "$components/Documentation/Sections/Render_Pass/RenderPassGetSubpasses.svelte";
    import RenderPassGetDependencies from "$components/Documentation/Sections/Render_Pass/RenderPassGetDependencies.svelte";
    import RenderPassBegin from "$components/Documentation/Sections/Render_Pass/RenderPassBegin.svelte";
    import RenderPassEnd from "$components/Documentation/Sections/Render_Pass/RenderPassEnd.svelte";
    import RenderPassBuilder from "$components/Documentation/Sections/Render_Pass_Builder/RenderPassBuilder.svelte";
    import RenderPassBuilderConstructor from "$components/Documentation/Sections/Render_Pass_Builder/RenderPassBuilderConstructor.svelte";
    import RenderPassBuilderSetLogicalDevice from "$components/Documentation/Sections/Render_Pass_Builder/RenderPassBuilderSetLogicalDevice.svelte";
    import RenderPassBuilderAddAttachment from "$components/Documentation/Sections/Render_Pass_Builder/RenderPassBuilderAddAttachment.svelte";
    import RenderPassBuilderAddInputAttachment from "$components/Documentation/Sections/Render_Pass_Builder/RenderPassBuilderAddInputAttachment.svelte";
    import RenderPassBuilderAddColorAttachment from "$components/Documentation/Sections/Render_Pass_Builder/RenderPassBuilderAddColorAttachment.svelte";
    import RenderPassBuilderSetDepthStencilAttachment from "$components/Documentation/Sections/Render_Pass_Builder/RenderPassBuilderSetDepthStencilAttachment.svelte";
    import RenderPassBuilderResolveCurrentAttachments from "$components/Documentation/Sections/Render_Pass_Builder/RenderPassBuilderResolveCurrentAttachments.svelte";
    import RenderPassBuilderConstructSubpass from "$components/Documentation/Sections/Render_Pass_Builder/RenderPassBuilderConstructSubpass.svelte";
    import RenderPassBuilderAddDependency from "$components/Documentation/Sections/Render_Pass_Builder/RenderPassBuilderAddDependency.svelte";
    import RenderPassBuilderGetResult from "$components/Documentation/Sections/Render_Pass_Builder/RenderPassBuilderGetResult.svelte";
    import RenderPassBuilderReset from "$components/Documentation/Sections/Render_Pass_Builder/RenderPassBuilderReset.svelte";
    import Framebuffer from "$components/Documentation/Sections/Framebuffer/Framebuffer.svelte";
    import FramebufferConstructor from "$components/Documentation/Sections/Framebuffer/FramebufferConstructor.svelte";
    import GetFramebufferHandle from "$components/Documentation/Sections/Framebuffer/getFramebufferHandle.svelte";
    import FramebufferGetExtent from "$components/Documentation/Sections/Framebuffer/FramebufferGetExtent.svelte";
    import FramebufferGetLayers from "$components/Documentation/Sections/Framebuffer/FramebufferGetLayers.svelte";
    import Sampler from "$components/Documentation/Sections/Sampler/Sampler.svelte";
    import SamplerConstructor from "$components/Documentation/Sections/Sampler/SamplerConstructor.svelte";
    import GetSamplerHandle from "$components/Documentation/Sections/Sampler/getSamplerHandle.svelte";
    import SamplerBuilder from "$components/Documentation/Sections/Sampler_Builder/SamplerBuilder.svelte";
    import SamplerBuilderConstructor from "$components/Documentation/Sections/Sampler_Builder/SamplerBuilderConstructor.svelte";
    import SamplerBuilderSetLogicalDevice from "$components/Documentation/Sections/Sampler_Builder/SamplerBuilderSetLogicalDevice.svelte";
    import SamplerBuilderSetFilters from "$components/Documentation/Sections/Sampler_Builder/SamplerBuilderSetFilters.svelte";
    import SamplerBuilderSetMipmapMode from "$components/Documentation/Sections/Sampler_Builder/SamplerBuilderSetMipmapMode.svelte";
    import SamplerBuilderSetAddressModes from "$components/Documentation/Sections/Sampler_Builder/SamplerBuilderSetAddressModes.svelte";
    import SamplerBuilderSetMipLodBias from "$components/Documentation/Sections/Sampler_Builder/SamplerBuilderSetMipLodBias.svelte";
    import SamplerBuilderSetMaxAnisotropy from "$components/Documentation/Sections/Sampler_Builder/SamplerBuilderSetMaxAnisotropy.svelte";
    import SamplerBuilderUnsetMaxAnisotropy from "$components/Documentation/Sections/Sampler_Builder/SamplerBuilderUnsetMaxAnisotropy.svelte";
    import SamplerBuilderSetCompareOp from "$components/Documentation/Sections/Sampler_Builder/SamplerBuilderSetCompareOp.svelte";
    import SamplerBuilderUnsetCompareOp from "$components/Documentation/Sections/Sampler_Builder/SamplerBuilderUnsetCompareOp.svelte";
    import SamplerBuilderSetLod from "$components/Documentation/Sections/Sampler_Builder/SamplerBuilderSetLod.svelte";
    import SamplerBuilderSetBorderColor from "$components/Documentation/Sections/Sampler_Builder/SamplerBuilderSetBorderColor.svelte";
    import SamplerBuilderEnableUnnormalizedCoordinates from "$components/Documentation/Sections/Sampler_Builder/SamplerBuilderEnableUnnormalizedCoordinates.svelte";
    import SamplerBuilderDisableUnnormalizedCoordinates from "$components/Documentation/Sections/Sampler_Builder/SamplerBuilderDisableUnnormalizedCoordinates.svelte";
    import SamplerBuilderGetResult from "$components/Documentation/Sections/Sampler_Builder/SamplerBuilderGetResult.svelte";
    import SamplerBuilderReset from "$components/Documentation/Sections/Sampler_Builder/SamplerBuilderReset.svelte";
    import GraphicsPipeline from "$components/Documentation/Sections/Graphics_Pipeline/GraphicsPipeline.svelte";
    import GraphicsPipelineConstructor from "$components/Documentation/Sections/Graphics_Pipeline/GraphicsPipelineConstructor.svelte";
    import GraphicsPipelineGetRenderPass from "$components/Documentation/Sections/Graphics_Pipeline/GraphicsPipelineGetRenderPass.svelte";
    import GraphicsPipelineBuilder from "$components/Documentation/Sections/Graphics_Pipeline_Builder/GraphicsPipelineBuilder.svelte";
    import GraphicsPipelineBuilderConstructor from "$components/Documentation/Sections/Graphics_Pipeline_Builder/GraphicsPipelineBuilderConstructor.svelte";
    import GraphicsPipelineBuilderAddShaderStage from "$components/Documentation/Sections/Graphics_Pipeline_Builder/GraphicsPipelineBuilderAddShaderStage.svelte";
    import GraphicsPipelineBuilderSetInputAssemblyState from "$components/Documentation/Sections/Graphics_Pipeline_Builder/GraphicsPipelineBuilderSetInputAssemblyState.svelte";
    import GraphicsPipelineBuilderSetVertexInputState from "$components/Documentation/Sections/Graphics_Pipeline_Builder/GraphicsPipelineBuilderSetVertexInputState.svelte";
    import GraphicsPipelineBuilderSetTessellationState from "$components/Documentation/Sections/Graphics_Pipeline_Builder/GraphicsPipelineBuilderSetTessellationState.svelte";
    import GraphicsPipelineBuilderAddViewportState from "$components/Documentation/Sections/Graphics_Pipeline_Builder/GraphicsPipelineBuilderAddViewportState.svelte";
    import GraphicsPipelineBuilderSetRasterizationState from "$components/Documentation/Sections/Graphics_Pipeline_Builder/GraphicsPipelineBuilderSetRasterizationState.svelte";
    import GraphicsPipelineBuilderSetMultisampleState from "$components/Documentation/Sections/Graphics_Pipeline_Builder/GraphicsPipelineBuilderSetMultisampleState.svelte";
    import GraphicsPipelineBuilderSetDepthStencilState from "$components/Documentation/Sections/Graphics_Pipeline_Builder/GraphicsPipelineBuilderSetDepthStencilState.svelte";
    import GraphicsPipelineBuilderSetColorBlendState from "$components/Documentation/Sections/Graphics_Pipeline_Builder/GraphicsPipelineBuilderSetColorBlendState.svelte";
    import GraphicsPipelineBuilderSetDynamicState from "$components/Documentation/Sections/Graphics_Pipeline_Builder/GraphicsPipelineBuilderSetDynamicState.svelte";
    import GraphicsPipelineBuilderSetRenderPass from "$components/Documentation/Sections/Graphics_Pipeline_Builder/GraphicsPipelineBuilderSetRenderPass.svelte";
    import GraphicsPipelineBuilderSetSubpass from "$components/Documentation/Sections/Graphics_Pipeline_Builder/GraphicsPipelineBuilderSetSubpass.svelte";
    import GraphicsPipelineBuilderGetResult from "$components/Documentation/Sections/Graphics_Pipeline_Builder/GraphicsPipelineBuilderGetResult.svelte";
    import GraphicsPipelineBuilderReset from "$components/Documentation/Sections/Graphics_Pipeline_Builder/GraphicsPipelineBuilderReset.svelte";

    const sections: Array<SectionObject> = [
        // GETTING STARTED
        {
            id: SectionID.GETTING_STARTED,
            label: "Getting Started",
            heading: 2,
            content: GettingStarted,
            props: {},
            visible: false,
        },
        {
            id: SectionID.CMAKE,
            label: "CMake",
            heading: 3,
            content: CMake,
            props: {},
            visible: false,
        },

        // FILLCAN
        {
            id: SectionID.FILLCAN,
            label: "Fillcan",
            heading: 2,
            content: Fillcan,
            props: {},
            visible: false,
        },
        {
            id: SectionID.FILLCAN_Constructor,
            label: "Constructor",
            heading: 3,
            content: FillcanConstructor,
            props: {},
            visible: false,
        },
        {
            id: SectionID.FILLCAN_getSupportedPhysicalDevices,
            label: "getSupportedPhysicalDevices",
            heading: 3,
            content: GetSupportedPhysicalDevices,
            props: {},
            visible: false,
        },
        {
            id: SectionID.FILLCAN_selectDevice,
            label: "selectDevice",
            heading: 3,
            content: SelectDevice,
            props: {},
            visible: false,
        },
        {
            id: SectionID.FILLCAN_getCurrentDevice,
            label: "getCurrentDevice",
            heading: 3,
            content: GetCurrentDevice,
            props: {},
            visible: false,
        },
        {
            id: SectionID.FILLCAN_createShaderModule,
            label: "createShaderModule",
            heading: 3,
            content: CreateShaderModule,
            props: {},
            visible: false,
        },

        // FILLCAN GRAPHICS
        {
            id: SectionID.FILLCAN_GRAPHICS,
            label: "Fillcan Graphics",
            heading: 2,
            content: FillcanGraphics,
            props: {},
            visible: false,
        },
        {
            id: SectionID.FILLCAN_GRAPHICS_Constructor,
            label: "Constructor",
            heading: 3,
            content: FillcanGraphicsConstructor,
            props: {},
            visible: false,
        },
        {
            id: SectionID.FILLCAN_GRAPHICS_getWindow,
            label: "getWindow",
            heading: 3,
            content: GetWindow,
            props: {},
            visible: false,
        },
        {
            id: SectionID.FILLCAN_GRAPHICS_mainLoop,
            label: "mainLoop",
            heading: 3,
            content: MainLoop,
            props: {},
            visible: false,
        },
        {
            id: SectionID.FILLCAN_GRAPHICS_createSwapchain,
            label: "createSwapchain",
            heading: 3,
            content: CreateSwapchain,
            props: {},
            visible: false,
        },
        {
            id: SectionID.FILLCAN_GRAPHICS_recreateSwapchain,
            label: "recreateSwapchain",
            heading: 3,
            content: RecreateSwapchain,
            props: {},
            visible: false,
        },
        {
            id: SectionID.FILLCAN_GRAPHICS_getSwapchain,
            label: "getSwapchain",
            heading: 3,
            content: GetSwapchain,
            props: {},
            visible: false,
        },
        {
            id: SectionID.FILLCAN_GRAPHICS_getSwapchains,
            label: "getSwapchains",
            heading: 3,
            content: GetSwapchains,
            props: {},
            visible: false,
        },
        {
            id: SectionID.FILLCAN_GRAPHICS_destroySwapchain,
            label: "destroySwapchain",
            heading: 3,
            content: DestroySwapchain,
            props: {},
            visible: false,
        },
        {
            id: SectionID.FILLCAN_GRAPHICS_getAssetManager,
            label: "getAssetManager",
            heading: 3,
            content: GetAssetManager,
            props: {},
            visible: false,
        },

        // WINDOW
        {
            id: SectionID.WINDOW,
            label: "Window",
            heading: 2,
            content: Window,
            props: {},
            visible: false,
        },
        {
            id: SectionID.WINDOW_Constructor,
            label: "Constructor",
            heading: 3,
            content: WindowConstructor,
            props: {},
            visible: false,
        },
        {
            id: SectionID.WINDOW_shouldClose,
            label: "shouldClose",
            heading: 3,
            content: ShouldClose,
            props: {},
            visible: false,
        },
        {
            id: SectionID.WINDOW_wasResized,
            label: "wasResized",
            heading: 3,
            content: WasResized,
            props: {},
            visible: false,
        },
        {
            id: SectionID.WINDOW_pollEvents,
            label: "pollEvents",
            heading: 3,
            content: PollEvents,
            props: {},
            visible: false,
        },
        {
            id: SectionID.WINDOW_getRequiredExtensions,
            label: "getRequiredExtensions",
            heading: 3,
            content: WindowGetRequiredExtensions,
            props: {},
            visible: false,
        },
        {
            id: SectionID.WINDOW_createSurface,
            label: "createSurface",
            heading: 3,
            content: CreateSurface,
            props: {},
            visible: false,
        },
        {
            id: SectionID.WINDOW_getSurface,
            label: "getSurface",
            heading: 3,
            content: GetSurface,
            props: {},
            visible: false,
        },
        {
            id: SectionID.WINDOW_getExtent,
            label: "getExtent",
            heading: 3,
            content: GetExtent,
            props: {},
            visible: false,
        },

        // INSTANCE
        {
            id: SectionID.INSTANCE,
            label: "Instance",
            heading: 2,
            content: Instance,
            props: {},
            visible: false,
        },
        {
            id: SectionID.INSTANCE_Constructor,
            label: "Constructor",
            heading: 3,
            content: InstanceConstructor,
            props: {},
            visible: false,
        },
        {
            id: SectionID.INSTANCE_getInstanceHandle,
            label: "getInstanceHandle",
            heading: 3,
            content: GetInstanceHandle,
            props: {},
            visible: false,
        },

        // DEVICE POOL
        {
            id: SectionID.DEVICE_POOL,
            label: "Device Pool",
            heading: 2,
            content: DevicePool,
            props: {},
            visible: false,
        },
        {
            id: SectionID.DEVICE_POOL_Constructor,
            label: "Constructor",
            heading: 3,
            content: DevicePoolConstructor,
            props: {},
            visible: false,
        },
        {
            id: SectionID.DEVICE_POOL_getSupportedPhysicalDevices,
            label: "getSupportedPhysicalDevices",
            heading: 3,
            content: DevicePoolgetSupportedPhysicalDevices,
            props: {},
            visible: false,
        },
        {
            id: SectionID.DEVICE_POOL_selectDevice,
            label: "selectDevice",
            heading: 3,
            content: DevicePoolselectDevice,
            props: {},
            visible: false,
        },
        {
            id: SectionID.DEVICE_POOL_getCurrentDevice,
            label: "getCurrentDevice",
            heading: 3,
            content: DevicePoolgetCurrentDevice,
            props: {},
            visible: false,
        },

        // PHYSICAL DEVICE
        {
            id: SectionID.PHYSICAL_DEVICE,
            label: "Physical Device",
            heading: 2,
            content: PhysicalDevice,
            props: {},
            visible: false,
        },
        {
            id: SectionID.PHYSICAL_DEVICE_Constructor,
            label: "Constructor",
            heading: 3,
            content: PhysicalDeviceConstructor,
            props: {},
            visible: false,
        },
        {
            id: SectionID.PHYSICAL_DEVICE_getPhysicalDeviceHandle,
            label: "getPhysicalDeviceHandle",
            heading: 3,
            content: GetPhysicalDeviceHandle,
            props: {},
            visible: false,
        },
        {
            id: SectionID.PHYSICAL_DEVICE_getRequiredExtensions,
            label: "getRequiredExtensions",
            heading: 3,
            content: GetRequiredExtensions,
            props: {},
            visible: false,
        },
        {
            id: SectionID.PHYSICAL_DEVICE_areExtensionsSupported,
            label: "areExtensionsSupported",
            heading: 3,
            content: AreExtensionsSupported,
            props: {},
            visible: false,
        },
        {
            id: SectionID.PHYSICAL_DEVICE_getRequiredFeatures,
            label: "getRequiredFeatures",
            heading: 3,
            content: GetRequiredFeatures,
            props: {},
            visible: false,
        },
        {
            id: SectionID.PHYSICAL_DEVICE_areFeaturesSupported,
            label: "areFeaturesSupported",
            heading: 3,
            content: AreFeaturesSupported,
            props: {},
            visible: false,
        },
        {
            id: SectionID.PHYSICAL_DEVICE_getFeatures,
            label: "getFeatures",
            heading: 3,
            content: GetFeatures,
            props: {},
            visible: false,
        },
        {
            id: SectionID.PHYSICAL_DEVICE_getProperties,
            label: "getProperties",
            heading: 3,
            content: GetProperties,
            props: {},
            visible: false,
        },
        {
            id: SectionID.PHYSICAL_DEVICE_getSurfaceCapabilitiesKHR,
            label: "getSurfaceCapabilitiesKHR",
            heading: 3,
            content: GetSurfaceCapabilitiesKhr,
            props: {},
            visible: false,
        },
        {
            id: SectionID.PHYSICAL_DEVICE_getSurfaceFormatsKHR,
            label: "getSurfaceFormatsKHR",
            heading: 3,
            content: GetSurfaceFormatsKhr,
            props: {},
            visible: false,
        },
        {
            id: SectionID.PHYSICAL_DEVICE_getSurfacePresentModesKHR,
            label: "getSurfacePresentModesKHR",
            heading: 3,
            content: GetSurfacePresentModesKhr,
            props: {},
            visible: false,
        },
        {
            id: SectionID.PHYSICAL_DEVICE_getQueueFamilyProperties,
            label: "getQueueFamilyProperties",
            heading: 3,
            content: GetQueueFamilyProperties,
            props: {},
            visible: false,
        },
        {
            id: SectionID.PHYSICAL_DEVICE_getFormatProperties,
            label: "getFormatProperties",
            heading: 3,
            content: GetFormatProperties,
            props: {},
            visible: false,
        },
        {
            id: SectionID.PHYSICAL_DEVICE_findSupportedFormat,
            label: "findSupportedFormat",
            heading: 3,
            content: FindSupportedFormat,
            props: {},
            visible: false,
        },
        {
            id: SectionID.PHYSICAL_DEVICE_getGraphicsQueueFamilyIndices,
            label: "getGraphicsQueueFamilyIndices",
            heading: 3,
            content: GetGraphicsQueueFamilyIndices,
            props: {},
            visible: false,
        },
        {
            id: SectionID.PHYSICAL_DEVICE_getPresentQueueFamilyIndices,
            label: "getPresentQueueFamilyIndices",
            heading: 3,
            content: GetPresentQueueFamilyIndices,
            props: {},
            visible: false,
        },
        {
            id: SectionID.PHYSICAL_DEVICE_getComputeQueueFamilyIndices,
            label: "getComputeQueueFamilyIndices",
            heading: 3,
            content: GetComputeQueueFamilyIndices,
            props: {},
            visible: false,
        },

        // LOGICAL DEVICE
        {
            id: SectionID.LOGICAL_DEVICE,
            label: "Logical Device",
            heading: 2,
            content: LogicalDevice,
            props: {},
            visible: false,
        },
        {
            id: SectionID.LOGICAL_DEVICE_Constructor,
            label: "Constructor",
            heading: 3,
            content: LogicalDeviceConstructor,
            props: {},
            visible: false,
        },
        {
            id: SectionID.LOGICAL_DEVICE_getLogicalDeviceHandle,
            label: "getLogicalDeviceHandle",
            heading: 3,
            content: GetLogicalDeviceHandle,
            props: {},
            visible: false,
        },
        {
            id: SectionID.LOGICAL_DEVICE_getPhysicalDevice,
            label: "getPhysicalDevice",
            heading: 3,
            content: GetPhysicalDevice,
            props: {},
            visible: false,
        },
        {
            id: SectionID.LOGICAL_DEVICE_waitIdle,
            label: "waitIdle",
            heading: 3,
            content: WaitIdle,
            props: {},
            visible: false,
        },
        {
            id: SectionID.LOGICAL_DEVICE_getGraphicsQueue,
            label: "getGraphicsQueue",
            heading: 3,
            content: GetGraphicsQueue,
            props: {},
            visible: false,
        },
        {
            id: SectionID.LOGICAL_DEVICE_getPresentQueue,
            label: "getPresentQueue",
            heading: 3,
            content: GetPresentQueue,
            props: {},
            visible: false,
        },
        {
            id: SectionID.LOGICAL_DEVICE_getComputeQueue,
            label: "getComputeQueue",
            heading: 3,
            content: GetComputeQueue,
            props: {},
            visible: false,
        },
        {
            id: SectionID.LOGICAL_DEVICE_beginSingleTimeCommandRecording,
            label: "beginSingleTimeCommandRecording",
            heading: 3,
            content: BeginSingleTimeCommandRecording,
            props: {},
            visible: false,
        },
        {
            id: SectionID.LOGICAL_DEVICE_endSingleTimeCommandRecording,
            label: "endSingleTimeCommandRecording",
            heading: 3,
            content: EndSingleTimeCommandRecording,
            props: {},
            visible: false,
        },

        // QUEUE
        {
            id: SectionID.QUEUE,
            label: "Queue",
            heading: 2,
            content: Queue,
            props: {},
            visible: false,
        },
        {
            id: SectionID.QUEUE_Constructor,
            label: "Constructor",
            heading: 3,
            content: QueueConstructor,
            props: {},
            visible: false,
        },
        {
            id: SectionID.QUEUE_getQueueHandle,
            label: "getQueueHandle",
            heading: 3,
            content: GetQueueHandle,
            props: {},
            visible: false,
        },
        {
            id: SectionID.QUEUE_getQueueFamilyIndex,
            label: "getQueueFamilyIndex",
            heading: 3,
            content: GetQueueFamilyIndex,
            props: {},
            visible: false,
        },
        {
            id: SectionID.QUEUE_getQueueIndex,
            label: "getQueueIndex",
            heading: 3,
            content: GetQueueIndex,
            props: {},
            visible: false,
        },
        {
            id: SectionID.QUEUE_createCommandPool,
            label: "createCommandPool",
            heading: 3,
            content: CreateCommandPool,
            props: {},
            visible: false,
        },
        {
            id: SectionID.QUEUE_getCommandPools,
            label: "getCommandPools",
            heading: 3,
            content: GetCommandPools,
            props: {},
            visible: false,
        },
        {
            id: SectionID.QUEUE_getCommandPool,
            label: "getCommandPool",
            heading: 3,
            content: GetCommandPool,
            props: {},
            visible: false,
        },
        {
            id: SectionID.QUEUE_destroyCommandPool,
            label: "destroyCommandPool",
            heading: 3,
            content: DestroyCommandPool,
            props: {},
            visible: false,
        },
        {
            id: SectionID.QUEUE_createRecording,
            label: "createRecording",
            heading: 3,
            content: CreateRecording,
            props: {},
            visible: false,
        },
        {
            id: SectionID.QUEUE_submitRecordings,
            label: "submitRecordings",
            heading: 3,
            content: SubmitRecordings,
            props: {},
            visible: false,
        },
        {
            id: SectionID.QUEUE_resetRecording,
            label: "resetRecording",
            heading: 3,
            content: ResetRecording,
            props: {},
            visible: false,
        },
        {
            id: SectionID.QUEUE_freeRecording,
            label: "freeRecording",
            heading: 3,
            content: FreeRecording,
            props: {},
            visible: false,
        },
        {
            id: SectionID.QUEUE_waitIdle,
            label: "waitIdle",
            heading: 3,
            content: QueueWaitIdle,
            props: {},
            visible: false,
        },

        // COMMAND POOL
        {
            id: SectionID.COMMAND_POOL,
            label: "Command Pool",
            heading: 2,
            content: CommandPool,
            props: {},
            visible: false,
        },
        {
            id: SectionID.COMMAND_POOL_Constructor,
            label: "Constructor",
            heading: 3,
            content: CommandPoolConstructor,
            props: {},
            visible: false,
        },
        {
            id: SectionID.COMMAND_POOL_getCommandPoolHandle,
            label: "getCommandPoolHandle",
            heading: 3,
            content: GetCommandPoolHandle,
            props: {},
            visible: false,
        },
        {
            id: SectionID.COMMAND_POOL_allocateCommandBuffers,
            label: "allocateCommandBuffers",
            heading: 3,
            content: AllocateCommandBuffers,
            props: {},
            visible: false,
        },
        {
            id: SectionID.COMMAND_POOL_freeCommandBuffers,
            label: "freeCommandBuffers",
            heading: 3,
            content: FreeCommandBuffers,
            props: {},
            visible: false,
        },
        {
            id: SectionID.COMMAND_POOL_reset,
            label: "reset",
            heading: 3,
            content: CommandPoolReset,
            props: {},
            visible: false,
        },

        // COMMAND BUFFER
        {
            id: SectionID.COMMAND_BUFFER,
            label: "Command Buffer",
            heading: 2,
            content: CommandBuffer,
            props: {},
            visible: false,
        },
        {
            id: SectionID.COMMAND_BUFFER_Constructor,
            label: "Constructor",
            heading: 3,
            content: CommandBufferConstructor,
            props: {},
            visible: false,
        },
        {
            id: SectionID.COMMAND_BUFFER_getCommandBufferHandle,
            label: "getCommandBufferHandle",
            heading: 3,
            content: GetCommandBufferHandle,
            props: {},
            visible: false,
        },
        {
            id: SectionID.COMMAND_BUFFER_getLevel,
            label: "getLevel",
            heading: 3,
            content: GetLevel,
            props: {},
            visible: false,
        },
        {
            id: SectionID.COMMAND_BUFFER_begin,
            label: "begin",
            heading: 3,
            content: CommandBufferBegin,
            props: {},
            visible: false,
        },
        {
            id: SectionID.COMMAND_BUFFER_end,
            label: "end",
            heading: 3,
            content: CommandBufferEnd,
            props: {},
            visible: false,
        },
        {
            id: SectionID.COMMAND_BUFFER_reset,
            label: "reset",
            heading: 3,
            content: CommandBufferReset,
            props: {},
            visible: false,
        },

        // COMMAND RECORDING
        {
            id: SectionID.COMMAND_RECORDING,
            label: "Command Recording",
            heading: 2,
            content: CommandRecording,
            props: {},
            visible: false,
        },
        {
            id: SectionID.COMMAND_RECORDING_endAll,
            label: "endAll",
            heading: 3,
            content: CommandRecordingEndAll,
            props: {},
            visible: false,
        },
        {
            id: SectionID.COMMAND_RECORDING_submit,
            label: "submit",
            heading: 3,
            content: CommandRecordingSubmit,
            props: {},
            visible: false,
        },
        {
            id: SectionID.COMMAND_RECORDING_reset,
            label: "reset",
            heading: 3,
            content: CommandRecordingReset,
            props: {},
            visible: false,
        },
        {
            id: SectionID.COMMAND_RECORDING_free,
            label: "free",
            heading: 3,
            content: CommandRecordingFree,
            props: {},
            visible: false,
        },
        {
            id: SectionID.COMMAND_RECORDING_createFence,
            label: "createFence",
            heading: 3,
            content: CommandRecordingCreateFence,
            props: {},
            visible: false,
        },
        {
            id: SectionID.COMMAND_RECORDING_waitForFence,
            label: "waitForFence",
            heading: 3,
            content: CommandRecordingWaitForFence,
            props: {},
            visible: false,
        },

        // SWAPCHAIN
        {
            id: SectionID.SWAPCHAIN,
            label: "Swapchain",
            heading: 2,
            content: Swapchain,
            props: {},
            visible: false,
        },
        {
            id: SectionID.SWAPCHAIN_Swapchain_Image,
            label: "Swapchain Image",
            heading: 3,
            content: SwapchainImage,
            props: {},
            visible: false,
        },
        {
            id: SectionID.SWAPCHAIN_Constructor,
            label: "Constructor",
            heading: 3,
            content: SwapchainConstructor,
            props: {},
            visible: false,
        },
        {
            id: SectionID.SWAPCHAIN_getSwapchainHandle,
            label: "getSwapchainHandle",
            heading: 3,
            content: GetSwapchainHandle,
            props: {},
            visible: false,
        },
        {
            id: SectionID.SWAPCHAIN_getNextImage,
            label: "getNextImage",
            heading: 3,
            content: SwapchaingetNextImage,
            props: {},
            visible: false,
        },
        {
            id: SectionID.SWAPCHAIN_getSurfaceFormat,
            label: "getSurfaceFormat",
            heading: 3,
            content: SwapchainGetSurfaceFormat,
            props: {},
            visible: false,
        },
        {
            id: SectionID.SWAPCHAIN_getImageCount,
            label: "getImageCount",
            heading: 3,
            content: SwapchainGetImageCount,
            props: {},
            visible: false,
        },
        {
            id: SectionID.SWAPCHAIN_getImageArrayLayers,
            label: "getImageArrayLayers",
            heading: 3,
            content: SwapchainGetImageArrayLayers,
            props: {},
            visible: false,
        },
        {
            id: SectionID.SWAPCHAIN_getImageUsage,
            label: "getImageUsage",
            heading: 3,
            content: SwapchainGetImageUsage,
            props: {},
            visible: false,
        },
        {
            id: SectionID.SWAPCHAIN_getImageSharingMode,
            label: "getImageSharingMode",
            heading: 3,
            content: SwapchainGetImageSharingMode,
            props: {},
            visible: false,
        },
        {
            id: SectionID.SWAPCHAIN_getImageExtent,
            label: "getImageExtent",
            heading: 3,
            content: SwapchainGetImageExtent,
            props: {},
            visible: false,
        },
        {
            id: SectionID.SWAPCHAIN_getPresentMode,
            label: "getPresentMode",
            heading: 3,
            content: SwapchainGetPresentMode,
            props: {},
            visible: false,
        },
        {
            id: SectionID.SWAPCHAIN_getQueueFamilyIndices,
            label: "getQueueFamilyIndices",
            heading: 3,
            content: SwapchainGetQueueFamilyIndices,
            props: {},
            visible: false,
        },
        {
            id: SectionID.SWAPCHAIN_present,
            label: "present",
            heading: 3,
            content: SwapchainPresent,
            props: {},
            visible: false,
        },

        // BUFFER DIRECTOR
        {
            id: SectionID.BUFFER_DIRECTOR,
            label: "Buffer Director",
            heading: 2,
            content: BufferDirector,
            props: {},
            visible: false,
        },
        {
            id: SectionID.BUFFER_DIRECTOR_Constructor,
            label: "Constructor",
            heading: 3,
            content: BufferDirectorConstructor,
            props: {},
            visible: false,
        },
        {
            id: SectionID.BUFFER_DIRECTOR_makeVertexBuffer,
            label: "makeVertexBuffer",
            heading: 3,
            content: BufferDirectorMakeVertexBuffer,
            props: {},
            visible: false,
        },
        {
            id: SectionID.BUFFER_DIRECTOR_makeVertexTransferDestinationBuffer,
            label: "makeVertexTransferDestinationBuffer",
            heading: 3,
            content: BufferDirectorMakeVertexTransferDestinationBuffer,
            props: {},
            visible: false,
        },
        {
            id: SectionID.BUFFER_DIRECTOR_makeUniformBuffer,
            label: "makeUniformBuffer",
            heading: 3,
            content: BufferDirectorMakeUniformBuffer,
            props: {},
            visible: false,
        },
        {
            id: SectionID.BUFFER_DIRECTOR_makeStorageBuffer,
            label: "makeStorageBuffer",
            heading: 3,
            content: BufferDirectorMakeStorageBuffer,
            props: {},
            visible: false,
        },
        {
            id: SectionID.BUFFER_DIRECTOR_makeUniformTexelBuffer,
            label: "makeUniformTexelBuffer",
            heading: 3,
            content: BufferDirectorMakeUniformTexelBuffer,
            props: {},
            visible: false,
        },
        {
            id: SectionID.BUFFER_DIRECTOR_makeStorageTexelBuffer,
            label: "makeStorageTexelBuffer",
            heading: 3,
            content: BufferDirectorMakeStorageTexelBuffer,
            props: {},
            visible: false,
        },
        {
            id: SectionID.BUFFER_DIRECTOR_makeIndexBuffer,
            label: "makeIndexBuffer",
            heading: 3,
            content: BufferDirectorMakeIndexBuffer,
            props: {},
            visible: false,
        },
        {
            id: SectionID.BUFFER_DIRECTOR_makeIndexTransferDestinationBuffer,
            label: "makeIndexTransferDestinationBuffer",
            heading: 3,
            content: BufferDirectorMakeIndexTransferDestinationBuffer,
            props: {},
            visible: false,
        },
        {
            id: SectionID.BUFFER_DIRECTOR_makeIndirectBuffer,
            label: "makeIndirectBuffer",
            heading: 3,
            content: BufferDirectorMakeIndirectBuffer,
            props: {},
            visible: false,
        },
        {
            id: SectionID.BUFFER_DIRECTOR_makeStagingBuffer,
            label: "makeStagingBuffer",
            heading: 3,
            content: BufferDirectorMakeStagingBuffer,
            props: {},
            visible: false,
        },

        // BUFFER BUILDER
        {
            id: SectionID.BUFFER_BUILDER,
            label: "Buffer Builder",
            heading: 2,
            content: BufferBuilder,
            props: {},
            visible: false,
        },
        {
            id: SectionID.BUFFER_BUILDER_Constructor,
            label: "Constructor",
            heading: 3,
            content: BufferBuilderConstructor,
            props: {},
            visible: false,
        },
        {
            id: SectionID.BUFFER_BUILDER_setLogicalDevice,
            label: "setLogicalDevice",
            heading: 3,
            content: BufferBuilderSetLogicalDevice,
            props: {},
            visible: false,
        },
        {
            id: SectionID.BUFFER_BUILDER_setFlags,
            label: "setFlags",
            heading: 3,
            content: BufferBuilderSetFlags,
            props: {},
            visible: false,
        },
        {
            id: SectionID.BUFFER_BUILDER_setSize,
            label: "setSize",
            heading: 3,
            content: BufferBuilderSetSize,
            props: {},
            visible: false,
        },
        {
            id: SectionID.BUFFER_BUILDER_setUsage,
            label: "setUsage",
            heading: 3,
            content: BufferBuilderSetUsage,
            props: {},
            visible: false,
        },
        {
            id: SectionID.BUFFER_BUILDER_setSharingMode,
            label: "setSharingMode",
            heading: 3,
            content: BufferBuilderSetSharingMode,
            props: {},
            visible: false,
        },
        {
            id: SectionID.BUFFER_BUILDER_setQueueFamilyIndices,
            label: "setQueueFamilyIndices",
            heading: 3,
            content: BufferBuilderSetQueueFamilyIndices,
            props: {},
            visible: false,
        },
        {
            id: SectionID.BUFFER_BUILDER_getResult,
            label: "getResult",
            heading: 3,
            content: BufferBuilderGetResult,
            props: {},
            visible: false,
        },
        {
            id: SectionID.BUFFER_BUILDER_reset,
            label: "reset",
            heading: 3,
            content: BufferBuilderReset,
            props: {},
            visible: false,
        },

        // BUFFER
        {
            id: SectionID.BUFFER,
            label: "Buffer",
            heading: 2,
            content: Buffer,
            props: {},
            visible: false,
        },
        {
            id: SectionID.BUFFER_Constructor,
            label: "Constructor",
            heading: 3,
            content: BufferConstructor,
            props: {},
            visible: false,
        },
        {
            id: SectionID.BUFFER_getBufferHandle,
            label: "getBufferHandle",
            heading: 3,
            content: GetBufferHandle,
            props: {},
            visible: false,
        },
        {
            id: SectionID.BUFFER_getFlags,
            label: "getFlags",
            heading: 3,
            content: BufferGetFlags,
            props: {},
            visible: false,
        },
        {
            id: SectionID.BUFFER_getSize,
            label: "getSize",
            heading: 3,
            content: BufferGetSize,
            props: {},
            visible: false,
        },
        {
            id: SectionID.BUFFER_getUsage,
            label: "getUsage",
            heading: 3,
            content: BufferGetUsage,
            props: {},
            visible: false,
        },
        {
            id: SectionID.BUFFER_getSharingMode,
            label: "getSharingMode",
            heading: 3,
            content: BufferGetSharingMode,
            props: {},
            visible: false,
        },
        {
            id: SectionID.BUFFER_getQueueFamilyIndices,
            label: "getQueueFamilyIndices",
            heading: 3,
            content: BufferGetQueueFamilyIndices,
            props: {},
            visible: false,
        },
        {
            id: SectionID.BUFFER_bindMemory,
            label: "bindMemory",
            heading: 3,
            content: BufferBindMemory,
            props: {},
            visible: false,
        },
        {
            id: SectionID.BUFFER_getMemory,
            label: "getMemory",
            heading: 3,
            content: BufferGetMemory,
            props: {},
            visible: false,
        },
        {
            id: SectionID.BUFFER_createBufferView,
            label: "createBufferView",
            heading: 3,
            content: BufferCreateBufferView,
            props: {},
            visible: false,
        },
        {
            id: SectionID.BUFFER_getBufferViews,
            label: "getBufferViews",
            heading: 3,
            content: BufferGetBufferViews,
            props: {},
            visible: false,
        },
        {
            id: SectionID.BUFFER_getBufferView,
            label: "getBufferView",
            heading: 3,
            content: BufferGetBufferView,
            props: {},
            visible: false,
        },
        {
            id: SectionID.BUFFER_destroyBufferViews,
            label: "destroyBufferViews",
            heading: 3,
            content: BufferDestroyBufferViews,
            props: {},
            visible: false,
        },
        {
            id: SectionID.BUFFER_destroyBufferView,
            label: "destroyBufferView",
            heading: 3,
            content: BufferDestroyBufferView,
            props: {},
            visible: false,
        },
        {
            id: SectionID.BUFFER_copyTo,
            label: "copyTo",
            heading: 3,
            content: BufferCopyTo,
            props: {},
            visible: false,
        },

        // BUFFER VIEW
        {
            id: SectionID.BUFFER_VIEW,
            label: "Buffer View",
            heading: 2,
            content: BufferView,
            props: {},
            visible: false,
        },
        {
            id: SectionID.BUFFER_VIEW_Constructor,
            label: "Constructor",
            heading: 3,
            content: BufferViewConstructor,
            props: {},
            visible: false,
        },
        {
            id: SectionID.BUFFER_VIEW_getBufferViewHandle,
            label: "getBufferViewHandle",
            heading: 3,
            content: GetBufferViewHandle,
            props: {},
            visible: false,
        },

        // IMAGE DIRECTOR
        {
            id: SectionID.IMAGE_DIRECTOR,
            label: "Image Director",
            heading: 2,
            content: ImageDirector,
            props: {},
            visible: false,
        },
        {
            id: SectionID.IMAGE_DIRECTOR_Constructor,
            label: "Constructor",
            heading: 3,
            content: ImageDirectorConstructor,
            props: {},
            visible: false,
        },
        {
            id: SectionID.IMAGE_DIRECTOR_make2DTexture,
            label: "make2DTexture",
            heading: 3,
            content: ImageDirectorMake2DTexture,
            props: {},
            visible: false,
        },
        {
            id: SectionID.IMAGE_DIRECTOR_makeDepthImage,
            label: "makeDepthImage",
            heading: 3,
            content: ImageDirectorMakeDepthImage,
            props: {},
            visible: false,
        },

        // IMAGE BUILDER
        {
            id: SectionID.IMAGE_BUILDER,
            label: "Image Builder",
            heading: 2,
            content: ImageBuilder,
            props: {},
            visible: false,
        },
        {
            id: SectionID.IMAGE_BUILDER_Constructor,
            label: "Constructor",
            heading: 3,
            content: ImageBuilderConstructor,
            props: {},
            visible: false,
        },
        {
            id: SectionID.IMAGE_BUILDER_setLogicalDevice,
            label: "setLogicalDevice",
            heading: 3,
            content: ImageBuilderSetLogicalDevice,
            props: {},
            visible: false,
        },
        {
            id: SectionID.IMAGE_BUILDER_setFlags,
            label: "setFlags",
            heading: 3,
            content: ImageBuilderSetFlags,
            props: {},
            visible: false,
        },
        {
            id: SectionID.IMAGE_BUILDER_setImageType,
            label: "setImageType",
            heading: 3,
            content: ImageBuilderSetImageType,
            props: {},
            visible: false,
        },
        {
            id: SectionID.IMAGE_BUILDER_setFormat,
            label: "setFormat",
            heading: 3,
            content: ImageBuilderSetFormat,
            props: {},
            visible: false,
        },
        {
            id: SectionID.IMAGE_BUILDER_setExtent,
            label: "setExtent",
            heading: 3,
            content: ImageBuilderSetExtent,
            props: {},
            visible: false,
        },
        {
            id: SectionID.IMAGE_BUILDER_setMipLevels,
            label: "setMipLevels",
            heading: 3,
            content: ImageBuilderSetMipLevels,
            props: {},
            visible: false,
        },
        {
            id: SectionID.IMAGE_BUILDER_setArrayLayers,
            label: "setArrayLayers",
            heading: 3,
            content: ImageBuilderSetArrayLayers,
            props: {},
            visible: false,
        },
        {
            id: SectionID.IMAGE_BUILDER_setSamples,
            label: "setSamples",
            heading: 3,
            content: ImageBuilderSetSamples,
            props: {},
            visible: false,
        },
        {
            id: SectionID.IMAGE_BUILDER_setImageTiling,
            label: "setImageTiling",
            heading: 3,
            content: ImageBuilderSetImageTiling,
            props: {},
            visible: false,
        },
        {
            id: SectionID.IMAGE_BUILDER_setImageUsage,
            label: "setImageUsage",
            heading: 3,
            content: ImageBuilderSetImageUsage,
            props: {},
            visible: false,
        },
        {
            id: SectionID.IMAGE_BUILDER_setSharingMode,
            label: "setSharingMode",
            heading: 3,
            content: ImageBuilderSetSharingMode,
            props: {},
            visible: false,
        },
        {
            id: SectionID.IMAGE_BUILDER_setQueueFamilyIndices,
            label: "setQueueFamilyIndices",
            heading: 3,
            content: ImageBuilderSetQueueFamilyIndices,
            props: {},
            visible: false,
        },
        {
            id: SectionID.IMAGE_BUILDER_setInitialLayout,
            label: "setInitialLayout",
            heading: 3,
            content: ImageBuilderSetInitialLayout,
            props: {},
            visible: false,
        },
        {
            id: SectionID.IMAGE_BUILDER_reset,
            label: "reset",
            heading: 3,
            content: ImageBuilderReset,
            props: {},
            visible: false,
        },
        {
            id: SectionID.IMAGE_BUILDER_getResult,
            label: "getResult",
            heading: 3,
            content: ImageBuilderGetResult,
            props: {},
            visible: false,
        },

        // IMAGE
        {
            id: SectionID.IMAGE,
            label: "Image",
            heading: 2,
            content: Image,
            props: {},
            visible: false,
        },
        {
            id: SectionID.IMAGE_Constructor,
            label: "Constructor",
            heading: 3,
            content: ImageConstructor,
            props: {},
            visible: false,
        },
        {
            id: SectionID.IMAGE_getImageHandle,
            label: "getImageHandle",
            heading: 3,
            content: GetImageHandle,
            props: {},
            visible: false,
        },
        {
            id: SectionID.IMAGE_getFlags,
            label: "getFlags",
            heading: 3,
            content: ImageGetFlags,
            props: {},
            visible: false,
        },
        {
            id: SectionID.IMAGE_getUsage,
            label: "getUsage",
            heading: 3,
            content: ImageGetUsage,
            props: {},
            visible: false,
        },
        {
            id: SectionID.IMAGE_getSharingMode,
            label: "getSharingMode",
            heading: 3,
            content: ImageGetSharingMode,
            props: {},
            visible: false,
        },
        {
            id: SectionID.IMAGE_getQueueFamilyIndices,
            label: "getQueueFamilyIndices",
            heading: 3,
            content: ImageGetQueueFamilyIndices,
            props: {},
            visible: false,
        },
        {
            id: SectionID.IMAGE_getType,
            label: "getType",
            heading: 3,
            content: ImageGetType,
            props: {},
            visible: false,
        },
        {
            id: SectionID.IMAGE_getFormat,
            label: "getFormat",
            heading: 3,
            content: ImageGetFormat,
            props: {},
            visible: false,
        },
        {
            id: SectionID.IMAGE_getExtent,
            label: "getExtent",
            heading: 3,
            content: ImageGetExtent,
            props: {},
            visible: false,
        },
        {
            id: SectionID.IMAGE_getMipLevels,
            label: "getMipLevels",
            heading: 3,
            content: ImageGetMipLevels,
            props: {},
            visible: false,
        },
        {
            id: SectionID.IMAGE_getArrayLayers,
            label: "getArrayLayers",
            heading: 3,
            content: ImageGetArrayLayers,
            props: {},
            visible: false,
        },
        {
            id: SectionID.IMAGE_getSamples,
            label: "getSamples",
            heading: 3,
            content: ImageGetSamples,
            props: {},
            visible: false,
        },
        {
            id: SectionID.IMAGE_getTiling,
            label: "getTiling",
            heading: 3,
            content: ImageGetTiling,
            props: {},
            visible: false,
        },
        {
            id: SectionID.IMAGE_getInitialLayout,
            label: "getInitialLayout",
            heading: 3,
            content: ImageGetInitialLayout,
            props: {},
            visible: false,
        },
        {
            id: SectionID.IMAGE_bindMemory,
            label: "bindMemory",
            heading: 3,
            content: ImageBindMemory,
            props: {},
            visible: false,
        },
        {
            id: SectionID.IMAGE_getMemory,
            label: "getMemory",
            heading: 3,
            content: ImageGetMemory,
            props: {},
            visible: false,
        },
        {
            id: SectionID.IMAGE_createImageView,
            label: "createImageView",
            heading: 3,
            content: ImageCreateImageView,
            props: {},
            visible: false,
        },
        {
            id: SectionID.IMAGE_getImageViews,
            label: "getImageViews",
            heading: 3,
            content: ImageGetImageViews,
            props: {},
            visible: false,
        },
        {
            id: SectionID.IMAGE_getImageView,
            label: "getImageView",
            heading: 3,
            content: ImageGetImageView,
            props: {},
            visible: false,
        },
        {
            id: SectionID.IMAGE_destroyImageViews,
            label: "destroyImageViews",
            heading: 3,
            content: ImageDestroyImageViews,
            props: {},
            visible: false,
        },
        {
            id: SectionID.IMAGE_destroyImageView,
            label: "destroyImageView",
            heading: 3,
            content: ImageDestroyImageView,
            props: {},
            visible: false,
        },
        {
            id: SectionID.IMAGE_copyTo,
            label: "copyTo",
            heading: 3,
            content: ImageCopyTo,
            props: {},
            visible: false,
        },
        {
            id: SectionID.IMAGE_transitionImageLayout,
            label: "transitionImageLayout",
            heading: 3,
            content: ImageTransitionImageLayout,
            props: {},
            visible: false,
        },

        // IMAGE VIEW
        {
            id: SectionID.IMAGE_VIEW,
            label: "Image View",
            heading: 2,
            content: ImageView,
            props: {},
            visible: false,
        },
        {
            id: SectionID.IMAGE_VIEW_Constructor,
            label: "Constructor",
            heading: 3,
            content: ImageViewConstructor,
            props: {},
            visible: false,
        },
        {
            id: SectionID.IMAGE_VIEW_getImageViewHandle,
            label: "getImageViewHandle",
            heading: 3,
            content: GetImageViewHandle,
            props: {},
            visible: false,
        },

        // SAMPLER BUILDER
        {
            id: SectionID.SAMPLER_BUILDER,
            label: "Sampler Builder",
            heading: 2,
            content: SamplerBuilder,
            props: {},
            visible: false,
        },
        {
            id: SectionID.SAMPLER_BUILDER_Constructor,
            label: "Constructor",
            heading: 3,
            content: SamplerBuilderConstructor,
            props: {},
            visible: false,
        },
        {
            id: SectionID.SAMPLER_BUILDER_setLogicalDevice,
            label: "setLogicalDevice",
            heading: 3,
            content: SamplerBuilderSetLogicalDevice,
            props: {},
            visible: false,
        },
        {
            id: SectionID.SAMPLER_BUILDER_setFilters,
            label: "setFilters",
            heading: 3,
            content: SamplerBuilderSetFilters,
            props: {},
            visible: false,
        },
        {
            id: SectionID.SAMPLER_BUILDER_setMipmapMode,
            label: "setMipmapMode",
            heading: 3,
            content: SamplerBuilderSetMipmapMode,
            props: {},
            visible: false,
        },
        {
            id: SectionID.SAMPLER_BUILDER_setAddressModes,
            label: "setAddressModes",
            heading: 3,
            content: SamplerBuilderSetAddressModes,
            props: {},
            visible: false,
        },
        {
            id: SectionID.SAMPLER_BUILDER_setMipLodBias,
            label: "setMipLodBias",
            heading: 3,
            content: SamplerBuilderSetMipLodBias,
            props: {},
            visible: false,
        },
        {
            id: SectionID.SAMPLER_BUILDER_setMaxAnisotropy,
            label: "setMaxAnisotropy",
            heading: 3,
            content: SamplerBuilderSetMaxAnisotropy,
            props: {},
            visible: false,
        },
        {
            id: SectionID.SAMPLER_BUILDER_unsetMaxAnisotropy,
            label: "unsetMaxAnisotropy",
            heading: 3,
            content: SamplerBuilderUnsetMaxAnisotropy,
            props: {},
            visible: false,
        },
        {
            id: SectionID.SAMPLER_BUILDER_setCompareOp,
            label: "setCompareOp",
            heading: 3,
            content: SamplerBuilderSetCompareOp,
            props: {},
            visible: false,
        },
        {
            id: SectionID.SAMPLER_BUILDER_unsetCompareOp,
            label: "unsetCompareOp",
            heading: 3,
            content: SamplerBuilderUnsetCompareOp,
            props: {},
            visible: false,
        },
        {
            id: SectionID.SAMPLER_BUILDER_setLod,
            label: "setLod",
            heading: 3,
            content: SamplerBuilderSetLod,
            props: {},
            visible: false,
        },
        {
            id: SectionID.SAMPLER_BUILDER_setBorderColor,
            label: "setBorderColor",
            heading: 3,
            content: SamplerBuilderSetBorderColor,
            props: {},
            visible: false,
        },
        {
            id: SectionID.SAMPLER_BUILDER_enableUnnormalizedCoordinates,
            label: "enableUnnormalizedCoordinates",
            heading: 3,
            content: SamplerBuilderEnableUnnormalizedCoordinates,
            props: {},
            visible: false,
        },
        {
            id: SectionID.SAMPLER_BUILDER_disableUnnormalizedCoordinates,
            label: "disableUnnormalizedCoordinates",
            heading: 3,
            content: SamplerBuilderDisableUnnormalizedCoordinates,
            props: {},
            visible: false,
        },
        {
            id: SectionID.SAMPLER_BUILDER_getResult,
            label: "getResult",
            heading: 3,
            content: SamplerBuilderGetResult,
            props: {},
            visible: false,
        },
        {
            id: SectionID.SAMPLER_BUILDER_reset,
            label: "reset",
            heading: 3,
            content: SamplerBuilderReset,
            props: {},
            visible: false,
        },

        // SAMPLER
        {
            id: SectionID.SAMPLER,
            label: "Sampler",
            heading: 2,
            content: Sampler,
            props: {},
            visible: false,
        },
        {
            id: SectionID.SAMPLER_Constructor,
            label: "Constructor",
            heading: 3,
            content: SamplerConstructor,
            props: {},
            visible: false,
        },
        {
            id: SectionID.SAMPLER_getSamplerHandle,
            label: "getSamplerHandle",
            heading: 3,
            content: GetSamplerHandle,
            props: {},
            visible: false,
        },

        // MEMORY
        {
            id: SectionID.MEMORY,
            label: "Memory",
            heading: 2,
            content: Memory,
            props: {},
            visible: false,
        },
        {
            id: SectionID.MEMORY_Constructor,
            label: "Constructor",
            heading: 3,
            content: MemoryConstructor,
            props: {},
            visible: false,
        },
        {
            id: SectionID.MEMORY_getMemoryHandle,
            label: "getMemoryHandle",
            heading: 3,
            content: GetMemoryHandle,
            props: {},
            visible: false,
        },
        {
            id: SectionID.MEMORY_map,
            label: "map",
            heading: 3,
            content: MemoryMap,
            props: {},
            visible: false,
        },
        {
            id: SectionID.MEMORY_unmap,
            label: "unmap",
            heading: 3,
            content: MemoryUnmap,
            props: {},
            visible: false,
        },
        {
            id: SectionID.MEMORY_getData,
            label: "getData",
            heading: 3,
            content: MemoryGetData,
            props: {},
            visible: false,
        },
        {
            id: SectionID.MEMORY_flush,
            label: "flush",
            heading: 3,
            content: MemoryFlush,
            props: {},
            visible: false,
        },
        {
            id: SectionID.MEMORY_invalidate,
            label: "invalidate",
            heading: 3,
            content: MemoryInvalidate,
            props: {},
            visible: false,
        },

        // SEMAPHORE
        {
            id: SectionID.SEMAPHORE,
            label: "Semaphore",
            heading: 2,
            content: Semaphore,
            props: {},
            visible: false,
        },
        {
            id: SectionID.SEMAPHORE_Constructor,
            label: "Constructor",
            heading: 3,
            content: SemaphoreConstructor,
            props: {},
            visible: false,
        },
        {
            id: SectionID.SEMAPHORE_getSemaphoreHandle,
            label: "getSemaphoreHandle",
            heading: 3,
            content: GetSemaphoreHandle,
            props: {},
            visible: false,
        },

        // FENCE
        {
            id: SectionID.FENCE,
            label: "Fence",
            heading: 2,
            content: Fence,
            props: {},
            visible: false,
        },
        {
            id: SectionID.FENCE_Constructor,
            label: "Constructor",
            heading: 3,
            content: FenceConstructor,
            props: {},
            visible: false,
        },
        {
            id: SectionID.FENCE_getFenceHandle,
            label: "getFenceHandle",
            heading: 3,
            content: GetFenceHandle,
            props: {},
            visible: false,
        },
        {
            id: SectionID.FENCE_waitFor,
            label: "waitFor",
            heading: 3,
            content: FenceWaitFor,
            props: {},
            visible: false,
        },
        {
            id: SectionID.FENCE_reset,
            label: "reset",
            heading: 3,
            content: FenceReset,
            props: {},
            visible: false,
        },
        {
            id: SectionID.FENCE_s_waitForAll,
            label: "s_waitForAll",
            heading: 3,
            content: FenceSWaitForAll,
            props: {},
            visible: false,
        },
        {
            id: SectionID.FENCE_s_resetAll,
            label: "s_resetAll",
            heading: 3,
            content: FenceSResetAll,
            props: {},
            visible: false,
        },

        // SHADER MODULE
        {
            id: SectionID.SHADER_MODULE,
            label: "Shader Module",
            heading: 2,
            content: ShaderModule,
            props: {},
            visible: false,
        },
        {
            id: SectionID.SHADER_MODULE_Constructor,
            label: "Constructor",
            heading: 3,
            content: ShaderModuleConstructor,
            props: {},
            visible: false,
        },
        {
            id: SectionID.SHADER_MODULE_getShaderModuleHandle,
            label: "getShaderModuleHandle",
            heading: 3,
            content: GetShaderModuleHandle,
            props: {},
            visible: false,
        },
        {
            id: SectionID.SHADER_MODULE_getDescriptorSetLayouts,
            label: "getDescriptorSetLayouts",
            heading: 3,
            content: ShaderModuleGetDescriptorSetLayouts,
            props: {},
            visible: false,
        },
        {
            id: SectionID.SHADER_MODULE_getDescriptorPool,
            label: "getDescriptorPool",
            heading: 3,
            content: ShaderModuleGetDescriptorPool,
            props: {},
            visible: false,
        },

        // DESCRIPTOR SET LAYOUT BUILDER
        {
            id: SectionID.DESCRIPTOR_SET_LAYOUT_BUILDER,
            label: "Descriptor Set Layout Builder",
            heading: 2,
            content: DescriptorSetLayoutBuilder,
            props: {},
            visible: false,
        },
        {
            id: SectionID.DESCRIPTOR_SET_LAYOUT_BUILDER_Constructor,
            label: "Constructor",
            heading: 3,
            content: DescriptorSetLayoutBuilderConstructor,
            props: {},
            visible: false,
        },
        {
            id: SectionID.DESCRIPTOR_SET_LAYOUT_BUILDER_setLogicalDevice,
            label: "setLogicalDevice",
            heading: 3,
            content: DescriptorSetLayoutBuilderSetLogicalDevice,
            props: {},
            visible: false,
        },
        {
            id: SectionID.DESCRIPTOR_SET_LAYOUT_BUILDER_addBinding,
            label: "addBinding",
            heading: 3,
            content: DescriptorSetLayoutBuilderAddBinding,
            props: {},
            visible: false,
        },
        {
            id: SectionID.DESCRIPTOR_SET_LAYOUT_BUILDER_getResult,
            label: "getResult",
            heading: 3,
            content: DescriptorSetLayoutBuilderGetResult,
            props: {},
            visible: false,
        },
        {
            id: SectionID.DESCRIPTOR_SET_LAYOUT_BUILDER_reset,
            label: "reset",
            heading: 3,
            content: DescriptorSetLayoutBuilderReset,
            props: {},
            visible: false,
        },
        {
            id: SectionID.DESCRIPTOR_SET_LAYOUT,
            label: "Descriptor Set Layout",
            heading: 2,
            content: DescriptorSetLayout,
            props: {},
            visible: false,
        },
        {
            id: SectionID.DESCRIPTOR_SET_LAYOUT_Constructor,
            label: "Constructor",
            heading: 3,
            content: DescriptorSetLayoutConstructor,
            props: {},
            visible: false,
        },
        {
            id: SectionID.DESCRIPTOR_SET_LAYOUT_getDescriptorSetLayoutHandle,
            label: "getDescriptorSetLayoutHandle",
            heading: 3,
            content: GetDescriptorSetLayoutHandle,
            props: {},
            visible: false,
        },
        {
            id: SectionID.DESCRIPTOR_SET_LAYOUT_getBindings,
            label: "getBindings",
            heading: 3,
            content: DescriptorSetLayoutGetBindings,
            props: {},
            visible: false,
        },

        // DESCRIPTOR POOL BUILDER
        {
            id: SectionID.DESCRIPTOR_POOL_BUILDER,
            label: "Descriptor Pool Builder",
            heading: 2,
            content: DescriptorPoolBuilder,
            props: {},
            visible: false,
        },
        {
            id: SectionID.DESCRIPTOR_POOL_BUILDER_Constructor,
            label: "Constructor",
            heading: 3,
            content: DescriptorPoolBuilderConstructor,
            props: {},
            visible: false,
        },
        {
            id: SectionID.DESCRIPTOR_POOL_BUILDER_setLogicalDevice,
            label: "setLogicalDevice",
            heading: 3,
            content: DescriptorPoolBuilderSetLogicalDevice,
            props: {},
            visible: false,
        },
        {
            id: SectionID.DESCRIPTOR_POOL_BUILDER_setFlags,
            label: "setFlags",
            heading: 3,
            content: DescriptorPoolBuilderSetFlags,
            props: {},
            visible: false,
        },
        {
            id: SectionID.DESCRIPTOR_POOL_BUILDER_addSet,
            label: "addSet",
            heading: 3,
            content: DescriptorPoolBuilderAddSet,
            props: {},
            visible: false,
        },
        {
            id: SectionID.DESCRIPTOR_POOL_BUILDER_getResult,
            label: "getResult",
            heading: 3,
            content: DescriptorPoolBuilderGetResult,
            props: {},
            visible: false,
        },
        {
            id: SectionID.DESCRIPTOR_POOL_BUILDER_reset,
            label: "reset",
            heading: 3,
            content: DescriptorPoolBuilderReset,
            props: {},
            visible: false,
        },

        // DESCRIPTOR POOL
        {
            id: SectionID.DESCRIPTOR_POOL,
            label: "Descriptor Pool",
            heading: 2,
            content: DescriptorPool,
            props: {},
            visible: false,
        },
        {
            id: SectionID.DESCRIPTOR_POOL_Constructor,
            label: "Constructor",
            heading: 3,
            content: DescriptorPoolConstructor,
            props: {},
            visible: false,
        },
        {
            id: SectionID.DESCRIPTOR_POOL_getDescriptorPoolHandle,
            label: "getDescriptorPoolHandle",
            heading: 3,
            content: GetDescriptorPoolHandle,
            props: {},
            visible: false,
        },
        {
            id: SectionID.DESCRIPTOR_POOL_allocateDescriptorSet,
            label: "allocateDescriptorSet",
            heading: 3,
            content: DescriptorPoolAllocateDescriptorSet,
            props: {},
            visible: false,
        },
        {
            id: SectionID.DESCRIPTOR_POOL_getDescriptorSets,
            label: "getDescriptorSets",
            heading: 3,
            content: DescriptorPoolGetDescriptorSets,
            props: {},
            visible: false,
        },
        {
            id: SectionID.DESCRIPTOR_POOL_getDescriptorSet,
            label: "getDescriptorSet",
            heading: 3,
            content: DescriptorPoolGetDescriptorSet,
            props: {},
            visible: false,
        },
        {
            id: SectionID.DESCRIPTOR_POOL_freeDescriptorSets,
            label: "freeDescriptorSets",
            heading: 3,
            content: DescriptorPoolFreeDescriptorSets,
            props: {},
            visible: false,
        },
        {
            id: SectionID.DESCRIPTOR_POOL_reset,
            label: "reset",
            heading: 3,
            content: DescriptorPoolReset,
            props: {},
            visible: false,
        },

        // DESCRIPTOR SET
        {
            id: SectionID.DESCRIPTOR_SET,
            label: "Descriptor Set",
            heading: 2,
            content: DescriptorSet,
            props: {},
            visible: false,
        },
        {
            id: SectionID.DESCRIPTOR_SET_Constructor,
            label: "Constructor",
            heading: 3,
            content: DescriptorSetConstructor,
            props: {},
            visible: false,
        },
        {
            id: SectionID.DESCRIPTOR_SET_getDescriptorSetHandle,
            label: "getDescriptorSetHandle",
            heading: 3,
            content: GetDescriptorSetHandle,
            props: {},
            visible: false,
        },
        {
            id: SectionID.DESCRIPTOR_SET_getLayout,
            label: "getLayout",
            heading: 3,
            content: DescriptorSetGetLayout,
            props: {},
            visible: false,
        },
        {
            id: SectionID.DESCRIPTOR_SET_getName,
            label: "getName",
            heading: 3,
            content: DescriptorSetGetName,
            props: {},
            visible: false,
        },
        {
            id: SectionID.DESCRIPTOR_SET_writeImage,
            label: "writeImage",
            heading: 3,
            content: DescriptorSetWriteImage,
            props: {},
            visible: false,
        },
        {
            id: SectionID.DESCRIPTOR_SET_writeBuffer,
            label: "writeBuffer",
            heading: 3,
            content: DescriptorSetWriteBuffer,
            props: {},
            visible: false,
        },
        {
            id: SectionID.DESCRIPTOR_SET_writeTexelBufferView,
            label: "writeTexelBufferView",
            heading: 3,
            content: DescriptorSetWriteTexelBufferView,
            props: {},
            visible: false,
        },
        {
            id: SectionID.DESCRIPTOR_SET_copy,
            label: "copy",
            heading: 3,
            content: DescriptorSetCopy,
            props: {},
            visible: false,
        },

        // PIPELINE BUILDER
        {
            id: SectionID.PIPELINE_BUILDER,
            label: "Pipeline Builder",
            heading: 2,
            content: PipelineBuilder,
            props: {},
            visible: false,
        },
        {
            id: SectionID.PIPELINE_BUILDER_Constructor,
            label: "Constructor",
            heading: 3,
            content: PipelineBuilderConstructor,
            props: {},
            visible: false,
        },
        {
            id: SectionID.PIPELINE_BUILDER_setLogicalDevice,
            label: "setLogicalDevice",
            heading: 3,
            content: PipelineBuilderSetLogicalDevice,
            props: {},
            visible: false,
        },
        {
            id: SectionID.PIPELINE_BUILDER_setFlags,
            label: "setFlags",
            heading: 3,
            content: PipelineBuilderSetFlags,
            props: {},
            visible: false,
        },
        {
            id: SectionID.PIPELINE_BUILDER_addPushConstant,
            label: "addPushConstant",
            heading: 3,
            content: PipelineBuilderAddPushConstant,
            props: {},
            visible: false,
        },
        {
            id: SectionID.PIPELINE_BUILDER_setPipelineCache,
            label: "setPipelineCache",
            heading: 3,
            content: PipelineBuilderSetPipelineCache,
            props: {},
            visible: false,
        },
        {
            id: SectionID.PIPELINE_BUILDER_setBasePipeline,
            label: "setBasePipeline",
            heading: 3,
            content: PipelineBuilderSetBasePipeline,
            props: {},
            visible: false,
        },
        {
            id: SectionID.PIPELINE_BUILDER_reset,
            label: "reset",
            heading: 3,
            content: PipelineBuilderReset,
            props: {},
            visible: false,
        },

        // PIPELINE
        {
            id: SectionID.PIPELINE,
            label: "Pipeline",
            heading: 2,
            content: Pipeline,
            props: {},
            visible: false,
        },
        {
            id: SectionID.PIPELINE_PIPELINE_SHADER_STAGE,
            label: "Pipeline Shader Stage",
            heading: 3,
            content: PipelineShaderStage,
            props: {},
            visible: false,
        },
        {
            id: SectionID.PIPELINE_Constructor,
            label: "Constructor",
            heading: 3,
            content: PipelineConstructor,
            props: {},
            visible: false,
        },
        {
            id: SectionID.PIPELINE_getPipelineHandle,
            label: "getPipelineHandle",
            heading: 3,
            content: GetPipelineHandle,
            props: {},
            visible: false,
        },
        {
            id: SectionID.PIPELINE_getPipelineLayout,
            label: "getPipelineLayout",
            heading: 3,
            content: PipelineGetPipelineLayout,
            props: {},
            visible: false,
        },
        {
            id: SectionID.PIPELINE_bindToCommandBuffer,
            label: "bindToCommandBuffer",
            heading: 3,
            content: PipelineBindToCommandBuffer,
            props: {},
            visible: false,
        },
        {
            id: SectionID.PIPELINE_getCommandBuffer,
            label: "getCommandBuffer",
            heading: 3,
            content: PipelineGetCommandBuffer,
            props: {},
            visible: false,
        },
        {
            id: SectionID.PIPELINE_bindDescriptorSets,
            label: "bindDescriptorSets",
            heading: 3,
            content: PipelineBindDescriptorSets,
            props: {},
            visible: false,
        },
        {
            id: SectionID.PIPELINE_getDescriptorSets,
            label: "getDescriptorSets",
            heading: 3,
            content: PipelineGetDescriptorSets,
            props: {},
            visible: false,
        },
        {
            id: SectionID.PIPELINE_getDescriptorSet,
            label: "getDescriptorSet",
            heading: 3,
            content: PipelineGetDescriptorSet,
            props: {},
            visible: false,
        },
        {
            id: SectionID.PIPELINE_pushConstantData,
            label: "pushConstantData",
            heading: 3,
            content: PipelinePushConstantData,
            props: {},
            visible: false,
        },

        // PIPELINE LAYOUT
        {
            id: SectionID.PIPELINE_LAYOUT,
            label: "Pipeline Layout",
            heading: 2,
            content: PipelineLayout,
            props: {},
            visible: false,
        },
        {
            id: SectionID.PIPELINE_LAYOUT_PUSH_CONSTANT,
            label: "Push Constant",
            heading: 3,
            content: PushConstant,
            props: {},
            visible: false,
        },
        {
            id: SectionID.PIPELINE_LAYOUT_Constructor,
            label: "Constructor",
            heading: 3,
            content: PipelineLayoutConstructor,
            props: {},
            visible: false,
        },
        {
            id: SectionID.PIPELINE_LAYOUT_getPipelineLayoutHandle,
            label: "getPipelineLayoutHandle",
            heading: 3,
            content: GetPipelineLayoutHandle,
            props: {},
            visible: false,
        },
        {
            id: SectionID.PIPELINE_LAYOUT_pushConstantData,
            label: "pushConstantData",
            heading: 3,
            content: PipelineLayoutPushConstantData,
            props: {},
            visible: false,
        },

        // COMPUTE PIPELINE BUILDER
        {
            id: SectionID.COMPUTE_PIPELINE_BUILDER,
            label: "Compute Pipeline Builder",
            heading: 2,
            content: ComputePipelineBuilder,
            props: {},
            visible: false,
        },
        {
            id: SectionID.COMPUTE_PIPELINE_BUILDER_Constructor,
            label: "Constructor",
            heading: 3,
            content: ComputePipelineBuilderConstructor,
            props: {},
            visible: false,
        },
        {
            id: SectionID.COMPUTE_PIPELINE_BUILDER_setShaderStage,
            label: "setShaderStage",
            heading: 3,
            content: ComputePipelineBuilderSetShaderStage,
            props: {},
            visible: false,
        },
        {
            id: SectionID.COMPUTE_PIPELINE_BUILDER_getResult,
            label: "getResult",
            heading: 3,
            content: ComputePipelineBuilderGetResult,
            props: {},
            visible: false,
        },
        {
            id: SectionID.COMPUTE_PIPELINE_BUILDER_reset,
            label: "reset",
            heading: 3,
            content: ComputePipelineBuilderReset,
            props: {},
            visible: false,
        },

        // COMPUTE PIPELINE
        {
            id: SectionID.COMPUTE_PIPELINE,
            label: "Compute Pipeline",
            heading: 2,
            content: ComputePipeline,
            props: {},
            visible: false,
        },
        {
            id: SectionID.COMPUTE_PIPELINE_Constructor,
            label: "Constructor",
            heading: 3,
            content: ComputePipelineConstructor,
            props: {},
            visible: false,
        },

        // RENDER PASS BUILDER
        {
            id: SectionID.RENDER_PASS_BUILDER,
            label: "Render Pass Builder",
            heading: 2,
            content: RenderPassBuilder,
            props: {},
            visible: false,
        },
        {
            id: SectionID.RENDER_PASS_BUILDER_Constructor,
            label: "Constructor",
            heading: 3,
            content: RenderPassBuilderConstructor,
            props: {},
            visible: false,
        },
        {
            id: SectionID.RENDER_PASS_BUILDER_setLogicalDevice,
            label: "setLogicalDevice",
            heading: 3,
            content: RenderPassBuilderSetLogicalDevice,
            props: {},
            visible: false,
        },
        {
            id: SectionID.RENDER_PASS_BUILDER_addAttachment,
            label: "addAttachment",
            heading: 3,
            content: RenderPassBuilderAddAttachment,
            props: {},
            visible: false,
        },
        {
            id: SectionID.RENDER_PASS_BUILDER_addInputAttachment,
            label: "addInputAttachment",
            heading: 3,
            content: RenderPassBuilderAddInputAttachment,
            props: {},
            visible: false,
        },
        {
            id: SectionID.RENDER_PASS_BUILDER_addColorAttachment,
            label: "addColorAttachment",
            heading: 3,
            content: RenderPassBuilderAddColorAttachment,
            props: {},
            visible: false,
        },
        {
            id: SectionID.RENDER_PASS_BUILDER_setDepthStencilAttachment,
            label: "setDepthStencilAttachment",
            heading: 3,
            content: RenderPassBuilderSetDepthStencilAttachment,
            props: {},
            visible: false,
        },
        {
            id: SectionID.RENDER_PASS_BUILDER_resolveCurrentAttachments,
            label: "resolveCurrentAttachments",
            heading: 3,
            content: RenderPassBuilderResolveCurrentAttachments,
            props: {},
            visible: false,
        },
        {
            id: SectionID.RENDER_PASS_BUILDER_constructSubpass,
            label: "constructSubpass",
            heading: 3,
            content: RenderPassBuilderConstructSubpass,
            props: {},
            visible: false,
        },
        {
            id: SectionID.RENDER_PASS_BUILDER_addDependency,
            label: "addDependency",
            heading: 3,
            content: RenderPassBuilderAddDependency,
            props: {},
            visible: false,
        },
        {
            id: SectionID.RENDER_PASS_BUILDER_getResult,
            label: "getResult",
            heading: 3,
            content: RenderPassBuilderGetResult,
            props: {},
            visible: false,
        },
        {
            id: SectionID.RENDER_PASS_BUILDER_reset,
            label: "reset",
            heading: 3,
            content: RenderPassBuilderReset,
            props: {},
            visible: false,
        },

        // RENDER PASS
        {
            id: SectionID.RENDER_PASS,
            label: "Render Pass",
            heading: 2,
            content: RenderPass,
            props: {},
            visible: false,
        },
        {
            id: SectionID.RENDER_PASS_Constructor,
            label: "Constructor",
            heading: 3,
            content: RenderPassConstructor,
            props: {},
            visible: false,
        },
        {
            id: SectionID.RENDER_PASS_getRenderPassHandle,
            label: "getRenderPassHandle",
            heading: 3,
            content: GetRenderPassHandle,
            props: {},
            visible: false,
        },
        {
            id: SectionID.RENDER_PASS_getAttachments,
            label: "getAttachments",
            heading: 3,
            content: RenderPassGetAttachments,
            props: {},
            visible: false,
        },
        {
            id: SectionID.RENDER_PASS_getSubpasses,
            label: "getSubpasses",
            heading: 3,
            content: RenderPassGetSubpasses,
            props: {},
            visible: false,
        },
        {
            id: SectionID.RENDER_PASS_getDependencies,
            label: "getDependencies",
            heading: 3,
            content: RenderPassGetDependencies,
            props: {},
            visible: false,
        },
        {
            id: SectionID.RENDER_PASS_begin,
            label: "begin",
            heading: 3,
            content: RenderPassBegin,
            props: {},
            visible: false,
        },
        {
            id: SectionID.RENDER_PASS_end,
            label: "end",
            heading: 3,
            content: RenderPassEnd,
            props: {},
            visible: false,
        },

        // FRAMEBUFFER
        {
            id: SectionID.FRAMEBUFFER,
            label: "Framebuffer",
            heading: 2,
            content: Framebuffer,
            props: {},
            visible: false,
        },
        {
            id: SectionID.FRAMEBUFFER_Constructor,
            label: "Constructor",
            heading: 3,
            content: FramebufferConstructor,
            props: {},
            visible: false,
        },
        {
            id: SectionID.FRAMEBUFFER_getFramebufferHandle,
            label: "getFramebufferHandle",
            heading: 3,
            content: GetFramebufferHandle,
            props: {},
            visible: false,
        },
        {
            id: SectionID.FRAMEBUFFER_getExtent,
            label: "getExtent",
            heading: 3,
            content: FramebufferGetExtent,
            props: {},
            visible: false,
        },
        {
            id: SectionID.FRAMEBUFFER_getLayers,
            label: "getLayers",
            heading: 3,
            content: FramebufferGetLayers,
            props: {},
            visible: false,
        },

        // GRAPHICS PIPELINE BUILDER
        {
            id: SectionID.GRAPHICS_PIPELINE_BUILDER,
            label: "Graphics Pipeline Builder",
            heading: 2,
            content: GraphicsPipelineBuilder,
            props: {},
            visible: false,
        },
        {
            id: SectionID.GRAPHICS_PIPELINE_BUILDER_Constructor,
            label: "Constructor",
            heading: 3,
            content: GraphicsPipelineBuilderConstructor,
            props: {},
            visible: false,
        },
        {
            id: SectionID.GRAPHICS_PIPELINE_BUILDER_addShaderStage,
            label: "addShaderStage",
            heading: 3,
            content: GraphicsPipelineBuilderAddShaderStage,
            props: {},
            visible: false,
        },

        {
            id: SectionID.GRAPHICS_PIPELINE_BUILDER_setInputAssemblyState,
            label: "setInputAssemblyState",
            heading: 3,
            content: GraphicsPipelineBuilderSetInputAssemblyState,
            props: {},
            visible: false,
        },

        {
            id: SectionID.GRAPHICS_PIPELINE_BUILDER_setVertexInputState,
            label: "setVertexInputState",
            heading: 3,
            content: GraphicsPipelineBuilderSetVertexInputState,
            props: {},
            visible: false,
        },

        {
            id: SectionID.GRAPHICS_PIPELINE_BUILDER_setTessellationState,
            label: "setTessellationState",
            heading: 3,
            content: GraphicsPipelineBuilderSetTessellationState,
            props: {},
            visible: false,
        },

        {
            id: SectionID.GRAPHICS_PIPELINE_BUILDER_addViewportState,
            label: "addViewportState",
            heading: 3,
            content: GraphicsPipelineBuilderAddViewportState,
            props: {},
            visible: false,
        },

        {
            id: SectionID.GRAPHICS_PIPELINE_BUILDER_setRasterizationState,
            label: "setRasterizationState",
            heading: 3,
            content: GraphicsPipelineBuilderSetRasterizationState,
            props: {},
            visible: false,
        },

        {
            id: SectionID.GRAPHICS_PIPELINE_BUILDER_setMultisampleState,
            label: "setMultisampleState",
            heading: 3,
            content: GraphicsPipelineBuilderSetMultisampleState,
            props: {},
            visible: false,
        },

        {
            id: SectionID.GRAPHICS_PIPELINE_BUILDER_setDepthStencilState,
            label: "setDepthStencilState",
            heading: 3,
            content: GraphicsPipelineBuilderSetDepthStencilState,
            props: {},
            visible: false,
        },

        {
            id: SectionID.GRAPHICS_PIPELINE_BUILDER_setColorBlendState,
            label: "setColorBlendState",
            heading: 3,
            content: GraphicsPipelineBuilderSetColorBlendState,
            props: {},
            visible: false,
        },

        {
            id: SectionID.GRAPHICS_PIPELINE_BUILDER_setDynamicState,
            label: "setDynamicState",
            heading: 3,
            content: GraphicsPipelineBuilderSetDynamicState,
            props: {},
            visible: false,
        },

        {
            id: SectionID.GRAPHICS_PIPELINE_BUILDER_setRenderPass,
            label: "setRenderPass",
            heading: 3,
            content: GraphicsPipelineBuilderSetRenderPass,
            props: {},
            visible: false,
        },

        {
            id: SectionID.GRAPHICS_PIPELINE_BUILDER_setSubpass,
            label: "setSubpass",
            heading: 3,
            content: GraphicsPipelineBuilderSetSubpass,
            props: {},
            visible: false,
        },

        {
            id: SectionID.GRAPHICS_PIPELINE_BUILDER_getResult,
            label: "getResult",
            heading: 3,
            content: GraphicsPipelineBuilderGetResult,
            props: {},
            visible: false,
        },

        {
            id: SectionID.GRAPHICS_PIPELINE_BUILDER_reset,
            label: "reset",
            heading: 3,
            content: GraphicsPipelineBuilderReset,
            props: {},
            visible: false,
        },

        // GRAPHICS PIPELINE
        {
            id: SectionID.GRAPHICS_PIPELINE,
            label: "Graphics Pipeline",
            heading: 2,
            content: GraphicsPipeline,
            props: {},
            visible: false,
        },
        {
            id: SectionID.GRAPHICS_PIPELINE_Constructor,
            label: "Constructor",
            heading: 3,
            content: GraphicsPipelineConstructor,
            props: {},
            visible: false,
        },
        {
            id: SectionID.GRAPHICS_PIPELINE_getRenderPass,
            label: "getRenderPass",
            heading: 3,
            content: GraphicsPipelineGetRenderPass,
            props: {},
            visible: false,
        },
    ];

    let currentVisibleSection: SectionObject | null = null;
    $: {
        sections;
        for (let i = 0; i < sections.length; i++) {
            if (sections[i].visible) {
                currentVisibleSection = sections[i];
                break;
            }
        }
    }

    let showHamburgerMenu = false;

    function handleHamburgerMenuClick(_e: MouseEvent) {
        showHamburgerMenu = !showHamburgerMenu;
    }

    function onReferenceClick() {
        showHamburgerMenu = false;
    }

    let mobile = false;
    stateStore.subscribe((newState) => {
        mobile = newState.Screen.width <= 1000;
    });
</script>

<svelte:head>
    {@html nord}
</svelte:head>

<div
    class="documentation {mobile ? 'mobile' : ''}"
    style="--sidebar-width: 22.5rem;"
>
    <div class="documentation-sidebar">
        <DocumentationSectionList {sections} {onReferenceClick} />
    </div>
    {#if mobile}
        <div class="documentation-pop-in">
            <div class="documentation-pop-in-inner">
                <button
                    on:click={handleHamburgerMenuClick}
                    class="hamburger-menu-button {showHamburgerMenu
                        ? 'activated'
                        : ''}"
                >
                    <HamburgerMenuIcon />
                </button>
            </div>
        </div>
    {/if}
    {#if mobile && showHamburgerMenu}
        <div
            in:fly={{ y: -10, duration: 500, opacity: 0 }}
            out:fly={{ y: -20, duration: 250, opacity: 0 }}
            class="documentation-pop-in-content"
        >
            <DocumentationSectionList {sections} {onReferenceClick} />
        </div>
    {/if}
    <div class="documentation-container {mobile ? 'mobile' : 'desktop'}">
        <h1>Documentation</h1>
        <p>
            This page contains the documentation for Fillcan (v{getState()
                .Fillcan.version}). It's intended for people who are familiar
            with C++ and Vulkan. <br />
            Some concepts within C++ and Vulkan will be elaborated upon if I think
            they are interesting.
        </p>
        <br /><br />
        <hr />
        {#each sections as section, i}
            <Section
                id={section.id}
                label={section.label}
                heading={section.heading}
                bind:visible={section.visible}
            >
                <svelte:component this={section.content} {...section.props} />
            </Section>
            <br />
            {#if i !== 0 && i < sections.length - 1 && sections.at(i + 1)?.heading === 2}
                <hr />
            {/if}
        {/each}
    </div>
</div>

<style lang="scss">
    .documentation {
        .documentation-container {
            font-family: $--font-family-default;
            color: $--fg-color-primary;
            margin-left: var(--sidebar-width);
            padding: 0 5vw 0 5vw;
            max-width: 100%;
            overflow-wrap: break-word;

            hr {
                color: $--fg-color-tertiary;
            }
        }

        .documentation-sidebar {
            top: 5rem; // 5rem is the height of the NavBar
            font-family: $--font-family-default;
            color: $--fg-color-primary;
            position: fixed;
            overflow-y: scroll;

            background-color: $--bg-color-secondary;
            width: var(--sidebar-width);
        }

        h1 {
            padding-top: 0;
        }

        h1 {
            font-size: 3rem;
        }
    }

    .documentation.mobile {
        .documentation-container {
            margin-left: 0;
        }
        .documentation-sidebar {
            display: none;
        }
    }

    .documentation:not(.mobile) {
        .documentation-pop-in {
            display: none;
        }
        .documentation-pop-in-content {
            display: none;
        }
    }

    .documentation-sidebar,
    .documentation-pop-in-content {
        top: $--navbar-height;
        height: calc(100% - $--navbar-height);
        overflow: auto;
    }

    .documentation-pop-in {
        position: fixed;
        bottom: 0;
        width: 100%;
        height: 2.5rem;
        background-color: $--bg-color-secondary;

        .documentation-pop-in-inner {
            width: 100%;
            height: 100%;
            display: flex;
            vertical-align: middle;
            align-content: center;
            .hamburger-menu-button {
                margin-left: 0.5rem;
                width: 1.75rem;
                height: 100%;
                border: none;
                background: none;
                cursor: pointer;
                fill: $--input-fg-color-secondary;
                transition: all 0.25s;
            }
            .hamburger-menu-button:hover,
            .hamburger-menu-button:focus,
            .hamburger-menu-button:active {
                fill: $--input-fg-color-primary;
            }

            .hamburger-menu-button.activated {
                fill: $--input-fg-color-primary;
                width: 2rem;
            }
        }
    }

    .documentation-pop-in-content {
        position: fixed;
        top: $--navbar-height; // Height of the NavBar
        bottom: 2.5rem; // Height of the pop-in menu
        height: calc(100% - 2.5rem - $--navbar-height);
        width: 100%;
        background-color: $--bg-color-secondary;
        overflow: auto;
    }
</style>
