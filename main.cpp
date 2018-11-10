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
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//lighting
//Function to initialize the lighting properties. you can add upto 8 lights in openGL (0-7)
void initLighting(){

//    //Decalring the Ambient, Diffuse components of the LIght_0 and the position in the eye coordinate system
//   GLfloat L0_Ambient[] = {1.0, 1.0, 1.0, 1.0};
//    //GLfloat L0_Diffuse[] = {1.0, 1.0, 1.0, 1.0};
//    //GLfloat L0_Specular[] = {1.0, 1.0, 1.0, 1.0};
//    GLfloat L0_postion[] = {5, 5, 0, 1.0};
//
//    glLightfv(GL_LIGHT0, GL_AMBIENT, L0_Ambient);
//   // glLightfv(GL_LIGHT0, GL_DIFFUSE, L0_Diffuse);
//   // glLightfv(GL_LIGHT0, GL_SPECULAR, L0_Specular);
//    glLightfv(GL_LIGHT0, GL_POSITION, L0_postion);

GLfloat L0_Ambient[] = {0.8, 0.8, 0.8, 1.0};
    GLfloat L0_Diffuse[] = {0.7, 0.7, 0.7, 1.0};
    GLfloat L0_postion[] = {0, 100, 0, 1.0};

    glLightfv(GL_LIGHT0, GL_AMBIENT, L0_Ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, L0_Diffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, L0_postion);

    GLfloat L1_Ambient[] = {0.5, 0.5, 0.5, 1.0};
    GLfloat L1_Diffuse[] = {0.7, 0.7, 0.7, 1.0};
    GLfloat L1_Specular[] = {0.0, 1.0, 0.0, 1.0};   //Declaration of the specular component of the light_1
    GLfloat L1_postion[] = {14.9, 15, -17, 1.0};

    glLightfv(GL_LIGHT1, GL_AMBIENT, L1_Ambient);
    //glLightfv(GL_LIGHT1, GL_EMISSION, L1_Diffuse);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, L1_Diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, L1_Specular);
    glLightfv(GL_LIGHT1, GL_POSITION, L1_postion);


    //Declaration of the light reflecting properties for the materials
    GLfloat specularReflectance[] = {1.0, 1.0, 1.0, 1.0};
    glMaterialfv(GL_FRONT, GL_SPECULAR, specularReflectance);
    glMateriali(GL_FRONT, GL_SHININESS, 50);


}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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


    unsigned char data[] =
    {
        128, 128, 128, 255,
        255, 0, 0, 255,
        0, 255, 0, 255,
        0, 0, 255, 255
    };



    glGenTextures( 1, &tex2 );
    glBindTexture( GL_TEXTURE_2D, tex2 );


    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
              GL_UNSIGNED_BYTE, image2);

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


    unsigned char data[] =
    {
        128, 128, 128, 255,
        255, 0, 0, 255,
        0, 255, 0, 255,
        0, 0, 255, 255
    };



    glGenTextures( 1, &tex3 );
    glBindTexture( GL_TEXTURE_2D, tex3 );


    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
              GL_UNSIGNED_BYTE, image3);

    // Use the following line in order to load the created texture map instead of the image
    // glTexImage2D( GL_TEXTURE_2D, 0,GL_RGBA, 2, 2, 0, GL_RGBA, GL_UNSIGNED_BYTE, data );

}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Timer(int x){
    animateRotation += animateRotation >= 360.0? -animateRotation : 5;
    glutPostRedisplay();

    glutTimerFunc(60, Timer, 1);
}


void init(){
    glClearColor(0.5f, 0.5f, 1.0f, 1.0f);
     GLfloat globalAmbient[] = {0.8, 0.8, 0.8, 1.0};
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);

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
    glEnable(GL_LIGHT1);
    // glEnable(GL_LIGHT2);

    // enable the normalization of the normal vectors (converting the vector values to the range 0-1)
    glEnable(GL_NORMALIZE);
    qobj = gluNewQuadric();
    gluQuadricDrawStyle(qobj, GLU_FILL);
    gluQuadricNormals(qobj, GLU_SMOOTH);

    initTexture();
    initTexture2();
    initTexture3();

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

