// fillcan
#include "fillcan/commands/command_buffer.hpp"
#include "fillcan/commands/command_pool.hpp"
#include "fillcan/commands/command_recording.hpp"
#include "vulkan/vulkan_core.h"
#include <fillcan/commands/queue.hpp>
#include <fillcan/instance/logical_device.hpp>
#include <iostream>
#include <memory>
#include <vector>

namespace fillcan {
    Queue::Queue(LogicalDevice* pLogicalDevice, unsigned int queueFamilyIndex, unsigned int queueIndex)
        : pLogicalDevice(pLogicalDevice), queueFamilyIndex(queueFamilyIndex), queueIndex(queueIndex) {
        vkGetDeviceQueue(this->pLogicalDevice->getLogicalDeviceHandle(), this->queueFamilyIndex, this->queueIndex, &this->hQueue);
        this->upCommandPool = std::make_unique<CommandPool>(
            this->pLogicalDevice, VK_COMMAND_POOL_CREATE_TRANSIENT_BIT | VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT, this->queueFamilyIndex);
    }
    Queue::~Queue() {}

    CommandRecording& Queue::createRecording(unsigned int primaryCommandBufferCount, unsigned int secondaryCommandBufferCount) {
        CommandRecording recording = {};
        if (primaryCommandBufferCount > 0) {
            recording.pPrimaryCommandBuffers =
                this->upCommandPool->allocateCommandBuffers(VK_COMMAND_BUFFER_LEVEL_PRIMARY, primaryCommandBufferCount);
        }
        if (secondaryCommandBufferCount > 0) {
            recording.pSecondaryCommandBuffers =
                this->upCommandPool->allocateCommandBuffers(VK_COMMAND_BUFFER_LEVEL_SECONDARY, secondaryCommandBufferCount);
        }
        this->recordings.push_back(recording);
        return this->recordings.back();
    }

    bool Queue::submitRecordings(std::vector<CommandRecording*> pCommandRecordings, VkFence fence) {
        bool success = true;
        for (CommandRecording* pCommandRecording : pCommandRecordings) {
            VkSubmitInfo submitInfo = {};
            submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
            submitInfo.pNext = nullptr;
            submitInfo.waitSemaphoreCount = pCommandRecording->waitSemaphores.size();
            submitInfo.pWaitSemaphores = pCommandRecording->waitSemaphores.data();
            submitInfo.pWaitDstStageMask = &pCommandRecording->waitDstStageMask;
            std::vector<VkCommandBuffer> commandBufferHandles = {};
            int i = 0;
            for (std::shared_ptr<CommandBuffer>& spCommandBuffer : pCommandRecording->pPrimaryCommandBuffers) {
                commandBufferHandles.push_back(spCommandBuffer->getCommandBufferHandle());
            }
            // Secondary Command Buffers shouldn't be submitted
            // for (std::shared_ptr<CommandBuffer>& spCommandBuffer : pCommandRecording->pSecondaryCommandBuffers) {
            //     commandBufferHandles.push_back(spCommandBuffer->getCommandBufferHandle());
            // }
            submitInfo.commandBufferCount = commandBufferHandles.size();
            submitInfo.pCommandBuffers = commandBufferHandles.data();
            submitInfo.signalSemaphoreCount = pCommandRecording->signalSemaphores.size();
            submitInfo.pSignalSemaphores = pCommandRecording->signalSemaphores.data();
            success = success && vkQueueSubmit(this->hQueue, 1, &submitInfo, fence) == VK_SUCCESS ? true : false;
        }
        return success;
    }

    bool resetRecording(CommandRecording& pCommandRecording);

    void Queue::freeRecording(CommandRecording& pCommandRecording) {
        std::vector<std::shared_ptr<CommandBuffer>> commandBuffers = pCommandRecording.pPrimaryCommandBuffers;
        commandBuffers.insert(commandBuffers.end(), pCommandRecording.pSecondaryCommandBuffers.begin(),
                              pCommandRecording.pSecondaryCommandBuffers.end());
        this->upCommandPool->freeCommandBuffers(commandBuffers);
    }

    bool Queue::waitIdle() { return vkQueueWaitIdle(this->hQueue); }
} // namespace fillcan