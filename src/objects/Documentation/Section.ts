export class Section {
    public id: string;
    public label: string;
    public heading: 2 | 3 | 4 | 5;
    public content: any;
    public props: any;
    public visible: boolean = false;
}

export enum SectionID {
    GETTING_STARTED = "Getting-Started",
    CMAKE = "CMake",

    // FILLCAN
    FILLCAN = "Fillcan",
    FILLCAN_Constructor = "Fillcan-Constructor",
    FILLCAN_getSupportedPhysicalDevices = "Fillcan-getSupportedPhysicalDevices",
    FILLCAN_selectDevice = "Fillcan-selectDevice",
    FILLCAN_getCurrentDevice = "Fillcan-getCurrentDevice",
    FILLCAN_createShaderModule = "Fillcan-createShaderModule",

    // FILLCAN GRAPHICS
    FILLCAN_GRAPHICS = "Fillcan-Graphics",
    FILLCAN_GRAPHICS_Constructor = "Fillcan-Graphics-Constructor",
    FILLCAN_GRAPHICS_getWindow = "Fillcan-Graphics-getWindow",
    FILLCAN_GRAPHICS_mainLoop = "Fillcan-Graphics-mainLoop",
    FILLCAN_GRAPHICS_createSwapchain = "Fillcan-Graphics-createSwapchain",
    FILLCAN_GRAPHICS_recreateSwapchain = "Fillcan-Graphics-recreateSwapchain",
    FILLCAN_GRAPHICS_getSwapchain = "Fillcan-Graphics-getSwapchain",
    FILLCAN_GRAPHICS_getSwapchains = "Fillcan-Graphics-getSwapchains",
    FILLCAN_GRAPHICS_destroySwapchain = "Fillcan-Graphics-destroySwapchain",
    FILLCAN_GRAPHICS_getAssetManager = "Fillcan-Graphics-getAssetManager",

    // WINDOW
    WINDOW = "Window",
    WINDOW_Constructor = "Window-Constructor",
    WINDOW_shouldClose = "Window-shouldClose",
    WINDOW_wasResized = "Window-wasResized",
    WINDOW_pollEvents = "Window-pollEvents",
    WINDOW_getRequiredExtensions = "Window-getRequiredExtensions",
    WINDOW_createSurface = "Window-createSurface",
    WINDOW_getSurface = "Window-getSurface",
    WINDOW_getExtent = "Window-getExtent",

    // INSTANCE
    INSTANCE = "Instance",
    INSTANCE_Constructor = "Instance-Constructor",
    INSTANCE_getInstanceHandle = "Instance-getInstanceHandle",

    // DEVICE POOL
    DEVICE_POOL = "Device-Pool",
    DEVICE_POOL_Constructor = "Device-Pool-Constructor",
    DEVICE_POOL_getSupportedPhysicalDevices = "Device-Pool-getSupportedPhysicalDevices",
    DEVICE_POOL_selectDevice = "Device-Pool-selectDevice",
    DEVICE_POOL_getCurrentDevice = "Device-Pool-getCurrentDevice",

    // PHYSICAL DEVICE
    PHYSICAL_DEVICE = "Physical-Device",
    PHYSICAL_DEVICE_Constructor = "Physical-Device-Constructor",
    PHYSICAL_DEVICE_getPhysicalDeviceHandle = "Physical-Device-getPhysicalDeviceHandle",
    PHYSICAL_DEVICE_getRequiredExtensions = "Physical-Device-getRequiredExtensions",
    PHYSICAL_DEVICE_areExtensionsSupported = "Physical-Device-areExtensionsSupported",
    PHYSICAL_DEVICE_getRequiredFeatures = "Physical-Device-getRequiredFeatures",
    PHYSICAL_DEVICE_areFeaturesSupported = "Physical-Device-areFeaturesSupported",
    PHYSICAL_DEVICE_getFeatures = "Physical-Device-getFeatures",
    PHYSICAL_DEVICE_getProperties = "Physical-Device-getProperties",
    PHYSICAL_DEVICE_getSurfaceCapabilitiesKHR = "Physical-Device-getSurfaceCapabilitiesKHR",
    PHYSICAL_DEVICE_getSurfaceFormatsKHR = "Physical-Device-getSurfaceFormatsKHR",
    PHYSICAL_DEVICE_getSurfacePresentModesKHR = "Physical-Device-getSurfacePresentModesKHR",
    PHYSICAL_DEVICE_getQueueFamilyProperties = "Physical-Device-getQueueFamilyProperties",
    PHYSICAL_DEVICE_getFormatProperties = "Physical-Device-getFormatProperties",
    PHYSICAL_DEVICE_findSupportedFormat = "Physical-Device-findSupportedFormat",
    PHYSICAL_DEVICE_getGraphicsQueueFamilyIndex = "Physical-Device-getGraphicsQueueFamilyIndex",
    PHYSICAL_DEVICE_getPresentQueueFamilyIndex = "Physical-Device-getPresentQueueFamilyIndex",
    PHYSICAL_DEVICE_getComputeQueueFamilyIndex = "Physical-Device-getComputeQueueFamilyIndex",

    // LOGICAL DEVICE
    LOGICAL_DEVICE = "Logical-Device",
    LOGICAL_DEVICE_Constructor = "Logical-Device-Constructor",
    LOGICAL_DEVICE_getLogicalDeviceHandle = "Logical-Device-getLogicalDeviceHandle",
    LOGICAL_DEVICE_getPhysicalDevice = "Logical-Device-getPhysicalDevice",
    LOGICAL_DEVICE_waitIdle = "Logical-Device-waitIdle",
    LOGICAL_DEVICE_getGraphicsQueue = "Logical-Device-getGraphicsQueue",
    LOGICAL_DEVICE_getPresentQueue = "Logical-Device-getPresentQueue",
    LOGICAL_DEVICE_getComputeQueue = "Logical-Device-getComputeQueue",
    LOGICAL_DEVICE_beginSingleTimeCommandRecording = "Logical-Device-beginSingleTimeCommandRecording",
    LOGICAL_DEVICE_endSingleTimeCommandRecording = "Logical-Device-endSingleTimeCommandRecording",

    SWAPCHAIN = "Swapchain",
    DESCRIPTOR_SET_LAYOUT_BUILDER = "Descriptor-Set-Layout-Builder",
    DESCRIPTOR_SET_LAYOUT = "Descriptor-Set-Layout",
    DESCRIPTOR_POOL_BUILDER = "Descriptor-Pool-Builder",
    DESCRIPTOR_POOL = "Descriptor-Pool",
    DESCRIPTOR_SET = "Descriptor-Set",
    QUEUE = "Queue",
    COMMAND_RECORDING = "Command-Recording",
    COMMAND_BUFFER = "Command-Buffer",
    ASSET_MANAGER = "Asset-Manager",
    BUFFER = "Buffer",
    IMAGE = "Image",
}
