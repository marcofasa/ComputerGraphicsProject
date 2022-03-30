/*
 * glfwGetKey(window, GLFW_KEY_xxx)
 */

//Namespace with global variable that are updated every clock of the method
namespace w
{
    glm::mat3 CamDir = glm::mat3(1.0f);
    glm::vec3 CamPos = glm::vec3(-3.0f,0.0f,2.0f);
    static auto startTime = std::chrono::high_resolution_clock::now();
    float lastTime = 0.0f;
}


//Apply an Euler Matrix with only a Roll to have the correct orientation when moving
glm::mat4 EulerRoll(glm::vec3 pos, float roll) {
    glm::mat4 out = glm::translate(glm::mat4(1.0), pos) * //Translation to position
                    glm::rotate(glm::mat4(1.0),roll, glm::vec3(0,1,0));//Roll over
    return out;
}


// Create the world matrix for the robot
glm::mat4 getRobotWorldMatrix(GLFWwindow* window) {
    //TIME AND CONSTANTS
    auto currentTime = std::chrono::high_resolution_clock::now();
    const float ROT_SPEED = glm::radians(60.0f);
    const float MOVE_SPEED = 0.75f;
    float time = std::chrono::duration<float, std::chrono::seconds::period>
            (currentTime - w::startTime).count();
    float deltaT = time - w::lastTime;
    w::lastTime = time;

    //output
    glm::mat4 out;

    //MOVEMENT <--> A west ,S south ,D right,W north
    if(glfwGetKey(window, GLFW_KEY_A)) {
        w::CamPos  -= MOVE_SPEED * glm::vec3( w::CamDir[0]) * deltaT;
        out= EulerRoll(w::CamPos,glm::radians(180.0f));
        return out;
    }
    //No roll because by default is looking right
    if(glfwGetKey(window, GLFW_KEY_D)) {
        w::CamPos += MOVE_SPEED * glm::vec3(w::CamDir[0]) * deltaT;
    }

    if(glfwGetKey(window, GLFW_KEY_S)) {
        w:: CamPos += MOVE_SPEED * glm::vec3(w::CamDir[2]) * deltaT;
        out= EulerRoll(w::CamPos,glm::radians(-90.0f));
        return out;
    }
    if(glfwGetKey(window, GLFW_KEY_W)) {
        w:: CamPos -= MOVE_SPEED * glm::vec3(w::CamDir[2]) * deltaT;
        out= EulerRoll(w::CamPos,glm::radians(90.0f));
        return out;
    }
    //DOWN
    if(glfwGetKey(window, GLFW_KEY_F)) {
        w:: CamPos -= MOVE_SPEED * glm::vec3(w::CamDir[1]) * deltaT;
    }

    //UP
    if(glfwGetKey(window, GLFW_KEY_R)) {
        w:: CamPos += MOVE_SPEED * glm::vec3(w::CamDir[1]) * deltaT;
    }

    //Passing to output if no Euler Roll Matrix applied
    out = glm::translate(glm::mat4(1), w::CamPos );

    return out;
}

