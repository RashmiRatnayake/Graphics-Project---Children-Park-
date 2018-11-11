#include <iostream>
#include<windows.h>//this must be typed before including glut library
#include<GL/freeglut.h>
#include<GL/freeglut_ext.h>
#include<GL/freeglut_std.h>
#include<math.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/glext.h>
#include <SimpleOpenGLImageLibrary/src/SOIL.h>


using namespace std;

//global variables
char message[6][80];
char message2[6][80];
char message3[6][80];
int numberOfQuotes=5,i;

// variables to move outermost Object Frame (to move all the rendered environment)
GLfloat moveX = 0.0f;
GLfloat moveY = 0.0f;
GLfloat moveZ = 0.0f;

// variables to rotate outermost Object Frame (to move all the rendered environment)
GLfloat rotX = 0.0f;
GLfloat rotY = 0.0f;
GLfloat rotZ = 0.0f;


// For animating the rotation of the objects
GLfloat animateRotation = 0.0f;

//variables to move the camera
GLfloat camY = 0.0f;
GLfloat camX = 0.0f;
GLfloat camZ = 0.0f;

// A quadratic object pointer used to draw the sides of the cylinder
GLUquadricObj *qobj;

//An array to store the normal vector data for the faces
GLfloat vNormal[3]= {};

GLuint tex;
GLuint tex2;
GLuint tex3;
GLuint tex4;
GLuint tex5;

GLuint drawATree;
GLfloat x,y,z;

void initLighting(){

    GLfloat L0_Ambient[] = {0.8, 0.8, 0.8, 1.0};
    GLfloat L0_Diffuse[] = {0.7, 0.7, 0.7, 1.0};
    GLfloat L0_postion[] = {0, 100, 0, 1.0};

    glLightfv(GL_LIGHT0, GL_AMBIENT, L0_Ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, L0_Diffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, L0_postion);

    GLfloat L1_Ambient[] = {0.5, 0.5, 0.5, 1.0};
    GLfloat L1_Diffuse[] = {0.7, 0.7, 0.7, 1.0};
    GLfloat L1_Specular[] = {0.0, 1.0, 0.0, 1.0};
    GLfloat L1_postion[] = {14.9, 15, -17, 1.0};

    glLightfv(GL_LIGHT1, GL_AMBIENT, L1_Ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, L1_Diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, L1_Specular);
    glLightfv(GL_LIGHT1, GL_POSITION, L1_postion);


    //Declaration of the light reflecting properties for the materials
    GLfloat specularReflectance[] = {1.0, 1.0, 1.0, 1.0};
    glMaterialfv(GL_FRONT, GL_SPECULAR, specularReflectance);
    glMateriali(GL_FRONT, GL_SHININESS, 50);


}

//textures
void initTexture(){

    int width, height;
    unsigned char* image = SOIL_load_image("C:/Users/Rashmi/Pictures/ground1.jpeg", &width, &height, 0, SOIL_LOAD_RGB);


    if (!image) {
        std::cout << "Failed to load texture: " << sizeof(image) << std::endl;
    }else{
        std::cout << &image << std::endl;
    }


    unsigned char data[] =
    {
        128, 128, 128, 255,
        255, 0, 0, 255,
        0, 255, 0, 255,
        0, 0, 255, 255
    };



    glGenTextures( 1, &tex );
    glBindTexture( GL_TEXTURE_2D, tex );


    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
              GL_UNSIGNED_BYTE, image);

    // Use the following line in order to load the created texture map instead of the image
    // glTexImage2D( GL_TEXTURE_2D, 0,GL_RGBA, 2, 2, 0, GL_RGBA, GL_UNSIGNED_BYTE, data );

}
void initTexture2(){

    int width, height;
    unsigned char* image2 = SOIL_load_image("C:/Users/Rashmi/Pictures/roof5.jpg", &width, &height, 0, SOIL_LOAD_RGB);


    if (!image2) {
        std::cout << "Failed to load texture: " << sizeof(image2) << std::endl;
    }else{
        std::cout << &image2 << std::endl;
    }

    glGenTextures( 1, &tex2 );
    glBindTexture( GL_TEXTURE_2D, tex2 );

    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,GL_UNSIGNED_BYTE, image2);

    // Use the following line in order to load the created texture map instead of the image
    // glTexImage2D( GL_TEXTURE_2D, 0,GL_RGBA, 2, 2, 0, GL_RGBA, GL_UNSIGNED_BYTE, data );
}
void initTexture3(){

    int width, height;
    unsigned char* image3 = SOIL_load_image("C:/Users/Rashmi/Pictures/wood1.jpg", &width, &height, 0, SOIL_LOAD_RGB);


    if (!image3) {
        std::cout << "Failed to load texture: " << sizeof(image3) << std::endl;
    }else{
        std::cout << &image3 << std::endl;
    }

    glGenTextures( 1, &tex3 );
    glBindTexture( GL_TEXTURE_2D, tex3 );

    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,GL_UNSIGNED_BYTE, image3);

    // Use the following line in order to load the created texture map instead of the image
    // glTexImage2D( GL_TEXTURE_2D, 0,GL_RGBA, 2, 2, 0, GL_RGBA, GL_UNSIGNED_BYTE, data );
}
void initTextureRoad(){

    int width, height;
    unsigned char* image = SOIL_load_image("C:/Users/Rashmi/Pictures/road2.jpg", &width, &height, 0, SOIL_LOAD_RGB);


    if (!image) {
        std::cout << "Failed to load texture: " << sizeof(image) << std::endl;
    }else{
        std::cout << &image << std::endl;
    }

    glGenTextures( 1, &tex4 );
    glBindTexture( GL_TEXTURE_2D, tex4 );

    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,GL_UNSIGNED_BYTE, image);

    // Use the following line in order to load the created texture map instead of the image
    // glTexImage2D( GL_TEXTURE_2D, 0,GL_RGBA, 2, 2, 0, GL_RGBA, GL_UNSIGNED_BYTE, data );
}
void initTextureGrass(){

    int width, height;
    unsigned char* image = SOIL_load_image("C:/Users/Rashmi/Pictures/ground.jpg", &width, &height, 0, SOIL_LOAD_RGB);


    if (!image) {
        std::cout << "Failed to load texture: " << sizeof(image) << std::endl;
    }else{
        std::cout << &image << std::endl;
    }

    glGenTextures( 1, &tex5 );
    glBindTexture( GL_TEXTURE_2D, tex5 );

    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,GL_UNSIGNED_BYTE, image);

    // Use the following line in order to load the created texture map instead of the image
    // glTexImage2D( GL_TEXTURE_2D, 0,GL_RGBA, 2, 2, 0, GL_RGBA, GL_UNSIGNED_BYTE, data );
}

