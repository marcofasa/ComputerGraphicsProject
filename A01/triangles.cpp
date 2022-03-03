/**************
 Function Triangle(float x1, float y1, float x2, float y2, float x3, float y3, float r, float g, float b)

 draws a triangle connecting points (x1,y1)  (x2, y2) and (x3, y3), colored with the (r,g,b) specified color.
 vertex are expressed in Normalized screen coordinates, (i.e. in range [-1,+1]), following the Vulkan convention.
 The red, green and blue (r,g,b) values are in the range [0,1].
 
 Using function Triangle(...) try to draw a children house, similar to the one below.
 
 First remove the two function below (given only as an example), and replace them with your own.
 Since it is a C program, you can use for loops if you think it can be helpful in your drawing.
 The for() command below that draws a sun like shape in exact center of the screen near the top,
 is an example on how you can use it: please remove it, and replace it with your own code.
 It is not necessery to use a for loop if you do not really need it: it has been put here only as
 an example to help students not familiar with C++.
***************/
//Creates a Square combining two symmetric triangles on their hypotenuse (Wanted to use 4 points to make it possible to convert it Quadrilateral)
auto Square = [&] (float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4,float r, float g, float b){
    Triangle(x1,y1,x2,y2,x3,y3,r,g,b);
    Triangle(x4,y4,x1,y1,x3,y3,r,g,b);
};

//Creates a Ring
auto Ring = [&] (float x,float y,float offsetInternal,float offsetExternal,float r, float g, float b) {

    float amplitude=32;
    for (int i = 0; i < 360; i++) {
        Triangle(x + offsetInternal * cos(amplitude / 32 * (i - 0.5)), y + offsetInternal * sin(amplitude/ 32 * (i - 0.5)),
                 x + offsetExternal * cos(amplitude / 32 * i), y + offsetExternal * sin(amplitude / 32 * i),
                 x + offsetInternal * cos(amplitude / 32 * (i + 0.5)), y + offsetInternal * sin(amplitude / 32 * (i + 0.5)),
                 r, g, b);
    }
};

//Creates a filled disk with a given color
auto DiskFlower= [&] (float x,float y,float r, float g, float b) {

    float amplitude=32;
    float offset2=0.03; //External Radius
    for (int i = 0; i < 360; i++) {
        Triangle(x , y ,
                 x + offset2 * cos(amplitude / 32 * i), y + offset2 * sin(amplitude / 32 * i),
                 x + offset2 * cos(amplitude / 32 * (i + 0.5)), y + offset2 * sin(amplitude / 32 * (i + 0.5)),
                 r, g, b);
    }
};

//Creates a Flower with a given color
auto Flower= [&] (float x,float y,float floor,float r, float g, float b) {

    //TOP
    float offset1=0.02; // Internal Radius
    float offset2=0.07; //External Radius
    float color=255;

    Ring(x,y,offset1,offset2, r, g, b);
    DiskFlower(x,y,1,1,0);

    //STEM
    float stemTop=y+offset2;
    float stemWidth=0.01;
    Square(x-stemWidth,stemTop,x-stemWidth,floor,x+stemWidth,floor,x+stemWidth,stemTop,0,100/color,0);

};

//Creates a Cloud
auto Cloud= [&] (float x,float y) {
    float amplitude=32;
    float offset2=0.13; //External Radius
    float color=255;

    for (int i = 0; i < 360; i++) {
        Triangle(x  , y ,
                 x + offset2 * cos(amplitude / 32 * i), y + offset2 * sin(amplitude / 32 * i),
                 x + offset2 * cos(amplitude / 32 * (i + 0.5)), y + offset2 * sin(amplitude / 32 * (i + 0.5)),
                 230/color,230/color,1);
    }
    x=x+offset2;

    for (int i = 0; i < 360; i++) {
        Triangle(x , y ,
                 x + offset2/2 * cos(amplitude / 32 * i), y + offset2/2 * sin(amplitude / 32 * i),
                 x + offset2/2 * cos(amplitude / 32 * (i + 0.5)), y + offset2/2 * sin(amplitude / 32 * (i + 0.5)),
                 230/color,230/color,1);
    }
    x=x-(2*offset2);

    for (int i = 0; i < 360; i++) {
        Triangle(x  , y ,
                 x + offset2/2 * cos(amplitude / 32 * i), y + offset2/2 * sin(amplitude / 32 * i),
                 x + offset2/2 * cos(amplitude / 32 * (i + 0.5)), y + offset2/2 * sin(amplitude / 32 * (i + 0.5)),
                 230/color,230/color,1);
    }


};

