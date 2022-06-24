// fillcan
#include "fillcan/commands/command_recording.hpp"
#include "vulkan/vulkan_core.h"
#include <algorithm>
#include <cstddef>
#include <fillcan/commands/command_buffer.hpp>
#include <fillcan/commands/queue.hpp>
#include <fillcan/graphics/model.hpp>
#include <fillcan/instance/logical_device.hpp>
#include <fillcan/memory/buffer.hpp>
#include <fillcan/memory/buffer_director.hpp>
#include <fillcan/memory/memory.hpp>

// std
#include <cstring>
#include <iostream>
#include <map>
#include <memory>
#include <stdexcept>
#include <unordered_map>
#include <utility>
#include <vector>

// tinyobjloader
#define TINYOBJLOADER_IMPLEMENTATION
#include <tinyobjloader/tiny_obj_loader.h>

namespace fillcan {
    Model::Model(LogicalDevice* pLogicalDevice, const std::vector<Vertex>& vertices, const std::vector<uint16_t>& indices)
        : pLogicalDevice(pLogicalDevice) {
        this->init(vertices, indices);
    }

    Model::Model(LogicalDevice* pLogicalDevice, std::string filePath) : pLogicalDevice(pLogicalDevice) {
        std::vector<Vertex> vertices;
        std::vector<uint16_t> indices;

        tinyobj::attrib_t attrib;
        std::vector<tinyobj::shape_t> shapes;
        std::vector<tinyobj::material_t> materials;
        std::string warn, err;

        if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, filePath.c_str())) {
            throw std::runtime_error(warn + err);
        }

        std::vector<std::pair<Vertex, uint32_t>> uniqueVertices{};

        for (const auto& shape : shapes) {
            for (const auto& index : shape.mesh.indices) {
                Vertex vertex{};

                if (index.vertex_index >= 0) {
                    vertex.position = {attrib.vertices[3 * index.vertex_index + 0 /* x */], attrib.vertices[3 * index.vertex_index + 1 /* y */],
                                       attrib.vertices[3 * index.vertex_index + 2 /* z */]};
                }

                if (index.normal_index >= 0) {
                    vertex.normal = {attrib.normals[3 * index.vertex_index + 0], attrib.normals[3 * index.vertex_index + 1],
                                     attrib.normals[3 * index.vertex_index + 2]};
                }

                if (index.texcoord_index >= 0) {
                    vertex.textureCoordinate = {attrib.texcoords[2 * index.texcoord_index + 0], attrib.texcoords[2 * index.texcoord_index + 1]};
                }

                // Check if vertex has already occured
                auto it = std::find_if(uniqueVertices.begin(), uniqueVertices.end(),
                                       [vertex](const std::pair<Vertex, uint32_t> pair) { return pair.first == vertex; });
                if (it == uniqueVertices.end()) {
                    // If vertex hasn't occured yet, add it to the list of vertices and it's it's index to the list of indices
                    uniqueVertices.push_back({vertex, static_cast<uint32_t>(vertices.size())});
                    indices.push_back(vertices.size());
                    vertices.push_back(vertex);
                } else {
                    // If vertex has occured, add it's index to the list of indices
                    indices.push_back(it->second);
                }
            }
        }

        this->init(vertices, indices);
    }

    Model::~Model() {}

    void Model::init(const std::vector<Vertex>& vertices, const std::vector<uint16_t>& indices) {
        this->vertexCount = static_cast<uint32_t>(vertices.size());
        this->indexCount = static_cast<uint32_t>(indices.size());

        this->createVertexBuffer(vertices);

        if (indices.size() > 0) {
            this->createIndexBuffer(indices);
        }
    }

    void Model::createVertexBuffer(const std::vector<Vertex>& vertices) {
        BufferDirector bufferDirector{};

        VkDeviceSize vertexBufferSize = sizeof(vertices[0]) * vertices.size();
        std::unique_ptr<Buffer> upStagingBuffer = bufferDirector.makeStagingBuffer(this->pLogicalDevice, vertexBufferSize);
        std::unique_ptr<Memory> upStagingBufferMemory =
            std::make_unique<Memory>(this->pLogicalDevice, upStagingBuffer.get(), VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT);
        upStagingBuffer->bindMemory(upStagingBufferMemory.get());
        void** ppStagingBufferVertexData = upStagingBuffer->getMemory()->map();
        memcpy(*ppStagingBufferVertexData, vertices.data(), upStagingBuffer->getSize());
        upStagingBuffer->getMemory()->unmap();

        this->upVertexBuffer = bufferDirector.makeVertexTransferDestinationBuffer(this->pLogicalDevice, sizeof(vertices[0]) * vertices.size());
        this->upVertexMemory = std::make_unique<Memory>(this->pLogicalDevice, upVertexBuffer.get(), VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
        this->upVertexBuffer->bindMemory(this->upVertexMemory.get());

        std::vector<VkBufferCopy> regions = {{.srcOffset = 0, .dstOffset = 0, .size = vertexBufferSize}};

        CommandRecording* pCommandRecording = this->pLogicalDevice->beginSingleTimeCommandRecording(this->pLogicalDevice->getGraphicsQueue());
        upStagingBuffer->copyTo(pCommandRecording->pPrimaryCommandBuffers[0], this->upVertexBuffer.get(), regions);
        this->pLogicalDevice->endSingleTimeCommandRecording(pCommandRecording);
    }

    void Model::createIndexBuffer(const std::vector<uint16_t>& indices) {
        BufferDirector bufferDirector{};

        VkDeviceSize indexBufferSize = sizeof(indices[0]) * indices.size();
        std::unique_ptr<Buffer> upStagingBuffer = bufferDirector.makeStagingBuffer(this->pLogicalDevice, indexBufferSize);
        std::unique_ptr<Memory> upStagingBufferMemory =
            std::make_unique<Memory>(this->pLogicalDevice, upStagingBuffer.get(), VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT);
        upStagingBuffer->bindMemory(upStagingBufferMemory.get());
        void** ppStagingBufferVertexData = upStagingBuffer->getMemory()->map();
        memcpy(*ppStagingBufferVertexData, indices.data(), upStagingBuffer->getSize());
        upStagingBuffer->getMemory()->unmap();

        this->upIndexBuffer = bufferDirector.makeIndexTransferDestinationBuffer(this->pLogicalDevice, sizeof(indices[0]) * indices.size());
        this->upIndexMemory = std::make_unique<Memory>(this->pLogicalDevice, upIndexBuffer.get(), VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT);
        this->upIndexBuffer->bindMemory(this->upIndexMemory.get());

        std::vector<VkBufferCopy> regions = {{.srcOffset = 0, .dstOffset = 0, .size = indexBufferSize}};

        CommandRecording* pCommandRecording = this->pLogicalDevice->beginSingleTimeCommandRecording(this->pLogicalDevice->getGraphicsQueue());
        upStagingBuffer->copyTo(pCommandRecording->pPrimaryCommandBuffers[0], this->upIndexBuffer.get(), regions);
        this->pLogicalDevice->endSingleTimeCommandRecording(pCommandRecording);
    }

    void Model::setTexture(Texture* pTexture) { this->pTexture = pTexture; }

    Texture* Model::getTexture() { return this->pTexture; }

    void Model::bind(CommandBuffer* pCommandBuffer) {
        VkBuffer hVertexBuffers[] = {upVertexBuffer->getBufferHandle()};
        VkDeviceSize offsets[] = {0};
        vkCmdBindVertexBuffers(pCommandBuffer->getCommandBufferHandle(), 0, 1, hVertexBuffers, offsets);
        if (this->upIndexBuffer != nullptr) {
            vkCmdBindIndexBuffer(pCommandBuffer->getCommandBufferHandle(), upIndexBuffer->getBufferHandle(), 0, VK_INDEX_TYPE_UINT16);
        }
        this->pCommandBuffer = pCommandBuffer;
    }

    void Model::draw() {
        if (this->pCommandBuffer == nullptr) {
            throw std::runtime_error("Model was not bound to a command buffer before drawing.");
        }
        vkCmdDraw(this->pCommandBuffer->getCommandBufferHandle(), this->vertexCount, 1, 0, 0);
    }

    void Model::drawIndexed() {
        if (this->pCommandBuffer == nullptr) {
            throw std::runtime_error("Model was not bound to a command buffer before drawing.");
        }
        vkCmdDrawIndexed(this->pCommandBuffer->getCommandBufferHandle(), this->indexCount, 1, 0, 0, 0);
    }

    std::vector<VkVertexInputBindingDescription> Model::Vertex::getBindingDescriptions() {
        return {{.binding = 0, .stride = sizeof(Vertex), .inputRate = VK_VERTEX_INPUT_RATE_VERTEX}};
    }

    std::vector<VkVertexInputAttributeDescription> Model::Vertex::getAttributeDescriptions() {
        return {getPositionAttributeDescription(0, 0), getColorAttributeDescription(1, 0), getTextureCoordinateAttributeDescription(2, 0),
                getNormalAttributeDescription(3, 0)};
    }

    VkVertexInputAttributeDescription Model::Vertex::getPositionAttributeDescription(unsigned int location, unsigned int binding) {
        return {.location = location, .binding = 0, .format = VK_FORMAT_R32G32B32_SFLOAT, .offset = offsetof(Vertex, position)};
    }

    VkVertexInputAttributeDescription Model::Vertex::getColorAttributeDescription(unsigned int location, unsigned int binding) {
        return {.location = location, .binding = 0, .format = VK_FORMAT_R32G32B32_SFLOAT, .offset = offsetof(Vertex, color)};
    }

    VkVertexInputAttributeDescription Model::Vertex::getTextureCoordinateAttributeDescription(unsigned int location, unsigned int binding) {
        return {.location = location, .binding = 0, .format = VK_FORMAT_R32G32_SFLOAT, .offset = offsetof(Vertex, textureCoordinate)};
    }

    VkVertexInputAttributeDescription Model::Vertex::getNormalAttributeDescription(unsigned int location, unsigned int binding) {
        return {.location = location, .binding = 0, .format = VK_FORMAT_R32G32B32_SFLOAT, .offset = offsetof(Vertex, normal)};
    }

} // namespace fillcan