void Timer(int x){
    animateRotation += animateRotation >= 360.0? -animateRotation : 5;
    glutPostRedisplay();

    glutTimerFunc(60, Timer, 1);
}


void makeCylinder(GLfloat height, GLfloat base){
GLUquadric *obj = gluNewQuadric();
//gluQuadricDrawStyle(obj, GLU_LINE);
glColor3f(0.03f, 0.23f, 0.01f);
glPushMatrix();
glRotatef(-90, 1.0,0.0,0.0);
gluCylinder(obj, base,base-(0.2*base), height, 20,20);
glPopMatrix();
glutSwapBuffers();
}

void drawTree(GLfloat height, GLfloat base){
GLfloat angle;
makeCylinder(height, base);
glTranslatef(0.0, height, 0.0);
height -= height*.2; base-= base*0.3;
for(int a= 0; a<3; a++){
angle = rand()%50+20;
if(angle >48)
angle = -(rand()%50+20);
if (height >1){
glPushMatrix();
glRotatef(angle,1,0.0,1);
drawTree(height,base);
glPopMatrix();

}
}
}

void init(){
    glClearColor(0.5f, 0.5f, 1.0f, 1.0f);
    GLfloat globalAmbient[] = {0.8, 0.8, 0.8, 1.0};
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);

    drawATree=glGenLists(1);
    glNewList(drawATree, GL_COMPILE);
    drawTree(4,0.2);
    glEndList();

    //Enable the adding of lights
    glEnable(GL_LIGHTING);

    glShadeModel(GL_SMOOTH);

    // Changing the global Ambient illumination without any lights present
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbient);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    initLighting();

    // Enabling the color tracking of each faces of the materials. this enables the color visibility of the materials
    glEnable(GL_COLOR_MATERIAL);

    //Turn on lighting
    glEnable(GL_LIGHT0);

    //turn on light1
    //glEnable(GL_LIGHT1);


    // enable the normalization of the normal vectors (converting the vector values to the range 0-1)
    glEnable(GL_NORMALIZE);
    qobj = gluNewQuadric();
    gluQuadricDrawStyle(qobj, GLU_FILL);
    gluQuadricNormals(qobj, GLU_SMOOTH);

    initTexture();
    initTexture2();
    initTexture3();
    initTextureRoad();
    initTextureGrass();
}

void drawFloor(){

    glBegin(GL_QUADS);
        glColor4f(0, 1, 0, 1);

        glNormal3d(0, 0, 1);
        glTexCoord2f(0,1);
        glVertex3f(50,0, 50);
        glTexCoord2f(1,1 );
        glVertex3f(-50,0, 50);
        glTexCoord2f(1,0 );
        glVertex3f(-50,0, -50);
        glTexCoord2f(0,0);
        glVertex3f(50,0, -50);

    glEnd();
}

void drawBalloonMan() {

    glPushMatrix();
    glColor3f(0.92f, 0.12f, 0.6f);

    // Draw Body
    glTranslatef(-30.0f ,4.1f, 15.0f);
    glutSolidSphere(4.0f,20,20);

    // Draw Head
    glColor3f(0.89f, 0.47f, 0.37f);
    glTranslatef(0.0f, 5.5f, 0.0f);
    glutSolidSphere(2.0f,20,20);

    // Draw Eyes and nose
    glPushMatrix();
    glRotatef(50,0,1,0);
    glColor3f(0.0f,0.0f,0.0f);
    glTranslatef(0.6f, 0.70f, 1.8f);
    GLdouble plane []= {0, 0, 1, 0};
    glClipPlane(GL_CLIP_PLANE0, plane);
        glEnable(GL_CLIP_PLANE0);
        glutSolidSphere(0.5f,10,10);
        glDisable(GL_CLIP_PLANE0);

    glTranslatef(-1.2f, 0.0f, -0.1f);
        glEnable(GL_CLIP_PLANE0);
        glutSolidSphere(0.5f,10,10);
        glDisable(GL_CLIP_PLANE0);
    glTranslatef(0.6f, -1.3f, 0.0f);
    glColor3f(1,0,0);
    glutSolidSphere(0.8f,10,10);
    glPopMatrix();

     //draw ears
    glRotatef(50,0,1,0);
    glColor3f(0.0f, 0.0f, 0.0f);
    glTranslatef(-1.3f, 1.4f, 0.9f);
    glutSolidSphere(0.5f,20,20);

    glTranslatef(2.5f, 0.2f, 0.0f);
    glutSolidSphere(0.5f,20,20);

 glPopMatrix();
}

