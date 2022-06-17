#pragma once

// fillcan
#include <fillcan/graphics/model.hpp>

// uuid
#include <uuid/uuid.h>

// std
#include <memory>
#include <string>

// glm
#include <glm/detail/type_mat.hpp>
#include <glm/detail/type_vec.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace fillcan {
    struct TransformComponent {
        glm::vec3 translation{};
        glm::vec3 scale{1.f, 1.f, 1.f};
        glm::vec3 rotation{};

        glm::mat4 mat4() {
            auto transform = glm::translate(glm::mat4{1.f}, translation);
            transform = glm::scale(transform, scale);

            transform = glm::rotate(transform, rotation.y, {0.f, 1.f, 0.f});
            transform = glm::rotate(transform, rotation.x, {1.f, 0.f, 0.f});
            transform = glm::rotate(transform, rotation.z, {0.f, 0.f, 1.f});

            return transform;
        };
    };

    class GameObject {
        using uuid_t = std::string;

      private:
        uuid_t uuid;
        GameObject(uuid_t uuid) : uuid(uuid) {}

      public:
        static GameObject createGameObject() { return GameObject(uuid::generate_uuid_v4()); }
        ~GameObject();

        GameObject(const GameObject&) = delete;
        GameObject& operator=(const GameObject&) = delete;
        GameObject(GameObject&&) = default;
        GameObject& operator=(GameObject&&) = default;

        uuid_t getUuid();

        std::shared_ptr<Model> model{};
        glm::vec3 color{};
        TransformComponent transform{};
    };
} // namespace fillcan