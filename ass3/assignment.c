
#include <GL/glut.h>
#include "robotParts.h"
GLUquadricObj  *obj; /* pointer to quadric object */

static GLfloat angle[] = {0.0,0.0,0.0};
static GLint axis = 0;
GLuint head, body, lArm, rArm;
void initRobot(){
	glMatrixMode(GL_MODELVIEW);
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	head=glGenlists(64);
	body=glGenlists(64);
	lArm=glGenlists(64);
	rArm=glGenlists(64);
	makeHead(obj,head);
	makeBody(obj,body);
	
}
void display(void)
{

	initRobot();
	//glClear(GL_COLOR_BUFFER_BIT);
	//glLoadIdentity();
	glCallList(head);
	//glRotatef(angle[0],1.0,0.0,0.0);
	//glRotatef(angle[1],0,1.0,0);
	//glRotatef(angle[2],0,0,1.0);
	//glCallList(b);
	glFlush();
	glutSwapBuffers();
	//glutPostRedisplay();
}



void mouse(int btn, int state, int x, int y)
{

/* left button increase viewing angle, right button decreases it */

	if(btn==GLUT_LEFT_BUTTON && state == GLUT_DOWN) 
        {
        angle[axis] += 5.0;
        if( angle[axis] > 360.0 ) angle[axis] -= 360.0;
        }
	/*if(btn==GLUT_RIGHT_BUTTON && state == GLUT_DOWN) 
        {
        angle[axis] -= 5.0;
        if( angle[axis] < 360.0 ) angle[axis] += 360.0;
        }*/
        display();
}

void menu(int id)
{

/* menu selects which angle to change or whether to quit */

  if(id == 1 ) axis=0;
   if(id == 2) axis=1;
   if(id == 3 ) axis=2;
   if(id ==4 ) exit(0);
}

void 
myReshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        glOrtho(-10.0, 10.0, -5.0 * (GLfloat) h / (GLfloat) w,
            15.0 * (GLfloat) h / (GLfloat) w, -10.0, 10.0);
    else
        glOrtho(-10.0 * (GLfloat) w / (GLfloat) h,
            10.0 * (GLfloat) w / (GLfloat) h, -5.0, 15.0, -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void init()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glColor3f(1.0, 0.0, 0.0);
	obj=gluNewQuadric(); /* allocate quadric object */
	gluQuadricDrawStyle(obj, GLU_LINE); /* render it as wireframe */
	//base(obj,0,0,0,0);
}
void keyboard(unsigned char key, int x, int y){
  if (key =='Q' | key =='q') exit(0);
}
void
main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Assignment 3");
	init();
	glutReshapeFunc(myReshape);
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	glutCreateMenu(menu);
	glutAddMenuEntry("Rotate X", 1);
	glutAddMenuEntry("Rotate Y", 2);
	glutAddMenuEntry("Rotate Z", 3);
	glutAddMenuEntry("quit", 4);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutMainLoop();
}