auto Sun= [&] () {
    float amplitude=32;
    float offset2=0.04; //External Radius

    for (int i = 0; i < 360; i++) {
        Triangle(0.65 + 0.02 * cos(6.28 / 32 * (i - 0.5)), -0.70 + 0.02 * sin(6.28 / 32 * (i - 0.5)),
                 0.65 + 0.10 * cos(6.28 / 32 * i), -0.70 + 0.10 * sin(6.28 / 32 * i),
                 0.65 + 0.02 * cos(6.28 / 32 * (i + 0.5)), -0.70 + 0.02 * sin(6.28 / 32 * (i + 0.5)),
                 1, 1, 0);
    }
    for (int i = 0; i < 360; i++) {
        Triangle(0.65 , -0.70 ,
                 0.65 + offset2 * cos(amplitude / 32 * i), -0.70 + offset2 * sin(amplitude / 32 * i),
                 0.65 + offset2 * cos(amplitude / 32 * (i + 0.5)), -0.70 + offset2 * sin(amplitude / 32 * (i + 0.5)),
                 1, 1, 0);
    }
};

//MEASURES DECLARATION
float color=255;

float rl=-0.05; //Roof Left
float rr=0.75; //RoofRight
float separator=0.16;
float roofTop=((rr-rl)/2)*-1;

float wl=0.075; //Wall Left
float wr=rr-(wl-rl); //Wall Right
float floor=0.81;

float doorHeight=0.3;
float doorTop=floor-doorHeight;
float doorWidth=0.12;
float doorLeft=(wr+wl-doorWidth)/2;
float doorRight=doorLeft+doorWidth;

float windowSize=0.13;
float windowBottom=doorTop-0.08;
float windowTop=windowBottom-windowSize;
float windowLeft=(wl+doorLeft-windowSize)/2;
float windowRight=windowLeft+windowSize;
float secondWindow=(doorRight+wr-windowSize)/2;

float flowerHeight=0.68;

//SKY
Square(1,1,1,-1,-1,-1,-1,1,0,191/color,1);

//WALL
Square(wl,separator, wl,floor, wr,floor,wr,separator,   0,0,1);

//WINDOWS
Square(windowLeft,windowTop, windowLeft,windowBottom, windowRight,windowBottom,windowRight,windowTop,   1,1,0);
Square(secondWindow,windowTop, secondWindow,windowBottom, windowSize+secondWindow,windowBottom,windowSize+secondWindow,windowTop,   1,1,0);

//DOOR
Square(doorLeft,doorTop, doorLeft, floor,doorRight,floor,doorRight,doorTop,   1,1,0);

//FLOOR
Square(-1,floor, -1, 1,1,1,+1,floor,   0,100/color,0);

//ROOF
Triangle(rl,separator, (wr+wl)/2,roofTop, rr,separator,   1,0,0);	// Draws a red triangle pointing right

//SUN
Sun();

//FLOWERS
Flower(-0.12,flowerHeight,floor,1,192/color,203/color);
Flower(-0.33,flowerHeight,floor,1,165/color,0);
Flower(-0.52,flowerHeight,floor,1,0,1);
Flower(0.75,flowerHeight,floor,1,0,1);
Flower(-0.72,flowerHeight,floor,230/color,230/color,1);

//CLOUDS
Cloud(0.65,-0.55);
Cloud(0.2,-0.7);
Cloud(0.0,-0.25);
Cloud(-0.75,-0.7);



