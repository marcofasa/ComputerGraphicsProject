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

void pushVertex(glm::vec3 pos,glm::vec3 norm, Vertex &v,std::vector<Vertex>& vertices){
    v.pos=pos;
    v.norm=norm;
    vertices.push_back(v);
}

//OK
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
        //Top center
        pushVertex(glm::vec3(cx,cy + height,cz),glm::vec3(0.0f,1.0f,0.0f),v,vertices);


        //Bottom center
        pushVertex(glm::vec3(cx,cy - height,cz),glm::vec3(0.0f,-1.0f,0.0f),v,vertices);




    for(int i=0;i<NSlices;i++){
            Vertex v;
            float ux = cos((float)(i*2.0*M_PI/NSlices));
            float uy = 0.0f;
            float uz = sin((float)(i*2.0*M_PI/NSlices));
            //Top Vertex
            v.pos=glm::vec3 (cx+radius*cos((float)(i*2.0*M_PI/NSlices)),cy+height,cz+radius*sin((float)(i*2.0*M_PI/NSlices)));
            //Vertical norm
        v.norm=glm::vec3(0.0f,1.0f,0.0f);
         vertices.push_back(v);
            //horizontal norm
        v.norm=glm::vec3(ux,uy,uz);
        vertices.push_back(v);


            //Bottom Vertexes
            v.pos=glm::vec3 ( cx+radius*cos((float)(i*2.0*M_PI/NSlices)), cy-height,cz+radius*sin((float)(i*2.0*M_PI/NSlices)));
        v.norm=glm::vec3(ux,uy,uz);
        vertices.push_back(v);
            v.norm=glm::vec3(0.0f,-1.0f,0.0f);
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


//OK
void Spring(float K,float R,float pipeRadius,int round,int stackCount,int NSlices,std::vector<Vertex>& vertices,std::vector<uint32_t>& indices){
    /*
     * The Spring combines the open=true Cylinder logic with a Helix formula skeleton.
     */
    float x1, y1, z1,x2,y2, z2;    // vertex position
    float nx1, ny1, nz1,nx2,ny2, nz2;    // vertex position

    float stackStep =  M_PI / stackCount;
    float stackAngle1,stackAngle2;
    int a,b, c, d;
    int con=0;

    //VERTEX definition (SPACE NEEDED -> ( (round * 2 * stackCount +1) * (2*NSlices) *3  )
    for(int m = 0; m <=  round * 2 * stackCount; ++m) {
        Vertex v;
        stackAngle1 = -M_PI/2 + (m * stackStep);        // starting from -pi/2 to pi/2
        /*
         * Helix Formula
         */
        x1 = R * cosf(stackAngle1);
        y1 = K * stackAngle1;
        z1 = R* sinf(stackAngle1);
        v.pos=glm::vec3(x1,y1,z1);
        v.norm=glm::vec3(cosf(stackAngle1),0.0f,sinf(stackAngle1)),
   vertices.push_back(v);

        //Generating next point of Helix
        stackAngle2 =  -M_PI/2 +((m+1) * stackStep);
        x2 = R * cosf(stackAngle2);
        y2 = K * (stackAngle2) ;
        z2 = R * sinf(stackAngle2);
              v.pos=glm::vec3(x2,y2,z2);
        v.norm=glm::vec3(cosf(stackAngle2),0.0f,sinf(stackAngle2)),
        vertices.push_back(v);


        //PIPE VERTEX
        for (int i = 0; i < NSlices; i++) {
           Vertex v;
            //Top Vertex
            v.pos=glm::vec3(x1 + pipeRadius* sin((float) (i * 2.0 * M_PI / NSlices))*cos(stackAngle1),
            y1 + pipeRadius * cos((float) (i * 2.0 * M_PI / NSlices)),
            (z1 + pipeRadius * sin((float) (i * 2.0 * M_PI / NSlices))*sin(stackAngle1)));
            nx1=sin((float) (i * 2.0 * M_PI / NSlices))*cos(stackAngle1);
            ny1=cos((float) (i * 2.0 * M_PI / NSlices));
            nz1=sin((float) (i * 2.0 * M_PI / NSlices))*sin(stackAngle1);
            v.norm=glm::vec3(nx1,ny1,nz1);
            vertices.push_back(v);
            //Bottom Vertex
            v.pos=glm::vec3(x2 + pipeRadius* sin((float) (i * 2.0 * M_PI / NSlices))*cos(stackAngle2),
                       y2 + pipeRadius * cos((float) (i * 2.0 * M_PI / NSlices)),
                       (z2 + pipeRadius * sin((float) (i * 2.0 * M_PI / NSlices))*sin(stackAngle2)));
            nx2=sin((float) (i * 2.0 * M_PI / NSlices))*cos(stackAngle2);
            ny2=cos((float) (i * 2.0 * M_PI / NSlices));
            nz2=sin((float) (i * 2.0 * M_PI / NSlices))*sin(stackAngle2);
            v.norm=glm::vec3(nx2,ny2,nz2);
            vertices.push_back(v);


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


void Cube (float size,std::vector<Vertex>& vertices,std::vector<uint32_t>& indices){

    Vertex v;
    //0
    pushVertex(glm::vec3(0, 0, 0),glm::vec3(0.0f,-1.0f,0.0f),v,vertices);
    pushVertex(glm::vec3(0, 0, 0),glm::vec3(-1.0f,0.0f,0.0f),v,vertices);
    pushVertex(glm::vec3(0, 0, 0),glm::vec3(0.0f,0.0f,-1.0f),v,vertices);

    //1
    pushVertex(glm::vec3( 0, 0, size),glm::vec3(0.0f,-1.0f,0.0f),v,vertices);
    pushVertex(glm::vec3( 0, 0, size),glm::vec3(-1.0f,0.0f,0.0f),v,vertices);
    pushVertex(glm::vec3( 0, 0, size),glm::vec3(0.0f,0.0f,1.0f),v,vertices);

    //2
    pushVertex(glm::vec3( size, 0,size),glm::vec3(0.0f,-1.0f,0.0f),v,vertices);
    pushVertex(glm::vec3( size, 0,size),glm::vec3(1.0f,0.0f,0.0f),v,vertices);
    pushVertex(glm::vec3( size,0, size),glm::vec3(0.0f,0.0f,1.0f),v,vertices);

    //3
    pushVertex(glm::vec3( size,0,  0),glm::vec3(0.0f,-1.0f,0.0f),v,vertices);
    pushVertex(glm::vec3( size,0,  0),glm::vec3(1.0f,0.0f,0.0f),v,vertices);
    pushVertex(glm::vec3( size,0,  0),glm::vec3(0.0f,0.0f,-1.0f),v,vertices);

    //4
    pushVertex(glm::vec3(0, size, 0),glm::vec3(0.0f,1.0f,0.0f),v,vertices);
    pushVertex(glm::vec3(0, size, 0),glm::vec3(-1.0f,0.0f,0.0f),v,vertices);
    pushVertex(glm::vec3(0, size, 0),glm::vec3(0.0f,0.0f,-1.0f),v,vertices);

    //5
    pushVertex(glm::vec3( 0,size, size),glm::vec3(0.0f,1.0f,0.0f),v,vertices);
    pushVertex(glm::vec3( 0,size,  size),glm::vec3(-1.0f,0.0f,0.0f),v,vertices);
    pushVertex(glm::vec3( 0,size, size),glm::vec3(0.0f,0.0f,1.0f),v,vertices);

    //6
    pushVertex(glm::vec3(size, size, size),glm::vec3(0.0f,1.0f,0.0f),v,vertices);
    pushVertex(glm::vec3(size, size, size),glm::vec3(1.0f,0.0f,0.0f),v,vertices);
    pushVertex(glm::vec3(size, size, size),glm::vec3(0.0f,0.0f,1.0f),v,vertices);

    //7
    pushVertex(glm::vec3(size, size, 0),glm::vec3(0.0f,1.0f,0.0f),v,vertices);
    pushVertex(glm::vec3(size, size, 0),glm::vec3(1.0f,0.0f,0.0f),v,vertices);
    pushVertex(glm::vec3(size, size, 0),glm::vec3(0.0f,0.0f,-1.0f),v,vertices);


    indices.resize(3 * 12);
    indices ={0, 3, 6, 6, 9, 0,
              2, 11, 14, 14, 11, 23,   // 36 indices
              15, 18, 21, 21, 12, 15,   // to the vertices of
              5, 20, 17, 5, 8, 20,   // 12 triangles composing
              22, 19, 7, 10, 7, 22,   // 6 faces of a cube
              13, 16, 1, 4, 1, 16};
/*
    indices.resize(3 * 12);
    indices ={   0, 1, 2, 2, 3, 0,
                 0, 3, 4, 4, 3, 7,   // 36 indices
                 5, 6, 7, 7, 4, 5,   // to the vertices of
                 1, 6, 5, 1, 2, 6,   // 12 triangles composing
                 7, 6, 2, 3, 2, 7,   // 6 faces of a cube
                 4, 5, 0, 1, 0, 5};
                 */
}

void makeModels() {
//// M1 : Cube
// Replace the code below, that creates a simple square, with the one to create a cube.

// Resizes the vertices array. Repalce the values with the correct number o
// second vertex of M1
Cube(1,M1_vertices,M1_indices);






//// M2 : Cylinder
// Replace the code below, that creates a simple rotated square, with the one to create a cylinder.

    Cylinder(0.0, 0.0, -3.0, 33, 1, 1, M2_vertices, M2_indices, true, true);

//// M3 : Sphere
// Replace the code below, that creates a simple triangle, with the one to create a sphere.

    Sphere(20, 30, 2,  M3_vertices,M3_indices);


//// M4 : Spring
// Replace the code below, that creates a simple octahedron, with the one to create a spring.
    Spring(0.7,8,1,3,10,20,M4_vertices, M4_indices);

}