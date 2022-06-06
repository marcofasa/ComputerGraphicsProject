// this function creates the geometries to be shown, and output thems
// in global variables M1_vertices and M1_indices to M4_vertices and M4_indices

struct Vertex {
	glm::vec3 pos;
	glm::vec3 norm;
	glm::vec2 UV;
};

std::vector<Vertex> M1_vertices;
std::vector<Vertex> M2_vertices;


/*
 *
vt 0.251680 0.998907
vt 0.127226 0.998907
vt 0.127226 0.874454
vt 0.251680 0.874453
vt 0.127226 0.750000
vt 0.251680 0.750000
vt 0.127226 0.625547
vt 0.251680 0.625547
vt 0.127226 0.501093
vt 0.251680 0.501093
vt 0.376133 0.750000
vt 0.376133 0.625547
vt 0.002773 0.750000
vt 0.002773 0.625547
 */

void Cube (float size,std::vector<Vertex>& vertices,std::vector<uint32_t>& indices){

    Vertex v;
    pushVertex(glm::vec3(0, 0, 0),glm::vec3(0.0f,-1.0f,0.0f),v,vertices);
    pushVertex(glm::vec3( 0, 0, size),glm::vec3(0.0f,-1.0f,0.0f),v,vertices);
    pushVertex(glm::vec3(0, size, size),glm::vec3(0.0f,1.0f,0.0f),v,vertices);
    pushVertex(glm::vec3( 0, size, 0),glm::vec3(0.0f,1.0f,0.0f),v,vertices);
    pushVertex(glm::vec3(size, 0, 0),glm::vec3(0.0f,-1.0f,0.0f),v,vertices);
    pushVertex(glm::vec3(size, 0, size),glm::vec3(0.0f,-1.0f,0.0f),v,vertices);
    pushVertex(glm::vec3(size, size, size),glm::vec3(0.0f,1.0f,0.0f),v,vertices);
    pushVertex(glm::vec3(size, size, 0),glm::vec3(0.0f,1.0f,0.0f),v,vertices);


    indices.resize(3 * 12);
    indices ={0, 1, 2, 2, 3, 0,
              0, 3, 4, 4, 3, 7,   // 36 indices
              5, 6, 7, 7, 4, 5,   // to the vertices of
              1, 6, 5, 1, 2, 6,   // 12 triangles composing
              7, 6, 2, 3, 2, 7,   // 6 faces of a cube
              4, 5, 0, 1, 0, 5};
}
void Cylinder(float cx,float cy,float cz,int NSlices,float radius,float height,std::vector<Vertex>& vertices,std::vector<uint32_t>& indices,bool closed, bool vertical){
    // Vertices definitions ( SPACE NEEDED -> (NSlices+1)*6 )

    Vertex v;
    v.pos=glm::vec3(cx,cy + height,cz);
    v.norm=glm::vec3(0.0f,1.0f,0.0f);

    vertices.push_back(v);
    v.pos=glm::vec3(cx,cy - height,cz);
    v.norm=glm::vec3(0.0f,-1.0f,0.0f);
    vertices.push_back(v);



    for(int i=0;i<NSlices;i++){
        Vertex v;
        float ux = cos((float)(i*2.0*M_PI/NSlices));
        float uy = 0.0f;
        float uz = sin((float)(i*2.0*M_PI/NSlices));
        //Top Vertex
        v.pos=glm::vec3 (cx+radius*cos((float)(i*2.0*M_PI/NSlices)),cy+height,cz+radius*sin((float)(i*2.0*M_PI/NSlices)));
        v.norm=glm::vec3(ux,uy,uz);
        //v.norm=glm::vec3(0.0f,1.0f,0.0f);

        vertices.push_back(v);
        //Bottom Vertexes
        v.pos=glm::vec3 ( cx+radius*cos((float)(i*2.0*M_PI/NSlices)), cy-height,cz+radius*sin((float)(i*2.0*M_PI/NSlices)));
        //v.norm=glm::vec3(0.0f,-1.0f,0.0f);
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
M1_vertices.resize(4);

// first vertex of M1
M1_vertices[0].pos  = glm::vec3(-1.0,-1.0,-1.0);
M1_vertices[0].norm = glm::vec3(0.0,0.0,1.0);
M1_vertices[0].UV   = glm::vec2(0.0,1.0);

// second vertex of M1
M1_vertices[1].pos  = glm::vec3(1.0,-1.0,-1.0);
M1_vertices[1].norm = glm::vec3(0.0,0.0,1.0);
M1_vertices[1].UV   = glm::vec2(1.0,1.0);

// third vertex of M1
M1_vertices[2].pos  = glm::vec3(1.0,1.0,-1.0);
M1_vertices[2].norm = glm::vec3(0.0,0.0,1.0);
M1_vertices[2].UV   = glm::vec2(1.0,0.0);

// fourth vertex of M1
M1_vertices[3].pos  = glm::vec3(-1.0,1.0,-1.0);
M1_vertices[3].norm = glm::vec3(0.0,0.0,1.0);
M1_vertices[3].UV   = glm::vec2(0.0,0.0);


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
M2_vertices.resize(4);

// Vertices definitions
M2_vertices[0].pos  = glm::vec3(0.0,-1.0,-1.1);
M2_vertices[0].norm = glm::vec3(0.0,0.0,1.0);
M2_vertices[0].UV   = glm::vec2(0.0,1.0);

M2_vertices[1].pos  = glm::vec3(1.0,0.0,-1.1);
M2_vertices[1].norm = glm::vec3(0.0,0.0,1.0);
M2_vertices[1].UV   = glm::vec2(1.0,1.0);

M2_vertices[2].pos  = glm::vec3(0.0,1.0,-1.1);
M2_vertices[2].norm = glm::vec3(0.0,0.0,1.0);
M2_vertices[2].UV   = glm::vec2(1.0,0.0);

M2_vertices[3].pos  = glm::vec3(-1.0,0.0,-1.1);
M2_vertices[3].norm = glm::vec3(0.0,0.0,1.0);
M2_vertices[3].UV   = glm::vec2(0.0,0.0);


// Resizes the indices array. Repalce the values with the correct number of
// indices (3 * number of triangles)
M2_indices.resize(6);

// indices definitions
M2_indices[0] = 0;
M2_indices[1] = 1;
M2_indices[2] = 2;
M2_indices[3] = 2;
M2_indices[4] = 3;
M2_indices[5] = 0;

}