// Following the Vulkan Tutorial as shown in the enclose Assignment13.pdf, complete
// this Vulkan initialization sample. You can copy and past code from Example E08,
// or from other assginments such as Assignment0.cpp

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <vector>

const uint32_t WIDTH = 640;
const uint32_t HEIGHT = 480;

class Assignment13 {
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
	
    GLFWwindow* window;
    VkInstance instance;

    void initWindow() {
        glfwInit();

		// Continue with window creation
    }

    void initVulkan() {
		createInstance();
		// Continue with:
		// Prsentation Surface Creation
		// Physical Device selection
		// Logical Device creation
		// Command Pool creation
		// Command Buffer creation
    }
    
    void createInstance() {
    	// place your Vulkan instance creation code here [you can take it from Assingment 12]
    }


	void initApp() {
		// This will not be needed in this assignment!
	}

    void mainLoop() {
    	// Wait for the window to close [you can take it from Assingment 12]
    }

    void cleanup() {
    	// Add code to release all resources

        glfwTerminate();
    }
};

int main() {
    Assignment13 app;

    try {
        app.run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}