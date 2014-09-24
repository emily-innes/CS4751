#include <GL/glut.h>
#include<math.h>
#include <stdio.h>
double width=250;
double height=250;
int expand=1;
double rate;
struct quad{
	double x1,x2,x3,x4,y1,y2,y3,y4;
	double len;
	double height;
};
struct quad square;
struct quad eye;
void init (void){
	glClearColor (1.0,1.0,1.0,0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0,1.0,0.0,1.0,-1.0,1.0);
	square.x1=0.0;
	square.x2=50.0;
	square.x3=50.0;
	square.x4=0.0;
	square.y1=50.0;
	square.y2=50.0;
	square.y3=0.0;
	square.y4=0.0;
	square.len=square.x2-square.x1;
	printf("%f",square.len);
	square.height=square.y1-square.y4;
	eye.x1=square.len*5.0/6.0;
	eye.x2=square.len*11.0/12.0;
	eye.x3=eye.x2;
	eye.x4=eye.x1;
	eye.y1=square.height*5.0/6.0;
	eye.y2=eye.y1;
	eye.y3=square.height*11.0/12.0;
	eye.y4=eye.y3;
	rate=0.5;
  
}

void display (void){
	double length;
	double hold;
	glClear (GL_COLOR_BUFFER_BIT);
	glColor3f(0.0,0.0,0.0);
	//printf("{ %f , %f} { %f , %f} { %f , %f}",x1, y, x2, y, x3, y2);
	glBegin(GL_POLYGON);
		glVertex3f (square.x1, square.y1, 0.0);
		glVertex3f (square.x2, square.y2, 0.0);
		glVertex3f (square.x3, square.y3, 0.0);
		glVertex3f(square.x4,square.y4,0.0);
	glEnd();
	glColor3f(0.0,1.0,0.0);
	glBegin(GL_LINES);
		glVertex3f (eye.x1, eye.y1, 0.1);
		glVertex3f (eye.x2, eye.y2, 0.1);
		glVertex3f (eye.x2, eye.y2, 0.1);
		glVertex3f (eye.x3, eye.y3, 0.1);
		glVertex3f (eye.x3, eye.y3, 0.1);
		glVertex3f (eye.x4, eye.y4, 0.1);
		glVertex3f (eye.x4, eye.y4, 0.1);
		glVertex3f (eye.x1, eye.y1, 0.1);
	glEnd();
	glFlush();
	glutSwapBuffers();
	//usleep(200000);
	length=abs(square.x2-square.x1);
	if(length>=square.len*2){
		expand=0;
	}
	if(length<=square.len){
		expand=1;
	}
	if(square.x2>=width){
		eye.x1-=rate;
		eye.x2-=rate;
		eye.x3-=rate;
		eye.x4-=rate;
		if(eye.x4<=square.x1+square.len/12.0){
			square.x3=width-rate;
			square.x2=width-rate;
			rate=-rate;
			eye.x4=eye.x3;
			eye.x3=eye.x1;
			eye.x2=eye.x1;
			eye.x1=eye.x4;
			square.x4=square.x3;
			square.x3=square.x1;
			square.x2=square.x1;
			square.x1=square.x4;
		}
	}
	else{
		if(expand==1){
			square.x2+=rate;
			square.x3+=rate;
			eye.x1+=rate;
			eye.x2+=rate;
			eye.x3+=rate;
			eye.x4+=rate;
		}
		else{
			square.x1+=rate;
			square.x4+=rate;
		
		}
	}
	
		
	glutPostRedisplay();


}
void mouse(int btn, int state, int x, int y){
  if (btn==GLUT_RIGHT_BUTTON && state==GLUT_DOWN) exit(0);
  if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN){

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
