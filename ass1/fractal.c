#include <GL/glut.h>
#include<math.h>
#include <stdio.h>
double width=500.0;
double height=500.0;
int n=0;
int lvl=0;
double x1,x2,y,y2;
double xPoints[256];
double yPoints[256];
void init (void){
  glClearColor (0.0,0.0,0.0,0.0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0,1.0,0.0,1.0,-1.0,1.0);
  glViewport(0,0,width,height);
  x1=0;
  x2=width;
  y=0;
  y2=0;
  
}
void divideSegment(double x1, double y1, double x2, double y2, int level){
	double len=(x2-x1)/3.0;
	double angle=atan((y2-y1)/(x2-x1));
	double x3,y3;
	x1=len*cos(angle);
        x2=len*2.0*cos(angle);
	x3=x1+len*cos((60+angle)*M_PI/180.0);
	y1=len*sin(angle);
	y2=len*2.0*sin(angle);
	y3=y1+len*sin((60+angle)*M_PI/180.0);
	printf("test1");
	xPoints[n]=x1;
	yPoints[n]=y1;
	printf("test2");
	n++;
	if(level>0){
		divideSegment(x1,y1,x3,y3,level-1);
	}
	xPoints[n]=x3;
	yPoints[n]=y3;
	n++;
	if(level>0){
		divideSegment(x3,y3,x2,y2,level-1);
	}
	xPoints[n]=x2;
	yPoints[n]=y2;
	n++;
  
}
void display (void){
  glClear (GL_COLOR_BUFFER_BIT);
  glColor3f(1.0,1.0,1.0);
  
 // printf("{ %f , %f} { %f , %f} { %f , %f}",x1, y, x2, y, x3, y2);

      divideSegment(x1,y,x2,y2,lvl);
  glBegin(GL_POLYGON);
	int i;
	for(i=0;i<n;i++){
		glVertex3f (xPoints[i], yPoints[i], 0.0);
		printf("{ %f, %f}",xPoints[i], yPoints[i]);
	}
  glEnd();
  glFlush();
  glutSwapBuffers();
 glutPostRedisplay();

}

void mouse(int btn, int state, int x, int y){
  if (btn==GLUT_RIGHT_BUTTON && state==GLUT_DOWN) exit(0);
}

void keyboard(unsigned char key, int x, int y){
  if (key =='Q' | key =='q') exit(0);
}

  
int main (int argc, char** argv){

  glutInit(&argc, argv);
  glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(width,height);
  glutInitWindowPosition(100,100);
  glutCreateWindow("Assignment 1");
  glutMouseFunc (mouse);
  glutKeyboardFunc(keyboard);
  init();
  glutDisplayFunc(display);
  glutMainLoop();
  return 0;
}
