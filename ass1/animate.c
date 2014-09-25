#include <GL/glut.h>
#include<math.h>
#include <stdio.h>
double width=250.0;
double height=250.0;
double x1, x2;
double y,y2;
double speed =0.25;
double colorChange=0.001;
double red,blue;
void init (void){
  glClearColor (1.0,1.0,1.0,0.0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0,1.0,0.0,1.0,-1.0,1.0);
//initializing some points
  x1=0;
  x2=100;
  y=25;
  y2=125;
  red=1.0;
  blue=0.0;
  
}

void display (void){
  double hold;
  glClear (GL_COLOR_BUFFER_BIT);
  glColor3f(red,0,blue);
  glBegin(GL_POLYGON);
      glVertex3f (x1, y, 0.0);
      glVertex3f (x2, y, 0.0);
      glVertex3f (x2, y2, 0.0);
      glVertex3f(x1,y2,0.0);
   glEnd();
   glFlush();
   glutSwapBuffers();
	//moving the figure to the right
   x1+=speed;
   x2+=speed;
	//code for color change
   if(red>=0){
	red-=colorChange;
   }
   else{
	blue+=colorChange;
   }
   if(blue>=1){
	hold=red;
	red=blue;
	blue=hold;
   }
   
  //handling when the right border is reached
   if (x2>=width){
	x1-=speed;
	speed=-speed;
   }
   //handling when the left border is reached
   if(x1<=0){
	x1=0;
	speed=0;
   }
   glutPostRedisplay();
 

}

void mouse(int btn, int state, int x, int y){
  if (btn==GLUT_RIGHT_BUTTON && state==GLUT_DOWN) exit(0);
  if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN){
  x1=0;
  x2=100;
  speed=0.25;
}
}

void keyboard(unsigned char key, int x, int y){
  if (key =='Q' | key =='q') exit(0);
}
void reshape(GLsizei w, GLsizei h){
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
glOrtho(0.0, (GLdouble)w, 0.0,(GLdouble)h,-1.0, 1.0);
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
glViewport(0,0,w,h);
glFlush();
width=w;
height=h;

}
  
int main (int argc, char** argv){

  glutInit(&argc, argv);
  glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(width,height);
  glutInitWindowPosition(100,100);
  glutCreateWindow("Assignment 1");
  glutMouseFunc (mouse);
  glutKeyboardFunc(keyboard);
  glutReshapeFunc(reshape);
  init();
  glutDisplayFunc(display);
  glutIdleFunc(display);
  glutMainLoop();
  return 0;
}