void drawGate() {

    glPushMatrix();
        glColor3f(0.39f, 0.24f, 0.02f);
        // Draw left horizontal cylinders
        glTranslatef(-45.0f ,2.0f, 23.0f);
        glRotatef(90,0.0f ,1.0f, 0.0f);
        glutSolidCylinder(0.3,38,20,20);
        glTranslatef(0.0f ,1.0f, 0.0f);
        glutSolidCylinder(0.3,38,20,20);
        glTranslatef(0.0f ,1.0f, 0.0f);
        glutSolidCylinder(0.3,38,20,20);
        glTranslatef(0.0f ,1.0f, 0.0f);
        glutSolidCylinder(0.3,38,20,20);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.39f, 0.24f, 0.02f);
        // Draw right horizontal cylinders
        glTranslatef(5.0f ,2.0f, 23.0f);
        glRotatef(90,0.0f ,1.0f, 0.0f);
        glutSolidCylinder(0.3,40,20,20);
        glTranslatef(0.0f ,1.0f, 0.0f);
        glutSolidCylinder(0.3,40,20,20);
        glTranslatef(0.0f ,1.0f, 0.0f);
        glutSolidCylinder(0.3,40,20,20);
        glTranslatef(0.0f ,1.0f, 0.0f);
        glutSolidCylinder(0.3,18,20,20);
    glPopMatrix();

    // Draw Nameboard
    glPushMatrix();
         glColor3f(0.52f, 0.32f, 0.02f);
         glTranslatef(5.0f, 0.0f, 23.0f);
         glRotatef(90,-1.0f,0.0f,0.0f);
         glutSolidCylinder(0.4,14,50,50);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.52f, 0.32f, 0.02f);
        glTranslatef(-7.0f, 0.0f, 23.0f);
        glRotatef(90,-1.0f,0.0f,0.0f);
        glutSolidCylinder(0.4,14,50,50);
    glPopMatrix();

    //frame
    glPushMatrix();
        glColor3f(0.52f, 0.32f, 0.02f);
        glTranslatef(5.0f, 14.0f, 23.0f);
        glRotatef(90,0.0f,-1.0f,0.0f);
        glutSolidCylinder(0.2,12,50,50);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.52f, 0.32f, 0.02f);
        glTranslatef(5.0f, 11.0f, 23.0f);
        glRotatef(90,0.0f,-1.0f,0.0f);
        glutSolidCylinder(0.2,12,50,50);
    glPopMatrix();

    //name
    glPushMatrix();
        glTranslatef(4.6f, 11.0f, 23.0f);
        glRotatef(180,0.0f,-1.0f,0.0f);

        glBegin(GL_QUADS);
            glPolygonMode(GL_FRONT, GL_FILL);
            glColor3f(1.0f,1.0f,1.0f);
            glVertex3f(0,0, 0);
            glColor3f(1.0f,1.0f,1.0f);
            glVertex3f(12,0, 0);
            glColor3f(0.92f, 0.11f, 0.93f);
            glVertex3f(12,3,0 );
            glColor3f(0.89f, 0.47f, 0.37f);
            glVertex3f(0,3, 0);
        glEnd();

    glPopMatrix();

    glPushMatrix();
        glTranslatef(0.0f, 13.0f, 23.0f);

        for(int l=0, lenghOfQuote = 0;l<numberOfQuotes;l++)
        {
            lenghOfQuote = (int)strlen(message[l]);
            glPushMatrix();
                glScalef(1/152.38, 1/152.38, 1/152.38);
                glTranslatef(-(lenghOfQuote*37),-(l*200), 5);//if translation is not done, all the lines will be drawn on top  of each other
                for (i = 0; i < lenghOfQuote; i++)
                {
                    glColor3f(0.0,0.0,0.0);
                    glutStrokeCharacter(GLUT_STROKE_ROMAN, message[l][i]);//or we can use GLUT_STROKE_MONO_ROMAN which is somewhat thinner//or get libraries for other fonts
                }
            glPopMatrix();
        }
    glPopMatrix();
}

void drawBoundary() {

    glPushMatrix();
        glColor3f(0.39f, 0.24f, 0.02f);
        // Draw left horizontal cylinders
        glTranslatef(-45.0f ,2.0f, 23.0f);
        glRotatef(-180,0.0f ,1.0f, 0.0f);
        glutSolidCylinder(0.3,68,20,20);
        glTranslatef(0.0f ,1.0f, 0.0f);
        glutSolidCylinder(0.3,68,20,20);
        glTranslatef(0.0f ,1.0f, 0.0f);
        glutSolidCylinder(0.3,68,20,20);
        glTranslatef(0.0f ,1.0f, 0.0f);
        glutSolidCylinder(0.3,68,20,20);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.39f, 0.24f, 0.02f);
        // Draw right horizontal cylinders
        glTranslatef(45.0f ,2.0f, 23.0f);
        glRotatef(180,0.0f ,1.0f, 0.0f);
        glutSolidCylinder(0.3,68,20,20);
        glTranslatef(0.0f ,1.0f, 0.0f);
        glutSolidCylinder(0.3,68,20,20);
        glTranslatef(0.0f ,1.0f, 0.0f);
        glutSolidCylinder(0.3,68,20,20);
        glTranslatef(0.0f ,1.0f, 0.0f);
        glutSolidCylinder(0.3,68,20,20);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.39f, 0.24f, 0.02f);
        // Draw back horizontal cylinders
        glTranslatef(-45.0f ,2.0f, -45.0f);
        glRotatef(90,0.0f ,1.0f, 0.0f);
        glutSolidCylinder(0.3,90,20,20);
        glTranslatef(0.0f ,1.0f, 0.0f);
        glutSolidCylinder(0.3,90,20,20);
        glTranslatef(0.0f ,1.0f, 0.0f);
        glutSolidCylinder(0.3,90,20,20);
        glTranslatef(0.0f ,1.0f, 0.0f);
        glutSolidCylinder(0.3,90,20,20);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.39f, 0.24f, 0.02f);
        // Draw vertical parts of gate (back)
        glTranslatef(-45.0f ,0.0f, -45.0f);
        glRotatef(90,-1.0f,0.0f,0.0f);
        glutSolidCylinder(0.3,7,20,20);
        for(int i=0; i<17; i++){
            glTranslatef(5.0f ,0.0f, 0.0f);
            glutSolidCylinder(0.3,7,20,20);
        }
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.39f, 0.24f, 0.02f);
        // Draw vertical parts of gate (right)
        glTranslatef(45.0f ,0.0f, -45.0f);
        glRotatef(90,-1.0f,0.0f,0.0f);
        glutSolidCylinder(0.3,7,20,20);
        for(int i=0; i<13; i++){
            glTranslatef(0.0f ,-5.0f, 0.0f);
            glutSolidCylinder(0.3,7,20,20);
        }
    glPopMatrix();
    glPushMatrix();
        glColor3f(0.39f, 0.24f, 0.02f);
        // Draw vertical parts of gate(front right)
        glTranslatef(45.0f ,0.0f, 23.0f);
        glRotatef(90,-1.0f,0.0f,0.0f);
        glutSolidCylinder(0.3,7,20,20);
        glTranslatef(-7.0f ,0.0f, 0.0f);
        glutSolidCylinder(0.3,7,20,20);
        glTranslatef(-7.0f ,0.0f, 0.0f);
        glutSolidCylinder(0.3,7,20,20);
        glTranslatef(-7.0f ,0.0f, 0.0f);
        glutSolidCylinder(0.3,7,20,20);
        glTranslatef(-7.0f ,0.0f, 0.0f);
        glutSolidCylinder(0.3,7,20,20);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.39f, 0.24f, 0.02f);
        // Draw vertical parts of gate (front left)
        glTranslatef(-38.0f ,0.0f, 23.0f);
        glRotatef(90,-1.0f,0.0f,0.0f);
        glutSolidCylinder(0.3,7,20,20);
        glTranslatef(7.0f ,0.0f, 0.0f);
        glutSolidCylinder(0.3,7,20,20);
        glTranslatef(7.0f ,0.0f, 0.0f);
        glutSolidCylinder(0.3,7,20,20);
        glTranslatef(7.0f ,0.0f, 0.0f);
        glutSolidCylinder(0.3,7,20,20);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.39f, 0.24f, 0.02f);
        // Draw vertical parts of gate(left)
        glTranslatef(-45.0f ,0.0f, 23.0f);
        glRotatef(90,-1.0f,0.0f,0.0f);
        glutSolidCylinder(0.3,7,20,20);
        for(int i=0; i<13; i++){
            glTranslatef(0.0f ,5.0f, 0.0f);
        glutSolidCylinder(0.3,7,20,20);
        }
    glPopMatrix();
}

