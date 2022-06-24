
#include "app.hpp"

// vulkan
#include "fillcan/graphics/game_object.hpp"
#include "fillcan/graphics/model.hpp"
#include "fillcan/graphics/texture.hpp"
#include "glm/detail/func_common.hpp"
#include "glm/gtc/constants.hpp"
#include "shaderc/shaderc.h"
#include "vulkan/vulkan_core.h"

// fillcan
#include "fillcan/commands/command_buffer.hpp"
#include "fillcan/commands/command_recording.hpp"
#include "fillcan/graphics/framebuffer.hpp"
#include "fillcan/graphics/graphics_pipeline.hpp"
#include "fillcan/graphics/render_pass.hpp"
#include "fillcan/graphics/render_pass_builder.hpp"
#include "fillcan/graphics/swapchain.hpp"
#include "fillcan/memory/buffer.hpp"
#include "fillcan/memory/buffer_director.hpp"
#include "fillcan/memory/fence.hpp"
#include "fillcan/memory/image_view.hpp"
#include "fillcan/memory/memory.hpp"
#include "fillcan/memory/semaphore.hpp"
#include "fillcan/shader/descriptor_pool.hpp"
#include "fillcan/shader/descriptor_pool_builder.hpp"
#include "fillcan/shader/descriptor_set_layout.hpp"
#include "fillcan/shader/shader_module.hpp"
#include <exception>
#include <fillcan/graphics/asset_manager.hpp>
#include <fillcan/graphics/graphics_pipeline_builder.hpp>
#include <fillcan/shader/pipeline.hpp>
#include <fillcan/shader/pipeline_layout.hpp>

// std
#include <array>
#include <chrono>
#include <cstddef>
#include <cstring>
#include <fstream>
#include <functional>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <thread>
#include <utility>
#include <vector>

// glm
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/detail/type_vec.hpp>
#include <glm/glm.hpp>

namespace simple_model {
    App::App() {}
    App::~App() {}

    void App::run() {
        std::string name = "Model Application";
        std::cout << "Running App \"" << name << "\"\n";

        VkPhysicalDeviceFeatures requiredDeviceFeatures = {};
        requiredDeviceFeatures.samplerAnisotropy = true;
        this->upFillcan = std::make_unique<fillcan::FillcanGraphics>(name.c_str(), 1.0, 800, 600, requiredDeviceFeatures);
        upFillcan->selectDevice(0);
        std::cout << "Using Device: " << upFillcan->getCurrentDevice()->getPhysicalDevice()->getProperties().deviceName << "\n";

        this->upFillcan->createSwapchain(2, VK_PRESENT_MODE_IMMEDIATE_KHR);

        this->createRenderPass();

        this->preloadTextures();

        std::vector<std::unique_ptr<fillcan::DescriptorSetLayout>> upFragmentDescriptorSetLayouts = createFragmentDescriptorSetLayouts();
        std::unique_ptr<fillcan::DescriptorPool> upFragmentDescriptorPool = createDescriptorPool(upFragmentDescriptorSetLayouts);

        this->upVertexShaderModule =
            this->upFillcan->createShaderModule(this->APP_DIR + "/shaders", "simple.vert", shaderc_vertex_shader, {}, nullptr, true, false);

        this->upFragmentShaderModule =
            this->upFillcan->createShaderModule(this->APP_DIR + "/shaders", "simple.frag", shaderc_fragment_shader,
                                                std::move(upFragmentDescriptorSetLayouts), std::move(upFragmentDescriptorPool), true, false);

        this->createGraphicsPipeline(upVertexShaderModule.get(), upFragmentShaderModule.get());

        for (size_t i = 0; i < this->upFillcan->getSwapchain()->getImageCount(); i++) {
            this->pCommandRecordings.push_back(this->upFillcan->getCurrentDevice()->getGraphicsQueue()->createRecording(1, 0));
            this->pCommandRecordings[i]->createFence(this->upFillcan->getCurrentDevice(), VK_FENCE_CREATE_SIGNALED_BIT);
        }

        this->loadGameObjects();

        this->upFramebuffers.resize(this->upFillcan->getSwapchain()->getImageCount());

        upFillcan->MainLoop(std::bind(&App::update, this, std::placeholders::_1));
    }

