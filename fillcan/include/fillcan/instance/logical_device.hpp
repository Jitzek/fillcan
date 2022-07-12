#pragma once

// vulkan
#include "vulkan/vulkan_core.h"

// fillcan
#include <fillcan/commands/command_recording.hpp>
#include <fillcan/commands/queue.hpp>
#include <fillcan/instance/physical_device.hpp>

// std
#include <memory>

namespace fillcan {
    class LogicalDevice {
      private:
        VkDevice hLogicalDevice;
        PhysicalDevice* pPhysicalDevice;
        std::unique_ptr<Queue> upGraphicsQueue;
        std::unique_ptr<Queue> upPresentQueue;
        std::unique_ptr<Queue> upComputeQueue;

      public:
        /**
         * @brief Create a new Logical Device.
         *
         * @details The Logical Device class takes in a pointer to the Physical Device to construct around. It uses the Physical Device to construct
         * the graphics, presentation and computation Queues if available.
         * The Logical Device class is the software construction around a Physical Device. A Logical Device represents a reservation of resources
         * associated with a particular Physical Device. This includes a possible subset of the available Queues on the Physical Device, and it is the
         * Logical Device that the application will communicate with most of the time.
         *
         * @param pPhysicalDevice A pointer to the Physical Device to create a Logical Device from.
         */
        LogicalDevice(PhysicalDevice* pPhysicalDevice);
        ~LogicalDevice();
        LogicalDevice(const LogicalDevice&) = delete;
        LogicalDevice& operator=(const LogicalDevice&) = delete;

        /**
         * @brief Get the handle to the Vulkan Device.
         *
         * @return The handle to the Vulkan Device.
         */
        const VkDevice getLogicalDeviceHandle() const;

        /**
         * @brief Get a pointer to the Physical Device this Logical Device is constructed around.
         *
         * @return A pointer to the Physical Device this Logical Device is constructed around.
         */
        const PhysicalDevice* getPhysicalDevice() const;

        /**
         * @brief Wait for the Logical Device to become idle.
         *
         * @details Waits on the host for the completion of ongoing Queue operations for all Queues on this Logical Device.
         *
         */
        void waitIdle();

        /**
         * @brief Get a pointer to the graphics Queue.
         *
         * @return A pointer to the graphics Queue or nullptr if no Queue was found.
         */
        Queue* getGraphicsQueue() const;

        /**
         * @brief Get a pointer to the present Queue.
         *
         * @return A pointer to the present Queue or nullptr if no Queue was found.
         */
        Queue* getPresentQueue() const;

        /**
         * @brief Get a pointer to the compute Queue.
         *
         * @return A pointer to the compute Queue or nullptr if no Queue was found.
         */
        Queue* getComputeQueue() const;

        /**
         * @brief Start a Command Recording with a given Queue.
         *
         * @details Creates a Command Recording using the given Queue pointer. This Command Recording will contain 1 (one) Primary Command Buffer and
         * 0 (zero) Secondary Command Buffers. To end the recording, call @see LogicalDevice#endSingleTimeRecording.
         *
         * @see CommandRecording
         * @see CommandBuffer
         *
         * @param pQueue A pointer to the Queue from which a Command Recording will be created from.
         * @return A pointer to the created Command Recording.
         */
        CommandRecording* beginSingleTimeCommandRecording(Queue* pQueue);

        /**
         * @brief End a Command Recording.
         *
         * @details Ends a Command Recording (preferably created using @see LogicalDevice#beginSingleTimeRecording), submits the recording and waits
         * for the Queue to idle before returning.
         *
         * @param pCommandRecording The Command Recording to end.
         */
        void endSingleTimeCommandRecording(CommandRecording* pCommandRecording);
    };
} // namespace fillcan