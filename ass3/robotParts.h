#include <GL/glut.h>

#define BASE_HEIGHT 2.0
#define BASE_RADIUS 1.0
#define LOWER_ARM_HEIGHT 5.0
#define LOWER_ARM_WIDTH 0.5
#define UPPER_ARM_HEIGHT 5.0
#define UPPER_ARM_WIDTH 0.5


void arm(GLUquadricObj  *obj, double x, double y){
	/*make sure to include code for forearm and thumb*/
}

void makeHead(GLUquadricObj  *obj, GLuint head){
glNewList(head, GL_COMPILE);
		glColor3f(1.0,1.0,0);
		glPushMatrix();
		glTranslatef(BASE_HEIGHT);
		gluCylinder(obj, BASE_RADIUS/2, BASE_RADIUS/2, BASE_HEIGHT/4, 16, 16);
		
		glPopMatrix();
glEndList();

}

void makeBody(GLUquadraticObj *obj, GLuint body){
glNewList(body,GL_COMPILE);
	glColor3f(0,1.0,0);
	glPushMatrix();
	gluCylinder(obj, BASE_RADIUS,BASE_RADIUS, BASE_HEIGHT, 64,64);
	glPopMatrix();

glEndList();
}

void makeArms(GLUquadraticObj *obj, GLuint lArm, GLuint rArm){
GLuint t1;
t1=glGenlists(16);
glNewList(t1, GL_COMPILE){
	glPushMatrix();
	/**figure out what looks good**/
	glRotatef(-90,0,1,0);
	glScalef(UPPER_ARM_WIDTH/4, UPPER_ARM_WIDTH/4, UPPER_ARM)HEIGHT/8);
	glutWireCube(1.0);	
	glPopMatrix();
}
glNewList(rArm, GL_COMPILE){
	glPushMatrix();
	/**rotate some amount**/
	glScalef(UPPER_ARM_WIDTH,UPPER_ARM_WIDTH, UPPER_ARM_HEIGHT);
	
		

}
glNewList(lArm, GL_COMPILE){


}
void thumb(GLUquadricObj  *obj,int x, int y){}
