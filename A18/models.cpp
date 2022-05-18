// this function creates the geometries to be shown, and output thems
// in global variables M1_vertices and M1_indices to M4_vertices and M4_indices

struct Vertex {
	glm::vec3 pos;
	glm::vec3 norm;
};

std::vector<Vertex> M1_vertices;
std::vector<Vertex> M2_vertices;
std::vector<Vertex> M3_vertices;
std::vector<Vertex> M4_vertices;

void Sphere(int stackCount,int sectorCount,float radius,std::vector<Vertex>& vertices,std::vector<uint32_t>& indices){
    float x, y, z, xy;   // vertex position
    float sectorStep = 2 * M_PI / sectorCount;
    float nx, ny, nz, lengthInv = 1.0f / radius;    // vertex normal
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
            y = xy * sinf(sectorAngle);         // y=r * cos(u) * sin(v)
            Vertex v;
            nx = x * lengthInv;
            ny = y * lengthInv;
            nz = z * lengthInv;
            v.pos=glm::vec3(x,y,z);
            v.norm=glm::vec3(nx,ny,nz);
            vertices.push_back(v);
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

void Cylinder(float cx,float cy,float cz,int NSlices,float radius,float height,std::vector<Vertex>& vertices,std::vector<uint32_t>& indices,bool closed, bool vertical){
    // Vertices definitions ( SPACE NEEDED -> (NSlices+1)*6 )

        Vertex v;
        v.pos=glm::vec3(cx,cy + height,cz);
        v.norm=glm::vec3(0.0f,-1.0f,0.0f);

        vertices.push_back(v);
        v.pos=glm::vec3(cx,cy - height,cz);
        v.norm=glm::vec3(0.0f,1.0f,0.0f);
        vertices.push_back(v);



        for(int i=0;i<NSlices;i++){
            Vertex v;
            float ux = cos((float)(i*2.0*M_PI/NSlices));
            float uy = 0.0f;
            float uz = sin((float)(i*2.0*M_PI/NSlices));
            //Top Vertex
            v.pos=glm::vec3 (cx+radius*cos((float)(i*2.0*M_PI/NSlices)),cy+height,cz+radius*sin((float)(i*2.0*M_PI/NSlices)));
            v.norm=glm::vec3(ux,uy,uz);
            vertices.push_back(v);
            //Bottom Vertexes
            v.pos=glm::vec3 ( cx+radius*cos((float)(i*2.0*M_PI/NSlices)), cy-height,cz+radius*sin((float)(i*2.0*M_PI/NSlices)));
            vertices.push_back(v);
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
        indices.push_back ((a) +2);
        indices.push_back ((b) +2);
        indices.push_back ((d% ((NSlices)*2)) +2);
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

void makeModels() {
//// M1 : Cube
// Replace the code below, that creates a simple square, with the one to create a cube.

// Resizes the vertices array. Repalce the values with the correct number of
// vertices
M1_vertices.resize(4);

// first vertex of M1
M1_vertices[0].pos  = glm::vec3(-1.0,-1.0,-1.0);
M1_vertices[0].norm = glm::vec3(0.0,0.0,1.0);

// second vertex of M1
M1_vertices[1].pos  = glm::vec3(1.0,-1.0,-1.0);
M1_vertices[1].norm = glm::vec3(0.0,0.0,1.0);

// third vertex of M1
M1_vertices[2].pos  = glm::vec3(1.0,1.0,-1.0);
M1_vertices[2].norm = glm::vec3(0.0,0.0,1.0);

// fourth vertex of M1
M1_vertices[3].pos  = glm::vec3(-1.0,1.0,-1.0);
M1_vertices[3].norm = glm::vec3(0.0,0.0,1.0);


// Resizes the indices array. Repalce the values with the correct number of
// indices (3 * number of triangles)
M1_indices.resize(3 * 2);

// first triangle
M1_indices[0] = 0;
M1_indices[1] = 1;
M1_indices[2] = 2;

// second triangle
M1_indices[3] = 2;
M1_indices[4] = 3;
M1_indices[5] = 0;








//// M2 : Cylinder
// Replace the code below, that creates a simple rotated square, with the one to create a cylinder.

// Resizes the vertices array. Repalce the values with the correct number of
// vertices

    Cylinder(0.0, 0.0, -3.0, 33, 1, 1, M2_vertices, M2_indices, true, true);












//// M3 : Sphere
// Replace the code below, that creates a simple triangle, with the one to create a sphere.

// Resizes the vertices array. Repalce the values with the correct number of
// vertices
    Sphere(20, 30, 2,  M3_vertices,M3_indices);

// Resizes the indices array. Repalce the values with the correct number of
// indices (3 * number of triangles)









//// M4 : Spring
// Replace the code below, that creates a simple octahedron, with the one to create a spring.
M4_vertices.resize(6);

// Vertices definitions
M4_vertices[0].pos  = glm::vec3(0.0,1.414,-1.0);
M4_vertices[0].norm = glm::vec3(0.0,0.0,1.0);
M4_vertices[1].pos  = glm::vec3(0.0,-1.414,-1.0);
M4_vertices[1].norm = glm::vec3(0.0,0.0,1.0);
M4_vertices[2].pos  = glm::vec3(-1.0,0.0,-2.0);
M4_vertices[2].norm = glm::vec3(0.0,0.0,1.0);
M4_vertices[3].pos  = glm::vec3(-1.0,0.0,0.0);
M4_vertices[3].norm = glm::vec3(0.0,-1.0,0.0);
M4_vertices[4].pos  = glm::vec3(1.0,0.0,0.0);
M4_vertices[4].norm = glm::vec3(0.0,-1.0,0.0);
M4_vertices[5].pos  = glm::vec3(1.0,0.0,-2.0);
M4_vertices[5].norm = glm::vec3(0.0,-1.0,0.0);


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