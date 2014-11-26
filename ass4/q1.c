#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <GL/glut.h>
#include "useful.h"

GLfloat conePoints[4][4][3] = {
	{{ 1.0, -1.0, 0}, { 0.8, 0, 0}, {0, 4.0, 0}, {0, 4.0, 0}},
	{{ 0, -1.0, 1}, { 0, 0, 0.8}, {0, 4.0, 0}, {0, 4.0, 0}},
	{{ -1, -1.0, 0}, { -0.8, 0, 0}, {0, 4.0, 0}, {0, 4.0, 0}},
	{{0, -1.0, -1.0}, {0, 0, -0.8}, {0, 4.0, 0}, {0, 4.0, 0}}
	
};
/*GLfloat conePoints2[4][4][3]={
	{{0, -1.0, -1.0}, {0, 0, -0.8}, {0, 0, -0.8}, {0, 4.0, 0}},
	{{ -1, -1.0, 0}, { -0.8, 0, 0}, { -0.8, 0, 0}, {0, 4.0, 0}},
	{{ 0, -1.0, 1}, { 0, 0, 0.8}, { 0, 0, 0.8}, {0, 4.0, 0}},
	{{ 1.0, -1.0, 0}, { 0.8, 0, 0}, { 0.8, 0, 0}, {0, 4.0, 0}}
};*/
GLfloat spherePoints[6][3]={
	{0,-1.0,0},//bottom
	{1.0,0.5,0.0},//middle points
	{0.0,0.5,1.0},
	{-1.0,0.5,0.0},
	{0.0,0.5,-1.0},
	{0,1.0,0}//top
	

};
static GLfloat angle[]={0.0,0.0,0.0};


double cameraX=0;
double cameraY=0;
double cameraZoom=0;
void display(void)
{
   int i, j;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	glPushMatrix ();
	glRotatef(angle[0],1.0,0.0,0.0);
	glRotatef(angle[1],0.0,1.0,0.0);
	glRotatef(angle[2],0.0,0.0,1.0);
  	drawSphere(spherePoints);
/*glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4,
           0, 1, 12, 4, &conePoints2[0][0][0]);
   glEnable(GL_MAP2_VERTEX_3);
   glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
   glEnable(GL_DEPTH_TEST);
   for (j = 0; j <9; j++) {
      glBegin(GL_LINE_STRIP);
      for (i = 0; i <= 30; i++)
         glEvalCoord2f((GLfloat)i/30.0, (GLfloat)j/8.0);
      glEnd();
      glBegin(GL_LINE_STRIP);
      for (i = 0; i <= 30; i++)
         glEvalCoord2f((GLfloat)j/8.0, (GLfloat)i/30.0);
      glEnd();
   }*/
   glPopMatrix ();
   glFlush();
}

void init(void)
{
   glClearColor (0.0, 0.0, 0.0, 0.0);

   glShadeModel(GL_FLAT);
}

void reshape(int w, int h)
{
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   if (w <= h)
      glOrtho(-5.0, 5.0, -5.0*(GLfloat)h/(GLfloat)w, 
               5.0*(GLfloat)h/(GLfloat)w, -5.0, 5.0);
   else
      glOrtho(-5.0*(GLfloat)w/(GLfloat)h, 
               5.0*(GLfloat)w/(GLfloat)h, -5.0, 5.0, -5.0, 5.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}
void keyboard(unsigned char key, int x, int y){
/*****WASDQE for rotation about the relevant axis******/
	if (key =='W' | key =='w'){
		//switch(mode){
			//case(0):
				if(angle[0]>=360.0)angle[0]=0;
				angle[0]+=3.0;
			//break;
		//}
			
	}
	if( key=='S'| key=='s'){
		//switch(mode){
			//case(0):
			if(angle[0]<=0)angle[0]=360;
			angle[0]-=3.0;
			//break;
				
		//}
	}

	if (key =='E' | key =='e'){
			if(angle[1]>=360.0)angle[1]=0;
			angle[1]+=3.0;
		
	}
	if (key =='Q' | key =='q'){

			
			if(angle[1]<=0)angle[1]=360;
			angle[1]-=3.0;

	}
	if (key =='A' | key =='a'){
		//switch(mode){
			//case(0):
			if(angle[2]>=360.0)angle[2]=0;
			angle[2]+=3.0;
			//break;
		//}
	}
	if (key =='D' | key =='d'){
		//switch(mode){
			//case(0):
			if(angle[2]<=0)angle[2]=360;
			angle[2]-=3.0;
			//break;
		//}
	}
	/****camera position is controlled with ijkl, zoom with YU****/
	if (key =='I' | key =='i'){

				cameraY-=0.05;

			
	}
	if( key=='K'| key=='k'){

			cameraY+=0.05;
				

	}

	if (key =='J' | key =='j'){

			
			cameraX+=0.05;
	
	}
	if (key =='L' | key =='l'){

			cameraX-=0.05;
		
	}
	if(key=='U' | key=='u'){
		cameraZoom+=0.05;
	}
	if(key=='Y'| key=='y') cameraZoom-=0.05;

	glutPostRedisplay();

}
int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
   glutInitWindowSize (500, 500);
   glutInitWindowPosition (100, 100);
   glutCreateWindow (argv[0]);
   init ();
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
   glutMainLoop();
   return 0;
}
