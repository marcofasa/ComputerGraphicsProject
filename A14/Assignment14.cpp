// Following the Vulkan Tutorial as shown in the enclose Assignment13.pdf, complete
// this Vulkan initialization sample. You can copy and past code from Example E08,
// or from other assignments such as Assignment0.cpp

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

const std::vector<const char*> deviceExtensions = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger) {
    auto func = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
    if (func != nullptr) {
        return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
    } else {
        return VK_ERROR_EXTENSION_NOT_PRESENT;
    }
}

void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator) {
    auto func = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
    if (func != nullptr) {
        func(instance, debugMessenger, pAllocator);
    }
}

struct QueueFamilyIndices {
    std::optional<uint32_t> graphicsFamily;
    std::optional<uint32_t> presentFamily;

    bool isComplete() {
        return graphicsFamily.has_value() && presentFamily.has_value();
    }
};

struct SwapChainSupportDetails {
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
};


class Assignment14 {
public:
    void run() {
        initWindow();
        initVulkan();
        initApp();
        mainLoop();
        cleanup();
    }

private:
	// place all the application variables here. As an example, here the one for the GLFW Window
	// and the Vulkan instances are already defined.

    GLFWwindow *window;

    VkInstance instance;
    VkDebugUtilsMessengerEXT debugMessenger;
    VkSurfaceKHR surface;
    VkInstanceCreateInfo createInfo{};



    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
    VkDevice device;
    VkQueue graphicsQueue;
    VkQueue presentQueue;
    VkResult result;

    VkSwapchainKHR swapChain;
    std::vector<VkImage> swapChainImages;
    VkFormat swapChainImageFormat;
    VkExtent2D swapChainExtent;
    std::vector<VkImageView> swapChainImageViews;
    std::vector<VkSurfaceFormatKHR> SCformats;
    std::vector<VkPresentModeKHR> SCpresentModes;
    VkSurfaceCapabilitiesKHR SCcapabilities;


    VkCommandPool commandPool;
    VkCommandBuffer commandBuffer;



    void initWindow() {
        glfwInit();

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        window = glfwCreateWindow(WIDTH, HEIGHT, "Assignment 14", nullptr, nullptr);
    }

    void initVulkan() {

        createInstance();
        createSurface();
        pickPhysicalDevice();
        createLogicalDevice();
       createSwapChain();//NEW
        createImageViews();//NEW
        createCommandPool();
        createCommandBuffer();
    }

    void createInstance() {
        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "Assignment 14";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "No Engine";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_0;

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
        std::cout << "EXTENSIONS:\n";

        for (const auto &extension: extensionBase) {
            std::cout << '\t' << extension.extensionName << '\n';
        }
    }


	void initApp() {
		// This will not be needed in this assignment!
	}

    void mainLoop() {
        while (!glfwWindowShouldClose(window)) {
            glfwPollEvents();
        }
    }

    void cleanup(){
        /*
         *  NEW Added logic to clean up
         */
    for (auto imageView : swapChainImageViews) {
        vkDestroyImageView(device, imageView, nullptr);
    }

    vkDestroySwapchainKHR(device, swapChain, nullptr);
    vkDestroyDevice(device, nullptr);



        vkDestroyCommandPool(device, commandPool, nullptr);

        vkDestroyDevice(device, nullptr);
        vkDestroySurfaceKHR(instance, surface, nullptr);
        vkDestroyInstance(instance, nullptr);

        glfwDestroyWindow(window);

        glfwTerminate();
        std::cout << "Resources released correctly!\n\n";        glfwTerminate();
    }

