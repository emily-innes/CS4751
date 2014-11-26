#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <GL/glut.h>

GLfloat bodyPoints[4][4][3] = {
	{{ 1.0, 2, 0}, { 0.5, 1, -1}, {-.50, 1, -1}, {-1, 2, 0}},
	{{ 1.0, 2, 0}, { 0.5, 1, 0}, {-.50, 1, 0}, {-1, 2, 0}},
	{{ 1.0, 2, 0}, { 0.5, 1, 1}, {-.50, 1, 1}, {-1, 2, 0}},
	{{ 1.0, 2, 0}, { 0.5, 1, 2}, {-.50, 1, 2}, {-1, 2, 0}}
	
};

static GLfloat angle[]={0.0,0.0,0.0};


double cameraX=0;
double cameraY=0;
double cameraZoom=0;
GLfloat armDisplace=2;
GLfloat moveAmt=-0.01;
void updateStringray(){
	if(armDisplace>=2||armDisplace<=0) moveAmt=moveAmt*-1;
	armDisplace+=moveAmt;
	bodyPoints[0][0][1]=armDisplace;
	bodyPoints[0][3][1]=armDisplace;
	bodyPoints[1][0][1]=armDisplace;
	bodyPoints[1][3][1]=armDisplace;
	bodyPoints[2][0][1]=armDisplace;
	bodyPoints[2][3][1]=armDisplace;
	bodyPoints[3][0][1]=armDisplace;
	bodyPoints[3][3][1]=armDisplace;
}
void display(void)
{
   int i, j;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	glPushMatrix ();
	glRotatef(angle[0],1.0,0.0,0.0);
	glRotatef(angle[1],0.0,1.0,0.0);
	glRotatef(angle[2],0.0,0.0,1.0);
 
	glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4,
           0, 1, 12, 4, &bodyPoints[0][0][0]);
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
   }
   glPopMatrix ();
   glFlush();
   //glutPostRedisplay();
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
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
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
