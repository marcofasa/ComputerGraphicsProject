namespace t{

}

#define _USE_MATH_DEFINES
#include<math.h>

float GtoR(float grades){
    return (grades * M_PI / 180.0);
}

float RtoG(float radians){
    return (radians * 180.0 / M_PI);
}

// this function creates the geometries to be shown, and output thems
// in global variables M1_vertices and M1_indices to M4_vertices and M4_indices
void makeModels() {
//// M1 : Cube
// Replace the code below, that creates a simple square, with the one to create a cube.

// Resizes the vertices array. Repalce the values with the correct number of
// vertices components (3 * number of vertices==8)
M1_vertices.resize(3 * 8);

    M1_vertices= {0,0,0,  0,0,1, // Vertex array:
                0,1,1,  0,1,0, // x y z for
                1,0,0,  1,0,1, // 8 different vertices
                1,1,1,  1,1,0};
// Resizes the indices array. Repalce the values with the correct number of
// indices (3 * number of triangles)
M1_indices.resize(3*12);



    M1_indices={0,1,2, 2,3,0,
                0,3,4, 4,3,7,   // 36 indices
            5,6,7, 7,4,5,   // to the vertices of
            1,6,5, 1,2,6,   // 12 triangles composing
            7,6,2, 3,2,7,   // 6 faces of a cube
            4,5,0, 1,0,5};






//// M2 : Cylinder
// Replace the code below, that creates a simple rotated square, with the one to create a cylinder.

// Resizes the vertices array. Repalce the values with the correct number of
// vertices components (3 * number of vertices)
/*
 * TOP Cap
 *
 *
 *nsclice+1 needed
 *
 *
 *
 *
 *
 */

int NSlices=36;
float radius = 1;
float height =1;
float cx=0.0,cy=0.0,cz=-3.0;
M2_vertices.resize((NSlices+1)*3);

// Vertices definitions
M2_vertices[0] = cx;
M2_vertices[1] = cy + height;
M2_vertices[2] = cz;

for(int i=0;i<NSlices;i++){
    M2_vertices[(i+1)*3 +0]= cx+radius*cos((float)(i*2.0*M_PI/NSlices));
    M2_vertices[(i+1)*3 +1]= cy+height;
    M2_vertices[(i+1)*3 +2]= cz+radius*sin((float)(i*2.0*M_PI/NSlices));
}

// Resizes the indices array. Repalce the values with the correct number of
// indices (3 * number of triangles)
M2_indices.resize(3* NSlices);

    for (int i=0;i<NSlices;i++){
        M2_indices[i*3]=0;
        M2_indices[i*3+1]=i+1;
        //At the last iteration we must return to zero index because we are going overflow with the number of vertex
        M2_indices[i*3+2]=(i+1)% NSlices + 1;

    }



//// M3 : Sphere
// Replace the code below, that creates a simple triangle, with the one to create a sphere.

// Resizes the vertices array. Repalce the values with the correct number of
// vertices components (3 * number of vertices)
M3_vertices.resize(9);

// Vertices definitions
M3_vertices[0]  =  0.0;
M3_vertices[1]  =  1.0;
M3_vertices[2]  = -1.2;
M3_vertices[3]  = -0.866;
M3_vertices[4]  = -0.5;
M3_vertices[5]  = -1.2;
M3_vertices[6]  =  0.866;
M3_vertices[7]  = -0.5;
M3_vertices[8]  = -1.2;


// Resizes the indices array. Repalce the values with the correct number of
// indices (3 * number of triangles)
M3_indices.resize(3* 10);

// indices definitions
M3_indices[0] = 0;
M3_indices[1] = 1;
M3_indices[2] = 2;









//// M4 : Spring
// Replace the code below, that creates a simple octahedron, with the one to create a spring.
M4_vertices.resize(3 * 6);

// Vertices definitions
M4_vertices[0]  =  0.0;
M4_vertices[1]  =  1.414;
M4_vertices[2]  = -1.0;
M4_vertices[3]  =  0.0;
M4_vertices[4]  = -1.414;
M4_vertices[5]  = -1.0;
M4_vertices[6]  = -1.0;
M4_vertices[7]  =  0.0;
M4_vertices[8]  = -2.0;
M4_vertices[9]  = -1.0;
M4_vertices[10] =  0.0;
M4_vertices[11] =  0.0;
M4_vertices[12] =  1.0;
M4_vertices[13] =  0.0;
M4_vertices[14] =  0.0;
M4_vertices[15] =  1.0;
M4_vertices[16] =  0.0;
M4_vertices[17] = -2.0;


// Resizes the indices array. Repalce the values with the correct number of
// indices (3 * number of triangles)
M4_indices.resize(3 * 8);

// indices definitions
M4_indices[0]  = 0;
M4_indices[1]  = 2;
M4_indices[2]  = 3;
M4_indices[3]  = 1;
M4_indices[4]  = 3;
M4_indices[5]  = 2;
M4_indices[6]  = 0;
M4_indices[7]  = 3;
M4_indices[8]  = 4;
M4_indices[9]  = 1;
M4_indices[10] = 4;
M4_indices[11] = 3;
M4_indices[12] = 0;
M4_indices[13] = 4;
M4_indices[14] = 5;
M4_indices[15] = 1;
M4_indices[16] = 5;
M4_indices[17] = 4;
M4_indices[18] = 0;
M4_indices[19] = 5;
M4_indices[20] = 2;
M4_indices[21] = 1;
M4_indices[22] = 2;
M4_indices[23] = 5;
}