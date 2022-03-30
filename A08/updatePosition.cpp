/*
 * glfwGetKey(window, GLFW_KEY_xxx)
 */
namespace w
{
    glm::mat3 CamDir = glm::mat3(1.0f);
    glm::vec3 CamPos = glm::vec3(0.0f, 0.5f, 2.5f);
    static auto startTime = std::chrono::high_resolution_clock::now();
    float lastTime = 0.0f;

}


// Create the world matrix for the robot
glm::mat4 getRobotWorldMatrix(GLFWwindow* window) {
    auto currentTime = std::chrono::high_resolution_clock::now();
    static glm::vec3 pos = w::CamPos;
    const float ROT_SPEED = glm::radians(60.0f);
    const float MOVE_SPEED = 0.75f;
    float time = std::chrono::duration<float, std::chrono::seconds::period>
            (currentTime - w::startTime).count();
    float deltaT = time - w::lastTime;
    w::lastTime = time;
												// here glm::vec3(-3,0,2) represents a
												// meaningful initial position for the robot
												//
												// this variable is here just as an example!
												// it should replaced or combined with
												//  the ones you think necessary for the task
    if(glfwGetKey(window, GLFW_KEY_A)) {
        w::CamPos -= MOVE_SPEED * glm::vec3(w::CamDir[0]) * deltaT;
    }
    if(glfwGetKey(window, GLFW_KEY_D)) {
        w::CamPos += MOVE_SPEED * glm::vec3(w::CamDir[0]) * deltaT;
    }
    /*
    if(glfwGetKey(window, GLFW_KEY_S)) {
        CamPos += MOVE_SPEED * glm::vec3(CamDir[2]) * deltaT;
    }
    if(glfwGetKey(window, GLFW_KEY_W)) {
        CamPos -= MOVE_SPEED * glm::vec3(CamDir[2]) * deltaT;
    }
    if(glfwGetKey(window, GLFW_KEY_F)) {
        CamPos -= MOVE_SPEED * glm::vec3(CamDir[1]) * deltaT;
    }
    if(glfwGetKey(window, GLFW_KEY_R)) {
        CamPos += MOVE_SPEED * glm::vec3(CamDir[1]) * deltaT;
    }
*/


    glm::mat4 out;

        out = glm::translate(glm::mat4(1), w::CamPos );

	return out;
}

