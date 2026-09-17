
#include <GL/glut.h>
#include <cmath>
#include <iostream>
using namespace std;

bool night=false;
double xt=0;
double Cxt=-0.5f; double Cyt=0.0; float scale=1.0;
double Txt=0.0f; double Tyt=0.0f; float tScale=1.0;

void init(){
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    gluOrtho2D(-10.0, 10.0, -7.32, 7.3);
}

void drawLamp(float x, float y, float scale, bool flip) {
    float width = 0.06f * scale;
    float height = 2.5f * scale;
    float arm_length = 0.8f * scale;
    float dir = flip ? -1.0f : 1.0f;

    // Pole
    glColor3f(0.6f, 0.6f, 0.6f);
    glBegin(GL_POLYGON);
    glVertex2f(x - width, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x - width, y + height);
    glEnd();

    // Arm
    glBegin(GL_POLYGON);
    glVertex2f(x - width, y + height - width);
    glVertex2f(x + width, y + height - width);
    glVertex2f(x + width + arm_length*dir, y + height + width*2);
    glVertex2f(x - width + arm_length*dir, y + height + width*2);
    glEnd();

    // Light bulb
    glColor3f(1.0f, 1.0f, 0.6f);
    glBegin(GL_POLYGON);
    float bx = x + arm_length*dir;
    float by = y + height + width*2;
    glVertex2f(bx - width*2.0f, by);
    glVertex2f(bx + width*2.0f, by);
    glVertex2f(bx + width*2.0f, by - width*2.5f);
    glVertex2f(bx - width*2.0f, by - width*2.5f);
    glEnd();
}

void drawWaveRow(float x, float y, float scale){
    glBegin(GL_POLYGON);
    glColor3f(0.03f, 0.0f, 0.125f);
    glVertex2f(x-(0.75*scale), y);
    glVertex2f(x+(0.75*scale), y);
    glVertex2f(x+(0.5*scale), y+0.05);
    glVertex2f(x, y+0.1);
    glVertex2f(x-(0.5*scale), y+0.05);
    glEnd();
}

void drawCar(float Cx, float Cy){
    // Main body
    glColor3f(0.9f,0.9f,0.9f);
    glBegin(GL_QUADS);
        glVertex2f(Cx-(1.0*scale), Cy-(0.2*scale));
        glVertex2f(Cx+(1.0*scale), Cy+(0.2*scale));
        glVertex2f(Cx+(1.0*scale), Cy+(0.6*scale));
        glVertex2f(Cx-(1.0*scale), Cy+(0.35*scale));
    glEnd();

    // Upper body
    glColor3f(0.9f,0.9f,0.9f);
    glBegin(GL_POLYGON);
        glVertex2f(Cx+(0.6*scale), Cy+(0.5*scale));
        glVertex2f(Cx+(0.2*scale), Cy+(0.95*scale));
        glVertex2f(Cx-(0.7*scale), Cy+(0.7*scale));
        glVertex2f(Cx-(0.8*scale), Cy+(0.35*scale));
    glEnd();

    // Windows
    glBegin(GL_QUADS);
    glColor3f(0.9f,0.9f,0.0f);
    glVertex2f(Cx+(0.4*scale), Cy+(0.5*scale));
    glVertex2f(Cx+(0.2*scale), Cy+(0.8*scale));
    glVertex2f(Cx-(0.5*scale), Cy+(0.7*scale));
    glVertex2f(Cx-(0.7*scale), Cy+(0.38*scale));
    glEnd();

    glLineWidth(1.0f);
    glBegin(GL_LINE);
    glColor3f(0.9f,0.9f,0.0f);
    glVertex2f(Cx-(0.2*scale), Cy+(0.85*scale));
    glVertex2f(Cx-(0.1*scale), Cy+(0.3*scale));
    glEnd();

    // Wheels
    glColor3f(0.05f,0.05f,0.05f);

    // Back wheel
    glBegin(GL_POLYGON);
        for(int i=0;i<360;i++){
            float angle=i*3.14159f/180.0f;
            glVertex2f((Cx-(0.6*scale))+(0.18f*scale)*cos(angle),
                       (Cy-(0.1*scale))+(0.18f*scale)*sin(angle));
        }
    glEnd();

    // Front wheel
    glBegin(GL_POLYGON);
        for(int i=0;i<360;i++){
            float angle=i*3.14159f/180.0f;
            glVertex2f((Cx+(0.6*scale))+(0.18f*scale)*cos(angle),
                       (Cy+(0.1*scale))+(0.18f*scale)*sin(angle));
        }
    glEnd();
}

