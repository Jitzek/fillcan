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
    PHYSICAL_DEVICE_getMemoryProperties = "Physical-Device-getMemoryProperties",
    PHYSICAL_DEVICE_findSupportedFormat = "Physical-Device-findSupportedFormat",
    PHYSICAL_DEVICE_getGraphicsQueueFamilyIndices = "Physical-Device-getGraphicsQueueFamilyIndices",
    PHYSICAL_DEVICE_getPresentQueueFamilyIndices = "Physical-Device-getPresentQueueFamilyIndices",
    PHYSICAL_DEVICE_getComputeQueueFamilyIndices = "Physical-Device-getComputeQueueFamilyIndices",

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

    // QUEUE
    QUEUE = "Queue",
    QUEUE_Constructor = "Queue-Constructor",
    QUEUE_getQueueHandle = "Queue-getQueueHandle",
    QUEUE_getQueueFamilyIndex = "Queue-getQueueFamilyIndex",
    QUEUE_getQueueIndex = "Queue-getQueueIndex",
    QUEUE_createCommandPool = "Queue-createCommandPool",
    QUEUE_getCommandPools = "Queue-getCommandPools",
    QUEUE_getCommandPool = "Queue-getCommandPool",
    QUEUE_destroyCommandPool = "Queue-destroyCommandPool",
    QUEUE_createRecording = "Queue-createRecording",
    QUEUE_submitRecordings = "Queue-submitRecordings",
    QUEUE_resetRecording = "Queue-resetRecording",
    QUEUE_freeRecording = "Queue-freeRecording",
    QUEUE_waitIdle = "Queue-waitIdle",

    // COMMAND POOL
    COMMAND_POOL = "Command-Pool",
    COMMAND_POOL_Constructor = "Command-Pool-Constructor",
    COMMAND_POOL_getCommandPoolHandle = "Command-Pool-getCommandPoolHandle",
    COMMAND_POOL_allocateCommandBuffers = "Command-Pool-allocateCommandBuffers",
    COMMAND_POOL_freeCommandBuffers = "Command-Pool-freeCommandBuffers",
    COMMAND_POOL_reset = "Command-Pool-reset",

    // COMMAND BUFFER
    COMMAND_BUFFER = "Command-Buffer",
    COMMAND_BUFFER_Constructor = "Command-Buffer-Constructor",
    COMMAND_BUFFER_getCommandBufferHandle = "Command-Buffer-getCommandBufferHandle",
    COMMAND_BUFFER_getLevel = "Command-Buffer-getLevel",
    COMMAND_BUFFER_begin = "Command-Buffer-begin",
    COMMAND_BUFFER_end = "Command-Buffer-end",
    COMMAND_BUFFER_reset = "Command-Buffer-reset",

    // COMMAND RECORDING
    COMMAND_RECORDING = "Command-Recording",
    COMMAND_RECORDING_endAll = "Command-Recording-endAll",
    COMMAND_RECORDING_submit = "Command-Recording-submit",
    COMMAND_RECORDING_reset = "Command-Recording-reset",
    COMMAND_RECORDING_free = "Command-Recording-free",
    COMMAND_RECORDING_createFence = "Command-Recording-createFence",
    COMMAND_RECORDING_waitForFence = "Command-Recording-waitForFence",

    // SWAPCHAIN
    SWAPCHAIN = "Swapchain",
    SWAPCHAIN_Swapchain_Image = "Swapchain-Swapchain-Image",
    SWAPCHAIN_Constructor = "Swapchain-Constructor",
    SWAPCHAIN_getSwapchainHandle = "Swapchain-getSwapchainHandle",
    SWAPCHAIN_getNextImage = "Swapchain-getNextImage",
    SWAPCHAIN_getSurfaceFormat = "Swapchain-getSurfaceFormat",
    SWAPCHAIN_getImageCount = "Swapchain-getImageCount",
    SWAPCHAIN_getImageArrayLayers = "Swapchain-getImageArrayLayers",
    SWAPCHAIN_getImageUsage = "Swapchain-getImageUsage",
    SWAPCHAIN_getImageSharingMode = "Swapchain-getImageSharingMode",
    SWAPCHAIN_getImageExtent = "Swapchain-getImageExtent",
    SWAPCHAIN_getPresentMode = "Swapchain-getPresentMode",
    SWAPCHAIN_getQueueFamilyIndices = "Swapchain-getQueueFamilyIndices",
    SWAPCHAIN_present = "Swapchain-present",

    // BUFFER
    BUFFER = "Buffer",
    BUFFER_Constructor = "Buffer-Constructor",
    BUFFER_getBufferHandle = "Buffer-getBufferHandle",
    BUFFER_getFlags = "Buffer-getFlags",
    BUFFER_getSize = "Buffer-getSize",
    BUFFER_getUsage = "Buffer-getUsage",
    BUFFER_getSharingMode = "Buffer-getSharingMode",
    BUFFER_getQueueFamilyIndices = "Buffer-getQueueFamilyIndices",
    BUFFER_bindMemory = "Buffer-bindMemory",
    BUFFER_getMemory = "Buffer-getMemory",
    BUFFER_createBufferView = "Buffer-createBufferView",
    BUFFER_getBufferViews = "Buffer-getBufferViews",
    BUFFER_getBufferView = "Buffer-getBufferView",
    BUFFER_destroyBufferViews = "Buffer-destroyBufferViews",
    BUFFER_destroyBufferView = "Buffer-destroyBufferView",
    BUFFER_copyTo = "Buffer-copyTo",

    // BUFFER VIEW
    BUFFER_VIEW = "Buffer-View",
    BUFFER_VIEW_Constructor = "Buffer-View-Constructor",
    BUFFER_VIEW_getBufferViewHandle = "Buffer-View-getBufferViewHandle",

    // BUFFER DIRECTOR
    BUFFER_DIRECTOR = "Buffer-Director",
    BUFFER_DIRECTOR_Constructor = "Buffer-Director-Constructor",
    BUFFER_DIRECTOR_makeVertexBuffer = "Buffer-Director-makeVertexBuffer",
    BUFFER_DIRECTOR_makeVertexTransferDestinationBuffer = "Buffer-Director-makeVertexTransferDestinationBuffer",
    BUFFER_DIRECTOR_makeUniformBuffer = "Buffer-Director-makeUniformBuffer",
    BUFFER_DIRECTOR_makeStorageBuffer = "Buffer-Director-makeStorageBuffer",
    BUFFER_DIRECTOR_makeUniformTexelBuffer = "Buffer-Director-makeUniformTexelBuffer",
    BUFFER_DIRECTOR_makeStorageTexelBuffer = "Buffer-Director-makeStorageTexelBuffer",
    BUFFER_DIRECTOR_makeIndexBuffer = "Buffer-Director-makeIndexBuffer",
    BUFFER_DIRECTOR_makeIndexTransferDestinationBuffer = "Buffer-Director-makeIndexTransferDestinationBuffer",
    BUFFER_DIRECTOR_makeIndirectBuffer = "Buffer-Director-makeIndirectBuffer",
    BUFFER_DIRECTOR_makeStagingBuffer = "Buffer-Director-makeStagingBuffer",

    // BUFFER BUILDER
    BUFFER_BUILDER = "Buffer-Builder",
    BUFFER_BUILDER_Constructor = "Buffer-Builder-Constructor",
    BUFFER_BUILDER_setLogicalDevice = "Buffer-Builder-setLogicalDevice",
    BUFFER_BUILDER_setFlags = "Buffer-Builder-setFlags",
    BUFFER_BUILDER_setSize = "Buffer-Builder-setSize",
    BUFFER_BUILDER_setUsage = "Buffer-Builder-setUsage",
    BUFFER_BUILDER_setSharingMode = "Buffer-Builder-setSharingMode",
    BUFFER_BUILDER_setQueueFamilyIndices = "Buffer-Builder-setQueueFamilyIndices",
    BUFFER_BUILDER_getResult = "Buffer-Builder-getResult",
    BUFFER_BUILDER_reset = "Buffer-Builder-reset",

    // IMAGE
    IMAGE = "Image",
    IMAGE_Constructor = "Image-Constructor",
    IMAGE_getImageHandle = "Image-getImageHandle",
    IMAGE_getFlags = "Image-getFlags",
    IMAGE_getUsage = "Image-getUsage",
    IMAGE_getSharingMode = "Image-getSharingMode",
    IMAGE_getQueueFamilyIndices = "Image-getQueueFamilyIndices",
    IMAGE_getType = "Image-getType",
    IMAGE_getFormat = "Image-getFormat",
    IMAGE_getExtent = "Image-getExtent",
    IMAGE_getMipLevels = "Image-getMipLevels",
    IMAGE_getArrayLayers = "Image-getArrayLayers",
    IMAGE_getSamples = "Image-getSamples",
    IMAGE_getTiling = "Image-getTiling",
    IMAGE_getInitialLayout = "Image-getInitialLayout",
    IMAGE_bindMemory = "Image-bindMemory",
    IMAGE_getMemory = "Image-getMemory",
    IMAGE_createImageView = "Image-createImageView",
    IMAGE_getImageViews = "Image-getImageViews",
    IMAGE_getImageView = "Image-getImageView",
    IMAGE_destroyImageViews = "Image-destroyImageViews",
    IMAGE_destroyImageView = "Image-destroyImageView",
    IMAGE_copyTo = "Image-copyTo",
    IMAGE_transitionImageLayout = "Image-transitionImageLayout",

    // IMAGE VIEW
    IMAGE_VIEW = "Image-View",
    IMAGE_VIEW_Constructor = "Image-View-Constructor",
    IMAGE_VIEW_getImageViewHandle = "Image-View-getImageViewHandle",

    // IMAGE DIRECTOR
    IMAGE_DIRECTOR = "Image-Director",
    IMAGE_DIRECTOR_Constructor = "Image-Director-Constructor",
    IMAGE_DIRECTOR_make2DTexture = "Image-Director-make2DTexture",
    IMAGE_DIRECTOR_makeDepthImage = "Image-Director-makeDepthImage",

    // IMAGE BUILDER
    IMAGE_BUILDER = "Image-Builder",
    IMAGE_BUILDER_Constructor = "Image-Builder-Constructor",
    IMAGE_BUILDER_setLogicalDevice = "Image-Builder-setLogicalDevice",
    IMAGE_BUILDER_setFlags = "Image-Builder-setFlags",
    IMAGE_BUILDER_setImageType = "Image-Builder-setImageType",
    IMAGE_BUILDER_setFormat = "Image-Builder-setFormat",
    IMAGE_BUILDER_setExtent = "Image-Builder-setExtent",
    IMAGE_BUILDER_setMipLevels = "Image-Builder-setMipLevels",
    IMAGE_BUILDER_setArrayLayers = "Image-Builder-setArrayLayers",
    IMAGE_BUILDER_setSamples = "Image-Builder-setSamples",
    IMAGE_BUILDER_setImageTiling = "Image-Builder-setImageTiling",
    IMAGE_BUILDER_setImageUsage = "Image-Builder-setImageUsage",
    IMAGE_BUILDER_setSharingMode = "Image-Builder-setSharingMode",
    IMAGE_BUILDER_setQueueFamilyIndices = "Image-Builder-setQueueFamilyIndices",
    IMAGE_BUILDER_setInitialLayout = "Image-Builder-setInitialLayout",
    IMAGE_BUILDER_reset = "Image-Builder-reset",
    IMAGE_BUILDER_getResult = "Image-Builder-getResult",

    // SAMPLER BUILDER
    SAMPLER_BUILDER = "Sampler-Builder",
    SAMPLER_BUILDER_Constructor = "Sampler-Builder-Constructor",
    SAMPLER_BUILDER_setLogicalDevice = "Sampler-Builder-setLogicalDevice",
    SAMPLER_BUILDER_setFilters = "Sampler-Builder-setFilters",
    SAMPLER_BUILDER_setMipmapMode = "Sampler-Builder-setMipmapMode",
    SAMPLER_BUILDER_setAddressModes = "Sampler-Builder-setAddressModes",
    SAMPLER_BUILDER_setMipLodBias = "Sampler-Builder-setMipLodBias",
    SAMPLER_BUILDER_setMaxAnisotropy = "Sampler-Builder-setMaxAnisotropy",
    SAMPLER_BUILDER_unsetMaxAnisotropy = "Sampler-Builder-unsetMaxAnisotropy",
    SAMPLER_BUILDER_setCompareOp = "Sampler-Builder-setCompareOp",
    SAMPLER_BUILDER_unsetCompareOp = "Sampler-Builder-unsetCompareOp",
    SAMPLER_BUILDER_setLod = "Sampler-Builder-setLod",
    SAMPLER_BUILDER_setBorderColor = "Sampler-Builder-setBorderColor",
    SAMPLER_BUILDER_enableUnnormalizedCoordinates = "Sampler-Builder-enableUnnormalizedCoordinates",
    SAMPLER_BUILDER_disableUnnormalizedCoordinates = "Sampler-Builder-disableUnnormalizedCoordinates",
    SAMPLER_BUILDER_getResult = "Sampler-Builder-getResult",
    SAMPLER_BUILDER_reset = "Sampler-Builder-reset",

    // SAMPLER
    SAMPLER = "Sampler",
    SAMPLER_Constructor = "Sampler-Constructor",
    SAMPLER_getSamplerHandle = "Sampler-getSamplerHandle",

    // MEMORY
    MEMORY = "Memory",
    MEMORY_Constructor = "Memory-Constructor",
    MEMORY_getMemoryHandle = "Memory-getMemoryHandle",
    MEMORY_map = "Memory-map",
    MEMORY_unmap = "Memory-unmap",
    MEMORY_getData = "Memory-getData",
    MEMORY_flush = "Memory-flush",
    MEMORY_invalidate = "Memory-invalidate",

    // SEMAPHORE
    SEMAPHORE = "Semaphore",
    SEMAPHORE_Constructor = "Semaphore-Constructor",
    SEMAPHORE_getSemaphoreHandle = "Semaphore-getSemaphoreHandle",

    // FENCE
    FENCE = "Fence",
    FENCE_Constructor = "Fence-Constructor",
    FENCE_getFenceHandle = "Fence-getFenceHandle",
    FENCE_waitFor = "Fence-waitFor",
    FENCE_reset = "Fence-reset",
    FENCE_s_waitForAll = "Fence-s_waitForAll",
    FENCE_s_resetAll = "Fence-s_resetAll",

    // SHADER MODULE
    SHADER_MODULE = "Shader-Module",
    SHADER_MODULE_Constructor = "Shader-Module-Constructor",
    SHADER_MODULE_getShaderModuleHandle = "Shader-Module-getShaderModuleHandle",
    SHADER_MODULE_getDescriptorSetLayouts = "Shader-Module-getDescriptorSetLayouts",
    SHADER_MODULE_getDescriptorPool = "Shader-Module-getDescriptorPool",

    // DESCRIPTOR SET LAYOUT BUILDER
    DESCRIPTOR_SET_LAYOUT_BUILDER = "Descriptor-Set-Layout-Builder",
    DESCRIPTOR_SET_LAYOUT_BUILDER_Constructor = "Descriptor-Set-Layout-Builder-Constructor",
    DESCRIPTOR_SET_LAYOUT_BUILDER_setLogicalDevice = "Descriptor-Set-Layout-Builder-setLogicalDevice",
    DESCRIPTOR_SET_LAYOUT_BUILDER_addBinding = "Descriptor-Set-Layout-Builder-addBinding",
    DESCRIPTOR_SET_LAYOUT_BUILDER_getResult = "Descriptor-Set-Layout-Builder-getResult",
    DESCRIPTOR_SET_LAYOUT_BUILDER_reset = "Descriptor-Set-Layout-Builder-reset",

    // DESCRIPTOR SET LAYOUT
    DESCRIPTOR_SET_LAYOUT = "Descriptor-Set-Layout",
    DESCRIPTOR_SET_LAYOUT_Constructor = "Descriptor-Set-Layout-Constructor",
    DESCRIPTOR_SET_LAYOUT_getDescriptorSetLayoutHandle = "Descriptor-Set-Layout-getDescriptorSetLayoutHandle",
    DESCRIPTOR_SET_LAYOUT_getBindings = "Descriptor-Set-Layout-getBindings",

    // DESCRIPTOR POOL BUILDER
    DESCRIPTOR_POOL_BUILDER = "Descriptor-Pool-Builder",
    DESCRIPTOR_POOL_BUILDER_Constructor = "Descriptor-Pool-Builder-Constructor",
    DESCRIPTOR_POOL_BUILDER_setLogicalDevice = "Descriptor-Pool-Builder-setLogicalDevice",
    DESCRIPTOR_POOL_BUILDER_setFlags = "Descriptor-Pool-Builder-setFlags",
    DESCRIPTOR_POOL_BUILDER_addSet = "Descriptor-Pool-Builder-addSet",
    DESCRIPTOR_POOL_BUILDER_getResult = "Descriptor-Pool-Builder-getResult",
    DESCRIPTOR_POOL_BUILDER_reset = "Descriptor-Pool-Builder-reset",

    // DESCRIPTOR POOL
    DESCRIPTOR_POOL = "Descriptor-Pool",
    DESCRIPTOR_POOL_Constructor = "Descriptor-Pool-Constructor",
    DESCRIPTOR_POOL_getDescriptorPoolHandle = "Descriptor-Pool-getDescriptorPoolHandle",
    DESCRIPTOR_POOL_allocateDescriptorSet = "Descriptor-Pool-allocateDescriptorSet",
    DESCRIPTOR_POOL_getDescriptorSets = "Descriptor-Pool-getDescriptorSets",
    DESCRIPTOR_POOL_getDescriptorSet = "Descriptor-Pool-getDescriptorSet",
    DESCRIPTOR_POOL_freeDescriptorSets = "Descriptor-Pool-freeDescriptorSets",
    DESCRIPTOR_POOL_reset = "Descriptor-Pool-reset",

    // DESCRIPTOR SET
    DESCRIPTOR_SET = "Descriptor-Set",
    DESCRIPTOR_SET_Constructor = "Descriptor-Set-Constructor",
    DESCRIPTOR_SET_getDescriptorSetHandle = "Descriptor-Set-getDescriptorSetHandle",
    DESCRIPTOR_SET_getLayout = "Descriptor-Set-getLayout",
    DESCRIPTOR_SET_getName = "Descriptor-Set-getName",
    DESCRIPTOR_SET_writeImage = "Descriptor-Set-writeImage",
    DESCRIPTOR_SET_writeBuffer = "Descriptor-Set-writeBuffer",
    DESCRIPTOR_SET_writeTexelBufferView = "Descriptor-Set-writeTexelBufferView",
    DESCRIPTOR_SET_copy = "Descriptor-Set-copy",

    // PIPELINE BUILDER
    PIPELINE_BUILDER = "Pipeline-Builder",
    PIPELINE_BUILDER_Constructor = "Pipeline-Builder-Constructor",
    PIPELINE_BUILDER_setLogicalDevice = "Pipeline-Builder-setLogicalDevice",
    PIPELINE_BUILDER_setFlags = "Pipeline-Builder-setFlags",
    PIPELINE_BUILDER_addPushConstant = "Pipeline-Builder-addPushConstant",
    PIPELINE_BUILDER_setPipelineCache = "Pipeline-Builder-setPipelineCache",
    PIPELINE_BUILDER_setBasePipeline = "Pipeline-Builder-setBasePipeline",
    PIPELINE_BUILDER_reset = "Pipeline-Builder-reset",

    // PIPELINE LAYOUT
    PIPELINE_LAYOUT = "Pipeline-Layout",
    PIPELINE_LAYOUT_PUSH_CONSTANT = "Pipeline-Layout-Push-Constant",
    PIPELINE_LAYOUT_Constructor = "Pipeline-Layout-Constructor",
    PIPELINE_LAYOUT_getPipelineLayoutHandle = "Pipeline-Layout-getPipelineLayoutHandle",
    PIPELINE_LAYOUT_pushConstantData = "Pipeline-Layout-pushConstantData",

    // PIPELINE
    PIPELINE = "Pipeline",
    PIPELINE_PIPELINE_SHADER_STAGE = "Pipeline-Pipeline-Shader-Stage",
    PIPELINE_Constructor = "Pipeline-Constructor",
    PIPELINE_getPipelineHandle = "Pipeline-getPipelineHandle",
    PIPELINE_getPipelineLayout = "Pipeline-getPipelineLayout",
    PIPELINE_bindToCommandBuffer = "Pipeline-bindToCommandBuffer",
    PIPELINE_getCommandBuffer = "Pipeline-getCommandBuffer",
    PIPELINE_bindDescriptorSets = "Pipeline-bindDescriptorSets",
    PIPELINE_getDescriptorSets = "Pipeline-getDescriptorSets",
    PIPELINE_getDescriptorSet = "Pipeline-getDescriptorSet",
    PIPELINE_pushConstantData = "Pipeline-pushConstantData",

    // COMPUTE PIPELINE
    COMPUTE_PIPELINE = "Compute-Pipeline",
    COMPUTE_PIPELINE_Constructor = "Compute Pipeline-Constructor",

    // COMPUTE PIPELINE BUILDER
    COMPUTE_PIPELINE_BUILDER = "Compute-Pipeline-Builder",
    COMPUTE_PIPELINE_BUILDER_Constructor = "Compute-Pipeline-Builder-Constructor",
    COMPUTE_PIPELINE_BUILDER_setShaderStage = "Compute-Pipeline-Builder-setShaderStage",
    COMPUTE_PIPELINE_BUILDER_getResult = "Compute-Pipeline-Builder-getResult",
    COMPUTE_PIPELINE_BUILDER_reset = "Compute-Pipeline-Builder-reset",

    // RENDER PASS
    RENDER_PASS = "Render-Pass",
    RENDER_PASS_Constructor = "Render-Pass-Constructor",
    RENDER_PASS_getRenderPassHandle = "Render-Pass-getRenderPassHandle",
    RENDER_PASS_getAttachments = "Render-Pass-getAttachments",
    RENDER_PASS_getSubpasses = "Render-Pass-getSubpasses",
    RENDER_PASS_getDependencies = "Render-Pass-getDependencies",
    RENDER_PASS_begin = "Render-Pass-begin",
    RENDER_PASS_end = "Render-Pass-end",

    // RENDER PASS BUILDER
    RENDER_PASS_BUILDER = "Render-Pass-Builder",
    RENDER_PASS_BUILDER_Constructor = "Render-Pass-Builder-Constructor",
    RENDER_PASS_BUILDER_setLogicalDevice = "Render-Pass-Builder-setLogicalDevice",
    RENDER_PASS_BUILDER_addAttachment = "Render-Pass-Builder-addAttachment",
    RENDER_PASS_BUILDER_addInputAttachment = "Render-Pass-Builder-addInputAttachment",
    RENDER_PASS_BUILDER_addColorAttachment = "Render-Pass-Builder-addColorAttachment",
    RENDER_PASS_BUILDER_setDepthStencilAttachment = "Render-Pass-Builder-setDepthStencilAttachment",
    RENDER_PASS_BUILDER_resolveCurrentAttachments = "Render-Pass-Builder-resolveCurrentAttachments",
    RENDER_PASS_BUILDER_constructSubpass = "Render-Pass-Builder-constructSubpass",
    RENDER_PASS_BUILDER_addDependency = "Render-Pass-Builder-addDependency",
    RENDER_PASS_BUILDER_getResult = "Render-Pass-Builder-getResult",
    RENDER_PASS_BUILDER_reset = "Render-Pass-Builder-reset",

    // FRAMEBUFFER
    FRAMEBUFFER = "Framebuffer",
    FRAMEBUFFER_Constructor = "Framebuffer-Constructor",
    FRAMEBUFFER_getFramebufferHandle = "Framebuffer-getFramebufferHandle",
    FRAMEBUFFER_getExtent = "Framebuffer-getExtent",
    FRAMEBUFFER_getLayers = "Framebuffer-getLayers",

    // GRAPHICS PIPELINE BUILDER
    GRAPHICS_PIPELINE_BUILDER = "Graphics-Pipeline-Builder",

    // GRAPHICS PIPELINE
    GRAPHICS_PIPELINE = "Graphics-Pipeline",
    GRAPHICS_PIPELINE_Constructor = "Graphics-Pipeline-Constructor",
    GRAPHICS_PIPELINE_getRenderPass = "Graphics-Pipeline-getRenderPass",

    ASSET_MANAGER = "Asset-Manager",
}