    void createCommandPool() {
        QueueFamilyIndices queueFamilyIndices = findQueueFamilies(physicalDevice,false);

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


    void createSurface() {
        if (glfwCreateWindowSurface(instance, window, nullptr, &surface) != VK_SUCCESS) {
            throw std::runtime_error("failed to create window surface!");
        }else
        {
            std::cout << "window surface created\n";
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
        std::cout <<    "\n SPECS: \n ";

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
        createInfo.enabledExtensionCount =
                static_cast<uint32_t>(deviceExtensions.size());
        createInfo.ppEnabledExtensionNames = deviceExtensions.data();

        QueueFamilyIndices indices = findQueueFamilies(physicalDevice,true);
        std::cout << "AAAAAA";

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


    void createSwapChain() {
        querySwapChainSupport(physicalDevice);

// Creates the swap chain
        std::cout << "\tTrying to create the Swap Chain\n";

        // one: selection of format, mode and number of images
        VkSurfaceFormatKHR surfaceFormat =
                chooseSwapSurfaceFormat(SCformats);
        VkPresentModeKHR presentMode =
                chooseSwapPresentMode(SCpresentModes);
        VkExtent2D extent = chooseSwapExtent(SCcapabilities,window);

        uint32_t imageCount = SCcapabilities.minImageCount + 1;

        if (SCcapabilities.maxImageCount > 0 &&
            imageCount > SCcapabilities.maxImageCount) {
            imageCount = SCcapabilities.maxImageCount;
        }

        std::cout << "\tFormat chosen: " << surfaceFormat.format <<
                  ", Color Space:" << surfaceFormat.colorSpace << "\n";
        switch(presentMode) {
            case VK_PRESENT_MODE_IMMEDIATE_KHR:
                std::cout << "\tVK_PRESENT_MODE_IMMEDIATE_KHR\n";
                break;
            case VK_PRESENT_MODE_MAILBOX_KHR:
                std::cout << "\tVK_PRESENT_MODE_MAILBOX_KHR\n";
                break;
            case VK_PRESENT_MODE_FIFO_KHR:
                std::cout << "\tVK_PRESENT_MODE_FIFO_KHR\n";
                break;
            case VK_PRESENT_MODE_FIFO_RELAXED_KHR:
                std::cout << "\tVK_PRESENT_MODE_FIFO_RELAXED_KHR\n";
                break;
            default :
                std::cout << "\t\tMode: " << presentMode << "\n";
                break;
        }
        std::cout << "\tChosen Image Exent: " << extent.width << "x" <<
                  extent.height << "\n";
        std::cout << "\tSwap chain Image Count: " << imageCount << "\n";

        // two: actual swap chain creation
        VkSwapchainKHR swapChain;

        VkSwapchainCreateInfoKHR SCcreateInfo{};
        SCcreateInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
        SCcreateInfo.surface = surface;
        SCcreateInfo.minImageCount = imageCount;
        SCcreateInfo.imageFormat = surfaceFormat.format;
        SCcreateInfo.imageColorSpace = surfaceFormat.colorSpace;
        SCcreateInfo.imageExtent = extent;
        SCcreateInfo.imageArrayLayers = 1;
        SCcreateInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
        QueueFamilyIndices indices = findQueueFamilies(physicalDevice,false);

        uint32_t queueFamilyIndices[] = {indices.graphicsFamily.value(),
                                         indices.presentFamily.value()};
        if (indices.presentFamily != indices.presentFamily) {
            SCcreateInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
            SCcreateInfo.queueFamilyIndexCount = 2;
            SCcreateInfo.pQueueFamilyIndices = queueFamilyIndices;
        } else {
            SCcreateInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
            SCcreateInfo.queueFamilyIndexCount = 0;
            SCcreateInfo.pQueueFamilyIndices = nullptr;
        }

        SCcreateInfo.preTransform = SCcapabilities.currentTransform;
        SCcreateInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
        SCcreateInfo.presentMode = presentMode;
        SCcreateInfo.clipped = VK_TRUE;
        SCcreateInfo.oldSwapchain = VK_NULL_HANDLE;

        VkResult result = vkCreateSwapchainKHR(device, &SCcreateInfo,
                                               nullptr, &swapChain);
        if (result != VK_SUCCESS) {
            throw std::runtime_error("failed to create swap chain!");
        }
        std::cout << "\tSwap chain created\n";

    }

    void createImageViews() {
        uint32_t imageCount = SCcapabilities.minImageCount + 1;

        vkGetSwapchainImagesKHR(device, swapChain, &imageCount, nullptr);
        swapChainImages.resize(imageCount);
        vkGetSwapchainImagesKHR(device, swapChain, &imageCount,
                                swapChainImages.data());

        // two: VkImageView

        swapChainImageViews.resize(swapChainImages.size());
        VkSurfaceFormatKHR surfaceFormat =
                chooseSwapSurfaceFormat(SCformats);
        for (size_t i = 0; i < swapChainImages.size(); i++) {
            VkImageViewCreateInfo viewInfo{};
            viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
            viewInfo.image = swapChainImages[i];
            viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
            viewInfo.format = surfaceFormat.format;
            viewInfo.subresourceRange.aspectMask =
                    VK_IMAGE_ASPECT_COLOR_BIT;
            viewInfo.subresourceRange.baseMipLevel = 0;
            viewInfo.subresourceRange.levelCount = 1;
            viewInfo.subresourceRange.baseArrayLayer = 0;
            viewInfo.subresourceRange.layerCount = 1;

            VkImageView imageView;

            VkResult result = vkCreateImageView(device, &viewInfo, nullptr,
                                                &imageView);
            if (result != VK_SUCCESS) {
                throw std::runtime_error("failed to create image view!");
            }

            swapChainImageViews[i] = imageView;
        }
        std::cout << "\tImages and Views retrieved\n";

        // device resource release
        for (size_t i = 0; i < swapChainImageViews.size(); i++){
            vkDestroyImageView(device, swapChainImageViews[i], nullptr);
        }
        vkDestroySwapchainKHR(device, swapChain, nullptr);
        vkDestroyDevice(device, nullptr);
        std::cout << "\tResources released correctly\n\n";

    }



    VkSurfaceFormatKHR chooseSwapSurfaceFormat(
            const std::vector<VkSurfaceFormatKHR>& availableFormats)
    {
        for (const auto& availableFormat : availableFormats) {
            if (availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB &&
                availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
                return availableFormat;
            }
        }

        return availableFormats[0];
    }

    VkPresentModeKHR chooseSwapPresentMode(
            const std::vector<VkPresentModeKHR>& availablePresentModes) {
        for (const auto& availablePresentMode : availablePresentModes) {
            if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR) {
                return availablePresentMode;
            }
        }
        return VK_PRESENT_MODE_FIFO_KHR;
    }

    VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities,
                                GLFWwindow* window) {
        if (capabilities.currentExtent.width != UINT32_MAX) {
            return capabilities.currentExtent;
        } else {
            int width, height;
            glfwGetFramebufferSize(window, &width, &height);

            VkExtent2D actualExtent = {
                    static_cast<uint32_t>(width),
                    static_cast<uint32_t>(height)
            };
            actualExtent.width = std::max(capabilities.minImageExtent.width,
                                          std::min(capabilities.maxImageExtent.width, actualExtent.width));
            actualExtent.height = std::max(capabilities.minImageExtent.height,
                                           std::min(capabilities.maxImageExtent.height, actualExtent.height));
            return actualExtent;
        }
    }

    void querySwapChainSupport(VkPhysicalDevice device) {
        // Query Swap Chain Capabilities, supported Formats and Present modes
        // One: capabilities
        vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice, surface,
                                                  &SCcapabilities);
        std::cout << "\t Min. Image Count: " << SCcapabilities.minImageCount << "\n";
        std::cout << "\t Max. Image Count: " << SCcapabilities.maxImageCount << "\n";
        std::cout << "\t Min. Image Exent: " << SCcapabilities.minImageExtent.width << "x" <<
                  SCcapabilities.minImageExtent.height << "\n";
        std::cout << "\t Cur. Image Exent: " << SCcapabilities.currentExtent.width << "x" <<
                  SCcapabilities.currentExtent.height << "\n";
        std::cout << "\t Max. Image Exent: " << SCcapabilities.maxImageExtent.width << "x" <<
                  SCcapabilities.maxImageExtent.height << "\n";
        std::cout << "\n";

        // Two: formats
        uint32_t formatCount;
        vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, &formatCount,
                                             nullptr);