void drawTrain(){
    // Engine
    glBegin(GL_POLYGON);
    glColor3f(0.75f,0.65f,0.05f);
    glVertex2f(-1.5f*tScale, -1.75f*tScale);
    glVertex2f(-1.5f*tScale, -0.25f*tScale);
    glVertex2f(-3.9f*tScale, -0.7f*tScale);
    glVertex2f(-3.9f*tScale, -2.25f*tScale);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.15f,0.15f,0.85f);
    glVertex2f(-1.5f*tScale, -1.3f*tScale);
    glVertex2f(-1.5f*tScale, -1.675f*tScale);
    glVertex2f(-3.9f*tScale, -2.2f*tScale);
    glVertex2f(-3.5f*tScale, -1.67f*tScale);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.15f,0.15f,0.85f);
    glVertex2f(-3.9f*tScale, -2.2f*tScale);
    glVertex2f(-3.9f*tScale, -0.7f*tScale);
    glVertex2f(-3.5f*tScale, -0.6f*tScale);
    glVertex2f(-3.5f*tScale, -1.67f*tScale);
    glEnd();

    // Locomotive window
    glColor3f(0.9f, 0.9f, 0.9f);
    glBegin(GL_QUADS);
    glVertex2f(-0.8f,0.0f);
    glVertex2f(-0.45f,0.0f);
    glVertex2f(-0.45f,0.25f);
    glVertex2f(-0.8f,0.25f);
    glEnd();

    // Coach 1
    glBegin(GL_QUADS);
    glColor3f(0.3f,0.8f,0.4f);
    glVertex2f(-4.0f*tScale, -2.25f*tScale);
    glVertex2f(-4.0f*tScale,-0.7f*tScale);
    glVertex2f(-6.9f*tScale, -1.25f*tScale);
    glVertex2f(-6.9f*tScale, -2.8f*tScale);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(-6.9f*tScale, -2.0f*tScale);
    glVertex2f(-6.9f*tScale, -2.5f*tScale);
    glVertex2f(-4.0f*tScale, -2.0f*tScale);
    glVertex2f(-4.0f*tScale,-1.5f*tScale);
    glEnd();

    // Coach 2
    glBegin(GL_QUADS);
    glColor3f(0.3f,0.8f,0.4f);
    glVertex2f(-7.0f*tScale, -1.3f*tScale);
    glVertex2f(-10.0f*tScale, -1.8f*tScale);
    glVertex2f(-10.0f*tScale, -3.5f*tScale);
    glVertex2f(-7.0f*tScale, -2.8f*tScale);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(-7.0f*tScale, -2.5f*tScale);
    glVertex2f(-10.0f*tScale, -3.2f*tScale);
    glVertex2f(-10.0f*tScale, -2.65f*tScale);
    glVertex2f(-7.0f*tScale, -2.0f*tScale);
    glEnd();

}

