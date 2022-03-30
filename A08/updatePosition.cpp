/*
 * glfwGetKey(window, GLFW_KEY_xxx)
 */


// Create the world matrix for the robot
glm::mat4 getRobotWorldMatrix(GLFWwindow* window) {
	static glm::vec3 pos = glm::vec3(-3,0,2);	// variable to store robot position
												// here glm::vec3(-3,0,2) represents a
												// meaningful initial position for the robot
												//
												// this variable is here just as an example!
												// it should replaced or combined with
												//  the ones you think necessary for the task

	glm::mat4 out;
	
	out = glm::translate(glm::mat4(1), pos);	// this line has to be changed!
												// it is here just to allow the program to
												// be compiled and run
	return out;
}

