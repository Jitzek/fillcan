
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

        VkDeviceSize bufferSize = sizeof(ModelViewProjection);
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
        memcpy(*ppData, &this->mvp, sizeof(this->mvp));
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

    ModelViewProjection* Camera::getMVP() { return &this->mvp; }

    void Camera::SetModel(glm::mat4 identityMatrix) { this->mvp.model = identityMatrix; }

    void Camera::SetView(glm::vec3 position, glm::vec3 lookAt, glm::vec3 direction) { this->mvp.view = glm::lookAt(position, lookAt, direction); }

    void Camera::SetProjection(float fov, float ratio, float near, float far) {
        this->mvp.projection = glm::perspective(glm::radians(fov), ratio, near, far);
        this->mvp.projection[1][1] *= -1;
    }

} // namespace fillcan