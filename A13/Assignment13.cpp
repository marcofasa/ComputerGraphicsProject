
/*
1. Create a Window with GLFW. OK (50)
2. Create a Vulkan Instance. OK (83)
3. Create a Presentation Surface with GLFW. OK (84)
4. Cycle through the available device and pick up the first supporting both a graphic and a presentation queue. OK (85)
5. Create a Logical Device with both a graphic queue and a presentation queue. OK (86)
6. Create a Command Pool for the graphic queue. OK (87)
7. Create a Command Buffer from the previous Command Pool OK (88)
8. Release all the resources. OK (53)
 */
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <algorithm>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdint>
#include <limits>
#include <optional>
#include <set>

const uint32_t WIDTH = 640;
const uint32_t HEIGHT = 480;




struct QueueFamilyIndices {
    std::optional<uint32_t> graphicsFamily;
    std::optional<uint32_t> presentFamily;

    bool isComplete() {
        return graphicsFamily.has_value() && presentFamily.has_value();
    }
};

class Assignment13 {
public:
    void run() {
        initWindow();
        initVulkan();
        mainLoop();
        cleanup();

    }

private:
    GLFWwindow *window;

    VkInstance instance;
    VkDebugUtilsMessengerEXT debugMessenger;
    VkSurfaceKHR surface;


    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
    VkDevice device;
    VkQueue graphicsQueue;
    VkQueue presentQueue;
    VkResult result;

    VkCommandPool commandPool;
    VkCommandBuffer commandBuffer;


    void initWindow() {
        glfwInit();

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        window = glfwCreateWindow(WIDTH, HEIGHT, "Assignment 13", nullptr, nullptr);
    }

    void initVulkan() {
        createInstance();
        createSurface();
        pickPhysicalDevice();
        createLogicalDevice();
        createCommandPool();
        createCommandBuffer();

    }

    void mainLoop() {
        while (!glfwWindowShouldClose(window)) {
            glfwPollEvents();
        }
    }

    void cleanup() {
        vkDestroyCommandPool(device, commandPool, nullptr);

        vkDestroyDevice(device, nullptr);
        vkDestroySurfaceKHR(instance, surface, nullptr);
        vkDestroyInstance(instance, nullptr);

        glfwDestroyWindow(window);

        glfwTerminate();
        std::cout << "\tResources released correctly\n\n";
    }

    void createInstance() {


        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "Assignment 13";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "No Engine";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_0;

        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;

        auto extensions = getRequiredExtensions();
        createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
        createInfo.ppEnabledExtensionNames = extensions.data();

        VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
        createInfo.enabledLayerCount = 0;

        createInfo.pNext = nullptr;


        if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
            throw std::runtime_error("failed to create instance!");
        }

