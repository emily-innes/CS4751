#include <GL/glut.h>
#include<math.h>
#include <stdio.h>
struct hexagon{
int x1,x2,x3,x4;
int y1,y2,y3,y4;
}
struct hexagon hex;
void init (void){
  glClearColor (1.0,1.0,1.0,0.0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0,1.0,0.0,1.0,-1.0,1.0);
  hex.x1=0;
  hex.x2=20;
  hex.x3=40;
  hex.x4=60;
  hex.y1=0;
  hex.y2=20;
  hex.y3=40;
  hex.y4=60;
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  /* points clockwise from top left:
      x2y3 x3y3 x4y2 x3y1 x2y1 x1y2
  */
  
}

void display (void){
  double hold;
  glClear (GL_COLOR_BUFFER_BIT);
  glColor3f(red,0,blue);
  //printf("{ %f , %f} { %f , %f} { %f , %f}",x1, y, x2, y, x3, y2);
  glBegin(GL_POLYGON);
      glVertex3f (x1, y, 0.0);
      glVertex3f (x2, y, 0.0);
      glVertex3f (x2, y2, 0.0);
      glVertex3f(x1,y2,0.0);
   glEnd();
   glFlush();
   glutSwapBuffers();
   //usleep(200000);
   x1+=speed;
   x2+=speed;
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
   
  
   if (x2>=width){
	x1-=speed;
	speed=-speed;
   }
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
