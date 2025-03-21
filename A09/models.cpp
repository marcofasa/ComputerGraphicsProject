
#include <cstdlib>
#include <vector>
#include <fstream>
#include <array>
#include <unordered_map>
#include <chrono>


#include<math.h>

float GtoR(float grades){
    return (grades * M_PI / 180.0);
}

float RtoG(float radians){
    return (radians * 180.0 / M_PI);
}


void Cylinder(float cx,float cy,float cz,int NSlices,float radius,float height,std::vector<float>& vertices,std::vector<uint32_t>& indices,bool closed, bool vertical){
    // Vertices definitions ( SPACE NEEDED -> (NSlices+1)*6 )

    //Vertical position --> fix y coordinates
    if (vertical){

    vertices.push_back (cx);
    vertices.push_back (cy + height);
    vertices.push_back (cz);
    vertices.push_back (cx);
    vertices.push_back (cy - height);
    vertices.push_back (cz);


    for(int i=0;i<NSlices;i++){

        //Top Vertex
        vertices.push_back (cx+radius*cos((float)(i*2.0*M_PI/NSlices)));
        vertices.push_back (cy+height);
        vertices.push_back (cz+radius*sin((float)(i*2.0*M_PI/NSlices)));

        //Bottom Vertexes
        vertices.push_back ( cx+radius*cos((float)(i*2.0*M_PI/NSlices)));
        vertices.push_back ( cy-height);
        vertices.push_back ( cz+radius*sin((float)(i*2.0*M_PI/NSlices)));
     }
    }
    else {
        /*
         *
         *
         *
         * FROM THERE SPECULAR BUT TO MAKE CYLINDER HORIZONTAL
         *
         *
         *
         */
        vertices.push_back(cx + height);
        vertices.push_back(cy);
        vertices.push_back(cz);
        vertices.push_back(cx - height);
        vertices.push_back(cy);
        vertices.push_back(cz);

        for (int i = 0; i < NSlices; i++) {

            //Top Vertex
            vertices.push_back(cx + height);
            vertices.push_back(cy + radius * cos((float) (i * 2.0 * M_PI / NSlices)));
            vertices.push_back(cz + radius * sin((float) (i * 2.0 * M_PI / NSlices)));

            //Bottom Vertexes
            vertices.push_back(cx - height);
            vertices.push_back(cy + radius * cos((float) (i * 2.0 * M_PI / NSlices)));
            vertices.push_back(cz + radius * sin((float) (i * 2.0 * M_PI / NSlices)));
        }
    }

// Indices definition ( SPACE NEEDED -> 12* NSlices )
    int a=0,b=1,c=2,d=3;
    for (int i=0;i<NSlices;i++){/*


                            --    --                            --   --
                       --              --                --               --

                   --                      --        --                        --

                 --                           --    --                            --
                                 O                                 1
                 18              |            --   20              |            --
                                 |                                 |
                     19          |          3         21           |         5
                                 |                                 |
                                 2                                 4

         */

        //TOP
        if(closed){
        indices.push_back (0);
        indices.push_back ((a) +2);
        indices.push_back ((c% ((NSlices)*2)) +2);}

        //BODY
        //2 top+1 bottom
        indices.push_back ((a) +2);
        indices.push_back ((b) +2);
        indices.push_back ((d% ((NSlices)*2)) +2);
        //1 top+ 2 bottom
        indices.push_back ((a) +2 );
        indices.push_back ((c% ((NSlices)*2)) +2);
        indices.push_back ((d% ((NSlices)*2)) +2);

        //BOTTOM
        if(closed){
        indices.push_back (1);
        indices.push_back ((b% ((NSlices)*2)) +2 );
        indices.push_back ((d % ((NSlices)*2)) +2);}

        a=a+2;
        b=b+2;
        c=c+2;
        d=d+2;
    }
}

void Sphere(int stackCount,int sectorCount,float radius,std::vector<float>& vertices,std::vector<uint32_t>& indices){
    float x, y, z, xy;   // vertex position
    float sectorStep = 2 * M_PI / sectorCount;
    float stackStep = M_PI / stackCount;
    float sectorAngle, stackAngle;

    //VERTEX definition (SPACE NEEDED -> ((sectorCount+1)*(stackCount+1))*3) )
    for(int i = 0; i <= stackCount; ++i)
    {
        stackAngle = (M_PI / 2) - (i * stackStep);        // starting from pi/2 to -pi/2
        xy = radius * cosf(stackAngle);             // r * cos(u) (to save computation I store it outside the loop)
        z = radius * sinf(stackAngle);              // z=r * sin(u)
        // printf("-------\n");

        // add (sectorCount+1) vertices per stack
        // the first and last vertices have same position and normal, but different tex coords
        for(int j = 0; j <= sectorCount; ++j) {
            sectorAngle = j * sectorStep;           // starting from 0 to 2pi

            // vertex position (x, y, z)
            x = xy * cosf(sectorAngle);             // x=r * cos(u) * cos(v)
            y = xy * sinf(sectorAngle);             // y=r * cos(u) * sin(v)
            vertices.push_back (x);
            vertices.push_back (y);
            vertices.push_back (z);
            //printf("vertex \t %f %f %f \n", x,y,z);
        }

    }

    //INDICES definition ( SPACE NEEDED -> ((sectorCount*stackCount)*6) )
    int k1, k2;
    for(int i = 0; i < stackCount; ++i)
    {
        k1 = i * (sectorCount+1);     // beginning of current stack
        k2 = (i+1)* (sectorCount+1) ;  // beginning of next stack
        for(int j = 0; j <sectorCount; ++j, ++k1, ++k2) {
            // 2 triangles per sector excluding first and last
            // k1--k1+1
            // |  / |
            // | /  |
            // k2--k2+1

            if (i != 0 ) {
                indices.push_back (k1+1) ;
                indices.push_back (k2) ;
                indices.push_back (k1);
            }
            else{
                //  printf("indices  with k1=%d and k2=%d \n " , k1,k2);
            }
            if (i != (stackCount-1)){
                indices.push_back (k1+1);
                indices.push_back (k2);
                indices.push_back (k2+1);
            }
            else{
                // printf("indices with k1=%d and k2=%d \n " , k1,k2);
            }



        }}
}