    void App::update(double deltaTime) {
        // Recreate swapchain if window was resized
        if (this->upFillcan->getWindow()->wasResized()) {
            this->upFillcan->recreateSwapchain();
            return;
        }

        // Get current command recording
        fillcan::CommandRecording* pCurrentGraphicsCommandRecording = this->pCommandRecordings[this->currentFrameIndex];
        fillcan::CommandBuffer* pCurrentGraphicsCommandBuffer = pCurrentGraphicsCommandRecording->pPrimaryCommandBuffers[0];

        // Wait for the command recording to have finished
        pCurrentGraphicsCommandRecording->waitForFence();
        pCurrentGraphicsCommandRecording->reset();

        // Start new command recording
        pCurrentGraphicsCommandBuffer->begin(VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT);

        fillcan::SwapchainImage swapchainImage = this->upFillcan->getSwapchain()->getNextImage();

        if (swapchainImage.outOfDate) {
            return;
        }

        // Define semaphore for when image is ready to be rendered to
        pCurrentGraphicsCommandRecording->pWaitSemaphores.emplace_back(swapchainImage.pSemaphoreImageReady);
        // Define the stage(s) at where the semaphore should be waited for
        pCurrentGraphicsCommandRecording->waitDstStageMask = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
        // Define semphore for when image is ready to present
        pCurrentGraphicsCommandRecording->pSignalSemaphores.push_back(swapchainImage.pSemaphorePresentReady);

        /*
            Create framebuffer
        */
        // Create imageviews which will be used as attachments for the framebuffer
        std::vector<fillcan::ImageView*> pAttachments = {swapchainImage.pSwapchainImageView, swapchainImage.pDepthBufferImageView};
        this->upFramebuffers.at(this->currentFrameIndex) = std::move(std::make_unique<fillcan::Framebuffer>(
            this->upFillcan->getCurrentDevice(), this->upRenderPass.get(), pAttachments, this->upFillcan->getSwapchain()->getImageExtent().width,
            this->upFillcan->getSwapchain()->getImageExtent().height, this->upFillcan->getSwapchain()->getImageArrayLayers()));
        /* */

        std::vector<VkClearValue> clearValues = {{.color = {{0.0f, 0.0f, 0.0f, 1.0f}}}, {.depthStencil = {1.0f, 0}}};
        this->upRenderPass->begin(pCurrentGraphicsCommandBuffer, this->upFramebuffers.at(this->currentFrameIndex).get(), &clearValues);

        VkViewport viewport = {.x = 0.0f,
                               .y = 0.0f,
                               .width = static_cast<float>(this->upFillcan->getSwapchain()->getImageExtent().width),
                               .height = static_cast<float>(this->upFillcan->getSwapchain()->getImageExtent().height),
                               .minDepth = 0.0f,
                               .maxDepth = 1.0f};
        VkRect2D scissor = {.offset = {0, 0}, .extent = this->upFillcan->getSwapchain()->getImageExtent()};
        vkCmdSetViewport(pCurrentGraphicsCommandBuffer->getCommandBufferHandle(), 0, 1, &viewport);
        vkCmdSetScissor(pCurrentGraphicsCommandBuffer->getCommandBufferHandle(), 0, 1, &scissor);

        this->renderGameObjects(pCurrentGraphicsCommandBuffer);

        this->upRenderPass->end();

        pCurrentGraphicsCommandRecording->endAll();
        pCurrentGraphicsCommandRecording->submit();

        if (!this->upFillcan->getSwapchain()->present(&swapchainImage, {swapchainImage.pSemaphorePresentReady->getSemaphoreHandle()})) {
            return;
        }

        this->currentFrameIndex = (currentFrameIndex + 1) % this->upFillcan->getSwapchain()->getImageCount();
    }

    void App::preloadTextures() {
        this->upFillcan->getAssetManager()->createTexture(this->upFillcan->getCurrentDevice(), this->APP_DIR + "/textures/viking_room.png");
    }

    void App::loadGameObjects() {
        std::shared_ptr<fillcan::Model> spModel =
            std::make_unique<fillcan::Model>(this->upFillcan->getCurrentDevice(), this->APP_DIR + "/models/viking_room.obj");
        spModel->setTexture(this->upFillcan->getAssetManager()->getTexture(0));

        fillcan::GameObject cubeGameObject = fillcan::GameObject::createGameObject();
        cubeGameObject.transform.translation = {0.0f, 0.f, 0.5};
        cubeGameObject.transform.scale = {0.5f, 0.5f, 0.5f};
        cubeGameObject.transform.rotation.x = 1.2f;
        cubeGameObject.transform.rotation.y = 2.5f;
        cubeGameObject.transform.rotation.z = 0.65f;
        cubeGameObject.model = spModel;
        gameObjects.push_back(std::move(cubeGameObject));

        this->upFillcan->getAssetManager()->writeTexturesToDescriptorSet(
            this->upFillcan->getCurrentDevice(), this->upFragmentShaderModule->getDescriptorPool()->getDescriptorSet("TexturesDescriptorSet"));
    }

