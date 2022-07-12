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
#include <vector>

namespace fillcan {
    Queue::Queue(LogicalDevice* pLogicalDevice, unsigned int queueFamilyIndex, unsigned int queueIndex)
        : pLogicalDevice(pLogicalDevice), queueFamilyIndex(queueFamilyIndex), queueIndex(queueIndex) {
        vkGetDeviceQueue(this->pLogicalDevice->getLogicalDeviceHandle(), this->queueFamilyIndex, this->queueIndex, &this->hQueue);
        this->upCommandPool = std::make_unique<CommandPool>(
            this->pLogicalDevice, VK_COMMAND_POOL_CREATE_TRANSIENT_BIT | VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT, this->queueFamilyIndex);
    }

    Queue::~Queue() { this->upCommandPool.reset(); }

    const VkQueue Queue::getQueueHandle() const { return this->hQueue; }

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

        std::vector<std::vector<VkSemaphore>> hWaitSemaphoresCollection(pCommandRecordings.size());
        std::vector<std::vector<VkCommandBuffer>> hCommandBuffersCollection(pCommandRecordings.size());
        std::vector<std::vector<VkSemaphore>> hSignalSemaphoresCollection(pCommandRecordings.size());

        std::vector<VkSubmitInfo> submitInfos = {};
        for (int i = 0; i < pCommandRecordings.size(); i++) {
            VkSubmitInfo submitInfo = {};
            submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
            submitInfo.pNext = nullptr;

            hWaitSemaphoresCollection.at(i) = {};
            hWaitSemaphoresCollection.at(i).reserve(pCommandRecordings.at(i)->pWaitSemaphores.size());
            std::transform(pCommandRecordings.at(i)->pWaitSemaphores.begin(), pCommandRecordings.at(i)->pWaitSemaphores.end(),
                           std::back_inserter(hWaitSemaphoresCollection.at(i)),
                           [](Semaphore* pWaitSemaphore) { return pWaitSemaphore->getSemaphoreHandle(); });
            submitInfo.waitSemaphoreCount = hWaitSemaphoresCollection.at(i).size();
            submitInfo.pWaitSemaphores = hWaitSemaphoresCollection.at(i).data();

            submitInfo.pWaitDstStageMask = &pCommandRecordings.at(i)->waitDstStageMask;

            hCommandBuffersCollection.at(i) = {};
            hCommandBuffersCollection.at(i).reserve(pCommandRecordings.at(i)->pPrimaryCommandBuffers.size());
            std::transform(pCommandRecordings.at(i)->pPrimaryCommandBuffers.begin(), pCommandRecordings.at(i)->pPrimaryCommandBuffers.end(),
                           std::back_inserter(hCommandBuffersCollection.at(i)),
                           [](CommandBuffer* pCommandBuffer) { return pCommandBuffer->getCommandBufferHandle(); });
            submitInfo.commandBufferCount = hCommandBuffersCollection.at(i).size();
            submitInfo.pCommandBuffers = hCommandBuffersCollection.at(i).data();

            hSignalSemaphoresCollection.at(i) = {};
            hSignalSemaphoresCollection.at(i).reserve(pCommandRecordings.at(i)->pSignalSemaphores.size());
            std::transform(pCommandRecordings.at(i)->pSignalSemaphores.begin(), pCommandRecordings.at(i)->pSignalSemaphores.end(),
                           std::back_inserter(hSignalSemaphoresCollection.at(i)),
                           [](Semaphore* pSignalSemaphore) { return pSignalSemaphore->getSemaphoreHandle(); });
            submitInfo.signalSemaphoreCount = hSignalSemaphoresCollection.at(i).size();
            submitInfo.pSignalSemaphores = hSignalSemaphoresCollection.at(i).data();

            submitInfos.push_back(submitInfo);
        }

        return vkQueueSubmit(this->hQueue, submitInfos.size(), submitInfos.data(), pFence != nullptr ? pFence->getFenceHandle() : VK_NULL_HANDLE) ==
               VK_SUCCESS;
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