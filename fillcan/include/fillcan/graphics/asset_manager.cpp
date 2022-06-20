
// fillcan
#include "fillcan/commands/command_recording.hpp"
#include "fillcan/graphics/texture.hpp"
#include "fillcan/instance/logical_device.hpp"
#include "fillcan/shader/descriptor_set_layout_builder.hpp"
#include <fillcan/graphics/asset_manager.hpp>
#include <fillcan/shader/descriptor_set.hpp>
#include <fillcan/shader/descriptor_set_layout.hpp>

// std
#include <memory>
#include <vector>

namespace fillcan {
    AssetManager::AssetManager() {}

    AssetManager::~AssetManager() {}

    void AssetManager::createTexture(LogicalDevice* pLogicalDevice, std::string fileName) {
        this->upTextures.push_back(std::move(std::make_unique<Texture>(Texture::createTexture(pLogicalDevice, fileName))));
    }

    std::vector<std::unique_ptr<Texture>>& AssetManager::getTextures() { return this->upTextures; }

    Texture* AssetManager::getTexture(int index) { return this->upTextures.at(index).get(); }

    std::vector<std::unique_ptr<DescriptorSetLayout>> AssetManager::getTextureDescriptorSetLayouts(LogicalDevice* pLogicalDevice,
                                                                                                   unsigned int binding) {
        std::vector<std::unique_ptr<fillcan::DescriptorSetLayout>> upDescriptorSetLayouts;
        upDescriptorSetLayouts.reserve(1);

        DescriptorSetLayoutBuilder descriptorSetLayoutBuilder{};
        descriptorSetLayoutBuilder.setLogicalDevice(pLogicalDevice);

        // Combined Image Sampler
        descriptorSetLayoutBuilder.addBinding(binding, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, this->upTextures.size(),
                                              VK_SHADER_STAGE_FRAGMENT_BIT);

        upDescriptorSetLayouts.emplace_back(descriptorSetLayoutBuilder.getResult());

        return std::move(upDescriptorSetLayouts);
    }

    void AssetManager::writeTexturesToDescriptorSet(LogicalDevice* pLogicalDevice, DescriptorSet* pDescriptorSet) {
        std::vector<VkDescriptorImageInfo> descriptorImageInfos = {};
        descriptorImageInfos.reserve(this->upTextures.size());

        for (size_t i = 0; i < this->upTextures.size(); i++) {
            VkDescriptorImageInfo descriptorImageInfo = {.sampler = this->upTextures.at(i)->getSampler()->getSamplerHandle(),
                                                         .imageView = this->upTextures.at(i)->getImageView()->getImageViewHandle(),
                                                         .imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL};
            descriptorImageInfos.push_back(descriptorImageInfo);

            CommandRecording* pCommandRecording = pLogicalDevice->beginSingleTimeCommandRecording(pLogicalDevice->getGraphicsQueue());
            this->upTextures.at(i)->getImage()->transitionImageLayout(pCommandRecording->pPrimaryCommandBuffers[0], VK_IMAGE_LAYOUT_UNDEFINED,
                                                                      VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL, 0, VK_ACCESS_SHADER_READ_BIT,
                                                                      VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT);
            pLogicalDevice->endSingleTimeCommandRecording(pCommandRecording);

            // Same result, it's the same binding but a different array index
            // pDescriptorSet->write(pDescriptorSet->getLayout()->getBindings().at(0), &descriptorImageInfo, nullptr, nullptr, i, 1);
        }
        pDescriptorSet->write(pDescriptorSet->getLayout()->getBindings().at(0), descriptorImageInfos.data(), nullptr, nullptr, 0,
                              this->upTextures.size());
    }

} // namespace fillcan