void drawRoad(){
    glPushMatrix();
    glBegin(GL_QUADS);
glColor3f(0.13f, 0.12f, 0.11f);
glVertex3f(-4.0f, 0.1f, -10.0f);
glVertex3f(2.0f, 0.1f, -10.0f);
glVertex3f(2.0f, 0.1f, 25.0f);
glVertex3f(-4.0f, 0.1f, 25.0f);
    glEnd();
    glPopMatrix();


}

void drawMainRoad(){
    glPushMatrix();
        glTranslatef(-50,0.1,28 );
        glColor3f(1,1,1);

        glBegin(GL_QUADS);

        glTexCoord2f(0,1);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glTexCoord2f(1,1);
        glVertex3f(0.0f, 0.0f, 14.0f);
        glTexCoord2f(1,0);
        glVertex3f(100.0f, 0.0f,14.0f);
        glTexCoord2f(0,0);
        glVertex3f(100.0f,0.00f, 0.0f);

        glEnd();

    glPopMatrix();
}
void drawRoadLines(){
    glPushMatrix();
        glTranslatef(-45,0.2,34.5 );


        glBegin(GL_QUADS);

        glColor3f(1,1,1);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 0.0f, 0.7f);
        glVertex3f(10.0f, 0.0f,0.7f);
        glVertex3f(10.0f,0.00f, 0.0f);

        glEnd();

        glTranslatef(18,0,0);

        glBegin(GL_QUADS);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 0.0f, 0.7f);
        glVertex3f(10.0f, 0.0f,0.7f);
        glVertex3f(10.0f,0.00f, 0.0f);
        glEnd();

        glTranslatef(18,0,0);
        //yellow middle line
        glBegin(GL_QUADS);
        glColor3f(0.99f, 1.0f, 0.0f);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 0.0f, 1.0f);
        glVertex3f(15.0f, 0.0f,1.0f);
        glVertex3f(15.0f,0.00f, 0.0f);
        glEnd();

        glTranslatef(0,0,3);
        //yellow front lines
        glBegin(GL_QUADS);
        glColor3f(0.99f, 1.0f, 0.0f);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 0.0f, 1.0f);
        glVertex3f(15.0f, 0.0f,1.0f);
        glVertex3f(15.0f,0.00f, 0.0f);
        glEnd();

        glTranslatef(0,0,3);
        //yellow front lines
        glBegin(GL_QUADS);
        glColor3f(0.99f, 1.0f, 0.0f);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 0.0f, 1.0f);
        glVertex3f(15.0f, 0.0f,1.0f);
        glVertex3f(15.0f,0.00f, 0.0f);
        glEnd();

        glTranslatef(0,0,-9);
        //yellow back lines
        glBegin(GL_QUADS);
        glColor3f(0.99f, 1.0f, 0.0f);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 0.0f, 1.0f);
        glVertex3f(15.0f, 0.0f,1.0f);
        glVertex3f(15.0f,0.00f, 0.0f);
        glEnd();

        glTranslatef(0,0,-3);
        //yellow back lines
        glBegin(GL_QUADS);
        glColor3f(0.99f, 1.0f, 0.0f);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 0.0f, 1.0f);
        glVertex3f(15.0f, 0.0f,1.0f);
        glVertex3f(15.0f,0.00f, 0.0f);
        glEnd();

        glTranslatef(23,0,6);

        glBegin(GL_QUADS);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 0.0f, 0.7f);
        glVertex3f(10.0f, 0.0f,0.7f);
        glVertex3f(10.0f,0.00f, 0.0f);
        glEnd();

        glTranslatef(18,0,0);

        glBegin(GL_QUADS);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 0.0f, 0.7f);
        glVertex3f(10.0f, 0.0f,0.7f);
        glVertex3f(10.0f,0.00f, 0.0f);
        glEnd();

    glPopMatrix();
}

void drawGrass(){
        glPushMatrix();
    glTranslatef(-50,0.1,42.0 );

     glBegin(GL_QUADS);

glTexCoord2f(0,1);
glVertex3f(0.0f, 0.0f, 0.0f);
glTexCoord2f(1,1);
glVertex3f(0.0f, 0.0f, 14.0f);
glTexCoord2f(1,0);
glVertex3f(100.0f, 0.0f,14.0f);
glTexCoord2f(0,0);
glVertex3f(100.0f,0.00f, 0.0f);

glEnd();


    glPopMatrix();
}