void bridge(){
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    // Sky
    glBegin(GL_QUADS);
    if(night)
        glColor3f(0.03f, 0.0f, 0.125f);
    else
        glColor3f(0.45f, 0.2f, 0.3f);
    glVertex2f(-10.0f, 7.3f);
    glVertex2f(10.0f, 7.3f);
    if(night)
        glColor3f(0.058f, 0.56f, 0.713f);
    else
        glColor3f(0.95f, 0.5f, 0.3f);
    glVertex2f(10.0f, 4.0f);
    glVertex2f(-10.0f, 4.0f);
    glEnd();

    // Water
    glBegin(GL_QUADS);
    if(night)
        glColor3f(0.03f, 0.0f, 0.125f);
    else
        glColor3f(0.08f, 0.1f,  0.2f);
    glVertex2f(-10.0f, 4.0f);
    glVertex2f(10.0f, 4.0f);
    if(night)
        glColor3f(0.058f, 0.56f, 0.713f);
    else
        glColor3f(0.8f, 0.5f, 0.3f);
    glVertex2f(10.0f, -7.32f);
    glVertex2f(-10.0f, -7.32f);
    glEnd();

    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(-10.0f, 4.0f);
    glVertex2f(10.0f, 4.0f);
    glEnd();

    glPushMatrix();
    glTranslated(xt, 0, 0);
    //Waves
    drawWaveRow(-5.0f, -4.5f, 1.0);
    drawWaveRow(-3.2f, -4.5f, 1.0);
    drawWaveRow(-0.4f, -5.2f, 1.1);
    drawWaveRow(-4.7f, -5.3f, 1.0);
    drawWaveRow(2.2f, -2.8f, 1.0);
    drawWaveRow(5.4f, -3.1f, 1.0);
    drawWaveRow(-3.0f, -6.0f, 1.2);
    drawWaveRow(-7.0f, -7.0f, 1.5);
    drawWaveRow(3.0f, -4.4f, 1.0);
    drawWaveRow(7.0f, -5.0f, 1.0);
    drawWaveRow(9.0f, -5.0f, 1.0);
    drawWaveRow(4.0f, -6.0f, 1.0);
    drawWaveRow(9.0f, -2.0f, 1.0);
    drawWaveRow(2.0f, -6.0f, 1.0);
    drawWaveRow(8.0f, -6.0f, 1.0);
    drawWaveRow(9.0f, -3.0f, 1.0);
    drawWaveRow(7.0f, 1.0f, 1.0);
    glPopMatrix();

    //Stars
    glPointSize(2.0f);
    glBegin(GL_POINTS);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(-8.0f, 6.0f); glVertex2f(-5.0f, 5.5f);
    glVertex2f(-2.0f, 6.5f); glVertex2f(1.0f, 5.0f);
    glVertex2f(4.0f, 6.2f); glVertex2f(7.0f, 5.8f);
    glVertex2f(9.0f, 6.8f); glVertex2f(-6.0f, 4.5f);
    glVertex2f(-9.0f, 5.0f); glVertex2f(3.0f, 4.8f);
    glVertex2f(8.0f, 4.5f); glVertex2f(-4.0f, 4.2f);
    glEnd();

    // Railway
    glBegin(GL_POLYGON);
    glColor3f(0.2156f, 0.25f, 0.27f);
    glVertex2f(-10.0f, -3.65f);
    glVertex2f(-7.04f, -2.88f);
    glVertex2f(-5.46f, -0.9f);
    glVertex2f(-10.0f, -1.75f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.2156f, 0.25f, 0.27f);
    glVertex2f(-4.635f, -2.455f);
    glVertex2f(0.24f, -1.46f);
    glVertex2f(5.47f, -0.09f);
    glVertex2f(5.0f, 1.2f);
    glVertex2f(-3.15f, -0.48f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.2156f, 0.25f, 0.27f);
    glVertex2f(5.47f, -0.09f);
    glVertex2f(8.12f, 0.98f);
    glVertex2f(8.98f, 1.63f);
    glVertex2f(8.97f, 2.32f);
    glVertex2f(5.0f, 1.2f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.2156f, 0.25f, 0.27f);
    glVertex2f(6.0f, 3.5f);
    glVertex2f(5.34f, 3.02f);
    glVertex2f(5.115f, 3.14f);
    glVertex2f(4.86f, 3.22f);
    glVertex2f(4.08f, 3.42f);
    glVertex2f(3.58f, 3.52f);
    glVertex2f(-1.15f, 4.13f);
    glEnd();

    glPushMatrix();
    glTranslated(Txt, Tyt, 0);
    drawTrain();
    glPopMatrix();


    //Zig-Zag
    glBegin(GL_POLYGON);
    glColor3f(0.753f, 0.812f, 0.811f);
    glVertex2f(-3.15f, -0.48f);
    glVertex2f(-2.4f, -2.04f);
    glVertex2f(-3.0f, -2.16f);
    glVertex2f(-3.53f, -0.98f);

    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.753f, 0.812f, 0.811f);
    glVertex2f(-2.53f, -1.74f);
    glVertex2f(-1.88f, -0.23f);
    glVertex2f(-1.22f, -0.1f);
    glVertex2f(-2.08f, -1.96f);
    glVertex2f(-2.4f, -2.04f);

    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.753f, 0.812f, 0.811f);
    glVertex2f(-1.035f, -0.075f);
    glVertex2f(-0.5f, 0.04f);
    glVertex2f(0.24f, -1.46f);
    glVertex2f(-0.32f, -1.61f);

    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.753f, 0.812f, 0.811f);
    glVertex2f(0.095f, -1.155f);
    glVertex2f(0.61f, 0.24f);
    glVertex2f(1.22f, 0.384f);
    glVertex2f(0.53f, -1.4f);
    glVertex2f(0.24f, -1.46f);

    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.753f, 0.812f, 0.811f);
    glVertex2f(1.22f, 0.384f);
    glVertex2f(1.72f, 0.48f);
    glVertex2f(2.32f, -0.96f);
    glVertex2f(1.8f, -1.08f);

    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.753f, 0.812f, 0.811f);
    glVertex2f(2.76f, 0.68f);
    glVertex2f(3.4f, 0.85f);
    glVertex2f(2.62f, -0.88f);
    glVertex2f(2.32f, -0.96f);
    glVertex2f(2.21f, -0.7f);

    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.753f, 0.812f, 0.811f);
    glVertex2f(3.505f, 0.85f);
    glVertex2f(4.04f, -0.5f);
    glVertex2f(3.62f, -0.63f);
    glVertex2f(3.18f, 0.45f);
    glVertex2f(3.32f, 0.8f);

    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.753f, 0.812f, 0.811f);
    glVertex2f(4.28f, 1.0f);
    glVertex2f(4.64f, 1.08f);
    glVertex2f(4.7f, 1.0f);
    glVertex2f(4.27f, -0.44f);
    glVertex2f(4.04f, -0.5f);
    glVertex2f(3.925f, -0.21f);

    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.753f, 0.812f, 0.811f);
    glVertex2f(4.68f, 1.1f);
    glVertex2f(5.08f, -0.23f);
    glVertex2f(5.45f, -0.12f);
    glVertex2f(5.05f, 1.16f);

    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.753f, 0.812f, 0.811f);
    glVertex2f(5.36f, 0.18f);
    glVertex2f(5.61f, 1.27f);
    glVertex2f(5.87f, 1.335f);
    glVertex2f(5.915f, 1.12f);
    glVertex2f(5.635f, -0.05f);
    glVertex2f(5.45f, -0.11f);

    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.753f, 0.812f, 0.811f);
    glVertex2f(5.87f, 1.335f);
    glVertex2f(6.23f, 0.14f);
    glVertex2f(6.59f, 0.26f);
    glVertex2f(6.2f, 1.4f);

    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.753f, 0.812f, 0.811f);
    glVertex2f(6.74f, 1.54f);
    glVertex2f(6.96f, 1.61f);
    glVertex2f(7.01f, 1.45f);
    glVertex2f(6.71f, 0.3f);
    glVertex2f(6.59f, 0.26f);
    glVertex2f(6.49f, 0.55f);

    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.753f, 0.812f, 0.811f);
    glVertex2f(6.96f, 1.61f);
    glVertex2f(7.23f, 1.69f);
    glVertex2f(7.58f, 0.6f);
    glVertex2f(7.35f, 0.5f);

    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.753f, 0.812f, 0.811f);
    glVertex2f(7.66f, 1.82f);
    glVertex2f(7.95f, 1.91f);
    glVertex2f(7.7f, 0.67f);
    glVertex2f(7.58f, 0.6f);
    glVertex2f(7.49f, 0.9f);

    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.753f, 0.812f, 0.811f);
    glVertex2f(8.15f, 0.95f);
    glVertex2f(7.9f, 1.65f);
    glVertex2f(7.95f, 1.91f);
    glVertex2f(8.08f, 1.95f);
    glVertex2f(8.38f, 1.1f);

    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.753f, 0.812f, 0.811f);
    glVertex2f(8.28f, 1.34f);
    glVertex2f(8.45f, 2.07f);
    glVertex2f(8.74f, 2.18f);
    glVertex2f(8.5f, 1.2f);
    glVertex2f(8.38f, 1.1f);

    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.753f, 0.812f, 0.811f);
    glVertex2f(8.74f, 2.18f);
    glVertex2f(8.87f, 2.26f);
    glVertex2f(8.98f, 1.6f);
    glVertex2f(8.85f, 1.47f);

    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.753f, 0.812f, 0.811f);
    glVertex2f(8.97f, 2.32f);
    glVertex2f(9.11f, 2.43f);
    glVertex2f(9.06f, 1.64f);
    glVertex2f(8.98f, 1.6f);

    glEnd();

    glLineWidth(1.5f);
    glBegin(GL_LINES);
    glColor3f(0.72549f, 0.796f, 0.82745f);
    glVertex2f(5.5f, 3.34f); glVertex2f(5.34f, 3.02f);
    glVertex2f(5.34f, 3.02f); glVertex2f(5.34f, 3.42f);
    glVertex2f(5.28f, 3.44f); glVertex2f(5.115f, 3.14f);
    glVertex2f(5.115f, 3.14f); glVertex2f(5.11f, 3.49f);
    glVertex2f(5.02f, 3.515f); glVertex2f(4.86f, 3.22f);
    glVertex2f(4.86f, 3.22f); glVertex2f(4.86f, 3.55f);
    glVertex2f(4.75f, 3.575); glVertex2f(4.61f, 3.3f);
    glVertex2f(4.61f, 3.3f); glVertex2f(4.61f, 3.6f);
    glVertex2f(4.52f, 3.62f); glVertex2f(4.37f, 3.35f);
    glVertex2f(4.37f, 3.35f); glVertex2f(4.37f, 3.635f);
    glVertex2f(5.34f, 3.02f); glVertex2f(5.34f, 3.42f);
    glVertex2f(4.22f, 3.66f); glVertex2f(4.08f, 3.42f);
    glVertex2f(4.08f, 3.42f); glVertex2f(4.08f, 3.68f);
    glVertex2f(3.96f, 3.7f); glVertex2f(3.835f, 3.475f);
    glVertex2f(3.835f, 3.475f); glVertex2f(3.835f, 3.715f);
    glVertex2f(3.71f, 3.74f); glVertex2f(3.58f, 3.52f);
    glVertex2f(3.58f, 3.52f); glVertex2f(3.58f, 3.74f);
    glVertex2f(3.48f, 3.77f); glVertex2f(3.365f, 3.56f);
    glEnd();

    // Piller_1(Bright)
    glBegin(GL_POLYGON);

    glColor3f(0.9f, 0.9f, 0.9f);
    glVertex2f(-5.85f, -5.75f);
    glVertex2f(-5.7f, -4.0f);
    glVertex2f(-6.6f, -4.0f);
    glVertex2f(-6.75f, -6.05f);

    glEnd();

    glBegin(GL_POLYGON);

    glColor3f(0.9f, 0.9f, 0.9f);
    glVertex2f(-5.7f, -4.0f);
    glVertex2f(-3.15f, -0.48f);
    glVertex2f(-4.14f, -0.655f);
    glVertex2f(-6.6f, -4.0f);

    glEnd();

    // Piller_1(Dark)
    glBegin(GL_POLYGON);
    glColor3f(0.388f, 0.454f, 0.482f);
    glVertex2f(-7.74f, -3.205f);
    glVertex2f(-9.3f, -4.79f);
    glVertex2f(-9.3f, -5.77f);
    glVertex2f(-6.75f, -6.05f);
    glVertex2f(-6.6f, -4.0f);

    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.388f, 0.454f, 0.482f);
    glVertex2f(-7.74f, -3.205f);
    glVertex2f(-6.6f, -4.0f);
    glVertex2f(-4.14f, -0.655f);
    glVertex2f(-5.47f, -0.905f);
    glVertex2f(-7.06f, -2.92f);

    glEnd();

    // Piller_1(Shadow)
    glBegin(GL_POLYGON);
    glColor3f(0.164f, 0.203f, 0.239f);
    glVertex2f(-7.74f, -3.205f);
    glVertex2f(-9.3f, -4.78f);
    glVertex2f(-9.35f, -3.55f);

    glEnd();

    // Railing
    glBegin(GL_POLYGON);
    glColor3f(0.631f, 0.702f, 0.741f);
    glVertex2f(-10.0f, -1.75f);
    glVertex2f(5.875f, 1.332f);
    glVertex2f(8.74f, 2.18f);

    glVertex2f(8.28f, 2.2f);
    glVertex2f(5.0f, 1.38f);
    glVertex2f(-10.0f, -0.98f);

    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.631f, 0.702f, 0.741f);
    glVertex2f(-10.0f, -1.75f);
    glVertex2f(5.875f, 1.332f);
    glVertex2f(8.74f, 2.18f);
    glVertex2f(8.28f, 2.2f);
    glVertex2f(5.0f, 1.38f);
    glVertex2f(-10.0f, -0.98f);

    glEnd();

    double math_x_min = 5.0;
    double math_x_max = 9.31;
    double math_step = 0.01;

    glLineWidth(15.0f);
    glColor3f(0.631f, 0.702f, 0.741f);

    glBegin(GL_LINE_LOOP);
    for(double mx=math_x_min; mx<=9.28; mx+=math_step){
        double disc=(0.0077*mx*mx)-(51.9816*mx)+483.1736;

        if(disc>=0.0){
            double upper=((0.636*mx)+28.96+sqrt(disc))/12.4;
            double lower=((0.636*mx)+28.96-sqrt(disc))/12.4;

            glVertex2f(mx, lower);
        }
    }
    glEnd();

    glLineWidth(15.0f);
    glColor3f(0.631f, 0.702f, 0.741f);
    glBegin(GL_LINES);
    glVertex2f(-10.0f, 1.12f);
    glVertex2f(5.0f, 2.7f);
    glEnd();

    //Piller_2(Bright)
    glBegin(GL_POLYGON);
    glColor3f(0.9f, 0.9f, 0.9f);
    glVertex2f(2.44f, -1.4f);
    glVertex2f(1.0f, -1.8f);
    glVertex2f(0.1f, -3.02f);
    glVertex2f(0.92f, -2.84f);


    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.9f, 0.9f, 0.9f);
    glVertex2f(0.1f, -3.02f);
    glVertex2f(0.1f, -4.34f);
    glVertex2f(0.89f, -4.06f);
    glVertex2f(0.92f, -2.84f);

    glEnd();
    glFlush();

    //Piller_2(Dark)
    glBegin(GL_POLYGON);
    glColor3f(0.388f, 0.454f, 0.482f);
    glVertex2f(1.0f, -1.8f);
    glVertex2f(-1.75f, -3.45f);
    glVertex2f(-1.75f, -4.15f);
    glVertex2f(0.1f, -3.02f);

    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.388f, 0.454f, 0.482f);
    glVertex2f(-1.75f, -4.15f);
    glVertex2f(0.1f, -3.02f);
    glVertex2f(0.1f, -4.34f);

    glEnd();

    // Piller_2(Shadow)
    glBegin(GL_POLYGON);
    glColor3f(0.164f, 0.203f, 0.239f);
    glVertex2f(1.0f, -1.8f);
    glVertex2f(-1.9f, -2.55f);
    glVertex2f(-1.75f, -2.82f);
    glVertex2f(-1.75f, -3.45f);
    glEnd();

    //Piller_3(Bright)
    glBegin(GL_POLYGON);
    glColor3f(0.9f, 0.9f, 0.9f);
    glVertex2f(5.0f, -2.32f);
    glVertex2f(5.51f, -2.12f);
    glVertex2f(5.58f, -1.24f);
    glVertex2f(5.02f, -1.42f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.9f, 0.9f, 0.9f);
    glVertex2f(5.58f, -1.24f);
    glVertex2f(5.02f, -1.42f);
    glVertex2f(5.52f, -0.46f);
    glVertex2f(6.28f, -0.16f);
    glEnd();

    //Piller_3(Dark)
    glBegin(GL_POLYGON);
    glColor3f(0.388f, 0.454f, 0.482f);
    glVertex2f(5.02f, -1.42f);
    glVertex2f(5.0f, -2.32f);
    glVertex2f(3.42f, -2.26f);
    glVertex2f(3.48f, -1.84f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.388f, 0.454f, 0.482f);
    glVertex2f(5.52f, -0.46f);
    glVertex2f(5.02f, -1.42f);
    glVertex2f(3.48f, -1.84f);
    glEnd();

    // Piller_3(Shadow)
    glBegin(GL_POLYGON);
    glColor3f(0.164f, 0.203f, 0.239f);
    glVertex2f(5.52f, -0.46f);
    glVertex2f(3.44f, -1.13f);
    glVertex2f(3.55f, -1.35f);
    glVertex2f(3.48f, -1.84f);

    glEnd();

    //Piller_4(Bright)
    glBegin(GL_POLYGON);
    glColor3f(0.9f, 0.9f, 0.9f);
    glVertex2f(7.7f, 0.25f);
    glVertex2f(8.08f, 0.36f);
    glVertex2f(8.07f, -0.18f);
    glVertex2f(7.7f, -0.35f);

    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.9f, 0.9f, 0.9f);
    glVertex2f(7.7f, 0.25f);
    glVertex2f(7.95f, 0.58f);
    glVertex2f(8.56f, 0.96f);
    glVertex2f(8.08, 0.36f);
    glEnd();

    //Piller_4(Dark)
    glBegin(GL_POLYGON);
    glColor3f(0.388f, 0.454f, 0.482f);
    glVertex2f(6.86f, -0.11f);
    glVertex2f(6.86f, -0.29f);
    glVertex2f(7.7f, -0.35f);
    glVertex2f(7.7f, 0.25f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.388f, 0.454f, 0.482f);
    glVertex2f(7.95f, 0.58f);
    glVertex2f(7.7f, 0.25f);
    glVertex2f(6.86f, -0.11f);

    glEnd();

    // Piller_4(Shadow)
    glBegin(GL_POLYGON);
    glColor3f(0.164f, 0.203f, 0.239f);
    glVertex2f(7.95f, 0.58f);
    glVertex2f(6.86f, -0.11f);
    glVertex2f(6.86f, 0.07f);
    glEnd();

    //Piller_5(Bright)
    glBegin(GL_POLYGON);
    glColor3f(0.9f, 0.9f, 0.9f);
    glVertex2f(4.97f, 2.85f);
    glVertex2f(5.16f, 2.9f);
    glVertex2f(4.92f, 3.2f);
    glVertex2f(4.71f, 3.25f);
    glVertex2f(4.71f, 3.14f);
    glEnd();

    // Piller_5(Dark)
    glBegin(GL_POLYGON);
    glColor3f(0.388f, 0.454f, 0.482f);
    glVertex2f(5.5f, 3.09f);
    glVertex2f(4.92f, 3.2f);
    glVertex2f(5.16f, 2.9f);
    glEnd();

    //Piller_6(Bright)
    glBegin(GL_POLYGON);
    glColor3f(0.9f, 0.9f, 0.9f);
    glVertex2f(3.7f, 3.24f);
    glVertex2f(3.7f, 3.0f);
    glVertex2f(3.87f, 3.0f);
    glVertex2f(3.87f, 3.24f);
    glVertex2f(3.67f, 3.48f);
    glVertex2f(3.47f, 3.52f);
    glVertex2f(3.47f, 3.43f);
    glEnd();

    // Piller_6(Dark)
    glBegin(GL_POLYGON);
    glColor3f(0.388f, 0.454f, 0.482f);
    glVertex2f(3.87f, 3.24f);
    glVertex2f(3.87f, 3.0f);
    glVertex2f(4.23f, 3.0f);
    glVertex2f(4.23f, 3.37f);
    glVertex2f(3.67f, 3.48f);
    glEnd();

    //Piller_7(Bright)
    glBegin(GL_POLYGON);
    glColor3f(0.9f, 0.9f, 0.9f);
    glVertex2f(2.91f, 3.45f);
    glVertex2f(2.91f, 3.28f);
    glVertex2f(3.03f, 3.28f);
    glVertex2f(3.02f, 3.435f);
    glVertex2f(2.89f, 3.62f);
    glVertex2f(2.77f, 3.635f);
    glVertex2f(2.77f, 3.57f);
    glEnd();

    // Piller_7(Dark)
    glBegin(GL_POLYGON);
    glColor3f(0.388f, 0.454f, 0.482f);
    glVertex2f(3.02f, 3.435f);
    glVertex2f(3.03f, 3.28f);
    glVertex2f(3.27f, 3.28f);
    glVertex2f(3.27f, 3.56f);
    glVertex2f(2.89f, 3.62f);
    glEnd();

    //Piller_8(Bright)
    glBegin(GL_POLYGON);
    glColor3f(0.9f, 0.9f, 0.9f);
    glVertex2f(2.34f, 3.61f);
    glVertex2f(2.34f, 3.5f);
    glVertex2f(2.42f, 3.5f);
    glVertex2f(2.42f, 3.61f);
    glVertex2f(2.34f, 3.7f);
    glVertex2f(2.24f, 3.72f);
    glVertex2f(2.24f, 3.69f);
    glEnd();

    // Piller_8(Dark)
    glBegin(GL_POLYGON);
    glColor3f(0.388f, 0.454f, 0.482f);
    glVertex2f(2.42f, 3.61f);
    glVertex2f(2.42f, 3.5f);
    glVertex2f(2.57f, 3.5f);
    glVertex2f(2.57f, 3.67f);
    glVertex2f(2.34f, 3.7f);
    glEnd();

    //Piller_9(Bright)
    glBegin(GL_POLYGON);
    glColor3f(0.9f, 0.9f, 0.9f);
    glVertex2f(1.9f, 3.68f);
    glVertex2f(1.9f, 3.57f);
    glVertex2f(1.98f, 3.57f);
    glVertex2f(1.98f, 3.685f);
    glVertex2f(1.91f, 3.77f);
    glVertex2f(1.8f, 3.785);
    glEnd();

    // Piller_9(Dark)
    glBegin(GL_POLYGON);
    glColor3f(0.388f, 0.454f, 0.482f);
    glVertex2f(1.98f, 3.685f);
    glVertex2f(1.98f, 3.57f);
    glVertex2f(2.14f, 3.57f);
    glVertex2f(2.14f, 3.74f);
    glVertex2f(1.91f, 3.77f);
    glEnd();

    // Piller_10(Dark)
    glBegin(GL_POLYGON);
    glColor3f(0.388f, 0.454f, 0.482f);
    glVertex2f(1.55f, 3.76f);
    glVertex2f(1.55f, 3.69f);
    glVertex2f(1.72f, 3.69f);
    glVertex2f(1.72f, 3.8f);
    glVertex2f(1.51f, 3.82f);
    glEnd();

    // Piller_11(Dark)
    glBegin(GL_POLYGON);
    glColor3f(0.388f, 0.454f, 0.482f);
    glVertex2f(1.265f, 3.818);
    glVertex2f(1.265f, 3.78f);
    glVertex2f(1.36f, 3.78f);
    glVertex2f(1.36f, 3.86f);
    glVertex2f(1.22f, 3.855f);
    glEnd();

    // Piller_12(Dark)
    glBegin(GL_POLYGON);
    glColor3f(0.388f, 0.454f, 0.482f);
    glVertex2f(1.04f, 3.85f);
    glVertex2f(1.04f, 3.81f);
    glVertex2f(1.14f, 3.81f);
    glVertex2f(1.14f, 3.885f);
    glVertex2f(1.0f, 3.89f);
    glEnd();


    //Rail Railing(Dark)
    glBegin(GL_POLYGON);
    glColor3f(0.753f, 0.812f, 0.811f);
    glVertex2f(-4.75f, -2.68f);
    glVertex2f(0.5f, -1.6f);
    glVertex2f(1.0f, -1.8f);
    glVertex2f(-1.9f, -2.55f);
    glVertex2f(-5.15f, -3.25f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.753f, 0.812f, 0.811f);
    glVertex2f(1.0f, -1.8f);
    glVertex2f(2.44f, -1.4f);
    glVertex2f(3.44f, -1.13f);
    glVertex2f(5.52f, -0.46f);
    glVertex2f(5.42f, -0.27f);
    glVertex2f(4.15f, -0.61f);
    glVertex2f(0.5f, -1.6f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.753f, 0.812f, 0.811f);
    glVertex2f(5.52f, -0.46f);
    glVertex2f(6.28f, -0.16f);
    glVertex2f(7.95f, 0.58f);
    glVertex2f(8.26f, 0.92f);
    glVertex2f(5.42f, -0.27f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.753f, 0.812f, 0.811f);
    glVertex2f(7.95f, 0.58f);
    glVertex2f(8.56f, 0.96f);
    glVertex2f(9.06f, 1.64f);
    glVertex2f(8.26f, 0.92f);
    glEnd();

    // Road
    glColor3f(0.388f, 0.455f, 0.517f);
    glBegin(GL_POLYGON);

    for(double mx=math_x_max; mx>=math_x_min; mx-=math_step){
        double disc1=(0.0077*mx*mx)-(51.9816*mx)+483.1736;
        if(disc1>=0.0){
            double outerLower=((0.636*mx)+28.96-sqrt(disc1))/12.4;
            glVertex2f(mx, outerLower);
        }
    }

    for(double mx=math_x_min; mx<=5.61; mx+=math_step){
        double disc2=(-0.459*mx*mx)-(960116.1237*mx)+5385329.5198;
        if(disc2>=0.0){
            double innerLower=((69.33*mx)+7351.2445-sqrt(disc2))/2403.554;
            glVertex2f(mx, innerLower);
        }
    }

    for(double mx=5.61; mx>=math_x_min; mx-=math_step){
        double disc2=(-0.459*mx*mx)-(960116.1237*mx)+5385329.5198;
        if(disc2>=0.0){
            double innerUpper=((69.33*mx)+7351.2445+sqrt(disc2))/2403.554;
            glVertex2f(mx, innerUpper);
        }
    }

    for(double mx=math_x_min; mx<=math_x_max; mx+=math_step){
        double disc1=(0.0077*mx*mx)-(51.9816*mx)+483.1736;
        if(disc1>=0.0){
            double outerUpper=((0.636*mx)+28.96+sqrt(disc1))/12.4;
            glVertex2f(mx, outerUpper);
        }
    }
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.388f, 0.455f, 0.517f);
    glVertex2f(-10.0f, -0.98f);
    glVertex2f(5.0f, 1.38f);
    glVertex2f(5.0f, 2.85f);
    glVertex2f(-10.0f, 1.12f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.388f, 0.455f, 0.517f);
    glVertex2f(5.0f, 3.7975f);
    glVertex2f(5.0f, 3.525f);
    glVertex2f(-1.15f, 4.13f);
    glEnd();

    glLineWidth(0.75f);
    glBegin(GL_LINE_STRIP);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(-10.0f, 0.27f);
    glVertex2f(5.0f, 2.17f);
    glVertex2f(5.94f, 2.38f);
    glVertex2f(6.5f, 2.53f);
    glVertex2f(7.0f, 2.7f);
    glVertex2f(7.25f, 2.95f);
    glVertex2f(7.2f, 3.1f);
    glVertex2f(6.5f, 3.4f);
    glVertex2f(5.7f, 3.6f);
    glVertex2f(1.47f, 3.95f);
    glEnd();

    //Street Lamp
    drawLamp(-6.58, 1.52, 1.4, 0);
    drawLamp(1.47, 2.33, 1.1, 0);
    drawLamp(5.55, 3.2, 0.7, 0);


    // Moving Car
    glPushMatrix();
    glTranslated(Cxt, Cyt, 0);
    drawCar(-9.0f, 0.7f);
    glPopMatrix();

    // Street Lamp
    drawLamp(-1.29, 0.26, 1.3, 1);
    drawLamp(6.65, 1.73, 1.0, 1);
    drawLamp(9.3, 2.8, 0.7, 1);
    drawLamp(5.25, 3.775, 0.35, 1);
    drawLamp(4.6, 3.6, 0.4, 0);
    drawLamp(3.15, 3.85, 0.2, 1);
    drawLamp(2.85, 3.8, 0.2, 0);
    drawLamp(2.0 , 4, 0.1, 1);
    drawLamp(1.8, 3.9 , 0.1, 0);

    glFlush();
}

