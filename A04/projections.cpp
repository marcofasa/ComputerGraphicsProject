//The main parallel projection uses a half-width of w=2, the aspect ratio passed in parameter a
// and has the near and far planes located respectively at a distance of n=-4 and f=12.
//glm::mat4(1,0,0,0, 0,0,0,0, 0,0,0,0)
//glm::scale(glm::mat4(1.0),glm::vec3(1,-1,1))
#define _USE_MATH_DEFINES
#include<math.h>
//(float)cos(b * M_PI / 180.0)
//(float)sin(b * M_PI / 180.0)
float n=-4,f=12,w=2;
float l=-1*w,r=w;
glm::mat4 rotation45=glm::mat4((float)cos(45 * M_PI / 180.0),0,(float)-sin(45 * M_PI / 180.0),0, 0,1,0,0, (float)sin(45 * M_PI / 180.0),0,(float)cos(45 * M_PI / 180.0),0, 0,0,0,1);

// Create a matrix for Isometric projection with the given aspect ratio a
glm::mat4 PO1(float a) {
    float t=(w/a),b=-1*(w/a);
    glm::mat4 out = glm::mat4(1.0);
    out=glm::scale(glm::mat4(1.0),glm::vec3(1,-1,1))*glm::ortho(l,r,b,t,n,f) * glm::rotate(glm::mat4(1),(float)(35.26 * M_PI / 180.0),glm::vec3(1,0,0))*rotation45;
	return out;
}

// Create a matrix for Dimnetric projection (alpha = 45 degree)
// with the given aspect ration a
glm::mat4 PO2(float a) {
    float alpha=45;
    float t=(w/a),b=-1*(w/a);
	glm::mat4 out = glm::mat4(1.0);
    out=glm::scale(glm::mat4(1.0),glm::vec3(1,-1,1))*glm::ortho(l,r,b,t,n,f)*glm::rotate(glm::mat4(1),(float)(alpha * M_PI / 180.0),glm::vec3(1,0,0))*rotation45;
    return out;
}

// Create a matrix for Trimetric projection (alpha = 45 degree, beta = 60 degree)
// with the given aspect ration a
glm::mat4 PO3(float a) {
    int alpha=45, beta=60;
    float t=(w/a),b=-1*(w/a);
    glm::mat4 out = glm::mat4(1.0);
    out=glm::scale(glm::mat4(1.0),glm::vec3(1,-1,1))*glm::ortho(l,r,b,t,n,f)*glm::rotate(glm::mat4(1),(float)(alpha* M_PI / 180.0),glm::vec3(1,0,0))*glm::rotate(glm::mat4(1),(float)(beta* M_PI / 180.0),glm::vec3(0,1,0));
	return out;
}

// Create a matrix for Cabinet projection (alpha = 45, ro=1/2)
// with the given aspect ration a
glm::mat4 PO4(float a) {
    float t=(w/a),b=-1*(w/a);
    float ro=0.5;
    int alpha=45;
    glm::mat4 out = glm::mat4(1.0);
    out=glm::scale(glm::mat4(1.0),glm::vec3(1,-1,1))*glm::ortho(l,r,b,t,n,f)* glm::mat4(1,0,0,0,0,1,0,0,-ro*(float)cos(alpha * M_PI / 180.0),-ro*(float)sin(alpha * M_PI / 180.0),1,0,0,0,0,1);
    return out;
}