void drawSeeSaw(){

    glBegin(GL_QUADS);

    glColor3f(1.0f, 0.5f, 0.0f);

    glVertex3f(2.0f, 1.0f, 10.0f);
    glVertex3f(2.0f, 1.0f, 11.0f);
    glVertex3f(10.0f, 4.0f, 11.0f);
    glVertex3f(10.0f, 4.0f, 10.0f);

    glVertex3f(2.0f, 0.7f, 10.0f);
    glVertex3f(2.0f, 0.7f, 11.0f);
    glVertex3f(10.0f, 3.7f, 11.0f);
    glVertex3f(10.0f, 3.7f, 10.0f);

    glVertex3f(2.0f, 1.0f, 10.0f);
    glVertex3f(2.0f, 0.7f, 10.0f);
    glVertex3f(2.0f, 0.7f, 11.0f);
    glVertex3f(2.0f, 1.0f, 11.0f);

    glVertex3f(10.0f, 4.0f, 10.0f);
    glVertex3f(10.0f, 3.7f, 10.0f);
    glVertex3f(10.0f, 3.7f, 11.0f);
    glVertex3f(10.0f, 4.0f, 11.0f);


    glVertex3f(2.0f, 1.0f, 11.0f);
    glVertex3f(2.0f, 0.7f, 11.0f);
    glVertex3f(10.0f, 4.7f, 11.0f);
    glVertex3f(10.0f, 4.0f, 10.0f);


    glVertex3f(2.0f, 1.0f, 10.0f);
    glVertex3f(2.0f, 0.7f, 10.0f);
    glVertex3f(10.0f, 4.0f, 10.0f);
    glVertex3f(10.0f, 4.0f, 10.0f);

    glEnd();

    glTranslatef(6,0,10);
    glRotatef(-87,1,0,0);
    glutSolidCylinder(0.2,2.5,50,50);
    glRotatef(87,1,0,0);
    glTranslatef(0.6,0,0);
    glRotatef(-87,1,1,0);
    glutSolidCylinder(0.2,2.5,50,50);

}

void drawTubeSlide(){

//        glPushMatrix();
//            glTranslatef(-15,2,-15);
//           // glRotatef(90,1,0,0);
//            for(GLfloat i =0, j =0; i<10; i +=0.01, j+= 0.01){
//            glColor3f(0.3,0,0);
//            glRotatef(i, 0, 1, 0);
//            glTranslatef(j,0.01, 0.2);
//            glRotatef(90, 0, 1, 0);
//            glutSolidTorus(0.2,1.5,50,50);
//            }
//   // }
//    glPopMatrix();


    glPushMatrix();
            glTranslatef(-7,2,7);
            glPushMatrix();
            glRotatef(18,0,0,1);
            for(GLfloat i =0, j=0 ; i<2; i +=0.05, j+= 0.01){
                glColor3f(0.3,0,0);
                glRotatef(i, 0, 1, 0);
                glTranslatef(j,0.1, 0.2);
                glutSolidTorus(0.2,1.5,50,50);
            }

            glRotatef(70,1,0,0);
            glTranslatef(1.3,0,0);
            glutSolidCylinder(0.1,12,50,50);
            glTranslatef(-2.6,0,0);
            glutSolidCylinder(0.1,12,50,50);

            glPopMatrix();

    glPopMatrix();

}
void drawSteps(){
    glPushMatrix();
        glBegin(GL_QUADS);
            glColor3f(0,0,1);
            glVertex3f(23,8,8);
            glVertex3f(21.5,8,12.0);
            glVertex3f(22.7,8,12.0);
            glVertex3f(24,8,8);

            glVertex3f(24.5,6,8.0);
            glVertex3f(23,6,12.0);
            glVertex3f(24,6,12);
            glVertex3f(25.3,6,8);

            glVertex3f(25.7,4,8.0);
            glVertex3f(24.2,4,12.0);
            glVertex3f(25.2,4,12);
            glVertex3f(26.5,4,8);

            glVertex3f(26.9,2.5,8.0);
            glVertex3f(25.2,2.5,12.0);
            glVertex3f(26.2,2.5,12);
            glVertex3f(27.9,2.5,8);


            glVertex3f(27.9,0.7,8.0);
            glVertex3f(26.2,0.7,12.0);
            glVertex3f(27.2,0.7,12);
            glVertex3f(28.9,0.7,8);

        glEnd();
    glPopMatrix();
}
void drawChair(){
    glPushMatrix();
        glBegin(GL_QUADS);
            glColor3f(0,0,0);
            glVertex3f(0,3,0.0);
            glVertex3f(0,3,1.0);
            glVertex3f(1.5,3,1.0);
            glVertex3f(1.5,3,0);

            glColor3f(1,0,0);
            glVertex3f(0,3,0.0);
            glVertex3f(-0.5,6,0.0);
            glVertex3f(-0.5,6,1.0);
            glVertex3f(0,3,1.0);

            //legs
            glColor3f(0,0,0);
            glVertex3f(0,3,1.0);
            glVertex3f(0,0.2,1.0);
            glVertex3f(0.1,0.2,1.0);
            glVertex3f(0.1,3,1.0);

            glVertex3f(0.9,3,1.0);
            glVertex3f(0.9,0.2,1.0);
            glVertex3f(1,0.2,1.0);
            glVertex3f(1,3,1.0);

            glVertex3f(0.9,3,0.0);
            glVertex3f(0.9,0.2,0.0);
            glVertex3f(1,0.2,0.0);
            glVertex3f(1,3,0.0);

            glVertex3f(0,3,0.0);
            glVertex3f(0,0.2,0.0);
            glVertex3f(0.1,0.2,0.0);
            glVertex3f(0.1,3,0.0);
        glEnd();
    glPopMatrix();

}

void drawMerryGoRound(){

    glRotatef( 90, 1.0f, 0.0f, 0.0f );
    glutSolidTorus(0.4,4,50,50);
    glutSolidTorus(0.3,3,50,50);
    glTranslatef(-4,0.0,0 );
    glRotatef( 90, 0.0f, 1.0f, 0.0f );
    glutSolidCylinder(0.2,8,50,50);
    glRotatef(-90,0,1,0);
    glTranslatef(4,-4,0 );
    glRotatef(90,0,1,0);
    glRotatef(-90,1,0,0);
    glutSolidCylinder(0.2,8,50,50);

}