void drawFloor(){

    glBegin(GL_QUADS);
                   glColor4f(0, 1, 0, 1);
//                        glNormal3d(1, 0, 0);
//                        glTexCoord2f(1/8,1/8);
//                        glVertex3f(25,0, 25);
//                        glTexCoord2f(1-1/8,1/8 );
//                        glVertex3f(-25,0, 25);
//                        glTexCoord2f(1-1/8,1-1/8 );
//                        glVertex3f(-25,0, -25);
//                        glTexCoord2f(1/8,1-1/8);
//                        glVertex3f(25,0, -25);

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


//////////////////////////////////////////////////////////////////////////////////////
//balloon

void drawSnowMan() {


 glColor3f(1.0f, 1.0f, 1.0f);

// Draw Body
 glTranslatef(0.0f ,0.75f, 0.0f);
 glutSolidSphere(0.75f,20,20);


// Draw Head
 glTranslatef(0.0f, 1.0f, 0.0f);
 glutSolidSphere(0.25f,20,20);

// Draw Eyes
 glPushMatrix();
 glColor3f(0.0f,0.0f,0.0f);
 glTranslatef(0.05f, 0.10f, 0.18f);
 glutSolidSphere(0.05f,10,10);
 glTranslatef(-0.1f, 0.0f, 0.0f);
 glutSolidSphere(0.05f,10,10);
 glPopMatrix();

// Draw Nose
 glColor3f(1.0f, 0.5f , 0.5f);
 glRotatef(0.0f,1.0f, 0.0f, 0.0f);
 glutSolidCone(0.08f,0.5f,10,2);
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void drawGate() {

glPushMatrix();
 glColor3f(0.39f, 0.24f, 0.02f);
// Draw left horizontal cylinders
 glTranslatef(-23.0f ,2.0f, 23.0f);
 glRotatef(90,0.0f ,1.0f, 0.0f);
 glutSolidCylinder(0.3,16,20,20);
 glTranslatef(0.0f ,1.0f, 0.0f);
 glutSolidCylinder(0.3,16,20,20);
 glTranslatef(0.0f ,1.0f, 0.0f);
 glutSolidCylinder(0.3,16,20,20);
 glTranslatef(0.0f ,1.0f, 0.0f);
 glutSolidCylinder(0.3,16,20,20);
glPopMatrix();

glPushMatrix();
 glColor3f(0.39f, 0.24f, 0.02f);
// Draw right horizontal cylinders
 glTranslatef(5.0f ,2.0f, 23.0f);
 glRotatef(90,0.0f ,1.0f, 0.0f);
 glutSolidCylinder(0.3,18,20,20);
 glTranslatef(0.0f ,1.0f, 0.0f);
 glutSolidCylinder(0.3,18,20,20);
 glTranslatef(0.0f ,1.0f, 0.0f);
 glutSolidCylinder(0.3,18,20,20);
 glTranslatef(0.0f ,1.0f, 0.0f);
 glutSolidCylinder(0.3,18,20,20);
glPopMatrix();



// Draw Nameboard
 glPushMatrix();
 glColor3f(0.52f, 0.32f, 0.02f);
 glTranslatef(5.0f, 0.0f, 23.0f);
 glRotatef(90,-1.0f,0.0f,0.0f);
 glutSolidCylinder(0.4,14,50,50);
// glutSolidSphere(0.05f,10,10);
// glTranslatef(-0.1f, 0.0f, 0.0f);
// glutSolidSphere(0.05f,10,10);
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
// glutSolidSphere(0.05f,10,10);
// glTranslatef(-0.1f, 0.0f, 0.0f);
// glutSolidSphere(0.05f,10,10);
glPopMatrix();
 glPushMatrix();
glColor3f(0.52f, 0.32f, 0.02f);
 glTranslatef(5.0f, 11.0f, 23.0f);
 glRotatef(90,0.0f,-1.0f,0.0f);
 glutSolidCylinder(0.2,12,50,50);
// glutSolidSphere(0.05f,10,10);
// glTranslatef(-0.1f, 0.0f, 0.0f);
// glutSolidSphere(0.05f,10,10);
glPopMatrix();

//name
 glPushMatrix();
 glTranslatef(4.6f, 11.0f, 23.0f);
 glRotatef(180,0.0f,-1.0f,0.0f);

    glBegin(GL_QUADS);
                        glPolygonMode(GL_FRONT, GL_FILL);
                        glColor3f(.0f,1.0f,1.0f);
                        //glNormal3d(0, 0, 1);
                        glVertex3f(0,0, 0);
                        glColor3f(1.0f,1.0f,1.0f);
                        glVertex3f(12,0, 0);
                        glColor3f(1.0f,1.0f,1.0f);
                        glVertex3f(12,3,0 );
                        glColor3f(1.0f,1.0f,1.0f);
                        glVertex3f(0,3, 0);
                glEnd();
// glutSolidSphere(0.05f,10,10);
// glTranslatef(-0.1f, 0.0f, 0.0f);
// glutSolidSphere(0.05f,10,10);
glPopMatrix();
 glPushMatrix();
           // glRotatef(animateRotation, 0.0, 1.0, 0.0);
            glTranslatef(0.0f, 13.0f, 23.0f);
           // glRotatef(180,0,1,0);

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
 glTranslatef(-23.0f ,2.0f, 23.0f);
 glRotatef(-180,0.0f ,1.0f, 0.0f);
 glutSolidCylinder(0.3,46,20,20);
 glTranslatef(0.0f ,1.0f, 0.0f);
 glutSolidCylinder(0.3,46,20,20);
 glTranslatef(0.0f ,1.0f, 0.0f);
 glutSolidCylinder(0.3,46,20,20);
 glTranslatef(0.0f ,1.0f, 0.0f);
 glutSolidCylinder(0.3,46,20,20);
glPopMatrix();

glPushMatrix();
 glColor3f(0.39f, 0.24f, 0.02f);
// Draw right horizontal cylinders
 glTranslatef(23.0f ,2.0f, 23.0f);
 glRotatef(180,0.0f ,1.0f, 0.0f);
 glutSolidCylinder(0.3,46,20,20);
 glTranslatef(0.0f ,1.0f, 0.0f);
 glutSolidCylinder(0.3,46,20,20);
 glTranslatef(0.0f ,1.0f, 0.0f);
 glutSolidCylinder(0.3,46,20,20);
 glTranslatef(0.0f ,1.0f, 0.0f);
 glutSolidCylinder(0.3,46,20,20);
glPopMatrix();

glPushMatrix();
 glColor3f(0.39f, 0.24f, 0.02f);
// Draw right horizontal cylinders
 glTranslatef(-23.0f ,2.0f, -23.0f);
 glRotatef(90,0.0f ,1.0f, 0.0f);
 glutSolidCylinder(0.3,46,20,20);
 glTranslatef(0.0f ,1.0f, 0.0f);
 glutSolidCylinder(0.3,46,20,20);
 glTranslatef(0.0f ,1.0f, 0.0f);
 glutSolidCylinder(0.3,46,20,20);
 glTranslatef(0.0f ,1.0f, 0.0f);
 glutSolidCylinder(0.3,46,20,20);
glPopMatrix();

glPushMatrix();
 glColor3f(0.39f, 0.24f, 0.02f);
// Draw vertical parts of gate
 glTranslatef(-23.0f ,0.0f, -23.0f);
glRotatef(90,-1.0f,0.0f,0.0f);
 glutSolidCylinder(0.3,7,20,20);
 for(int i=0; i<8; i++){
 glTranslatef(5.0f ,0.0f, 0.0f);
 glutSolidCylinder(0.3,7,20,20);
 }
glPopMatrix();

glPushMatrix();
 glColor3f(0.39f, 0.24f, 0.02f);
// Draw vertical parts of gate
 glTranslatef(23.0f ,0.0f, -23.0f);
glRotatef(90,-1.0f,0.0f,0.0f);
 glutSolidCylinder(0.3,7,20,20);
 for(int i=0; i<8; i++){
 glTranslatef(0.0f ,-5.0f, 0.0f);
 glutSolidCylinder(0.3,7,20,20);
 }
 glPopMatrix();
glPushMatrix();
 glColor3f(0.39f, 0.24f, 0.02f);
// Draw vertical parts of gate
 glTranslatef(23.0f ,0.0f, 23.0f);
glRotatef(90,-1.0f,0.0f,0.0f);
 glutSolidCylinder(0.3,7,20,20);
 glTranslatef(-5.0f ,0.0f, 0.0f);
 glutSolidCylinder(0.3,7,20,20);
 glTranslatef(-5.0f ,0.0f, 0.0f);
 glutSolidCylinder(0.3,7,20,20);
glPopMatrix();

glPushMatrix();
 glColor3f(0.39f, 0.24f, 0.02f);
// Draw vertical parts of gate
 glTranslatef(-18.0f ,0.0f, 23.0f);
glRotatef(90,-1.0f,0.0f,0.0f);
 glutSolidCylinder(0.3,7,20,20);
 glTranslatef(5.0f ,0.0f, 0.0f);
 glutSolidCylinder(0.3,7,20,20);
glPopMatrix();

glPushMatrix();
 glColor3f(0.39f, 0.24f, 0.02f);
// Draw vertical parts of gate
 glTranslatef(-23.0f ,0.0f, 23.0f);
glRotatef(90,-1.0f,0.0f,0.0f);
 glutSolidCylinder(0.3,7,20,20);
 for(int i=0; i<8; i++){
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

void drawSeeSaw(){
    glPushMatrix();
 glColor3f(1.0f, 0.5f, 0.8f);
// Draw right horizontal cylinders
 glTranslatef(5.0f ,0.0f, 0.0f);
 //glRotatef(90,1.0f ,0.0f, 0.0f);
 glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
                                  // Top face (y = 1.0f)
                                  // Define vertices in counter-clockwise (CCW) order with normal pointing out
glColor3f(1.0f, 0.5f, 0.0f);     // Green
glVertex3f(2.0f, 1.0f, 10.0f);
glVertex3f(2.0f, 1.0f, 11.0f);
glVertex3f(10.0f, 4.0f, 11.0f);
glVertex3f(10.0f, 4.0f, 10.0f);

// Bottom face (y = -1.0f)
glColor3f(1.0f, 0.5f, 0.0f);     // Orange
glVertex3f(2.0f, 0.7f, 10.0f);
glVertex3f(2.0f, 0.7f, 11.0f);
glVertex3f(10.0f, 3.7f, 11.0f);
glVertex3f(10.0f, 3.7f, 10.0f);

// Front face  (z = 1.0f)
glColor3f(1.0f, 0.5f, 0.0f);     // Red
glVertex3f(2.0f, 1.0f, 10.0f);
glVertex3f(2.0f, 0.7f, 10.0f);
glVertex3f(2.0f, 0.7f, 11.0f);
glVertex3f(2.0f, 1.0f, 11.0f);

// Back face (z = -1.0f)
glColor3f(1.0f, 0.5f, 0.0f);     // Yellow

glVertex3f(10.0f, 4.0f, 10.0f);
glVertex3f(10.0f, 3.7f, 10.0f);//glRotatef(90,-1.0f,0.0f,0.0f);
glVertex3f(10.0f, 3.7f, 11.0f);
glVertex3f(10.0f, 4.0f, 11.0f);

// Left face (x = -1.0f)
//glColor3f(0.0f, 0.0f, 1.0f);     // Blue
glVertex3f(2.0f, 1.0f, 11.0f);
glVertex3f(2.0f, 0.7f, 11.0f);
glVertex3f(10.0f, 4.7f, 11.0f);
glVertex3f(10.0f, 4.0f, 10.0f);

// Right face (x = 1.0f)
//glColor3f(1.0f, 0.0f, 1.0f);     // Magenta
glVertex3f(2.0f, 1.0f, 10.0f);
glVertex3f(2.0f, 0.7f, 10.0f);
glVertex3f(10.0f, 4.0f, 10.0f);
glVertex3f(10.0f, 4.0f, 10.0f);
glEnd();  // End of drawing color-cube

glTranslatef(6,0,10);
glRotatef(-87,1,0,0);
glutSolidCylinder(0.2,2.5,50,50);
glRotatef(87,1,0,0);
glTranslatef(0.6,0,0);
glRotatef(-87,1,1,0);
glutSolidCylinder(0.2,2.5,50,50);
glPopMatrix();





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
            glTranslatef(5,2,-5);
           // glRotatef(70,1,0,0);
            glRotatef(18,0,0,1);
            //glRotatef(180,1,0,0);
            for(GLfloat i =0, j =0; i<2; i +=0.05, j+= 0.01){
            glColor3f(0.3,0,0);
            glRotatef(i, 0, 1, 0);
            glTranslatef(j,0.1, 0.2);
            //glRotatef(90, 0, 1, 0);
            glutSolidTorus(0.2,1.5,50,50);
            }
   // }
    //glPopMatrix();
    //glPushMatrix();
       // glColor3f(0,0,1);
        //glTranslatef(7,6,3);
        //glutSolidDodecahedron();
    glPopMatrix();


}

void drawMerryGoRound(){


    glColor3f(0.31f, 0.05f, 0.33f);
    glPushMatrix();
    glTranslatef(-16,3,0 );
    glRotatef( 90, 1.0f, 0.0f, 0.0f );

    glutSolidTorus(0.4,4,50,50);
    glutSolidTorus(0.3,3,50,50);
    glTranslatef(-4,0.0,0 );
   glRotatef( 90, 0.0f, 1.0f, 0.0f );
    glutSolidCylinder(0.2,8,50,50);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-16,3,-4 );
    glutSolidCylinder(0.2,8,50,50);
    glPopMatrix();




}

void drawMerryGoRoundStand(){
    //stand
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
     glColor3f(0.35f, 0.24f, 0.05f);
//back wall
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

//left
glColor3f(0.51f, 0.15f, 0.57f);
glVertex3f(6.0f, 5.9f, 0.01f);
glVertex3f(6.0f, 5.9f, 3.0f);
glVertex3f(6.0f, 0.4f,3.0f);
glVertex3f(6.0f,0.40f, 0.01f);
//right
glColor3f(0.51f, 0.15f, 0.57f);
glVertex3f(20.0f, 5.9f, 0.01f);
glVertex3f(20.0f, 5.9f, 3.0f);
glVertex3f(20.0f, 0.4f,3.0f);
glVertex3f(20.0f,0.40f, 0.01f);
//front
glColor3f(0.48f, 0.17f, 0.54f);
glVertex3f(6.0f, 5.9f, 3.0f);
glVertex3f(6.0f, 0.4f,3.0f);
glVertex3f(20.0f, 0.4f,3.0f);
glVertex3f(20.0f, 5.9f, 3.0f);
glEnd();

 glPushMatrix();
           // glRotatef(animateRotation, 0.0, 1.0, 0.0);
            glTranslatef(23.0f, 10.7f, 10.03f);
           // glRotatef(180,0,1,0);

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
           // glRotatef(animateRotation, 0.0, 1.0, 0.0);
            glTranslatef(14.8f, 8.8f, 10.03f);
           // glRotatef(180,0,1,0);

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
//glTexCoord2f(0,1);
//glVertex3f(6.0f, 6.0f, 1.0f);
//glTexCoord2f(1,1);
//glVertex3f(6.0f, 6.0f, 3.0f);
//glTexCoord2f(1,0);
//glVertex3f(20.0f, 6.0f,3.0f);
//glTexCoord2f(0,0);
//glVertex3f(20.0f,6.00f, 1.01f);

//table1
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
glPopMatrix();

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
        gluLookAt(0.0 + camX, 7.0 + camY, 30.0 + camZ, 0, 0, 0, 0, 1.0, 0);

        // move the object frame using keyboard keys
        glTranslatef(moveX, moveY, moveZ );
        glRotatef( rotX, 1.0f, 0.0f, 0.0f );
        glRotatef( rotY, 0.0f, 1.0f, 0.0f );
        glRotatef( rotZ, 0.0f, 0.0f, 1.0f );

        glPushMatrix();
           // glRotatef(180, 0.0, 1.0, 0.0);
            //glTranslatef(0.0, 1.1, 0.0);

            //DrawGrid();
           // glColor3f(1.0, 1.0, 1.0);
            glPushMatrix();
            glEnable( GL_TEXTURE_2D );
            glBindTexture( GL_TEXTURE_2D, tex );
            drawFloor();
            glDisable(GL_TEXTURE_2D);
            glPopMatrix();

            //glColor3f(1,1,1);
            drawGate();
            drawRoad();
           // glColor3f(1,1,1);
            drawSeeSaw();
            drawBoundary();
            drawTubeSlide();

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



            // glPushMatrix();
           // glRotatef(animateRotation, 0.0, 1.0, 0.0);
            //glTranslatef(0.0, -0.5, 0.0);
            //glScalef(2,2,2);
          //  glMatrixMode(GL_MODLEVIEW);
glPushMatrix();
glTranslatef(-16, 0, 0);
glRotatef(animateRotation, 0.0, 1.0, 0.0);
glTranslatef(16,0,0);
 drawMerryGoRound();
glPopMatrix();
drawMerryGoRoundStand();


        glPopMatrix();

    drawSnowMan();
    glPopMatrix();
            glPushMatrix();
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
