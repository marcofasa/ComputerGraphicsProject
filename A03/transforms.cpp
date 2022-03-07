#define _USE_MATH_DEFINES
#include<math.h>

    // Rotate 45 degrees around an arbitrary axis passing through (1,0,-1). The x-axis can be aligned to the arbitrary axis after a rotation of 30 degrees around the z-axis, and then -60 degrees around the y-axis.

    glm::mat4 MT1 = glm::mat4(1);

            glm::mat4 T1a = glm::translate(glm::mat4(1),glm::vec3(1,0,-1)); // T(1,0,-1)
            glm::mat4 T1b = glm::rotate(glm::mat4(1),(float)(300 * M_PI / 180.0),glm::vec3(0,1,0)); //R(y-axis)
            glm::mat4 T1c = glm::rotate(glm::mat4(1),(float)(30 * M_PI / 180.0),glm::vec3(0,0,1)); //R(z-axis)
            glm::mat4 T1d = glm::rotate(glm::mat4(1),(float)(45 * M_PI / 180.0),glm::vec3(1,0,0)); //R(arbitrary-axis)
            glm::mat4 T1e = inverse(T1c); //R(z-axis)^-1
            glm::mat4 T1f = inverse(T1b); //R(y-axis)^-1
            glm::mat4 T1g = inverse(T1a); //T(1,0,-1)^-1

            glm::mat4 T1 = T1a*T1b*T1c*T1d*T1e*T1f*T1g;

            MT1=T1*MT1;



    // Half the size of an object, using as fixed point (5,0,-2)

	glm::mat4 MT2 =  glm::mat4(1);

            glm::mat4 T2a = glm::translate(glm::mat4(1), glm::vec3(5,0,-2));
            glm::mat4 T2b  = glm::scale(glm::mat4(1),glm::vec3(0.5));
            glm::mat4 T2c = inverse(T2a);
            glm::mat4 T2 =T2a*T2b*T2c;

            MT2=T2*MT2;






    // TODO Mirror the starship along a plane passing through (1,1,1), and obtained rotating 15 degree around the x axis the xz plane
	glm::mat4 MT3 = glm::mat4(1);

    glm::mat4 T3a = glm::translate(glm::mat4(1),glm::vec3(1,1,1));
    glm::mat4 T3b = glm::mat4(-1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1);
    glm::mat4 T3c = glm::rotate(glm::mat4(1),(float)(15 * M_PI / 180.0),glm::vec3(1,0,0)); //R(y-axis)
    //glm::mat4 T3d = glm::rotate(glm::mat4(1),60.0f*-1,glm::vec3(0,1,0)); //R(y-axis)
    glm::mat4 T3e = inverse(T3c);
    glm::mat4 T3f = inverse(T3a);

    glm::mat4 T3=T3a*T3c*T3b*T3e*T3f;

    MT3=T3*MT3;


    // Apply the inverse of the following sequence of transforms: Translation of (0, 0, 5) then rotation of 30 degree around the Y axis, and finally a uniform scaling of a factor of 3.
	glm::mat4 MT4 = glm::mat4(1);

    glm::mat4 T4a = glm::translate(glm::mat4(1),glm::vec3(0,0,5));
    glm::mat4 T4b = glm::rotate(glm::mat4(1),(float)(30 * M_PI / 180.0),glm::vec3(0,1,0)); //R(y-axis)
    glm::mat4 T4c  = glm::scale(glm::mat4(1),glm::vec3(3));


    glm::mat4 T4=inverse(T4a)*inverse(T4b)*inverse(T4c);




MT4=T4*MT4;



