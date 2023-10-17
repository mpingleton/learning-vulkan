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
    if (result == VK_ERROR_INCOMPATIBLE_DRIVER) cout << "Incompatible driver." << endl;

    if (result != VK_SUCCESS) return 1;
    
    cout << "Succeeded in creating a Vulkan instance!" << endl;

    // First figure out how many devices are in the system.
    uint32_t physicalDeviceCount = 0;
    result = vkEnumeratePhysicalDevices(m_instance, &physicalDeviceCount, nullptr);
    if (result != VK_SUCCESS) return 2;

    cout << "We have " << physicalDeviceCount << " devices on this system." << endl;
    m_physicalDevices.resize(physicalDeviceCount);
    vkEnumeratePhysicalDevices(m_instance, &physicalDeviceCount, m_physicalDevices.data());
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
    vkGetPhysicalDeviceProperties(m_physicalDevices[0], &deviceProperties);
    cout << "\t- " << deviceProperties.deviceName << endl;

    VkPhysicalDeviceFeatures deviceFeatures = { };
    vkGetPhysicalDeviceFeatures(m_physicalDevices[0], &deviceFeatures);

    VkPhysicalDeviceFeatures requiredFeatures = { };
    requiredFeatures.multiDrawIndirect = deviceFeatures.multiDrawIndirect;
    requiredFeatures.tessellationShader = VK_TRUE;
    requiredFeatures.geometryShader = VK_TRUE;

    VkPhysicalDeviceMemoryProperties memoryProperties;
    vkGetPhysicalDeviceMemoryProperties(m_physicalDevices[0], &memoryProperties);

    uint32_t queueFamilyPropertyCount = 0;
    vector<VkQueueFamilyProperties> queueFamilyProperties;
    vkGetPhysicalDeviceQueueFamilyProperties(m_physicalDevices[0], &queueFamilyPropertyCount, nullptr);
    queueFamilyProperties.resize(queueFamilyPropertyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(m_physicalDevices[0], &queueFamilyPropertyCount, &queueFamilyProperties[0]);

    // Create a logical device.
    const VkDeviceQueueCreateInfo deviceQueueCreateInfo = {
        VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO, // sType
        nullptr, // pNext
        0,  // flags
        0,  // queueFamilyIndex
        1,  // queueCount
        nullptr // pQueuePriorities
    };

    const VkDeviceCreateInfo deviceCreateInfo = {
        VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO, // sType
        nullptr, // pNext
        0, // flags
        1, // queueCreateInfoCount
        &deviceQueueCreateInfo, // pQueueCreateInfos
        0, // enabledLayerCount
        nullptr, // ppEnabledLayerNames
        0, // enabledExtensionCount
        nullptr, // ppEnabledExtensionNames
        &requiredFeatures // pEnabledFeatures
    };

    VkDevice m_logicalDevice;
    result = vkCreateDevice(m_physicalDevices[0], &deviceCreateInfo, nullptr, &m_logicalDevice);
    if (result != VK_SUCCESS) return 3;

    uint32_t numInstanceLayers = 0;
    vector<VkLayerProperties> instanceLayerProperties;
    vkEnumerateInstanceLayerProperties(&numInstanceLayers, nullptr);
    cout << "Found " << numInstanceLayers << " instance layers supported by this Vulkan system." << endl;
    if (numInstanceLayers != 0)
    {
        instanceLayerProperties.resize(numInstanceLayers);
        vkEnumerateInstanceLayerProperties(&numInstanceLayers, instanceLayerProperties.data());

        for (uint32_t layerIndex = 0; layerIndex < numInstanceLayers; layerIndex++)
        {
            cout << "\t- " << instanceLayerProperties[layerIndex].layerName << " (" << instanceLayerProperties[layerIndex].description << ")" << endl;
        }
    }
    
    return 0;
}