void drawMerryGoRoundStand1(){

    glPushMatrix();
    glTranslatef(-17,0,0 );
    glRotatef(-90,1,0,0);
    glutSolidCylinder(0.2,3.0,50,50);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-16,2,0 );
    glRotatef(-90,1,0,0);
    glutSolidCylinder(1,0.5,50,50);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-15,0,0 );
    glRotatef(-90,1,0,0);
    glutSolidCylinder(0.2,3.0,50,50);
    glPopMatrix();
}

void drawCanteen(){
    glPushMatrix();
    glTranslatef(-15,0,-20 );


    glBegin(GL_QUADS);

    //back wall
    glColor3f(0.35f, 0.24f, 0.05f);
    glVertex3f(0.0f, 19.8f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(30.0f, 0.0f, 0.0f);
    glVertex3f(30.0f, 19.8f, 0.0f);


    //front wall
    glColor3f(0.8f, 0.65f, 0.44f);
    glVertex3f(0.0f, 13.0f, 10.0f);
    glVertex3f(0.0f, 8.0f, 10.0f);
    glVertex3f(30.0f, 8.0f, 10.0f);
    glVertex3f(30.0f, 13.0f, 10.0f);

    glVertex3f(0.0f, 8.0f, 10.0f);
    glVertex3f(0.0f, 0.0f, 10.0f);
    glVertex3f(10.0f, 0.0f, 10.0f);
    glVertex3f(10.0f,8.0f, 10.0f);

    glVertex3f(17.0f, 8.0f, 10.0f);
    glVertex3f(17.0f, 0.0f, 10.0f);
    glVertex3f(30.0f, 0.0f, 10.0f);
    glVertex3f(30.0f,8.0f, 10.0f);

    //left wall
    glVertex3f(0.0f, 20.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 10.0f);
    glVertex3f(0.0f,13.0f, 10.0f);

    //right wall
    glVertex3f(30.0f, 20.0f, 0.0f);
    glVertex3f(30.0f, 13.0f, 10.0f);
    glVertex3f(30.0f, 0.0f, 10.0f);
    glVertex3f(30.0f,0.0f, 0.0f);

    //floor
    glColor3f(0.51f, 0.46f, 0.38f);
    glVertex3f(0.0f, 0.01f, 0.0f);
    glVertex3f(0.0f, 0.01f, 10.0f);
    glVertex3f(30.0f, 0.01f, 10.0f);
    glVertex3f(30.0f,0.01f, 0.0f);

    //welcomeboard
    glColor3f(0.9f, 0.84f, 0.75f);
    glVertex3f(9.99f, 10.00f, 10.01f);
    glVertex3f(9.99f, 8.01f, 10.01f);
    glVertex3f(17.01f, 8.01f, 10.01f);
    glVertex3f(17.01f,10.00f, 10.01f);

    //canteenboard
    glColor3f(0.9f, 0.84f, 0.75f);
    glVertex3f(17.8f, 12.00f, 10.01f);
    glVertex3f(17.8f, 10.01f, 10.01f);
    glVertex3f(24.0f, 10.01f, 10.01f);
    glVertex3f(24.0f,12.00f, 10.01f);

    //table left
    glColor3f(0.51f, 0.15f, 0.57f);
    glVertex3f(6.0f, 5.9f, 0.01f);
    glVertex3f(6.0f, 5.9f, 3.0f);
    glVertex3f(6.0f, 0.4f,3.0f);
    glVertex3f(6.0f,0.40f, 0.01f);
    //table right
    glColor3f(0.51f, 0.15f, 0.57f);
    glVertex3f(20.0f, 5.9f, 0.01f);
    glVertex3f(20.0f, 5.9f, 3.0f);
    glVertex3f(20.0f, 0.4f,3.0f);
    glVertex3f(20.0f,0.40f, 0.01f);
    //table front
    glColor3f(0.48f, 0.17f, 0.54f);
    glVertex3f(6.0f, 5.9f, 3.0f);
    glVertex3f(6.0f, 0.4f,3.0f);
    glVertex3f(20.0f, 0.4f,3.0f);
    glVertex3f(20.0f, 5.9f, 3.0f);

    glEnd();

    glPushMatrix();

        glTranslatef(23.0f, 10.7f, 10.03f);

            for(int l=0, lenghOfQuote = 0;l<numberOfQuotes;l++)
            {
                lenghOfQuote = (int)strlen(message[l]);

                glPushMatrix();
                    glScalef(1/152.38, 1/152.38, 1/152.38);
                    glTranslatef(-(lenghOfQuote*37),-(l*200), 5);//if translation is not done, all the lines will be drawn on top  of each other
                    for (i = 0; i < lenghOfQuote; i++)
                    {
                        glColor3f(0.0,0.0,0.0);
                        glutStrokeCharacter(GLUT_STROKE_ROMAN, message2[l][i]);//or we can use GLUT_STROKE_MONO_ROMAN which is somewhat thinner//or get libraries for other fonts
                    }
                glPopMatrix();
            }

    glPopMatrix();

    glPushMatrix();

        glTranslatef(14.8f, 8.8f, 10.03f);

        for(int l=0, lenghOfQuote = 0;l<numberOfQuotes;l++)
        {
            lenghOfQuote = (int)strlen(message[l]);
            glPushMatrix();
                glScalef(1/152.38, 1/152.38, 1/152.38);
                glTranslatef(-(lenghOfQuote*37),-(l*200), 5);//if translation is not done, all the lines will be drawn on top  of each other
                for (i = 0; i < lenghOfQuote; i++)
                {
                    glColor3f(1.0,0.0,0.0);
                    glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, message3[l][i]);//or we can use GLUT_STROKE_MONO_ROMAN which is somewhat thinner//or get libraries for other fonts
                }
            glPopMatrix();
        }

    glPopMatrix();

//bar-table
//top-stuff
//teapot
    glPushMatrix();
        glTranslatef(17,6.8,1.7);
        glColor3f(0.33f, 0.15f, 0.11f);
        glutSolidTeapot(1.0);
    glPopMatrix();



//teapot
    glPushMatrix();
        glTranslatef(7.0,4.2,6.0);
        glColor3f(0.33f, 0.15f, 0.11f);
        glRotatef(90,1.0,0.0,0.0);
        glutSolidTorus(0.03,1,100,100);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(7.0,4.25,6.0);
        glColor3f(0.6f, 0.76f, 0.7f);
        glRotatef(90,1.0,0.0,0.0);
        glutSolidCylinder(0.97,0.2,100,100);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(7.0,4.41,5.5);
        glColor3f(0.43f, 0.09f, 0.14f);
        glutSolidTeapot(0.5);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(6.5,4.41,6.3);
        glColor3f(0.43f, 0.09f, 0.14f);
        glutSolidTeacup(0.5);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(7.4,4.41,6.3);
        glColor3f(0.43f, 0.09f, 0.14f);
        glutSolidTeacup(0.5);
    glPopMatrix();
//glPopMatrix();

glBegin(GL_LINE_LOOP);
glColor3f(0,0,0);
glVertex3f(17.8f, 12.00f, 10.02f);
glVertex3f(17.8f, 10.01f, 10.02f);
glVertex3f(24.0f, 10.01f, 10.02f);
glVertex3f(24.0f,12.00f, 10.02f);
glEnd();

glBegin(GL_LINE_LOOP);
glColor3f(0,0,1);
    glVertex3f(9.99f, 10.00f, 10.02f);
glVertex3f(9.99f, 8.01f, 10.02f);
glVertex3f(17.01f, 8.01f, 10.02f);
glVertex3f(17.01f,10.00f, 10.02f);
glEnd();
    glPopMatrix();


}

