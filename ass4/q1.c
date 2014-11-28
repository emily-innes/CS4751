/* Demo.cpp
* A simple OpenGL program using GLUT.  It creates a blank black
* window which can be used as a starting point for OpenGL programming.
*
* Link in opengl32, glu32, and glut32 libraries and make sure to include
* windows.h if you are compiling with Eclipse in Windows.
*
* Author: Paul Solt  3-4-07
* Based on examples from the Red book OpenGL Programming Guide
*/
#include <windows.h>
#include <GL/glut.h>

const int WIDTH = 600;
const int HEIGHT = 480;

/* Prototypes */
void init();
void display();

/* Definitions */



GLfloat tailPts[4][4][3] = {
		{ { -0.25, 0, 1.5 }, { -0.125, 0, 2 }, { 0.375, 0, 2.5 }, { 0, 0, 3 } },
		{ { -0.125, 0, 1.5 }, { 0, 0, 2 }, { 0.5, 0, 2.5 }, { 0, 0, 3 } },
		{ { 0.125, 0, 1.5 }, { 0.375, 0, 2 }, { 0.375, 0, 2.5 }, { 0, 0, 3 } },
		{ { 0.25, 0, 1.5 }, { 0.5, 0, 2 }, { 0.5, 0, 2.5 }, { 0, 0, 3 } }

};

static GLfloat angle[] = { 0, 45, 0 };


double cameraX = 0;
double cameraY = 0;
double cameraZoom = 0;
GLfloat armHeight = 0.0;
GLfloat perStep = -.02;
GLfloat waggle = 0.0;
GLfloat wagPS = -0.04;
void updatePerspective(){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, 0.8, 0.1, 20);
}
void
initlights(void)
{
	GLfloat ambient[] = { 0.2, 0.2, 0.2, 1.0 };
	GLfloat position[] = { 0.0, 0.0, 2.0, 1.0 };
	GLfloat mat_diffuse[] = { 0.3, 0.6, 0.1, 1.0 };
	GLfloat mat_specular[] = { 0.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_POSITION, position);

	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
}


