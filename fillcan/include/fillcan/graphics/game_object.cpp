
// fillcan
#include "glm/gtc/matrix_transform.hpp"
#include <fillcan/graphics/game_object.hpp>
#include <iostream>

#define GLM_ENABLE_EXPERIMENTAL
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#define GLM_FORCE_RADIANS
#include "glm/gtx/string_cast.hpp"

namespace fillcan {
    glm::mat4 TransformComponent::mat4() {
        // auto transform = glm::translate(glm::mat4{1.f}, translation);

        // transform = glm::rotate(transform, rotation.y, {0.f, 1.f, 0.f});
        // transform = glm::rotate(transform, rotation.x, {1.f, 0.f, 0.f});
        // transform = glm::rotate(transform, rotation.z, {0.f, 0.f, 1.f});

        // transform = glm::scale(transform, scale);
        // return transform;
        const float c3 = glm::cos(rotation.z);
        const float s3 = glm::sin(rotation.z);
        const float c2 = glm::cos(rotation.x);
        const float s2 = glm::sin(rotation.x);
        const float c1 = glm::cos(rotation.y);
        const float s1 = glm::sin(rotation.y);
        return glm::mat4{{
                             scale.x * (c1 * c3 + s1 * s2 * s3),
                             scale.x * (c2 * s3),
                             scale.x * (c1 * s2 * s3 - c3 * s1),
                             0.0f,
                         },
                         {
                             scale.y * (c3 * s1 * s2 - c1 * s3),
                             scale.y * (c2 * c3),
                             scale.y * (c1 * c3 * s2 + s1 * s3),
                             0.0f,
                         },
                         {
                             scale.z * (c2 * s1),
                             scale.z * (-s2),
                             scale.z * (c1 * c2),
                             0.0f,
                         },
                         {translation.x, translation.y, translation.z, 1.0f}};
    }

    GameObject::~GameObject() {}

    GameObject::uuid_t GameObject::getUuid() { return this->uuid; }
} // namespace fillcan