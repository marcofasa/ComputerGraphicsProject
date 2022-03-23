#define _USE_MATH_DEFINES
#include<math.h>

float GtoR(float grades){
    return (grades * M_PI / 180.0);
}


 // Create a look in direction matrix
 // Pos    -> Position of the camera
 // Angs.x -> direction (alpha)
 // Angs.y -> elevation (beta)
 // Angs.z -> roll (rho)
glm::mat4 LookInDirMat(glm::vec3 Pos, glm::vec3 Angs) {
	glm::mat4 out = glm::mat4(1.0);
    out= glm::rotate(glm::mat4(1.0),-GtoR(Angs.z),glm::vec3(0,0,1))*
             glm::rotate(glm::mat4(1.0),-GtoR(Angs.y),glm::vec3(1,0,0))*
             glm::rotate(glm::mat4(1.0),-GtoR(Angs.x),glm::vec3(0,1,0))*
             glm::translate(glm::mat4(1.0),Pos);
    out=glm::inverse(out);
	return out;
}

 // Create a look at matrix
 // Pos    -> Position of the camera (c)
 // aim    -> Position of the target (a)
 // Roll   -> roll (rho)
glm::mat4 LookAtMat(glm::vec3 Pos, glm::vec3 aim, float Roll) {
	glm::mat4 out = glm::mat4(1.0);
    out=glm::lookAt(Pos,aim,glm::vec3(0,1,0));
	return out;
}