void Spring(float K,float R,float pipeRadius,int round,int stackCount,int NSlices,std::vector<float>& vertices,std::vector<uint32_t>& indices){
    /*
     * The Spring combines the open=true Cylinder logic with a Helix formula skeleton.
     */
    float x1, y1, z1,x2,y2, z2;    // vertex position
    float stackStep =  M_PI / stackCount;
    float stackAngle1,stackAngle2;
    int a,b, c, d;
    int con=0;

    //VERTEX definition (SPACE NEEDED -> ( (round * 2 * stackCount +1) * (2*NSlices) *3  )
    for(int m = 0; m <=  round * 2 * stackCount; ++m) {
        stackAngle1 = -M_PI/2 + (m * stackStep);        // starting from -pi/2 to pi/2
        /*
         * Helix Formula
         */
        x1 = R * cosf(stackAngle1);
        y1 = K * stackAngle1;
        z1 = R* sinf(stackAngle1);
        vertices.push_back(x1);
        vertices.push_back(y1);
        vertices.push_back(z1);

        //Generating next point of Helix
        stackAngle2 =  -M_PI/2 +((m+1) * stackStep);
        x2 = R * cosf(stackAngle2);
        y2 = K * (stackAngle2) ;
        z2 = R * sinf(stackAngle2);
        vertices.push_back(x2);
        vertices.push_back(y2);
        vertices.push_back(z2);

        //PIPE VERTEX
        for (int i = 0; i < NSlices; i++) {

            //Top Vertex
            vertices.push_back(x1 + pipeRadius* sin((float) (i * 2.0 * M_PI / NSlices))*cos(stackAngle1) );
            vertices.push_back(y1 + pipeRadius * cos((float) (i * 2.0 * M_PI / NSlices)));
            vertices.push_back(z1 + pipeRadius * sin((float) (i * 2.0 * M_PI / NSlices))*sin(stackAngle1));

            //Bottom Vertex
            vertices.push_back(x2 + pipeRadius* sin((float) (i * 2.0 * M_PI / NSlices))*cos(stackAngle2) );
            vertices.push_back(y2 + pipeRadius * cos((float) (i * 2.0 * M_PI / NSlices)));
            vertices.push_back(z2 + pipeRadius * sin((float) ((i) * 2.0 * M_PI / NSlices))*sin(stackAngle2));
        }

        // Indices definition ( SPACE NEEDED -> (2* NSlices) *(2*round*stackCount+1) * 3 )
        a = 2; b = 3; c =4; d = 5;
         for (int i = 0; i < NSlices; i++) {

            //PIPE
            indices.push_back (a + (NSlices+1)*2*m);
            indices.push_back (b + (NSlices+1)*2*m);
            indices.push_back (d + (NSlices+1)*2*m);
            indices.push_back (a + (NSlices+1)*2*m);
            indices.push_back (c +(NSlices+1)*2*m);
            indices.push_back (d +(NSlices+1)*2*m);
           // printf(" indices %d,%d,%d,%d  \n",a,b,c,d);

            a = a + 2;
            b = b+ 2;
            c = (c%((NSlices)*2)) + 2;
            d = ((d)%((NSlices)*2)) + 2;
        }
       // printf(" indices %d,%d,%d,%d at %d  \n",a,b,c,d,m);
       //   printf(" -------- \n");
    }
}

void Cube (float size){

    M1_vertices.resize(3 * 8);


    M1_vertices = {0, 0, 0, 0, 0, size,      // Vertex array:
                0, size, size, 0, size, 0,          // x y z for
                          size, 0, 0, size, 0, size,   // 8 different vertices
                          size, size, size, size, size, 0};

    M1_indices.resize(3 * 12);
    M1_indices ={0, 1, 2, 2, 3, 0,
                  0, 3, 4, 4, 3, 7,   // 36 indices
                  5, 6, 7, 7, 4, 5,   // to the vertices of
                  1, 6, 5, 1, 2, 6,   // 12 triangles composing
                  7, 6, 2, 3, 2, 7,   // 6 faces of a cube
                  4, 5, 0, 1, 0, 5};
}

void makeModels() {

//// M1 : Cube

    Cube(1);

//// M2 : Cylinder

    Cylinder(0.0, 0.0, -3.0, 33, 1, 1, M2_vertices, M2_indices, true, true);

//// M3 : Sphere

    Sphere(20, 20, 2, M3_vertices, M3_indices);

//// M4 : Spring

    Spring(0.7,8,1,3,20,20,M4_vertices, M4_indices);
}