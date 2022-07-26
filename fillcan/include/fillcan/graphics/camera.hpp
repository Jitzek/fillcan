#pragma once

// fillcan
#include <fillcan/memory/buffer.hpp>
#include <fillcan/memory/memory.hpp>

// glm
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#define GLM_FORCE_RADIANS
#include <glm/detail/type_mat.hpp>
#include <glm/detail/type_vec.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// std
#include <memory>
#include <vector>

namespace fillcan {
    class LogicalDevice;
    class DescriptorSetLayout;
    class DescriptorSet;
    class GraphicsPipeline;

    // The worldobjects' relation to the camera
    struct Projection {
        float fov = 90.f;
        float aspect = 4.f / 3.f;
        float near = 0.1f;
        float far = 100.f;

        glm::mat4 mat4() {
            glm::mat4 projection = glm::perspective(glm::radians(fov), aspect, near, far);
            projection[1][1] *= -1;
            return projection;
        }
    };

    // The camera's relation to the world
    struct View {
        glm::vec3 position = glm::vec3(0.f);
        glm::vec3 direction = glm::vec3(0.f);

        glm::mat4 mat4() {
            glm::vec3 _position = position * glm::vec3(-1.f, 1.f, 1.f);
            glm::vec3 _direction = direction * glm::vec3(-1.f, 1.f, 1.f);
            glm::mat4 view = glm::lookAt(_position, _position + _direction, glm::vec3(0, 1, 0));
            return view;
        }
    };

    struct ViewProjection {
        View view;
        Projection projection;
    };

    class Camera {
      private:
        struct ViewProjectionBufferData {
            glm::mat4 view;
            glm::mat4 projection;
        };
        LogicalDevice* pLogicalDevice;
        std::vector<std::unique_ptr<Buffer>> upUniformBuffers = {};
        std::vector<std::unique_ptr<Memory>> upUniformBufferMemories = {};
        ViewProjection vp = {.view = {}, .projection = {}};
        std::vector<DescriptorSet*> pDescriptorSets = {};

        unsigned int currentIndex = 0;
        unsigned int bufferCount = 1;

        glm::vec3 position = glm::vec3(0.f);
        glm::vec3 rotation = glm::vec3(0.f);

      public:
        Camera(LogicalDevice* pLogicalDevice, unsigned int bufferCount);
        ~Camera();

        void bindDescriptorSets(std::vector<DescriptorSet*> pDescriptorSets);
        void updateBuffer(GraphicsPipeline* pPipeline);

        std::vector<std::unique_ptr<DescriptorSetLayout>> getDescriptorSetLayouts(unsigned int binding);

        ViewProjection* getVP();

        void setView(glm::vec3 position, glm::vec3 direction);
        void setProjection(float fov, float ratio, float near, float far);

        void setFov(float fov);
        void setNear(float near);
        void setFar(float far);
        void setAspect(float aspect);

        void setPositionXYZ(glm::vec3 position);
        void setDirectionXYZ(glm::vec3 direction);
        void translateXYZ(glm::vec3 translation);
        void rotateXYZ(glm::vec3 rotation);
        void lookAt(glm::vec3 lookAt);
    };
} // namespace fillcan