        if (formatCount != 0) {
            SCformats.resize(formatCount);
            vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface,
                                                 &formatCount, SCformats.data());
            std::cout << "\t Supported Formats: " << formatCount << "\n";
            for(int i = 0; i < formatCount; i++) {
                std::cout << "\t\tFormat: " << SCformats[i].format <<
                          ", Color Space:" << SCformats[i].colorSpace <<"\n";
            }
        }
        std::cout << "[see: <https://www.khronos.org/registry/vulkan/specs/1.3-extensions/man/html/VkFormat.html> for Formats]\n";
        std::cout << "[see: <https://www.khronos.org/registry/vulkan/specs/1.3-extensions/man/html/VkColorSpaceKHR.html> for Color Spaces]\n";
        std::cout << "\n";

        // Three: present modes
        uint32_t presentModeCount;
        vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface,
                                                  &presentModeCount, nullptr);

        std::vector<VkPresentModeKHR> SCpresentModes;
        if (presentModeCount != 0) {
            SCpresentModes.resize(presentModeCount);
            vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface,
                                                      &presentModeCount, SCpresentModes.data());
            std::cout << "\t Supported Modes: " << presentModeCount << "\n";
            for(int i = 0; i < presentModeCount; i++) {
                switch(SCpresentModes[i]) {
                    case VK_PRESENT_MODE_IMMEDIATE_KHR:
                        std::cout << "\t\tVK_PRESENT_MODE_IMMEDIATE_KHR\n";
                        break;
                    case VK_PRESENT_MODE_MAILBOX_KHR:
                        std::cout << "\t\tVK_PRESENT_MODE_MAILBOX_KHR\n";
                        break;
                    case VK_PRESENT_MODE_FIFO_KHR:
                        std::cout << "\t\tVK_PRESENT_MODE_FIFO_KHR\n";
                        break;
                    case VK_PRESENT_MODE_FIFO_RELAXED_KHR:
                        std::cout << "\t\tVK_PRESENT_MODE_FIFO_RELAXED_KHR\n";
                        break;
                    default :
                        std::cout << "\t\tMode: " << SCpresentModes[i] << "\n";
                        break;
                }
            }
        }
        std::cout << "\n";

    }

    bool isDeviceSuitable(VkPhysicalDevice device) {
        QueueFamilyIndices indices = findQueueFamilies(device,false);

        bool extensionsSupported = checkDeviceExtensionSupport(device);

        bool swapChainAdequate = true;


        return indices.isComplete() && extensionsSupported && swapChainAdequate;
    }

    bool checkDeviceExtensionSupport(VkPhysicalDevice device) {
        uint32_t extensionCount;
        vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

        std::vector<VkExtensionProperties> availableExtensions(extensionCount);
        vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());

        std::set<std::string> requiredExtensions(deviceExtensions.begin(), deviceExtensions.end());

        for (const auto& extension : availableExtensions) {
            requiredExtensions.erase(extension.extensionName);
        }

        return requiredExtensions.empty();
    }






