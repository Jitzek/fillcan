
// fillcan
#include "fillcan/memory/buffer.hpp"
#include "fillcan/memory/buffer_director.hpp"
#include "fillcan/shader/descriptor_set.hpp"
#include "fillcan/shader/descriptor_set_layout.hpp"
#include "fillcan/shader/descriptor_set_layout_builder.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <cstddef>
#include <fillcan/graphics/camera.hpp>
#include <fillcan/graphics/graphics_pipeline.hpp>

// std
#include <memory>
#include <string.h>

namespace fillcan {
    Camera::Camera(LogicalDevice* pLogicalDevice, unsigned int bufferCount, unsigned int maxBufferCount) : pLogicalDevice(pLogicalDevice) {
        this->upUniformBuffers.resize(maxBufferCount);
        this->upUniformBufferMemories.resize(maxBufferCount);

        this->resizeBufferCount(bufferCount);

        VkDeviceSize bufferSize = sizeof(ViewProjectionBufferData);
        BufferDirector bufferDirector{};
        for (size_t i = 0; i < this->upUniformBuffers.size(); i++) {
            std::unique_ptr<Buffer> upUniformBuffer = bufferDirector.makeUniformBuffer(pLogicalDevice, bufferSize);
            std::unique_ptr<Memory> upUniformBufferMemory =
                std::make_unique<Memory>(pLogicalDevice, upUniformBuffer.get(), VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT);
            upUniformBuffer->bindMemory(upUniformBufferMemory.get());
            this->upUniformBuffers.at(i) = std::move(upUniformBuffer);
            this->upUniformBufferMemories.at(i) = std::move(upUniformBufferMemory);
        }
    }

    Camera::~Camera() {}

    void Camera::resizeBufferCount(unsigned int bufferCount) {
        if (bufferCount > this->upUniformBuffers.size())
            bufferCount = static_cast<unsigned int>(this->upUniformBuffers.size());
        this->bufferCount = bufferCount;
    }

    void Camera::bindDescriptorSets(std::vector<DescriptorSet*> pDescriptorSets) {
        this->pDescriptorSets = pDescriptorSets;
        for (size_t i = 0; i < this->upUniformBuffers.size(); i++) {
            this->pDescriptorSets.at(i)->writeBuffer(this->pDescriptorSets.at(i)->getLayout()->getBindings()[0], this->upUniformBuffers.at(i).get());
        }
    }

    void Camera::updateBuffer(GraphicsPipeline* pPipeline, unsigned int firstSet, int index) {
        pPipeline->bindDescriptorSets({this->pDescriptorSets.at(this->currentIndex)}, firstSet);
        this->currentIndex = (this->currentIndex + 1) % this->bufferCount;

        Buffer* pCurrentBuffer = this->upUniformBuffers.at(index).get();
        void** ppData = pCurrentBuffer->getMemory()->map();
        ViewProjectionBufferData mvpBufferData = {.view = this->vp.view.mat4(), .projection = this->vp.projection.mat4()};
        memcpy(*ppData, &mvpBufferData, sizeof(mvpBufferData));
        pCurrentBuffer->getMemory()->flush();
        pCurrentBuffer->getMemory()->unmap();
    }

    std::vector<std::unique_ptr<DescriptorSetLayout>> Camera::getDescriptorSetLayouts(unsigned int binding) {
        std::vector<std::unique_ptr<DescriptorSetLayout>> upDescriptorSetLayouts;
        upDescriptorSetLayouts.reserve(1);

        DescriptorSetLayoutBuilder descriptorSetLayoutBuilder{};
        descriptorSetLayoutBuilder.setLogicalDevice(this->pLogicalDevice);

        // Uniform Buffer
        descriptorSetLayoutBuilder.addBinding(binding, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 1, VK_SHADER_STAGE_VERTEX_BIT);

        upDescriptorSetLayouts.push_back(descriptorSetLayoutBuilder.getResult());

        return std::move(upDescriptorSetLayouts);
    }

    ViewProjection* Camera::getVP() { return &this->vp; }

    void Camera::setView(glm::vec3 position, glm::vec3 direction) { this->vp.view = {.position = position, .direction = direction}; }

    void Camera::setProjection(float fov, float aspect, float near, float far) {
        this->vp.projection = {.fov = fov, .aspect = aspect, .near = near, .far = far};
    }

    // Projection
    void Camera::setFov(float fov) { this->vp.projection.fov = fov; }
    void Camera::setNear(float near) { this->vp.projection.near = near; }
    void Camera::setFar(float far) { this->vp.projection.far = far; }
    void Camera::setAspect(float aspect) { this->vp.projection.aspect = aspect; }

    // View
    void Camera::setPositionXYZ(glm::vec3 position) { this->vp.view.position = position; }
    void Camera::setDirectionXYZ(glm::vec3 direction) { this->vp.view.direction = direction; }
    void Camera::translateXYZ(glm::vec3 translation) { this->vp.view.position += translation; }
    void Camera::rotateXYZ(glm::vec3 rotation) { this->vp.view.direction += rotation; }
    void Camera::lookAt(glm::vec3 lookAt) { this->vp.view.direction = lookAt - this->vp.view.position; }

} // namespace fillcan