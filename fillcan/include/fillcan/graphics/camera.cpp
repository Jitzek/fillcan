
// fillcan
#include "fillcan/memory/buffer_director.hpp"
#include "fillcan/shader/descriptor_set.hpp"
#include "fillcan/shader/descriptor_set_layout.hpp"
#include "fillcan/shader/descriptor_set_layout_builder.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <cstddef>
#include <fillcan/graphics/camera.hpp>
#include <memory>
#include <string.h>

namespace fillcan {
    Camera::Camera(LogicalDevice* pLogicalDevice, unsigned int bufferCount) : pLogicalDevice(pLogicalDevice) {
        VkDeviceSize bufferSize = sizeof(ModelViewProjection);
        this->upUniformBuffers.reserve(bufferCount);
        this->upUniformBufferMemories.reserve(bufferCount);

        BufferDirector bufferDirector{};
        for (size_t i = 0; i < bufferCount; i++) {
            std::unique_ptr<Buffer> upUniformBuffer = bufferDirector.makeUniformBuffer(pLogicalDevice, bufferSize);
            std::unique_ptr<Memory> upUniformBufferMemory =
                std::make_unique<Memory>(pLogicalDevice, upUniformBuffer.get(), VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT);
            upUniformBuffer->bindMemory(upUniformBufferMemory.get());
            this->upUniformBuffers.push_back(std::move(upUniformBuffer));
            this->upUniformBufferMemories.push_back(std::move(upUniformBufferMemory));
        }
    }

    Camera::~Camera() {}

    void Camera::writeBufferToDescriptorSet(DescriptorSet* pDescriptorSet) {
        for (size_t i = 0; i < this->upUniformBuffers.size(); i++) {
            pDescriptorSet->writeBuffer(pDescriptorSet->getLayout()->getBindings()[0], this->upUniformBuffers.at(i).get());
        }
    }

    void Camera::updateBuffer(int index) {
        void** ppData = this->upUniformBuffers.at(index)->getMemory()->map();
        memcpy(*ppData, &this->mvp, sizeof(this->mvp));
        this->upUniformBuffers.at(index)->getMemory()->flush();
        this->upUniformBuffers.at(index)->getMemory()->unmap();
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