void keyPress(unsigned char key, int x, int y){
    switch(key){
        case 'D':
        case 'd':
            night = false;
            break;

        case 'N':
        case 'n':
            night = true;
            break;
    }
    glutPostRedisplay();
}

void timer(int value){
    xt+=0.01;
    glutPostRedisplay();
    glutTimerFunc(60, timer, 0);
}

void moveCar(int value){
    Cxt+=0.1;
    Cyt+=0.0125;
    scale-=0.002;
    if(Cxt>14.9){
        Cxt+=0.01;
        Cyt+=0.04;
        scale-=0.005;
    }
    if(Cyt>2.53){
        Cxt-=0.4;
        Cyt+=0.001;
        if(scale>=0.0)
        scale-=0.025;
        else scale=0.0;
    }
    if(Cyt>=2.95){
        Cxt-=0.1;
        Cyt+=0.05;
        if(scale>=0.0)
        scale-=0.025;
        else scale=0.0;
    }
    glutPostRedisplay();
    glutTimerFunc(60, moveCar, 0);
}

void moveTrain(int value){
    Txt+=0.1;
    Tyt+=0.02;
    tScale-=0.001;
    if(Txt>=8.5){
        Txt+=0.0;
        Tyt+=0.01;
        tScale-=0.01;
    }
    if(Txt>=10.0){
        tScale=0.0;
    }
    glutPostRedisplay();
    glutTimerFunc(60, moveTrain, 0);
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowSize(1080, 720);
    glutInitWindowPosition(150, 50);
    glutCreateWindow("Padma Bridge");

    init();
    glutDisplayFunc(bridge);
    glutKeyboardFunc(keyPress);
    glutTimerFunc(30, timer, 0);
    glutTimerFunc(30, moveCar, 0);
    glutTimerFunc(30, moveTrain, 0);
    glutMainLoop();
    return 0;
}