    void App::renderGameObjects(fillcan::CommandBuffer* pCommandBuffer) {
        this->upGraphicsPipeline->bindToCommandBuffer(pCommandBuffer);
        this->upGraphicsPipeline->bindDescriptorSets();
        for (fillcan::GameObject& gameObject : this->gameObjects) {
            // gameObject.transform.rotation.y =
            //     glm::mod(gameObject.transform.rotation.y + (0.5f * this->upFillcan->deltaTimef()), glm::two_pi<float>());
            // gameObject.transform.rotation.x =
            //     glm::mod(gameObject.transform.rotation.x + (0.25f * this->upFillcan->deltaTimef()), glm::two_pi<float>());
            SimplePushConstantData data = {.transform = gameObject.transform.mat4(),
                                           .color = gameObject.color,
                                           .textureIndex =
                                               gameObject.model->getTexture() != nullptr ? gameObject.model->getTexture()->getIndex() : -1};
            std::unique_ptr<SimplePushConstantData> simplePushConstantData = std::make_unique<SimplePushConstantData>(data);
            this->upGraphicsPipeline->pushConstantData("SimplePushConstant", std::move(simplePushConstantData));

            gameObject.model->bind(pCommandBuffer);
            gameObject.model->draw();
            // gameObject.model->drawIndexed();
        }
    }

    void App::createRenderPass() {
        fillcan::RenderPassBuilder renderPassBuilder = {};
        renderPassBuilder.setLogicalDevice(this->upFillcan->getCurrentDevice());

        // Add attachment for subpass 1 describing the swapchain image
        unsigned int swapChainAttachmentIndex = renderPassBuilder.addAttachment({.flags = 0,
                                                                                 .format = this->upFillcan->getSwapchain()->getSurfaceFormat().format,
                                                                                 .samples = VK_SAMPLE_COUNT_1_BIT,
                                                                                 .loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR,
                                                                                 .storeOp = VK_ATTACHMENT_STORE_OP_STORE,
                                                                                 .stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
                                                                                 .stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE,
                                                                                 .initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,
                                                                                 .finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR});
        // Define attachment as a color attachment
        renderPassBuilder.addColorAttachment(swapChainAttachmentIndex, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL, false);

        // Add attachment for subpass 1 describing the depth image
        unsigned int depthImageAttachmentIndex =
            renderPassBuilder.addAttachment({.flags = 0,
                                             .format = this->upFillcan->getCurrentDevice()->getPhysicalDevice()->findSupportedFormat(
                                                 {VK_FORMAT_D32_SFLOAT, VK_FORMAT_D32_SFLOAT_S8_UINT, VK_FORMAT_D24_UNORM_S8_UINT},
                                                 VK_IMAGE_TILING_OPTIMAL, VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT),
                                             .samples = VK_SAMPLE_COUNT_1_BIT,
                                             .loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR,
                                             .storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE,
                                             .stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
                                             .stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE,
                                             .initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,
                                             .finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL});
        // Define attachment as a depthstencil attachment
        renderPassBuilder.setDepthStencilAttachment(depthImageAttachmentIndex, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL, false);

        // Construct subpass 1, this will combine the attachment described before into a new subpass
        unsigned int subpassIndex = renderPassBuilder.constructSubpass();

        // Add a dependency for subpass 1 to make sure the subpass waits for the previous stages before executing
        renderPassBuilder.addDependency({.srcSubpass = VK_SUBPASS_EXTERNAL,
                                         .dstSubpass = subpassIndex,
                                         .srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT,
                                         .dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT,
                                         .srcAccessMask = 0,
                                         .dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT});

        this->upRenderPass = renderPassBuilder.getResult();
    }

    std::vector<std::unique_ptr<fillcan::DescriptorSetLayout>> App::createFragmentDescriptorSetLayouts() {
        std::vector<std::unique_ptr<fillcan::DescriptorSetLayout>> upDescriptorSetLayouts =
            this->upFillcan->getAssetManager()->getTextureDescriptorSetLayouts(this->upFillcan->getCurrentDevice(), 1);

        return std::move(upDescriptorSetLayouts);
    }

    std::unique_ptr<fillcan::DescriptorPool>
    App::createDescriptorPool(std::vector<std::unique_ptr<fillcan::DescriptorSetLayout>>& upDescriptorSetLayouts) {
        fillcan::DescriptorPoolBuilder descriptorPoolBuilder{};
        descriptorPoolBuilder.setLogicalDevice(this->upFillcan->getCurrentDevice());
        descriptorPoolBuilder.setFlags(VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT);
        descriptorPoolBuilder.addSet(upDescriptorSetLayouts.at(0).get(), "TexturesDescriptorSet");
        return std::move(descriptorPoolBuilder.getResult());
    }

