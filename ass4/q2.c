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

GLfloat ctrlpts[4][4][3] =
{
		{{ 1.0, 0, 0}, { 0.5, 0, -1}, {-.50, 0, -1}, {-1, 0, 0}},
			{{ 1.0, 0, 0}, { 0.5, 0, 0}, {-.50, 0, 0}, {-1, 0, 0}},
			{{ 1.0, 0, 0}, { 0.5, 0, 1}, {-.50, 0, 1}, {-1, 0, 0}},
			{{ 1.0, 0, 0}, { 0.5, 0, 2}, {-.50, 0, 2}, {-1, 0, 0}}
};
GLfloat tailPts[4][4][3]={
{{-0.25,0,1.5},{-0.125,0,2},{0.375,0,2.5},{0,0,3}},
{{-0.125,0,1.5},{0,0,2},{0.5,0,2.5},{0,0,3}},
{{0.125,0,1.5},{0.375,0,2},{0.375,0,2.5},{0,0,3}},
{{0.25,0,1.5},{0.5,0,2},{0.5,0,2.5},{0,0,3}}

};

static GLfloat angle[]={20.0,45.0,25.0};


double cameraX=0;
double cameraY=0;
double cameraZoom=0;
GLfloat armHeight=0.0;
GLfloat perStep= -.02;
GLfloat waggle=0.0;
GLfloat wagPS=-0.04;
void
initlights(void)
{
    GLfloat ambient[] = {0.2, 0.2, 0.2, 1.0};
    GLfloat position[] = {0.0, 0.0, 2.0, 1.0};
    GLfloat mat_diffuse[] = {0.3, 0.6, 0.1, 1.0};
    GLfloat mat_specular[] = {0.0, 1.0, 1.0, 1.0};
    GLfloat mat_shininess[] = {50.0};

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_POSITION, position);

    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
}
void updateStingray(){
	if(armHeight<=-1.||armHeight>=1.)perStep=perStep*-1;
	if(waggle>=1.0||waggle<=-1.0)wagPS=wagPS*-1;
	armHeight+=perStep;
	waggle+=wagPS;
	int i;
	for(i=0;i<4;i++){
		//controlling arm flapping motion
		ctrlpts[i][0][1]=armHeight;
		tailPts[i][0][1]=armHeight/3.0;
		tailPts[i][3][1]=armHeight/8.0;
		ctrlpts[i][3][1]=armHeight;
		//controlling tail waggle
		tailPts[i][1][3]+=wagPS;
		tailPts[i][2][3]-=wagPS;
	}
}

void
myinit(void)
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glEnable(GL_DEPTH_TEST);
   // glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4,
    //    0, 1, 12, 4, &ctrlpts[0][0][0]);
   // glEnable(GL_MAP2_VERTEX_3);
   // glEnable(GL_AUTO_NORMAL);
   // glEnable(GL_NORMALIZE);
  //  glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
   initlights();       /* for lighted version only */
}
void
display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor4f(1.0,0.0,1.0,1.0);
    glPushMatrix();
    glRotatef(angle[0],1.0,0.0,0.0);
	glRotatef(angle[1],0.0,1.0,0.0);
	glRotatef(angle[2],0.0,0.0,1.0);
    //glRotatef(85.0, 1.0, 1.0, 1.0);
	glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 4, &ctrlpts[0][0][0]);
	glEnable(GL_MAP2_VERTEX_3);
	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);
	glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
    glEvalMesh2(GL_FILL, 0, 20, 0, 20);
	glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 4, &tailPts[0][0][0]);
	glEnable(GL_MAP2_VERTEX_3);
	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);
	glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
    glEvalMesh2(GL_FILL, 0, 20, 0, 20);
    glPopMatrix();
    updateStingray();
    glFlush();
    glutSwapBuffers();
    glutPostRedisplay();
}
void keyboard(unsigned char key, int x, int y){
/*****WASDQE for rotation about the relevant axis******/
	if (key =='W' | key =='w'){
		//switch(mode){
			//case(0):
				if(angle[0]>=360.0)angle[0]=0;
				angle[0]+=3.0;
			//break;
		//}

	}
	if( key=='S'| key=='s'){
		//switch(mode){
			//case(0):
			if(angle[0]<=0)angle[0]=360;
			angle[0]-=3.0;
			//break;

		//}
	}

	if (key =='D' | key =='d'){
			if(angle[1]>=360.0)angle[1]=0;
			angle[1]+=3.0;

	}
	if (key =='A' | key =='a'){


			if(angle[1]<=0)angle[1]=360;
			angle[1]-=3.0;

	}
	if (key =='Q' | key =='q'){
		//switch(mode){
			//case(0):
			if(angle[2]>=360.0)angle[2]=0;
			angle[2]+=3.0;
			//break;
		//}
	}
	if (key =='E' | key =='e'){
		//switch(mode){
			//case(0):
			if(angle[2]<=0)angle[2]=360;
			angle[2]-=3.0;
			//break;
		//}
	}
	/****camera position is controlled with ijkl, zoom with YU****/
	if (key =='I' | key =='i'){

				cameraY-=0.05;


	}
	if( key=='K'| key=='k'){

			cameraY+=0.05;


	}

	if (key =='J' | key =='j'){


			cameraX+=0.05;

	}
	if (key =='L' | key =='l'){

			cameraX-=0.05;

	}
	if(key=='U' | key=='u'){
		cameraZoom+=0.05;
	}
	if(key=='Y'| key=='y') cameraZoom-=0.05;

	glutPostRedisplay();

}


void
myReshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        glOrtho(-4.0, 4.0, -4.0 * (GLfloat) h / (GLfloat) w,
            4.0 * (GLfloat) h / (GLfloat) w, -4.0, 4.0);
    else
        glOrtho(-4.0 * (GLfloat) w / (GLfloat) h,
            4.0 * (GLfloat) w / (GLfloat) h, -4.0, 4.0, -4.0, 4.0);
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
    glutKeyboardFunc(keyboard)
;    glutMainLoop();
    return 0;             /* ANSI C requires main to return int. */
}
