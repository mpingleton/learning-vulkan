#include <iostream>
#include <vector>
#include <vulkan/vulkan.hpp>

using namespace std;

int main(int argc, char** argv)
{
    VkInstance m_instance;
    vector<VkPhysicalDevice> m_physicalDevices;

    VkResult result = VK_SUCCESS;
    VkApplicationInfo appInfo = { };
    VkInstanceCreateInfo instanceCreateInfo = { };
    
    // A generic application info structure.
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Learning Vulkan";
    appInfo.applicationVersion = 1;
    appInfo.apiVersion = VK_MAKE_VERSION(1, 0, 0);

    // Create the instance.
    instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    instanceCreateInfo.pApplicationInfo = &appInfo;

    result = vkCreateInstance(&instanceCreateInfo, nullptr, &m_instance);
    if (result != VK_SUCCESS) return 1;
    
    cout << "Succeeded in creating a Vulkan instance!" << endl;

    // First figure out how many devices are in the system.
    uint32_t physicalDeviceCount = 0;
    result = vkEnumeratePhysicalDevices(m_instance, &physicalDeviceCount, nullptr);
    if (result != VK_SUCCESS) return 2;

    cout << "We have " << physicalDeviceCount << " devices on this system." << endl;
    m_physicalDevices.resize(physicalDeviceCount);
    vkEnumeratePhysicalDevices(m_instance, &physicalDeviceCount, m_physicalDevices.data());

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
    
    return 0;
}