 #ifndef VULKANTEST_HPP
 #define VULKANTEST_HPP

#include <iostream>
#include <vector>
#include <vulkan/vulkan.hpp>

using namespace std;

class VulkanTest
{
public:
    VkInstance m_instance;
    vector<VkPhysicalDevice> m_physicalDevices;
    VkDevice m_logicalDevice;

    VkResult initInstance();
    VkResult getPhysicalDevices();
    VkResult createLogicalDevice();

    void getInstanceLayers();
    void getInstanceExtensions();
    void shutdownInstance();
};

 #endif