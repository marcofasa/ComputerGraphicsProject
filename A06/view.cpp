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
    out=    glm::translate(glm::mat4(1.0),Pos)
            *glm::rotate(glm::mat4(1.0),Angs.x,glm::vec3(0,1,0))
            *glm::rotate(glm::mat4(1.0),Angs.y,glm::vec3(1,0,0))
            *glm::rotate(glm::mat4(1.0),Angs.z,glm::vec3(0,0,1)); //Mc
    out=glm::inverse(out); //Mv

    /*        OR Compute directly the inverse of Mc
     *     out=    glm::translate(glm::mat4(1.0),Pos) where pos has its coordinates multiplied by -1
            *glm::rotate(glm::mat4(1.0),Angs.x,glm::vec3(0,1,0))
            *glm::rotate(glm::mat4(1.0),Angs.y,glm::vec3(1,0,0))
            *glm::rotate(glm::mat4(1.0),Angs.z,glm::vec3(0,0,1));
     */

	return out;
}

 // Create a look at matrix
 // Pos    -> Position of the camera (c)
 // aim    -> Position of the target (a)
 // Roll   -> roll (rho)
glm::mat4 LookAtMat(glm::vec3 Pos, glm::vec3 aim, float Roll) {
	glm::mat4 out = glm::mat4(1.0);

     out=glm::lookAt(Pos,aim,glm::vec3(0,1,0)); //Mv

     /*    There are 2 ways to apply the Roll
      * 1. Changing the direction of the up vector, according to the roll angle.
        2. Placing a rotation along the z-axis of -r after transformation of the view matrix created
        with the technique shown during the lessons.
      */

     out=glm::inverse(out); //Mc
     out=out*glm::rotate(glm::mat4(1.0),-Roll,glm::vec3(0,0,1));//Apply rotation of -p on z-axis
     out=glm::inverse(out);//Mv

     return out;
}


