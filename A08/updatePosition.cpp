/*
 * glfwGetKey(window, GLFW_KEY_xxx)
 */
namespace w
{
    glm::mat3 CamDir = glm::mat3(1.0f);
    glm::vec3 CamPos = glm::vec3(-3.0f,0.0f,2.0f);
    static auto startTime = std::chrono::high_resolution_clock::now();
    float lastTime = 0.0f;

}


// Create the world matrix for the robot
glm::mat4 getRobotWorldMatrix(GLFWwindow* window) {
    auto currentTime = std::chrono::high_resolution_clock::now();
    const float ROT_SPEED = glm::radians(60.0f);
    const float MOVE_SPEED = 0.75f;
    float time = std::chrono::duration<float, std::chrono::seconds::period>
            (currentTime - w::startTime).count();
    float deltaT = time - w::lastTime;
    w::lastTime = time;

    bool movement=false;
    bool rotation=false;


    //MOVEMENT <--> A,S,D,W
    if(glfwGetKey(window, GLFW_KEY_A)) {
        w::CamPos  -= MOVE_SPEED * glm::vec3( w::CamDir[0]) * deltaT;
        movement=true;
    }
    if(glfwGetKey(window, GLFW_KEY_D)) {
        w::CamPos += MOVE_SPEED * glm::vec3(w::CamDir[0]) * deltaT;
        movement=true;
    }
    if(glfwGetKey(window, GLFW_KEY_S)) {
        w:: CamPos += MOVE_SPEED * glm::vec3(w::CamDir[2]) * deltaT;
        movement=true;
    }
    if(glfwGetKey(window, GLFW_KEY_W)) {
        w:: CamPos -= MOVE_SPEED * glm::vec3(w::CamDir[2]) * deltaT;
        movement=true;
    }
    if(glfwGetKey(window, GLFW_KEY_F)) {
        w:: CamPos -= MOVE_SPEED * glm::vec3(w::CamDir[1]) * deltaT;
        movement=true;
    }
    if(glfwGetKey(window, GLFW_KEY_R)) {
        w:: CamPos += MOVE_SPEED * glm::vec3(w::CamDir[1]) * deltaT;
        movement=true;
    }

    //ROTATION <--> ARROWS
    if(glfwGetKey(window, GLFW_KEY_LEFT)) {
        w::CamDir = glm::mat3(glm::rotate(glm::mat4(1.0f),
                                       deltaT * ROT_SPEED,
                                       glm::vec3( w::CamDir[1])) * glm::mat4( w::CamDir));
        rotation= true;
    }
    if(glfwGetKey(window, GLFW_KEY_RIGHT)) {
        w::CamDir = glm::mat3(glm::rotate(glm::mat4(1.0f),
                                       -deltaT * ROT_SPEED,
                                       glm::vec3( w::CamDir[1])) * glm::mat4( w::CamDir));
        rotation= true;
    }
    if(glfwGetKey(window, GLFW_KEY_UP)) {
        w::CamDir = glm::mat3(glm::rotate(glm::mat4(1.0f),
                                       deltaT * ROT_SPEED,
                                       glm::vec3( w::CamDir[0])) * glm::mat4( w::CamDir));
        rotation= true;
    }
    if(glfwGetKey(window, GLFW_KEY_DOWN)) {
        w::CamDir = glm::mat3(glm::rotate(glm::mat4(1.0f),
                                       -deltaT * ROT_SPEED,
                                       glm::vec3( w::CamDir[0])) * glm::mat4( w::CamDir));
        rotation= true;
    }


//Passing to output
    glm::mat4 out;
        out = glm::translate(glm::mat4(1), w::CamPos );



	return out;
}

