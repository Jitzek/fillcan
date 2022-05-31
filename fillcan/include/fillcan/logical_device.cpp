#include "fillcan/logical_device.hpp"

namespace fillcan {
    LogicalDevice::LogicalDevice(PhysicalDevice* pPhysicalDevice): pPhysicalDevice(pPhysicalDevice) {
    }

    LogicalDevice::~LogicalDevice() {}
} // namespace fillcan