    void App::createGraphicsPipeline(fillcan::ShaderModule* pVertexShaderModule, fillcan::ShaderModule* pFragmentShaderModule) {
        fillcan::GraphicsPipelineBuilder graphicsPipelineBuilder{};
        graphicsPipelineBuilder.setLogicalDevice(this->upFillcan->getCurrentDevice());
        graphicsPipelineBuilder.addShaderStage({.stage = VK_SHADER_STAGE_VERTEX_BIT, .pShaderModule = pVertexShaderModule, .name = "main"});
        graphicsPipelineBuilder.addShaderStage({.stage = VK_SHADER_STAGE_FRAGMENT_BIT, .pShaderModule = pFragmentShaderModule, .name = "main"});

        graphicsPipelineBuilder.addPushConstant(
            "SimplePushConstant",
            {.stageFlags = VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT, .offset = 0, .size = sizeof(SimplePushConstantData)});

        graphicsPipelineBuilder.setInputAssemblyState({.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST, .primitiveRestartEnable = VK_FALSE});

        // Describe the vertex shader
        graphicsPipelineBuilder.setVertexInputState(
            {fillcan::Model::Vertex::getBindingDescriptions(),
             {fillcan::Model::Vertex::getPositionAttributeDescription(0), fillcan::Model::Vertex::getColorAttributeDescription(1),
              fillcan::Model::Vertex::getTextureCoordinateAttributeDescription(2)}});

        // The viewports and scissors are dynamic, but the amount of viewports and scissors should still be defined
        std::vector<VkViewport> viewports = {};
        viewports.resize(1);
        std::vector<VkRect2D> scissors = {};
        scissors.resize(1);
        graphicsPipelineBuilder.addViewportState({viewports, scissors});

        graphicsPipelineBuilder.setRasterizationState({.depthClampEnable = VK_FALSE,
                                                       .rasterizerDiscardEnable = VK_FALSE,
                                                       .polygonMode = VK_POLYGON_MODE_FILL,
                                                       .cullmode = VK_CULL_MODE_NONE,
                                                       .frontFace = VK_FRONT_FACE_CLOCKWISE,
                                                       .depthBiasEnable = VK_FALSE,
                                                       .depthBiasConstantFactor = 0.0f,
                                                       .depthBiasClamp = 0.0f,
                                                       .depthBiasSlopeFactor = 0.0f,
                                                       .lineWidth = 1.0f});

        graphicsPipelineBuilder.setMultisampleState({.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT,
                                                     .sampleShadingEnable = VK_FALSE,
                                                     .minSampleShading = 1.0f,
                                                     .sampleMask = {},
                                                     .alphaToCoverageEnable = VK_FALSE,
                                                     .alphaToOneEnable = VK_FALSE});

        // Enable z-testing
        graphicsPipelineBuilder.setDepthStencilState({.depthTestEnable = VK_TRUE,
                                                      .depthWriteEnable = VK_TRUE,
                                                      .depthCompareOp = VK_COMPARE_OP_LESS,
                                                      .depthBoundsTestEnable = VK_FALSE,
                                                      .stencilTestEnable = VK_FALSE,
                                                      .front = {},
                                                      .back = {},
                                                      .minDepthBounds = 0.0f,
                                                      .maxDepthBounds = 1.0f});

        VkPipelineColorBlendAttachmentState colorBlendAttachment = {};
        colorBlendAttachment.blendEnable = VK_FALSE;
        colorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
        colorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
        colorBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD;
        colorBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
        colorBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
        colorBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD;
        colorBlendAttachment.colorWriteMask =
            VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
        std::vector<VkPipelineColorBlendAttachmentState> colorBlendAttachments = {colorBlendAttachment};
        graphicsPipelineBuilder.setColorBlendState({.logicOpEnable = VK_FALSE,
                                                    .logicOp = VK_LOGIC_OP_COPY,
                                                    .attachments = colorBlendAttachments,
                                                    .blendConstants = std::array<float, 4>{0.0f, 0.0f, 0.0f, 0.0f}});

        // Set the viewports and scissors to dynamic to allow for window resizing
        std::vector<VkDynamicState> dynamicStates = {VK_DYNAMIC_STATE_VIEWPORT, VK_DYNAMIC_STATE_SCISSOR};
        graphicsPipelineBuilder.setDynamicState({.dynamicStates = dynamicStates});
        graphicsPipelineBuilder.setRenderPass(this->upRenderPass.get());

        this->upGraphicsPipeline = graphicsPipelineBuilder.getResult();
    }
} // namespace simple_model