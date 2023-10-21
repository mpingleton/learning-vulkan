#include "VulkanTest.hpp"

#include <iostream>
#include <vulkan/vulkan.hpp>

int main(int argc, char** argv)
{
    VulkanTest vkt;
    VkResult result = VK_SUCCESS;

    result = vkt.initInstance();
    if (result == VK_ERROR_INCOMPATIBLE_DRIVER) cout << "Incompatible driver." << endl;
    if (result != VK_SUCCESS) return 1;
    cout << "Succeeded in creating a Vulkan instance!" << endl;

    result = vkt.getPhysicalDevices();
    if (result != VK_SUCCESS) return 2;

    /*
    for (int deviceIndex = 0;  deviceIndex < m_physicalDevices.size(); deviceIndex++)
    {
        VkPhysicalDeviceProperties deviceProperties = { };
        vkGetPhysicalDeviceProperties(m_physicalDevices[deviceIndex], &deviceProperties);
        cout << deviceProperties.deviceName << endl;

        VkPhysicalDeviceFeatures deviceFeatures = { };
        vkGetPhysicalDeviceFeatures(m_physicalDevices[deviceIndex], &deviceFeatures);

        VkPhysicalDeviceMemoryProperties memoryProperties;
        vkGetPhysicalDeviceMemoryProperties(m_physicalDevices[deviceIndex], &memoryProperties);

        uint32_t queueFamilyPropertyCount = 0;
        vector<VkQueueFamilyProperties> queueFamilyProperties;
        vkGetPhysicalDeviceQueueFamilyProperties(m_physicalDevices[deviceIndex], &queueFamilyPropertyCount, nullptr);
        queueFamilyProperties.resize(queueFamilyPropertyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(m_physicalDevices[deviceIndex], &queueFamilyPropertyCount, &queueFamilyProperties[0]);
    }
    */

    // The above commented-out code runs through each physical device that the computer has.  For now, we just want to use the first one.
    VkPhysicalDeviceProperties deviceProperties = { };
    vkGetPhysicalDeviceProperties(vkt.m_physicalDevices[0], &deviceProperties);
    cout << "\t- " << deviceProperties.deviceName << endl;

    // Create a logical device.
    result = vkt.createLogicalDevice();
    if (result != VK_SUCCESS) return 3;
    
    vkt.getInstanceLayers();
    vkt.getInstanceExtensions();

    // Shut down cleanly.
    cout << "Shutting down... ";
    vkt.shutdownInstance();
    cout << "done!" << endl;
    
    return 0;
}