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

int NSlices=33;
float radius = 1;
float height =1;
float cx=0.0,cy=0.0,cz=-3.0;
M2_vertices.resize((NSlices+1)*6);

// Vertices definitions
M2_vertices[0] = cx;
M2_vertices[1] = cy + height;
M2_vertices[2] = cz;

    M2_vertices[3] = cx;
    M2_vertices[4] = cy - height;
    M2_vertices[5] = cz;

for(int i=0;i<NSlices;i++){
    M2_vertices[(i+1)*6 +0]= cx+radius*cos((float)(i*2.0*M_PI/NSlices));
    M2_vertices[(i+1)*6 +1]= cy+height;
    M2_vertices[(i+1)*6 +2]= cz+radius*sin((float)(i*2.0*M_PI/NSlices));
    //----
    M2_vertices[(i+1)*6 +3]= cx+radius*cos((float)(i*2.0*M_PI/NSlices));
    M2_vertices[(i+1)*6 +4]= cy-height;
    M2_vertices[(i+1)*6 +5]= cz+radius*sin((float)(i*2.0*M_PI/NSlices));
}

// Resizes the indices array. Repalce the values with the correct number of
// indices (3 * number of triangles)
M2_indices.resize(12* NSlices);
int a=0,b=1,c=2,d=3;
    for (int i=0;i<NSlices;i++){
        M2_indices[i*12]=0;
        M2_indices[i*12+1]=(a% ((NSlices)*2)) +2;

        //At the last iteration we must return to zero index because we are going overflow with the number of vertex
        M2_indices[i*12+2]=(c% ((NSlices)*2)) +2;
        //Triangolo sopra


        M2_indices[i*12+3]=(a% ((NSlices)*2)) +2;
        M2_indices[i*12+4]=(b% ((NSlices)*2)) +2;
        //At the last iteration we must return to zero index because we are going overflow with the number of vertex
        M2_indices[i*12+5]=(d% ((NSlices)*2)) +2;

        M2_indices[i*12+6]=(a% ((NSlices)*2)) +2 ;
        M2_indices[i*12+7]=(c% ((NSlices)*2)) +2;
        //At the last iteration we must return to zero index because we are going overflow with the number of vertex
        M2_indices[i*12+8]=(d% ((NSlices)*2)) +2 ;
//Quadrato

        M2_indices[i*12+9]=1;
        M2_indices[i*12+10]=(b% ((NSlices)*2)) +2 ;
        //At the last iteration we must return to zero index because we are going overflow with the number of vertex
        M2_indices[i*12+11]=(d % ((NSlices)*2)) +2;

        a=a+2;
        b=b+2;
        c=c+2;
        d=d+2;
    }



//// M3 : Sphere
// Resizes the vertices array. Repalce the values with the correct number of
// vertices components (3 * number of vertices)

/*
    float x, y, z;                             // vertex position
    float stackCount=40;
    float sectorCount=40;
    float sectorStep = 2 * M_PI / sectorCount;
    float stackStep = M_PI / stackCount;
    float theta, stackAngle;
    float r=2;
    float phi;
    M3_vertices.resize((sectorCount*stackCount)*3*4);
    for(int i = 0; i <= stackCount; ++i)
    {
        phi = (M_PI / 2) - (stackStep * i));        // starting from pi/2 to -pi/2
        z= r*sinf(phi);
        // add (sectorCount+1) vertices per stack
        // the first and last vertices have same position and normal, but different tex coords
        for(int j = 0; j <= sectorCount; ++j) {
            theta = j * sectorStep;           // starting from 0 to 2pi

            // vertex position (x, y, z)
            x = r * cosf(phi) * cosf(theta);             // r * cos(u) * cos(v)
            y = r * cosf(phi) * sinf(theta);             // r * cos(u) * sin(v)


            M3_vertices.push_back(x);
            M3_vertices.push_back(y);
            M3_vertices.push_back(z);


        }}



// generate CCW index list of sphere triangles
// k1--k1+1
// |  / |
// | /  |
// k2--k2+1

// Resizes the indices array. Replace the values with the correct number of
// indices (3 * number of triangles)
M3_indices.resize(sectorCount*stackCount*6);

    int k1, k2;
    for(int i = 0; i < stackCount; ++i)
    {
        k1 = i * (sectorCount + 1);     // beginning of current stack
        k2 = k1 + sectorCount + 1;      // beginning of next stack

        for(int j = 0; j < sectorCount; ++j, ++k1, ++k2)
        {
            // 2 triangles per sector excluding first and last stacks
            // k1 => k2 => k1+1
            if(i != 0)
            {
                M3_indices.push_back(k1);
                M3_indices.push_back(k2);
                M3_indices.push_back(k1 + 1);
            }

            // k1+1 => k2 => k2+1
            if(i != (stackCount-1))
            {
                M3_indices.push_back(k1 + 1);
                M3_indices.push_back(k2);
                M3_indices.push_back(k2 + 1);
            }
        }
    }
*/
int stackCount=20,sectorCount=20;

    float x, y, z, xy;                              // vertex position
    float sectorStep = 2 * M_PI / sectorCount;
    float stackStep = M_PI / stackCount;
    float sectorAngle, stackAngle;
    M3_vertices.resize((sectorCount*stackCount+1)*3);

    for(int i = 0; i <= stackCount; ++i)
    {
        stackAngle = M_PI / 2 - i * stackStep;        // starting from pi/2 to -pi/2
        xy = radius * cos(stackAngle);             // r * cos(u)
        z = radius * sin(stackAngle);              // r * sin(u)

        // add (sectorCount+1) vertices per stack
        // the first and last vertices have same position and normal, but different tex coords
        for(int j = 0; j <= sectorCount; ++j) {
            sectorAngle = j * sectorStep;           // starting from 0 to 2pi

            // vertex position (x, y, z)
            x = xy * cos(sectorAngle);             // r * cos(u) * cos(v)
            y = xy * sin(sectorAngle);             // r * cos(u) * sin(v)
            M3_vertices[(i*sectorCount*3)+(j*3)]=x;
            M3_vertices[(i*sectorCount*3)+(j*3)+1]=y;
            M3_vertices[(i*sectorCount*3)+(j*3)+2]=z;
            printf("vertex %d %d \t %f %f %f \n", i ,j,x,y,z);
        }}

M3_indices.resize((sectorCount*stackCount+2)*8);
    int k1, k2;
    for(int i = 0; i < stackCount; ++i)
    {
        k1 = (i * sectorCount) +1  ;     // beginning of current stack
        k2 = k1 + sectorCount  ;    // beginning of next stack

        for(int j = 0; j < sectorCount; ++j, ++k1, ++k2) {
            // k1--k1+1
            // |  / |
            // | /  |
            // k2--k2+1
            // 2 triangles per sector excluding first and last
            if(i != 0)
            {
                M3_indices[(i*sectorCount*6)+(j*6)]=k1;
                M3_indices[(i*sectorCount*6)+(j*6)+1]=k2+1 ;
                M3_indices[(i*sectorCount*6)+(j*6)+2]=(k1 + 2);
            }
            else{
                M3_indices[(j*3)]=(0);
                M3_indices[(j*3)+1]=(k2) ;
                M3_indices[(j*3)+2]=(k2 + 1);
                continue;
            }

            if(i != (stackCount-1))
            {
                M3_indices[(i*sectorCount*6)+(j*6)+3]=(k1+1);
                M3_indices[(i*sectorCount*6)+(j*6)+4]=(k2) ;
                M3_indices[(i*sectorCount*6)+(j*6)+5]=(k2 + 1);
            }



        }}




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