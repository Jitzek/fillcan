#pragma once

// vulkan
#include "vulkan/vulkan_core.h"

namespace fillcan {
    class Sampler
    {
        private:
            VkSampler hSampler;
        public:
            Sampler();
            ~Sampler();

            VkSampler getSamplerHandle();
    };
}