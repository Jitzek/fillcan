#pragma once

// fillcan
#include <fillcan/graphics/texture.hpp>

// std
#include <memory>
#include <string>
#include <vector>

namespace fillcan {
    class LogicalDevice;
    class DescriptorSetLayout;
    class DescriptorSet;
    class AssetManager {
      private:
        std::vector<std::unique_ptr<Texture>> upTextures = {};

      public:
        AssetManager();
        ~AssetManager();

        void createTexture(LogicalDevice* pLogicalDevice, std::string fileName);
        std::vector<std::unique_ptr<Texture>>& getTextures();
        Texture* getTexture(int index);
        std::vector<std::unique_ptr<DescriptorSetLayout>> getTextureDescriptorSetLayouts(LogicalDevice* pLogicalDevice, unsigned int binding);
        void writeTexturesToDescriptorSet(LogicalDevice* pLogicalDevice, DescriptorSet* pDescriptorSet);
    };
} // namespace fillcan