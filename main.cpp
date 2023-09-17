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
    if (result == VK_SUCCESS)
    {
        cout << "Succeeded" << endl;

        // First figure out how many devices are in the system.
        uint32_t physicalDeviceCount = 0;
        result = vkEnumeratePhysicalDevices(m_instance, &physicalDeviceCount, nullptr);

        if (result == VK_SUCCESS)
        {
            cout << "We have " << physicalDeviceCount << " devices on this system." << endl;
            m_physicalDevices.resize(physicalDeviceCount);
            vkEnumeratePhysicalDevices(m_instance, &physicalDeviceCount, &m_physicalDevices[0]);
        }
    }

    return 0;
}