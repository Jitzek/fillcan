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
    FILLCAN_beginSingleTimeRecording = "Fillcan-beginSingleTimeRecording",
    FILLCAN_endSingleTimeRecording = "Fillcan-endSingleTimeRecording",

    // FILLCAN_GRAPHICS
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

    DEVICE_POOL = "Device-Pool",
    PHYSICAL_DEVICE = "Physical-Device",
    LOGICAL_DEVICE = "Logical-Device",
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
}
