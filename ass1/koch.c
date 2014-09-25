#include <GL/glut.h>
#include<math.h>
#include <stdio.h>
double width=250.0;
double height=250.0;
double x1, x2, x3;
double y,y2,y3;
int n=0;
int MAX_LEVEL =5;
void init (void){
	double angle;
	glClearColor (1.0,1.0,1.0,0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0,1.0,0.0,1.0,-1.0,1.0);
	x1=width/4.0;
	x2=width*3.0/4.0;
	y=height/4.0;
	double len=x2-x1;
	y2=y;
  	angle=atan((y2-y)/(x2-x1));
	x3=x1+len*cos(angle+60*M_PI/180.0);
	y3=y+len*sin(angle+60*M_PI/180.0);
}
/*
Recursive method to split a line into three equal segments, two of which form an equilateral triangle
*/
void drawVertices(double startx, double starty, double endx, double endy, int level){

	double width,height,x1,x2,x3,y,y2,y3;
	width=endx-startx;
	height=endy-starty;

	if(level>0){
		//divide segment in 3
		x1=startx+width/3;
		y=starty+height/3;
		x3=x1+width/3;
		y3=y+height/3;

		//code for the midpoint
		x2=(startx+endx)/2.0+(tan(60*M_PI/180)*(starty-endy)/6.0);
		y2=(starty+endy)/2.0+(tan(60*M_PI/180)*(endx-startx)/6.0);
		
		drawVertices(startx,starty,x1,y,level-1);
		drawVertices(x1,y,x2,y2,level-1);
		drawVertices(x2,y2,x3,y3,level-1);
		drawVertices(x3,y3,endx,endy,level-1);
	}
	else{
		//just draw the line
		glVertex3f(startx,starty,0.0);
		glVertex3f(endx,endy,0.0);
	}
		
	
}
void display (void){
  glClear (GL_COLOR_BUFFER_BIT);
  glColor3f(1.0,0.0,0.0);
	glBegin(GL_LINES);
		drawVertices(x1,y,x3,y3,n);
		drawVertices(x3,y3,x2,y2,n);
		drawVertices(x2,y2,x1,y,n);
	glEnd();
  glFlush();
}


void mouse(int btn, int state, int x, int y){
	if (btn==GLUT_RIGHT_BUTTON && state==GLUT_DOWN) exit(0);
	if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN){
		n=(n+1)%MAX_LEVEL;
		glutPostRedisplay();
		//cycles which level is displayed
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
