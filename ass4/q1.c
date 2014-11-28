
//#include <windows.h>
#include <GL/glut.h>

const int WIDTH = 600;
const int HEIGHT = 480;

/* Prototypes */
void init();
void display();


//variable for the viewing angle
static GLfloat angle[] = { 0, 45, 0 };

//variable for the camera's x position
double cameraX = 0;

//variable for the camera's y position
double cameraY = 0;

//variable for the camera's z position
double cameraZ = 1;

/* Function for updating the perspective*/
void updatePerspective(int w, int h){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0,w/h, 0.1, 20);
}

void
initlights(void)
{
    GLfloat ambient[] = {0.2, 0.2, 0.2, 1.0};
    GLfloat position[] = {0.0, 3, 0.5, 1.0};
    GLfloat mat_diffuse[] = {1.0, 1.0, 1.00, 1.0};
    GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat mat_shininess[] = {50.0};

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_POSITION, position);

    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
}
void init(void){
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glEnable(GL_DEPTH_TEST);
	//initlights();
}

/* Function for drawing the cone */
void drawCone(){
	GLfloat conePoints[4][4][3] = {
		{ { 0, -1.0, 1 }, { 0, 0, 0.8 }, { 0, 4.0, 0 }, { 0, 4.0, 0 } },
		{ { .8, -1.0, .8 }, { 0, 0, 0.6 }, { 0, 4.0, 0 }, { 0, 4.0, 0 } },
		{ { .8, -1.0, -.8 }, { 0.6, 0, -0.6 }, { 0, 4.0, 0 }, { 0, 4.0, 0 } },
		{ { 0, -1.0, -1.0 }, { 0, 0, -0.8 }, { 0, 4.0, 0 }, { 0, 4.0, 0 } }

	};

	glColor4f(85/256.0, 0, 0, 1);
	glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 4, &conePoints[0][0][0]);
	glEnable(GL_MAP2_VERTEX_3);
	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);
	glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
	glEvalMesh2(GL_FILL, 0, 20, 0, 20);
	glPushMatrix();
	glColor4f(125/256.0, 19/256.0, 19/256.0, 1);
	glRotatef(180.0, 0, 1.0, 0.0);
	glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 4, &conePoints[0][0][0]);
	glEnable(GL_MAP2_VERTEX_3);
	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);
	glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
	glEvalMesh2(GL_FILL, 0, 20, 0, 20);
	glPopMatrix();
}
/* Function for drawing 1/4 of the sphere */
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

/* Function for drawing a full sphere */
void drawSphere(){
	glColor4f(34/256.0,102/256.0, 102/256.0, 1.0);
	sphereSegment();
	glPushMatrix();
	glColor4f(46/256.0,66/256.0,114/256.0,1.0);
	glRotatef(180.0, 0.0, 1.0, 0.0);
	sphereSegment();
	glPopMatrix();
	glPushMatrix();
	glColor4f(45/256.0,136/256.0,45/256.0,1.0);
	glRotatef(180.0, 1.0, 0, 0.0);
	sphereSegment();
	glPopMatrix();
	glPushMatrix();
	glColor4f(34/256.0,102/256.0, 102/256.0, 1.0);
	glRotatef(180.0, 0.0, 0.0, 1.0);
	sphereSegment();
	glPopMatrix();

}
/* Function to draw a plane */
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
/* Function to draw a slightly curved cube */
void drawCube(){
	glColor4f(0/256.0,64/256.0,8/256.0,1.0);
	drawPlane(-0.1);
	glPushMatrix();
	glRotatef(180, 0, 0, 1.0);
	glColor4f(0/256.0,64/256.0,8/256.0,1.0);
	drawPlane(-0.1);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 1.0, 0, 0.0);
	glColor4f(137/256.0,199/256.0,145/256.0,1.0);
	drawPlane(-0.1);
	glPopMatrix();
	glPushMatrix();
	glRotatef(-90.0, 1.0, 0, 0);
	glColor4f(85/256.0,166/256.0,95/256.0,1.0);
	drawPlane(-0.1);
	glPopMatrix();
	glPushMatrix();
	glRotatef(-90.0, 0, 0, 1.0);
	glColor4f(44/256.0,132/256.0,55/256.0,1.0);
	drawPlane(-0.1);
	glPopMatrix();
	glRotatef(90.0, 0, 0, 1.0);
	glColor4f(15/256.0,98/256.0,25/256.0,1.0);
	drawPlane(-0.1);
	glPopMatrix();

}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_FLAT);
	glShadeModel(GL_FLAT);
	glPushMatrix();
	glRotatef(angle[0], 1.0, 0.0, 0.0);
	glRotatef(angle[1], 0.0, 1.0, 0.0);
	glRotatef(angle[2], 0.0, 0.0, 1.0);
	glTranslatef(cameraZ, 0.7,  -1*cameraZ);

	// floor
	glPushMatrix();
	glColor4f(2/256.0, 12/256.0, 34/256.0, 1.0);
	drawPlane(0);
	//left wall
	glColor4f(6/256.0, 21/256.0, 57/256.0, 1.0);
	glPushMatrix();
	glRotatef(90, 1.0, 0, 0);
	drawPlane(0);
	glPopMatrix();
	//right wall
	glColor4f(20/256.0, 39/256.0, 83/256.0, 1.0);
	glPushMatrix();
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
	//transformation for the sphere
	glPushMatrix();
	glTranslatef(-.375, -.85, -.66);
	glScalef(.1, .1, .1);
	drawSphere();
	glPopMatrix();
	//transformation for the cone
	glPushMatrix();
	glTranslatef(-.4, -1, .90);
	glScalef(.1, .1, .1);
	drawCone();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glFlush();
	glutSwapBuffers();
	glutPostRedisplay();
}
/* Keyboard Function. WS to move along the main diagonal of the scene, AD to look around*/
void keyboard(unsigned char key, int x, int y){

	if (key == 'W' | key == 'w'){
		if(cameraZ<=-1){}
		else cameraZ -= 0.03;
	}
	if (key == 'S' | key == 's'){
		if(cameraZ>=1){}
		else cameraZ += 0.03;
	}

	if (key == 'D' | key == 'd'){
		if (angle[1] >= 360.0)angle[1] = 0;
		angle[1] += 3.0;

	}
	if (key == 'A' | key == 'a'){
		if (angle[1] <= 0)angle[1] = 360;
		angle[1] -= 3.0;

	}
	glutPostRedisplay();

}

void
myReshape(int w, int h)
{
	glViewport(0, 0, w, h);
	updatePerspective(w,h);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int
main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("Assignment 4 Scene");
	glutInitWindowSize(WIDTH,HEIGHT);
	glutInitWindowPosition(100,100);
	init();
	glutReshapeFunc(myReshape);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;             /* ANSI C requires main to return int. */
}