void drawTable(){
    glPushMatrix();
        glColor3f(0.54f, 0.35f, 0.05f);
        glBegin(GL_POLYGON);
        glVertex3f(4.0f, 4.00f, 6.0f);
        glVertex3f(6.0f, 4.0f, 8.0f);
        glVertex3f(8.0f, 4.0f, 8.0f);
        glVertex3f(10.0f,4.00f, 6.0f);
        glVertex3f(8.0f, 4.00f, 4.0f);
        glVertex3f(6.0f,4.00f, 4.0f);
        glEnd();
    glPopMatrix();
    //legs
    glColor3f(0.6f, 0.28f, 0.11f);
    glPushMatrix();
        glTranslatef(6,0.2,5);
        glRotatef(-90,1,0,0);
        glutSolidCylinder(0.1,3.79,50,50);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(8,0.2,5);
        glRotatef(-90,1,0,0);
        glutSolidCylinder(0.1,3.79,50,50);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(6,0.2,7);
        glRotatef(-90,1,0,0);
        glutSolidCylinder(0.1,3.79,50,50);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(8,0.2,7);
        glRotatef(-90,1,0,0);
        glutSolidCylinder(0.1,3.79,50,50);
    glPopMatrix();

}

void drawBarTableTop(){
    glPushMatrix();
    glTranslatef(-15,0,-20 );


     glBegin(GL_QUADS);

//bar-table
//top
//glColor3f(0.38f, 0.03f, 0.45f);
glTexCoord2f(0,1);
glVertex3f(6.0f, 6.0f, 1.0f);
glTexCoord2f(1,1);
glVertex3f(6.0f, 6.0f, 3.0f);
glTexCoord2f(1,0);
glVertex3f(20.0f, 6.0f,3.0f);
glTexCoord2f(0,0);
glVertex3f(20.0f,6.00f, 1.01f);

glEnd();


    glPopMatrix();

}

