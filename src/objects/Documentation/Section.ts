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
    FILLCAN_getWindow = "Fillcan-Graphics-getWindow",
    FILLCAN_mainLoop = "Fillcan-Graphics-mainLoop",

    WINDOW = "Window",
    INSTANCE = "Instance",
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
}
