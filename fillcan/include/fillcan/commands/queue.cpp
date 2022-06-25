// vulkan
#include "vulkan/vulkan_core.h"

// fillcan
#include <fillcan/commands/command_buffer.hpp>
#include <fillcan/commands/command_pool.hpp>
#include <fillcan/commands/command_recording.hpp>
#include <fillcan/commands/queue.hpp>
#include <fillcan/instance/logical_device.hpp>
#include <fillcan/memory/fence.hpp>
#include <fillcan/memory/semaphore.hpp>

// std
#include <iostream>
#include <memory>

namespace fillcan {
    Queue::Queue(LogicalDevice* pLogicalDevice, unsigned int queueFamilyIndex, unsigned int queueIndex)
        : pLogicalDevice(pLogicalDevice), queueFamilyIndex(queueFamilyIndex), queueIndex(queueIndex) {
        vkGetDeviceQueue(this->pLogicalDevice->getLogicalDeviceHandle(), this->queueFamilyIndex, this->queueIndex, &this->hQueue);
        this->upCommandPool = std::make_unique<CommandPool>(
            this->pLogicalDevice, VK_COMMAND_POOL_CREATE_TRANSIENT_BIT | VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT, this->queueFamilyIndex);
    }

    Queue::~Queue() { this->upCommandPool.reset(); }

    VkQueue Queue::getQueueHandle() { return this->hQueue; }

    CommandRecording* Queue::createRecording(unsigned int primaryCommandBufferCount, unsigned int secondaryCommandBufferCount) {
        CommandRecording recording = {};
        if (primaryCommandBufferCount > 0) {
            recording.pPrimaryCommandBuffers =
                this->upCommandPool->allocateCommandBuffers(VK_COMMAND_BUFFER_LEVEL_PRIMARY, primaryCommandBufferCount);
        }
        if (secondaryCommandBufferCount > 0) {
            recording.pSecondaryCommandBuffers =
                this->upCommandPool->allocateCommandBuffers(VK_COMMAND_BUFFER_LEVEL_SECONDARY, secondaryCommandBufferCount);
        }
        recording.pQueue = this;
        // recording.createFence(this->pLogicalDevice, 0);
        this->upCommandRecordings.emplace_back(std::move(std::make_unique<CommandRecording>(std::move(recording))));
        return this->upCommandRecordings.back().get();
    }

    bool Queue::submitRecordings(std::vector<CommandRecording*> pCommandRecordings, Fence* pFence) {
        bool success = true;
        for (CommandRecording* pCommandRecording : pCommandRecordings) {
            VkSubmitInfo submitInfo = {};
            submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
            submitInfo.pNext = nullptr;

            std::vector<VkSemaphore> hWaitSemaphores = {};
            hWaitSemaphores.reserve(pCommandRecording->pWaitSemaphores.size());
            std::transform(pCommandRecording->pWaitSemaphores.begin(), pCommandRecording->pWaitSemaphores.end(), std::back_inserter(hWaitSemaphores),
                           [](Semaphore* pWaitSemaphore) { return pWaitSemaphore->getSemaphoreHandle(); });
            submitInfo.waitSemaphoreCount = hWaitSemaphores.size();
            submitInfo.pWaitSemaphores = hWaitSemaphores.data();

            submitInfo.pWaitDstStageMask = &pCommandRecording->waitDstStageMask;
            std::vector<VkCommandBuffer> hCommandBuffers = {};
            hCommandBuffers.reserve(pCommandRecording->pPrimaryCommandBuffers.size());
            std::transform(pCommandRecording->pPrimaryCommandBuffers.begin(), pCommandRecording->pPrimaryCommandBuffers.end(),
                           std::back_inserter(hCommandBuffers),
                           [](CommandBuffer* pCommandBuffer) { return pCommandBuffer->getCommandBufferHandle(); });
            submitInfo.commandBufferCount = hCommandBuffers.size();
            submitInfo.pCommandBuffers = hCommandBuffers.data();

            std::vector<VkSemaphore> hSignalSemaphores = {};
            hSignalSemaphores.reserve(pCommandRecording->pSignalSemaphores.size());
            std::transform(pCommandRecording->pSignalSemaphores.begin(), pCommandRecording->pSignalSemaphores.end(),
                           std::back_inserter(hSignalSemaphores), [](Semaphore* pSignalSemaphore) { return pSignalSemaphore->getSemaphoreHandle(); });
            submitInfo.signalSemaphoreCount = hSignalSemaphores.size();
            submitInfo.pSignalSemaphores = hSignalSemaphores.data();
            success =
                success && vkQueueSubmit(this->hQueue, 1, &submitInfo, pFence != nullptr ? pFence->getFenceHandle() : VK_NULL_HANDLE) == VK_SUCCESS
                    ? true
                    : false;
        }
        return success;
    }

    bool Queue::resetRecording(CommandRecording* pCommandRecording, VkCommandBufferResetFlags flags) {
        bool successfulReset = true;
        for (CommandBuffer* pPrimaryCommandBuffer : pCommandRecording->pPrimaryCommandBuffers) {
            if (!pPrimaryCommandBuffer->reset(flags)) {
                successfulReset = false;
            }
        }
        for (CommandBuffer* pSecondaryCommandBuffer : pCommandRecording->pSecondaryCommandBuffers) {
            if (!pSecondaryCommandBuffer->reset(flags)) {
                successfulReset = false;
            }
        }
        return successfulReset;
    }

    void Queue::freeRecording(CommandRecording* pCommandRecording) {
        std::vector<CommandBuffer*> pCommandBuffers = pCommandRecording->pPrimaryCommandBuffers;
        pCommandBuffers.insert(pCommandBuffers.end(), pCommandRecording->pSecondaryCommandBuffers.begin(),
                               pCommandRecording->pSecondaryCommandBuffers.end());
        this->upCommandPool->freeCommandBuffers(pCommandBuffers);
        this->upCommandRecordings.erase(std::remove_if(
            this->upCommandRecordings.begin(), this->upCommandRecordings.end(),
            [pCommandRecording](std::unique_ptr<CommandRecording>& rupCommandRecording) { return rupCommandRecording.get() == pCommandRecording; }));
    }

    bool Queue::waitIdle() { return vkQueueWaitIdle(this->hQueue); }
} // namespace fillcan