void drawRoof(){
    glPushMatrix();
    glTranslatef(-15,0,-20 );
    glColor3f(1,1,1);

     glBegin(GL_QUADS);

  glTexCoord2f(0,1);
glVertex3f(-1.0f, 20.1f, -1.0f);
glTexCoord2f(1,1 );
glVertex3f(-1.0f, 13.1f, 11.0f);
 glTexCoord2f(1,0 );
glVertex3f(31.0f, 13.1f, 11.0f);
glTexCoord2f(0,0);
glVertex3f(31.0f,20.1f, -1.0f);


glEnd();
    glPopMatrix();

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void display() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
        // camera orientation (eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ)
        gluLookAt(0.0 + camX, 7.0 + camY, 52.0 + camZ, 0, 0, 0, 0, 1.0, 0);

        // move the object frame using keyboard keys
        glTranslatef(moveX, moveY, moveZ );
        glRotatef( rotX, 1.0f, 0.0f, 0.0f );
        glRotatef( rotY, 0.0f, 1.0f, 0.0f );
        glRotatef( rotZ, 0.0f, 0.0f, 1.0f );

        glPushMatrix();

            glPushMatrix();
                glEnable( GL_TEXTURE_2D );
                glBindTexture( GL_TEXTURE_2D, tex );
                drawFloor();
                glDisable(GL_TEXTURE_2D);
            glPopMatrix();

            drawGate();
            drawRoad();

            glPushMatrix();
                glColor3f(0.0f, 0.0f, 1.0f);
                glTranslatef(15.0f ,1.0f, 0.0f);
                glRotatef(30,0,1,0);
                drawTubeSlide();

            glPopMatrix();
            drawSteps();

            drawBoundary();

            //drawTubeSlide();

            glPushMatrix();
                glEnable( GL_TEXTURE_2D );
                glBindTexture( GL_TEXTURE_2D, tex2 );
                drawRoof();
                glDisable(GL_TEXTURE_2D);
            glPopMatrix();

            glEnable( GL_TEXTURE_2D );
            glBindTexture( GL_TEXTURE_2D, tex3 );
            drawBarTableTop();
            glDisable(GL_TEXTURE_2D);

            drawCanteen();

            glPushMatrix();
                glTranslatef(-15,-0.1,-20 );
                drawTable();
            glPopMatrix();

            glPushMatrix();
                glTranslatef(-11,-0.1,-14 );
                drawChair();
            glPopMatrix();

            glPushMatrix();
                glTranslatef(-4,-0.1,-12 );
                glRotatef(170,0,1,0);
                drawChair();
            glPopMatrix();

            glPushMatrix();
                glTranslatef(2,-0.1,-20 );
                drawTable();
            glPopMatrix();

            glPushMatrix();
                glTranslatef(5,-0.1,-14 );
                drawChair();
            glPopMatrix();

            glPushMatrix();
                glTranslatef(12,-0.1,-14 );
                glRotatef(190,0,1,0);
                drawChair();
            glPopMatrix();

            glPushMatrix();
                glTranslatef(8.5,-0.1,-11 );
                glRotatef(90,0,1,0);
                drawChair();
            glPopMatrix();

            glEnable( GL_TEXTURE_2D );
            glBindTexture( GL_TEXTURE_2D, tex4 );
            drawMainRoad();
            glDisable(GL_TEXTURE_2D);
            drawRoadLines();

            glEnable( GL_TEXTURE_2D );
            glBindTexture( GL_TEXTURE_2D, tex5 );
            drawGrass();
            glDisable(GL_TEXTURE_2D);

            glPushMatrix();
                glTranslatef(-16, 0, 0);
                glRotatef(animateRotation, 0.0, 1.0, 0.0);
                glTranslatef(16,0,0);
                glColor3f(0.31f, 0.05f, 0.33f);
                glPushMatrix();
                    glTranslatef(-16,3,0 );
                    drawMerryGoRound();
                glPopMatrix();
            glPopMatrix();

            drawMerryGoRoundStand1();

            glPushMatrix();
                glTranslatef(-30,0.3,-2);
                drawSeeSaw();
            glPopMatrix();

            glPushMatrix();
                glTranslatef(25,0.3,-30);
                drawSeeSaw();
            glPopMatrix();

            glPushMatrix();
                glTranslatef(22,0.3,12);
                drawTable();
            glPopMatrix();

            glPushMatrix();
                glTranslatef(25,0.3,17);
                drawChair();
            glPopMatrix();

            glPushMatrix();
                glTranslatef(33,0.3,17);
                glRotatef(180,0,1,0);
                drawChair();
            glPopMatrix();

            glPushMatrix();
                glTranslatef(33,0.3,20);
                glRotatef(160,0,1,0);
                drawChair();
            glPopMatrix();

            glPushMatrix();
                glTranslatef(-35,0,0);
                glCallList(drawATree);
            glPopMatrix();

            glPushMatrix();
                glTranslatef(-35,0,-24);
                glRotatef(30,0,1,0);
                glCallList(drawATree);
            glPopMatrix();

             glPushMatrix();
                glTranslatef(35,0,-24);
                glRotatef(-30,0,1,0);
                glCallList(drawATree);
            glPopMatrix();

            glPushMatrix();
                glTranslatef(20,0,-40);
                glRotatef(-30,0,1,0);
                glCallList(drawATree);
            glPopMatrix();

            glPushMatrix();
                glTranslatef(25,0,0);
                glRotatef(-50,0,1,0);
                glCallList(drawATree);
            glPopMatrix();

            glPushMatrix();
                glTranslatef(45,0,24);
                glRotatef(-50,0,1,0);
                glCallList(drawATree);
            glPopMatrix();

             glPushMatrix();
                glTranslatef(-45,0,24);
                glRotatef(-30,0,1,0);
                glCallList(drawATree);
            glPopMatrix();

            glPushMatrix();
                glTranslatef(-40,0,46);
                glRotatef(-30,0,1,0);
                glCallList(drawATree);
            glPopMatrix();

            glPushMatrix();
                glTranslatef(-10,0,48);
                glRotatef(-20,0,1,0);
                glCallList(drawATree);
            glPopMatrix();

            glPushMatrix();
                glTranslatef(10,0,46);
                glRotatef(-80,0,1,0);
                glCallList(drawATree);
            glPopMatrix();

            glPushMatrix();
                glTranslatef(30,0,48);
                glRotatef(-35,0,1,0);
                glCallList(drawATree);
            glPopMatrix();

        glPopMatrix();

        drawBalloonMan();
    glPopMatrix();


    glutSwapBuffers();

}
//handlers
//void handler_func(int x, int y){
//    if(MOUSEEVENTF_MOVE){
//
//    }
//
//}

void keyboardSpecial(int key, int x, int y){
    if(key == GLUT_KEY_UP)
        moveZ += 1;

    if(key == GLUT_KEY_DOWN)
        moveZ -= 1;

    if(key == GLUT_KEY_LEFT)
        rotY += 5.0;

    if(key == GLUT_KEY_RIGHT)
        rotY -= 5.0;

    glutPostRedisplay();


}

void keyboard(unsigned char key , int x , int y){
    if(key == 'w')
        camY += 0.5;
    if(key == 's')
        camY -= 0.5;

    if(key == 'c')
        glPolygonMode(GL_BACK, GL_LINE);
        // glPolygonMode(GL_FRONT, GL_FILL);
    if(key == 'C')
        glPolygonMode(GL_BACK, GL_FILL);

    if(key == 'k')
        glDisable(GL_LIGHT0);
    if(key == 'K')
        glEnable(GL_LIGHT0);

    if(key == 'l')
        glDisable(GL_LIGHT1);
    if(key == 'L')
        glEnable(GL_LIGHT1);

    glutPostRedisplay();

}

void changeSize(GLsizei w, GLsizei h){
	glViewport(0, 0, w, h);
    GLfloat aspect_ratio = h == 0 ? w/1 : (GLfloat)w/(GLfloat)h;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    //Define the Perspective projection frustum
    // (FOV_in_vertical, aspect_ratio, z-distance to the near plane from the camera position, z-distance to far plane from the camera position)
    gluPerspective(120.0, aspect_ratio, 1.0, 100.0);

                // if(w <= h)
                //     glOrtho(-20.0, 20.0, -20/aspect_ratio, 20/aspect_ratio, 20.0, -20.0);

                // else
                //     glOrtho(-20.0* aspect_ratio, 20.0* aspect_ratio, -20.0, 20.0, 20.0, -20.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv) {

    strcpy(message[0],"Children's Park");
    strcpy(message[1],"Kandy");

    strcpy(message2[0],"Canteen");
    strcpy(message3[0],"WELCOME!");
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE| GLUT_DEPTH | GLUT_RGBA);

    glutCreateWindow("OpenGL Setup Test");
    glutInitWindowSize(1000, 1000);
    glutInitWindowPosition(0, 0);
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(changeSize);
    // keyboard function activation
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(keyboardSpecial);

    glutTimerFunc(60.0, Timer, 1);
    glutMainLoop();


    return 0;
}
