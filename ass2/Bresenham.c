#include <GL/glut.h>
#include "parse.h"
#include "graphics.h"
struct line lines[256];
struct circle circles[256];
int lineIndex=0;
int circleIndex=0;
int read =1;
void display (void){
	int i,j,x,y,x2,y2,r;
	int type=4;
	glClear (GL_COLOR_BUFFER_BIT);
	glColor3f(0.0,0.0,0.0);
	if(read==1){
		read=readInput(&x,&y,&x2,&y2,&r,&type);
		//printf("%d",read);
		if(type==1){
			struct line l1;
			l1.x1=x;
			l1.y1=y;
			l1.x2=x2;
			l1.y2=y2;
			lines[lineIndex]=l1;
			lineIndex++;
		}
		if(type==2){
			struct circle c1;
			c1.x=x;
			c1.y=y;
			c1.r=r;
			circles[circleIndex]=c1;
			circleIndex++;
		}
	}
	for(i=0;i<lineIndex;i++){
		bresenham (lines[i].x1, lines[i].y1, lines[i].x2, lines[i].y2);
		
		//printf("%d,%d,%d,%d\n",lines[i].x1, lines[i].y1, lines[i].x2, lines[i].y2);
	}
	for(i=0;i<circleIndex;i++){
		midpoint(circles[i].x, circles[i].y, circles[i].r);
	}
	glFlush();
	glutSwapBuffers();
	glutPostRedisplay();
	
	
	
	
}


void reshape(GLsizei w, GLsizei h){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, (GLdouble)w, 0.0,(GLdouble)h,-1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glViewport(0,0,w,h);
	glFlush();
	glutPostRedisplay();
}
int main (int argc, char** argv){

	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(300,300);
	glutInitWindowPosition(100,100);
	glutCreateWindow("Assignment 2");
	glutDisplayFunc(display);	
  	glutIdleFunc(display);
	glutReshapeFunc(reshape);
	glClearColor (1.0,1.0,1.0,0.0);
	glViewport(0,0,300,300);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0,300.0,0.0,300.0,-1.0,1.0);
	glutMainLoop();
	return 0;
}