void
myinit(void)
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_FLAT);
}
void drawCone(){
	GLfloat conePoints[4][4][3] = {
			{ { 0, -1.0, 1 }, { 0, 0, 0.8 }, { 0, 4.0, 0 }, { 0, 4.0, 0 } },
			{ { .8, -1.0, .8 }, { 0, 0, 0.6 }, { 0, 4.0, 0 }, { 0, 4.0, 0 } },
			{ { .8, -1.0, -.8 }, { 0.6, 0, -0.6 }, { 0, 4.0, 0 }, { 0, 4.0, 0 } },
			{ { 0, -1.0, -1.0 }, { 0, 0, -0.8 }, { 0, 4.0, 0 }, { 0, 4.0, 0 } }

	};
	glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 4, &conePoints[0][0][0]);
	glEnable(GL_MAP2_VERTEX_3);
	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);
	glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
	glEvalMesh2(GL_FILL, 0, 20, 0, 20);
	glPushMatrix();
	glRotatef(180.0, 0, 1.0, 0.0);
	glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 4, &conePoints[0][0][0]);
	glEnable(GL_MAP2_VERTEX_3);
	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);
	glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
	glEvalMesh2(GL_FILL, 0, 20, 0, 20);
	glPopMatrix();
}
void sphereSegment(){
	GLfloat spherePoints[4][4][3] = {
			{ { 0, 1, 0 }, { 0, 1, 0.2 }, { 0, 1, 0.8 }, { 0, 0, 1 } },
			{ { 0, 1, 0 }, { 0.4, 1, 0.4 }, { 0.6, 1, 0.6 }, { 1, 0, 1 } },
			{ { 0, 1, 0 }, { 0.4, 1, -0.4 }, { 0.6, 1, -0.6 }, { 1, 0, -1 } },
			{ { 0, 1, 0 }, { 0, 1, -0.2 }, { 0, 1, -0.8 }, { 0, 0, -1.0 } }
	};
	glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 4, &spherePoints[0][0][0]);
	glEnable(GL_MAP2_VERTEX_3);
	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);
	glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
	glEvalMesh2(GL_FILL, 0, 20, 0, 20);
}
void drawSphere(){
	sphereSegment();
	glPushMatrix();
	glRotatef(180.0, 0.0, 1.0, 0.0);
	sphereSegment();
	glPopMatrix();
	glPushMatrix();
	glRotatef(180.0, 1.0, 0, 0.0);
	sphereSegment();
	glPopMatrix();
	glPushMatrix();
	glRotatef(180.0, 1.0, 0.0, 0.0);
	sphereSegment();
	glPopMatrix();

}
void drawPlane(GLfloat warp){
	GLfloat planePoints[4][4][3] = {
			{ { 1, -1, -1 }, { 1, -1 + warp, 0 }, { 1, -1 + warp, 0 }, { 1, -1, 1 } },
			{ { 0.5, -1, -1 }, { 0.5, -1 + warp, 0 }, { 0.5, -1 + warp, 0 }, { 0.5, -1, 1 } },
			{ { -0.5, -1, -1 }, { -0.5, -1 + warp, 0 }, { -0.5, -1 + warp, 0 }, { -0.5, -1, 1 } },
			{ { -1, -1, -1 }, { -1, -1 + warp, 0 }, { -1, -1 + warp, 0 }, { -1, -1, 1 } }
	};
	glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 4, &planePoints[0][0][0]);
	glEnable(GL_MAP2_VERTEX_3);
	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);
	glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
	glEvalMesh2(GL_FILL, 0, 20, 0, 20);
}
void drawCube(){
	drawPlane(-0.1);
	glPushMatrix();
	glRotatef(180, 0, 0, 1.0);
	drawPlane(-0.1);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 1.0, 0, 0.0);
	drawPlane(-0.1);
	glPopMatrix();
	glPushMatrix();
	glRotatef(-90.0, 1.0, 0, 0);
	drawPlane(-0.1);
	glPopMatrix();
	glPushMatrix();
	glRotatef(-90.0, 0, 0, 1.0);
	drawPlane(-0.1);
	glPopMatrix();
	glRotatef(90.0, 0, 0, 1.0);
	drawPlane(-0.1);
	glPopMatrix();

}
void
display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// glMatrixMode(GL_PROJECTION);
	//gluPerspective(3,1,-10,10);

	glPushMatrix();
	glRotatef(angle[0], 1.0, 0.0, 0.0);
	glRotatef(angle[1], 0.0, 1.0, 0.0);
	glRotatef(angle[2], 0.0, 0.0, 1.0);
	//glScalef(2,2,2);
	glTranslatef(1 - cameraZoom, 0.7, -1 + cameraZoom);

	glPushMatrix();
	//green floor
	glColor4f(0, 1.0, 0, 1.0);
	drawPlane(0);
	glColor4f(1.0, 0, 0, 1.0);
	glPushMatrix();
	//red wall
	glRotatef(90, 1.0, 0, 0);
	drawPlane(0);
	glPopMatrix();
	glColor4f(0.0, 0, 1.0, 1.0);
	glPushMatrix();
	//blue wall
	glRotatef(90, 0, 0, 1.0);
	drawPlane(0);
	glPopMatrix();
	//transformation for the cube
	glPushMatrix();
	glTranslatef(.25, -.875, -.66);
	glScalef(0.1, 0.1, 0.1);
	glColor4f(0.688, 0.422, 0.223, 1.0);
	drawCube();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-.375, -.85, -.66);
	glScalef(.1, .1, .1);
	glColor4f(0.178, 0.258, 0.445, 1.0);
	drawSphere();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-.4, -1, .90);
	glScalef(.1, .1, .1);
	glColor4f(.133, .399, .399, .1);
	drawCone();
	glPopMatrix();
	glPopMatrix();

	glPopMatrix();
	glFlush();
	glutSwapBuffers();
	glutPostRedisplay();
}
void keyboard(unsigned char key, int x, int y){
	/*****WASDQE for rotation about the relevant axis******/
	if (key == 'W' | key == 'w'){
		//switch(mode){
		//case(0):
		/*if(angle[0]>=360.0)angle[0]=0;
		angle[0]+=3.0;*/
		cameraZoom += 0.03;
		//break;
		//}

	}
	if (key == 'S' | key == 's'){
		//switch(mode){
		//case(0):
		//if(angle[0]<=0)angle[0]=360;
		//	angle[0]-=3.0;
		cameraZoom -= 0.03;
		//break;

		//}
	}

	if (key == 'D' | key == 'd'){
		if (angle[1] >= 360.0)angle[1] = 0;
		angle[1] += 3.0;

	}
	if (key == 'A' | key == 'a'){


		if (angle[1] <= 0)angle[1] = 360;
		angle[1] -= 3.0;

	}
	if (key == 'Q' | key == 'q'){
		//switch(mode){
		//case(0):
		if (angle[2] >= 360.0)angle[2] = 0;
		angle[2] += 3.0;
		//break;
		//}
	}
	if (key == 'E' | key == 'e'){
		//switch(mode){
		//case(0):
		if (angle[2] <= 0)angle[2] = 360;
		angle[2] -= 3.0;
		//break;
		//}
	}





	glutPostRedisplay();

}

/*void setProjectionMatrix (int width, int height)
{
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluPerspective (50.0*cameraZoom, (float)width/(float)height, -5, 5);
}*/
void
myReshape(int w, int h)
{
	glViewport(0, 0, w, h);
	updatePerspective();
	/*  if (w <= h)
	glOrtho(-4.0, 4.0, -4.0 * (GLfloat) h / (GLfloat) w,
	4.0 * (GLfloat) h / (GLfloat) w, -4.0, 4.0);
	else
	glOrtho(-4.0 * (GLfloat) w / (GLfloat) h,
	4.0 * (GLfloat) w / (GLfloat) h, -4.0, 4.0, -4.0, 4.0);*/

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int
main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow(argv[0]);
	myinit();
	glutReshapeFunc(myReshape);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;             /* ANSI C requires main to return int. */
}