/**
 * If debug true prints the queue available for this device
 * @param device
 * @param debug
 * @return
 */
    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device,bool debug) {
        QueueFamilyIndices indices;

        uint32_t queueFamilyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

        std::vector <VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());
        if (debug) std::cout << "\n\tQueue Families found: " << queueFamilyCount << "\n";


        int i = 0;
        for (const auto &queueFamily: queueFamilies) {
            if(debug)  std::cout << "\t\tFam. " << i<< ": queueCount = " <<
                                 queueFamily.queueCount << "; ";


            if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
                indices.graphicsFamily = i; //aQueueWithGraphicsCapability
            }
            if ((queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) != 0) {
                if(debug)  std::cout << " Graphics";
            }
            if ((queueFamily.queueFlags & VK_QUEUE_COMPUTE_BIT) != 0)
                if(debug) std::cout << " Compute";
            if ((queueFamily.queueFlags & VK_QUEUE_TRANSFER_BIT) != 0)
                if(debug)  std::cout << " Transfer";

            VkBool32 presentSupport = false;
            vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &presentSupport);

            if (presentSupport) {
                if(debug)  std::cout << " Presentation";
                indices.presentFamily = i;
            }
            if(debug)   std::cout << "\n";
            i++;
            //std::cout << "AAAAAA \n";

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



};





int main() {
    Assignment14 app;

    try {
        app.run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}