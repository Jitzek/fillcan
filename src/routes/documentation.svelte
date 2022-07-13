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
    import GetGraphicsQueueFamilyIndex from "$components/Documentation/Sections/Physical_Device/getGraphicsQueueFamilyIndex.svelte";
    import GetPresentQueueFamilyIndex from "$components/Documentation/Sections/Physical_Device/getPresentQueueFamilyIndex.svelte";
    import GetComputeQueueFamilyIndex from "$components/Documentation/Sections/Physical_Device/getComputeQueueFamilyIndex.svelte";
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

    const sections: Array<SectionObject> = [
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
            id: SectionID.PHYSICAL_DEVICE_getGraphicsQueueFamilyIndex,
            label: "getGraphicsQueueFamilyIndex",
            heading: 3,
            content: GetGraphicsQueueFamilyIndex,
            props: {},
            visible: false,
        },
        {
            id: SectionID.PHYSICAL_DEVICE_getPresentQueueFamilyIndex,
            label: "getPresentQueueFamilyIndex",
            heading: 3,
            content: GetPresentQueueFamilyIndex,
            props: {},
            visible: false,
        },
        {
            id: SectionID.PHYSICAL_DEVICE_getComputeQueueFamilyIndex,
            label: "getComputeQueueFamilyIndex",
            heading: 3,
            content: GetComputeQueueFamilyIndex,
            props: {},
            visible: false,
        },
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
</script>

<svelte:head>
    {@html nord}
</svelte:head>

<div
    class="documentation {$stateStore.Screen.displayType === DisplayType.MOBILE
        ? 'mobile'
        : ''}"
    style="--sidebar-width: 20rem;"
>
    <div class="documentation-sidebar">
        <!-- <ul class="references-list">
            {#each sections as section, i}
                <li
                    class="reference-item h{section.heading} {currentVisibleSection !==
                        null && section.id === currentVisibleSection.id
                        ? 'active'
                        : ''}"
                >
                    <a href="{getState().URL.root}/documentation#{section.id}">
                        {section.label}
                    </a>
                </li>
            {/each}
        </ul> -->
        <DocumentationSectionList {sections} />
    </div>
    {#if $stateStore.Screen.displayType === DisplayType.MOBILE}
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
    {#if $stateStore.Screen.displayType === DisplayType.MOBILE && showHamburgerMenu}
        <div
            in:fly={{ y: -10, duration: 500, opacity: 0 }}
            out:fly={{ y: -20, duration: 250, opacity: 0 }}
            class="documentation-pop-in-content"
        >
            <ul class="references-list">
                {#each sections as section, i}
                    <li
                        class="reference-item h{section.heading} {currentVisibleSection !==
                            null && section.id === currentVisibleSection.id
                            ? 'active'
                            : ''}"
                    >
                        <a
                            href="{getState().URL
                                .root}/documentation#{section.id}"
                        >
                            {section.label}
                        </a>
                    </li>
                {/each}
            </ul>
        </div>
    {/if}
    <div
        class="documentation-container  {$stateStore.Screen.displayType ===
        DisplayType.MOBILE
            ? 'mobile'
            : 'desktop'}"
    >
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
            padding: 0 15vw 0 5vw;

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
        .references-list {
            font-family: $--font-family-input;
            list-style: none;
            text-decoration: none;
            padding: 1.5rem 1.5rem 1.5rem 2.5rem;
            margin: 0;
            a {
                letter-spacing: 0.025rem;
                text-decoration: none;
            }
            .reference-item.h2 {
                margin-top: 1rem;
                a {
                    color: $--input-fg-color-primary;
                    text-transform: uppercase;
                    font-size: 1.2rem;
                }
            }
            .reference-item.h3 {
                a {
                    color: $--input-fg-color-secondary;
                    padding-left: 1rem;
                    font-size: 1.1rem;
                }
            }
            .reference-item.h4 {
                a {
                    color: $--input-fg-color-secondary;
                    padding-left: 2rem;
                    font-size: 1.05rem;
                }
            }
            .reference-item.h5 {
                a {
                    color: $--input-fg-color-secondary;
                    padding-left: 3rem;
                    font-size: 1rem;
                }
            }
            .reference-item.active {
                background-color: black !important;
            }

            a:hover,
            a:focus,
            a:active {
                text-decoration: underline;
            }
        }
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
