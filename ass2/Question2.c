#include <GL/glut.h>
#include "parse.h"
#include "graphics.h"
struct poly polygons[64];
int read =1;
int polyCount=0;
void display (void){
	int i;
	int vertices=0;
	
	if(read==1){
		int* newVertices;
		newVertices=readPolygonInput(&vertices,&read);
		printf("%d vertices", vertices/2);
		struct poly p1;
		for(i=0;i<vertices/2;i++){
			p1.xPoints[i]=newVertices[2*i];
			p1.yPoints[i]=newVertices[2*i+1];
			
		}
		p1.vertices=i;
		polygons[polyCount]=p1;
		polyCount++;
	}
	for(i=0;i<polyCount;i++){
		drawPolygon(polygons[i]);
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
