
// fillcan
#include <fillcan/graphics/game_object.hpp>

namespace fillcan {
    GameObject::~GameObject() {}

    GameObject::uuid_t GameObject::getUuid() { return this->uuid; }
} // namespace fillcan