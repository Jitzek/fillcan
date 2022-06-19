#pragma once

// fillcan
#include "fillcan/memory/memory.hpp"
#include "glm/detail/func_trigonometric.hpp"
#include "glm/detail/type_vec.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <fillcan/memory/buffer.hpp>

#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#define GLM_FORCE_RADIANS
#include <glm/detail/type_mat.hpp>
#include <glm/glm.hpp>

// std
#include <memory>
#include <vector>

namespace fillcan {
    class LogicalDevice;
    class DescriptorSetLayout;
    class DescriptorSet;

    struct ModelViewProjection {
        glm::mat4 model;
        glm::mat4 view;
        glm::mat4 projection;
    };

    class Camera {
      private:
        LogicalDevice* pLogicalDevice;
        std::vector<std::unique_ptr<Buffer>> upUniformBuffers = {};
        std::vector<std::unique_ptr<Memory>> upUniformBufferMemories = {};
        ModelViewProjection mvp = {.model = glm::mat4(0.0f), .view = glm::mat4(0.0f), .projection = glm::mat4(0.0f)};

      public:
        Camera(LogicalDevice* pLogicalDevice, unsigned int bufferCount);
        ~Camera();

        void writeBufferToDescriptorSet(DescriptorSet* pDescriptorSet);
        void updateBuffer(int index);

        std::vector<std::unique_ptr<DescriptorSetLayout>> getDescriptorSetLayouts(unsigned int binding);

        ModelViewProjection* getMVP();

        void SetModel(glm::mat4 identityMatrix);
        void SetView(glm::vec3 position, glm::vec3 lookAt, glm::vec3 direction);
        void SetProjection(float fov, float ratio, float near, float far);
    };
} // namespace fillcan