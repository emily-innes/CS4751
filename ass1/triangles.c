#include <GL/glut.h>
#include<math.h>
#include <stdio.h>
double width=250.0;
double height=250.0;
double x1, x2, x3;
double y,y2;
void init (void){
  glClearColor (1.0,1.0,0.0,0.0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0,1.0,0.0,1.0,-1.0,1.0);
  x1=width*3.0/4.0;
  x2=width/4.0;
  y=x2;
  x3=x2+((x1-x2)/2.0); 
  y2=y+tan(60.0*M_PI/180.0)*(x1-x2)/2.0;
  
}

void display (void){
  glClear (GL_COLOR_BUFFER_BIT);
  glColor3f(0.0,0.0,1.0);
  //printf("{ %f , %f} { %f , %f} { %f , %f}",x1, y, x2, y, x3, y2);
  glBegin(GL_POLYGON);
      glVertex3f (x1, y, 0.0);
      glVertex3f (x2, y, 0.0);
      glVertex3f (x3, y2, 0.0);
   glEnd();
  glFlush();
 

}
void mouse(int btn, int state, int x, int y){
  if (btn==GLUT_RIGHT_BUTTON && state==GLUT_DOWN) exit(0);
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
x1=w*3.0/4.0;
x2=w/4.0;
x3=x2+((x1-x2)/2.0); 
glFlush();

}
  
int main (int argc, char** argv){

  glutInit(&argc, argv);
  glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(width,height);
  glutInitWindowPosition(100,100);
  glutCreateWindow("Assignment 1");
  glutMouseFunc (mouse);
  glutKeyboardFunc(keyboard);
  glutReshapeFunc(reshape);
  init();
  glutDisplayFunc(display);
  glutMainLoop();
  return 0;
}
