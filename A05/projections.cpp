//glm::mat4(1,0,0,0, 0,0,0,0, 0,0,0,0)
//glm::scale(glm::mat4(1.0),glm::vec3(1,-1,1))
#define _USE_MATH_DEFINES
#include<math.h>
//(float)tan(b * M_PI / 180.0)
//(float)sin(b * M_PI / 180.0)

float n=0.1,f=9.9;


// Create a matrix for Perspecrtive projection with the given aspect ratio a,
// and a FovY = 90o


glm::mat4 PO1(float a) {
    float FovY=90;
    float t=n*(float)tan(FovY * M_PI / 180.0);
    float b=-1*n*(float)tan(FovY * M_PI / 180.0);
    float l=-1*a*n*(float)tan(FovY * M_PI / 180.0);
    float r=a*n*(float)tan(FovY * M_PI / 180.0);

    glm::mat4 out1 = glm::scale(glm::mat4(1.0),glm::vec3(1,-1,1))*glm::frustum(l,r,b,t,n,f);
    glm::mat4 out = glm::perspective(float(FovY * M_PI / 180.0),a,n,f);
    out[1][1]*=-1;

	return out;
}

// TODO Create a matrix for Perspecrtive projection with the given aspect ratio a,
// and a FovY = 120o
glm::mat4 PO2(float a) {
    float FovY=120;
    float t=n*(float)tan(FovY * M_PI / 180.0);
    float b=-1*n*(float)tan(FovY * M_PI / 180.0);
    float l=-1*a*n*(float)tan(FovY * M_PI / 180.0);
    float r=a*n*(float)tan(FovY * M_PI / 180.0);
	glm::mat4 out1 = glm::scale(glm::mat4(1.0),glm::vec3(1,-1,1))*glm::frustum(l,r,b,t,n,f);
    glm::mat4 out = glm::perspective(float(FovY * M_PI / 180.0),a,n,f);
    out[1][1]*=-1;
	return out;
}

// Create a matrix for Perspecrtive projection with the given aspect ratio a,
// and a FovY = 30o
glm::mat4 PO3(float a) {
    float FovY=30;
    float t=n*(float)tan(FovY * M_PI / 180.0);
    float b=-1*n*(float)tan(FovY * M_PI / 180.0);
    float l=-a*n*(float)tan(FovY * M_PI / 180.0);
    float r=a*n*(float)tan(FovY * M_PI / 180.0);
    glm::mat4 out1 = glm::scale(glm::mat4(1.0),glm::vec3(1,-1,1))*glm::frustum(l,r,b,t,n,f);
    glm::mat4 out = glm::perspective(float(FovY * M_PI / 180.0),a,n,f);
    out[1][1]*=-1;
	return out;
}

// TODO Create a matrix for Perspecrtive projection, with the given aspect ratio a.
// Here the perspective should only show the left side of the view
// with a FovY = 90o. Here r=0, and l, t and b should be computed
// to match both the aspect ratio and the FovY
glm::mat4 PO4(float a) {
    float FovY=90;
    float t=n*(float)tan(FovY * M_PI / 180.0);
    float b=-1*n*(float)tan(FovY * M_PI / 180.0);
    float l=-a*n*(float)tan(FovY * M_PI / 180.0);
    float r=0;
    glm::mat4 out = glm::scale(glm::mat4(1.0),glm::vec3(1,-1,1))*glm::frustum(l,r,b,t,n,f);
	return out;
}