        //PRINTING ALL EXTENSIONS USED
        uint32_t extensionCount = 0;
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
        std::vector <VkExtensionProperties> extensionBase(extensionCount);
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensionBase.data());
        std::cout << "available extensions:\n";

        for (const auto &extension: extensionBase) {
            std::cout << '\t' << extension.extensionName << '\n';
        }
    }

    void createCommandPool() {
        QueueFamilyIndices queueFamilyIndices = findQueueFamilies(physicalDevice);

        VkCommandPoolCreateInfo poolInfo{};
        poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
        poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
        poolInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily.value();

        if (vkCreateCommandPool(device, &poolInfo, nullptr, &commandPool) != VK_SUCCESS) {
            throw std::runtime_error("failed to create command pool!");
        }
    }

    void createCommandBuffer() {
        VkCommandBufferAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        allocInfo.commandPool = commandPool;
        allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        allocInfo.commandBufferCount = 1;

        result = vkAllocateCommandBuffers(device, &allocInfo, &commandBuffer);
        if (result != VK_SUCCESS) {
            throw std::runtime_error("failed to allocate command buffer!");
        }

        std::cout << "\t \nCommand Pool and Command Buffers created\n";
    }


    void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT &createInfo) {
        createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
        createInfo.messageSeverity =
                VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
                VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
        createInfo.messageType =
                VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
                VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
        createInfo.pfnUserCallback = debugCallback;
    }


    void createSurface() {
        if (glfwCreateWindowSurface(instance, window, nullptr, &surface) != VK_SUCCESS) {
            throw std::runtime_error("failed to create window surface!");
        }
    }

    void pickPhysicalDevice() {
        uint32_t deviceCount = 0;
        vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);

        if (deviceCount == 0) {
            throw std::runtime_error("failed to find GPUs with Vulkan support!");
        }

        std::vector<VkPhysicalDevice> devices(deviceCount);
        vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

        //Cycling to pick the first available device
        for (const auto& device : devices) {
            if (isDeviceSuitable(device)) {
                physicalDevice = device;
                break;
            }
        }

        if (physicalDevice == VK_NULL_HANDLE) {
            throw std::runtime_error("failed to find a suitable GPU!");
        }
        // Show device properties
        VkPhysicalDeviceProperties deviceProperties;
        vkGetPhysicalDeviceProperties(physicalDevice, &deviceProperties);

        std::cout <<  "\tAPI version: 0x" << std::hex <<
                  deviceProperties.apiVersion << "\n";
        std::cout << "\tDriver version: 0x" << std::hex <<
                  deviceProperties.driverVersion << "\n";
        std::cout << "\tVendor ID: 0x" << std::hex << deviceProperties.vendorID << "\n";
        std::cout << "\tDevice ID: 0x" << std::hex << deviceProperties.deviceID << "\n";
        std::cout << "\tPhysical Device Type: " << deviceProperties.deviceType << "\t";
        if(deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU )
            std::cout << " (Discrete GPU)\n";
        if(deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU )
            std::cout << " (Integrated GPU)\n";
        if(deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU )
            std::cout << " (Virtual GPU)\n";
        if(deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_CPU )
            std::cout <<  " (CPU)\n";
        std::cout << "\tDevice Name: " << deviceProperties.deviceName << "\n";

        // Show device features
        VkPhysicalDeviceFeatures deviceFeatures;
        vkGetPhysicalDeviceFeatures(physicalDevice, &deviceFeatures);

        std::cout << "\n\tPhysical Device Features:\n";
        std::cout << "\t\tgeometryShader = " << deviceFeatures.geometryShader << "\n";
        std::cout << "\t\ttessellationShader = " <<
                  deviceFeatures.tessellationShader << "\n";
        std::cout << "\t\tmultiDrawIndirect = " << deviceFeatures.multiDrawIndirect << "\n";
        std::cout << "\t\twideLines = " << deviceFeatures.wideLines << "\n";
        std::cout << "\t\tlargePoints = " << deviceFeatures.largePoints << "\n";
        std::cout << "\t\tmultiViewport = " << deviceFeatures.multiViewport << "\n";
        std::cout << "\t\tocclusionQueryPrecise = " <<
                  deviceFeatures.occlusionQueryPrecise << "\n";
        std::cout << "\t\tpipelineStatisticsQuery = " <<
                  deviceFeatures.pipelineStatisticsQuery << "\n";
        std::cout << "\t\tshaderFloat64 = " << deviceFeatures.shaderFloat64 << "\n";
        std::cout << "\t\tshaderInt64 = " << deviceFeatures.shaderInt64 << "\n";
        std::cout << "\t\tshaderInt16 = " << deviceFeatures.shaderInt16 << "\n";

        // Show device memory properties
        VkPhysicalDeviceMemoryProperties vpdmp;
        vkGetPhysicalDeviceMemoryProperties(physicalDevice, &vpdmp);
        std::cout << "\n\tMemory Types: " << vpdmp.memoryTypeCount << "\n";
        for(unsigned int i = 0; i < vpdmp.memoryTypeCount; i++) {
            VkMemoryType vmt = vpdmp.memoryTypes[i];
            std::cout << "\t\tMemory: " << i << ":";
            if((vmt.propertyFlags & VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT) != 0 )
                std::cout << " DeviceLocal";
            if((vmt.propertyFlags & VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT) != 0 )
                std::cout << " HostVisible";
            if((vmt.propertyFlags & VK_MEMORY_PROPERTY_HOST_COHERENT_BIT) != 0 )
                std::cout << " HostCoherent";
            if((vmt.propertyFlags & VK_MEMORY_PROPERTY_HOST_CACHED_BIT) != 0 )
                std::cout << " HostCached";
            if((vmt.propertyFlags & VK_MEMORY_PROPERTY_LAZILY_ALLOCATED_BIT) != 0 )
                std::cout << " LazilyAllocated";
            std::cout << "\n";
        }
        // Memory heaps
        std::cout << "\n\tMemory Heaps: " << vpdmp.memoryHeapCount << "\n";
        for(unsigned int i = 0; i < vpdmp.memoryHeapCount; i++ ) {
            std::cout << "\t\tHeap : " << i;
            VkMemoryHeap vmh = vpdmp.memoryHeaps[i];
            std::cout << " size = " << std::hex << (unsigned long int)vmh.size;
            if((vmh.flags & VK_MEMORY_HEAP_DEVICE_LOCAL_BIT) != 0)
                std::cout << " DeviceLocal";
            std::cout << "\n";
        }
    }

        void createLogicalDevice() {
            QueueFamilyIndices indices = findQueueFamilies(physicalDevice);

            std::vector <VkDeviceQueueCreateInfo> queueCreateInfos;
            std::set <uint32_t> uniqueQueueFamilies = {indices.graphicsFamily.value(), indices.presentFamily.value()};

            float queuePriority = 1.0f;
            for (uint32_t queueFamily: uniqueQueueFamilies){
                VkDeviceQueueCreateInfo queueCreateInfo{};
                queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
                queueCreateInfo.queueFamilyIndex = queueFamily;
                queueCreateInfo.queueCount = 1;
                queueCreateInfo.pQueuePriorities = &queuePriority;
                queueCreateInfos.push_back(queueCreateInfo);
            }

            VkPhysicalDeviceFeatures deviceFeatures{};

            VkDeviceCreateInfo createInfo{};
            createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

            createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
            createInfo.pQueueCreateInfos = queueCreateInfos.data();

            createInfo.pEnabledFeatures = &deviceFeatures;

            createInfo.enabledExtensionCount = 0;

            createInfo.enabledLayerCount = 0;


            if (vkCreateDevice(physicalDevice, &createInfo, nullptr, &device) != VK_SUCCESS) {
                throw std::runtime_error("failed to create logical device!");
            }

            vkGetDeviceQueue(device, indices.graphicsFamily.value(), 0, &graphicsQueue);
            vkGetDeviceQueue(device, indices.presentFamily.value(), 0, &presentQueue);
        }

        bool isDeviceSuitable(VkPhysicalDevice device) {
            QueueFamilyIndices indices = findQueueFamilies(device);

            return indices.isComplete();
        }

        QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device) {
            QueueFamilyIndices indices;

            uint32_t queueFamilyCount = 0;
            vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

            std::vector <VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
            vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());
            std::cout << "\n\tQueue Families found: " << queueFamilyCount << "\n";

            int i = 0;
            for (const auto &queueFamily: queueFamilies) {
                std::cout << "\t\tFam. " << i << ": queueCount = " <<
                      queueFamily.queueCount << "; ";

                if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
                    indices.graphicsFamily = i;
                }
                if ((queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) != 0) {
                    std::cout << " Graphics";
                }
                if ((queueFamily.queueFlags & VK_QUEUE_COMPUTE_BIT) != 0)
                    std::cout << " Compute";
                if ((queueFamily.queueFlags & VK_QUEUE_TRANSFER_BIT) != 0)
                    std::cout << " Transfer";

                VkBool32 presentSupport = false;
                vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &presentSupport);

                if (presentSupport) {
                    std::cout << " Presentation";
                    indices.presentFamily = i;
                }
                std::cout << "\n";

                if (indices.isComplete()) {
                    break;
                }

                i++;
            }

            return indices;
        }

        std::vector<const char *> getRequiredExtensions() {
            uint32_t glfwExtensionCount = 0;
            const char **glfwExtensions;
            glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

            std::vector<const char *> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);


            return extensions;
        }


        static VKAPI_ATTR VkBool32
        VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                                 VkDebugUtilsMessageTypeFlagsEXT messageType,
                                 const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData, void *pUserData) {
            std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;

            return VK_FALSE;
        }
    };


    int main() {
        Assignment13 app;

        try {
            app.run();
        } catch (const std::exception &e) {
            std::cerr << e.what() << std::endl;
            return EXIT_FAILURE;
        }

        return EXIT_SUCCESS;
    }
