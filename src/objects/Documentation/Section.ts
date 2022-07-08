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
    FILLCAN_getWindow = "Fillcan-getWindow",
    FILLCAN_createShaderModule = "Fillcan-createShaderModule",

    FILLCAN_GRAPHICS = "Fillcan-Graphics",
    WINDOW = "Window",
    INSTANCE = "Instance",
    PHYSICAL_DEVICE = "Physical-Device",
    LOGICAL_DEVICE = "Logical-Device",
    SWAPCHAIN = "Swapchain",
    DESCRIPTOR_SET_LAYOUT_BUILDER = "Descriptor-Set-Layout-Builder",
    DESCRIPTOR_SET_LAYOUT = "Descriptor-Set-Layout",
    DESCRIPTOR_POOL_BUILDER = "Descriptor-Pool-Builder",
    DESCRIPTOR_POOL = "Descriptor-Pool",
    DESCRIPTOR_SET = "Descriptor-Set",
}
