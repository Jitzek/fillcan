
// fillcan
#include <fillcan/graphics/sampler.hpp>

namespace fillcan {
    Sampler::Sampler() {}
    Sampler::~Sampler() {}

    VkSampler Sampler::getSamplerHandle() { return this->hSampler; }
} // namespace fillcan