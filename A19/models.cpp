// this function creates the geometries to be shown, and output thems
// in global variables M1_vertices and M1_indices to M4_vertices and M4_indices

struct Vertex {
	glm::vec3 pos;
	glm::vec3 norm;
	glm::vec2 UV;
};

std::vector<Vertex> M1_vertices;
std::vector<Vertex> M2_vertices;


void pushVertex(glm::vec3 pos,glm::vec3 norm,glm::vec2 UV, Vertex &v,std::vector<Vertex>& vertices){
    v.pos=pos;
    v.norm=norm;
    v.UV=UV;
    vertices.push_back(v);
}


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

void Cube (float size,std::vector<Vertex>& vertices,std::vector<uint32_t>& indices) {

    Vertex v;
    //0
    pushVertex(glm::vec3(0, 0, 0), glm::vec3(0.0f, -1.0f, 0.0f),glm::vec2(0.125,0.25), v, vertices);
    pushVertex(glm::vec3(0, 0, 0), glm::vec3(-1.0f, 0.0f, 0.0f),glm::vec2(0.125,0.25), v, vertices);
    pushVertex(glm::vec3(0, 0, 0), glm::vec3(0.0f, 0.0f, -1.0f),glm::vec2(0.125,0.25), v, vertices);

    //1
    pushVertex(glm::vec3(0, 0, size), glm::vec3(0.0f, -1.0f, 0.0f),glm::vec2(0.125,0.125), v, vertices);
    pushVertex(glm::vec3(0, 0, size), glm::vec3(-1.0f, 0.0f, 0.0f),glm::vec2(0.0,0.25), v, vertices);
    pushVertex(glm::vec3(0, 0, size), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.125,0.125),v, vertices);

    //2
    pushVertex(glm::vec3(size, 0, size), glm::vec3(0.0f, -1.0f, 0.0f),glm::vec2(0.25,0.125), v, vertices);
    pushVertex(glm::vec3(size, 0, size), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.375,0.25),v, vertices);
    pushVertex(glm::vec3(size, 0, size), glm::vec3(0.0f, 0.0f, 1.0f),glm::vec2(0.25,0.125), v, vertices);

    //3
    pushVertex(glm::vec3(size, 0, 0), glm::vec3(0.0f, -1.0f, 0.0f),glm::vec2(0.25,0.25), v, vertices);
    pushVertex(glm::vec3(size, 0, 0), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.25,0.25),v, vertices);
    pushVertex(glm::vec3(size, 0, 0), glm::vec3(0.0f, 0.0f, -1.0f),glm::vec2(0.25,0.25), v, vertices);

    //4
    pushVertex(glm::vec3(0, size, 0), glm::vec3(0.0f, 1.0f, 0.0f),glm::vec2(0.125,0.375), v, vertices);
    pushVertex(glm::vec3(0, size, 0), glm::vec3(-1.0f, 0.0f, 0.0f),glm::vec2(0.125,0.375), v, vertices);
    pushVertex(glm::vec3(0, size, 0), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(0.125,0.375),v, vertices);

    //5
    pushVertex(glm::vec3(0, size, size), glm::vec3(0.0f, 1.0f, 0.0f),glm::vec2(0.125,0.5), v, vertices);
    pushVertex(glm::vec3(0, size, size), glm::vec3(-1.0f, 0.0f, 0.0f),glm::vec2(0.0,0.375), v, vertices);
    pushVertex(glm::vec3(0, size, size), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.125,0.0),v, vertices);

    //6
    pushVertex(glm::vec3(size, size, size), glm::vec3(0.0f, 1.0f, 0.0f),glm::vec2(0.25,0.5), v, vertices);
    pushVertex(glm::vec3(size, size, size), glm::vec3(1.0f, 0.0f, 0.0f),glm::vec2(0.375,0.375), v, vertices);
    pushVertex(glm::vec3(size, size, size), glm::vec3(0.0f, 0.0f, 1.0f),glm::vec2(0.25,0.0), v, vertices);

    //7
    pushVertex(glm::vec3(size, size, 0), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.25,0.375),v, vertices);
    pushVertex(glm::vec3(size, size, 0), glm::vec3(1.0f, 0.0f, 0.0f),glm::vec2(0.25,0.375), v, vertices);
    pushVertex(glm::vec3(size, size, 0), glm::vec3(0.0f, 0.0f, -1.0f),glm::vec2(0.25,0.375), v, vertices);


    indices.resize(3 * 12);
    indices = {0, 3, 6, 6, 9, 0,
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

void Cylinder(float cx,float cy,float cz,int NSlices,float radius,float height,std::vector<Vertex>& vertices,std::vector<uint32_t>& indices,bool closed, bool vertical){
    // Vertices definitions ( SPACE NEEDED -> (NSlices+1)*6 )

    Vertex v;
    //Top center (0)
    pushVertex(glm::vec3(cx,cy + height,cz),glm::vec3(0.0f,1.0f,0.0f),glm::vec2(0.625,0.125),v,vertices);


    //Bottom center (1)
    pushVertex(glm::vec3(cx,cy - height,cz),glm::vec3(0.0f,-1.0f,0.0f),glm::vec2(0.875,0.125),v,vertices);


Vertex firstVertexTop;
    Vertex firstVertexBottom;


    for(int i=0;i<NSlices;i++){
        float U,V;
        float textR=0.125;
        Vertex v;
        float tetha=(float)(i*2.0*M_PI/NSlices);

        float ux = cos(tetha);
        float uy = 0.0f;
        float uz = sin(tetha);

        //Top Vertex
        v.pos=glm::vec3 (cx+radius*cos(tetha),cy+height,cz+radius*sin(tetha));
        //Vertical norm
        v.norm=glm::vec3(0.0f,1.0f,0.0f);


        //UV
        U=0.625+textR*cos(tetha);
        V=0.125+textR*sin(tetha);
        v.UV=glm::vec2(U,V);


        vertices.push_back(v);
        //horizontal norm
        v.norm=glm::vec3(ux,uy,uz);
        if(i==0){
            firstVertexTop=v;
        }

        //Range for UV of the side of the cylinder
        float range=0.5*i/(NSlices);

        std::cout<<range<<'\n';
        //UV
        U=0.5+range;
        V=0.25;
        v.UV=glm::vec2(U,V);
        std::cout<<U<<','<<V<<'\n';

        vertices.push_back(v);


        //Bottom Vertexes
        v.pos=glm::vec3 ( cx+radius*cos((float)(i*2.0*M_PI/NSlices)), cy-height,cz+radius*sin((float)(i*2.0*M_PI/NSlices)));
        //Vertical Norm
        v.norm=glm::vec3(0.0f,-1.0f,0.0f);



        //UV
        U=0.875+textR*cos(tetha);
        V=0.125+textR*sin(tetha);
        v.UV=glm::vec2(U,V);



        vertices.push_back(v);


        //Horizontal Norm
        v.norm=glm::vec3(ux,uy,uz);

        if(i==0){
            firstVertexBottom=v;
        }


        //UV
        U=0.5+range;
        V=0.5;
        v.UV=glm::vec2(U,V);
        std::cout<<U<<','<<V<<'\n';
        std::cout<<"--------\n";
        vertices.push_back(v);

    }

    //Re pushing the first UVs to the last
    firstVertexTop.UV=glm::vec2(1,0.25);
    vertices.push_back(firstVertexTop);

    firstVertexBottom.UV=glm::vec2(1,0.5);
    vertices.push_back(firstVertexBottom);


// Indices definition ( SPACE NEEDED -> 12* NSlices )
    int a=0,b=1,c=2,d=3,top=0,bot=0;
    for (int i=0;i<NSlices;i++){/*


                            --    --                            --   --
                       --              --                --               --

                   --                      --        --                        --

                 --                           --    --                            --
                                 O                                 1
                 20(21)          |            --  18(19)           |            --
                                 |                                 |
                     22(23)      |          6(7)         24(25)    |         8(9)
                                 |                                 |
                                 2(3)                               4(5)

         */

        //TOP
        indices.push_back (0);
        indices.push_back (top+2);
        indices.push_back ((top+4)%(NSlices*4) +2);



        //BODY

        indices.push_back (bot +5);
        indices.push_back (top+3);
        if((top+4)%(NSlices*4)==0){
            indices.push_back (NSlices*4+2);

        }else{
            indices.push_back ((top+4)%(NSlices*4) +3);

        }
        std::cout<<"T("<<top+4<<"\n";



        indices.push_back (bot +5);
        if((bot+4)%((NSlices)*4)==0){
            indices.push_back ((vertices.size()-1));

        }else{
            indices.push_back ((bot+4)%((NSlices)*4)  +5);
        }

        //std::cout<<"B("<<top+4<<","<<(bot+4)<<"\n";
        if((top+4)%(NSlices*4)==0){
            indices.push_back ((vertices.size()-2));
        }
        else{
            indices.push_back ((top+4)%(NSlices*4) +3);
        }



        //BOTTOM

        indices.push_back (1);
        indices.push_back (bot +4);
        indices.push_back ((bot+4)%((NSlices)*4)  +4);
        //std::cout<<"B("<<bot+4<<","<<(bot+4)%((NSlices)*4)  +4<<"\n";

        bot=bot+4;
        top=top+4;
        a=a+2;
        b=b+2;
        c=c+2;
        d=d+2;
    }

}

void makeModels() {
//// M1 : Cube

    Cube(1,M1_vertices,M1_indices);



//// M2 : Cylinder
// Replace the code below, that creates a simple rotated square, with the one to create a cylinder.

    Cylinder(0.0, 0.0, -3.0, 6, 1, 1, M2_vertices, M2_indices, true, true);


}