#include "VulkanTest.hpp"

VkResult VulkanTest::initInstance()
{
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
    return vkCreateInstance(&instanceCreateInfo, nullptr, &m_instance);
}

VkResult VulkanTest::getPhysicalDevices()
{
    VkResult result = VK_SUCCESS;

    uint32_t physicalDeviceCount = 0;
    result = vkEnumeratePhysicalDevices(m_instance, &physicalDeviceCount, nullptr);
    if (result != VK_SUCCESS) return result;

    m_physicalDevices.resize(physicalDeviceCount);
    result = vkEnumeratePhysicalDevices(m_instance, &physicalDeviceCount, m_physicalDevices.data());

    return result;
}

VkResult VulkanTest::createLogicalDevice()
{
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

    return vkCreateDevice(m_physicalDevices[0], &deviceCreateInfo, nullptr, &m_logicalDevice);
}

void VulkanTest::getInstanceLayers()
{
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
}

void VulkanTest::getInstanceExtensions()
{
    uint32_t numInstanceExtensions = 0;
    vector<VkExtensionProperties> instanceExtensionProperties;
    vkEnumerateInstanceExtensionProperties(nullptr, &numInstanceExtensions, nullptr);
    cout << "Found " << numInstanceExtensions << " instance extensions supported by this Vulkan system." << endl;
    if (numInstanceExtensions != 0)
    {
        instanceExtensionProperties.resize(numInstanceExtensions);
        vkEnumerateInstanceExtensionProperties(nullptr, &numInstanceExtensions, instanceExtensionProperties.data());

        for (uint32_t extensionIndex = 0; extensionIndex < numInstanceExtensions; extensionIndex++)
        {
            cout << "\t- " << instanceExtensionProperties[extensionIndex].extensionName << endl;
        }
    }
}

void VulkanTest::shutdownInstance()
{
    vkDeviceWaitIdle(m_logicalDevice);
    vkDestroyDevice(m_logicalDevice, nullptr);
}