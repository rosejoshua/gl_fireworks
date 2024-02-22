//---------------------------------------
// Program: fireworks.cpp; based on square.cpp
// Purpose: Demonstrate basic OpenGL commands
//          to draw simple fireworks.
// Author:  John Gauch, Joshua Rose
// Date:    February 2024
//---------------------------------------
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#ifdef MAC
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <vector>
#include <iostream>
using namespace std;

//---------------------------------------
// Global values
//---------------------------------------
const int MIN_NUM_FWORKS = 5;
const int MAX_NUM_FWORKS = 10;
const int NUM_LINES_FACTOR = 100;
const float MAX_ORIGIN = 0.8f;
const float RAD_MIN = 0.3f;
const float RAD_MAX = 0.55f;

//---------------------------------------
// Line struct
//---------------------------------------
struct linef {
   float x1;
   float y1;
   float z1;
   float x2;
   float y2;
   float z2;
};

//---------------------------------------
// Draw a firework using Fibonnaci Lattice
//---------------------------------------
void drawFirework(float originX, float originY, float originZ, int numLinesFactor, float radius)
{
   float red = (float) rand()/RAND_MAX;
   float green = (float) rand()/RAND_MAX;
   float blue = (float) rand()/RAND_MAX;
   float pi = 2 * acosf(0.0);
   int numLines = numLinesFactor + (int)(numLinesFactor*radius*2); //bigger radius = more lines
   vector<linef> lines; //store lines for a single firework

   //Fibonnaci Lattice code translated from c# version at https://medium.com/@vagnerseibert/distributing-points-on-a-sphere-6b593cc05b42
   //gives us mostly even spaced points on a sphere, used as endpoints from each firework origin
   for (int i = 0; i < numLines; i++)
   {
      float k = i + 0.5;
      float phi = acosf(1.0f - 2.0f * k / numLines);
      float theta = pi * (1 + sqrtf(5)) * k;
      float x = cosf(theta) * sinf(phi);
      float y = sinf(theta) * sinf(phi);
      float z = cosf(phi);
      linef l;
      l.x1 = 0.0 + originX;
      l.y1 = 0.0 + originY;
      l.z1 = 0.0 + originZ;
      l.x2 = x * radius + originX;
      l.y2 = y * radius + originY;
      l.z2 = z * radius + originZ;
      lines.push_back(l);
   }

   //tell OpenGL about each line
   for (int i = 0; i < lines.size(); i++)
   {
      linef l = lines.at(i);
      glBegin(GL_LINE_LOOP);
      glColor3f(red, green, blue);
      glVertex3f(l.x1, l.y1, l.z1);
      glVertex3f(l.x2, l.y2, l.z2);
      glEnd();
   }
}

//---------------------------------------
// Init function for OpenGL
//---------------------------------------
void init()
{
   glClearColor(0.0, 0.0, 0.0, 1.0);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
}

//---------------------------------------
// Display callback for OpenGL
//---------------------------------------
void display()
{
   int numFireworks = (float) (rand() % (MAX_NUM_FWORKS - MIN_NUM_FWORKS + 1) + MIN_NUM_FWORKS);
   glClear(GL_COLOR_BUFFER_BIT);

   //create random origin and radius based on constants, the call drawFirework() to generate the lines
   for (int i = 0; i < numFireworks; i++)
   {
      float originX = ((float)rand()/RAND_MAX * 2.0f + -1.0f) * MAX_ORIGIN;
      float originY = ((float)rand()/RAND_MAX * 2.0f + -1.0f) * MAX_ORIGIN;
      float originZ = ((float)rand()/RAND_MAX * 2.0f + -1.0f) * MAX_ORIGIN;
      float radius = (float)rand()/RAND_MAX * (RAD_MAX - RAD_MIN) + RAD_MIN;
      drawFirework(originX, originY, originZ, NUM_LINES_FACTOR, radius);
   }
   glFlush();
}

//---------------------------------------
// Main program
//---------------------------------------
int main(int argc, char *argv[])
{
   /* initialize random seed: */
   srand (time(NULL));
   
   glutInit(&argc, argv);
   glutInitWindowSize(500, 500);
   glutInitWindowPosition(250, 250);
   glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
   glutCreateWindow("Fireworks");
   glutDisplayFunc(display);
   init();
   glutMainLoop();
   return 0;
}
