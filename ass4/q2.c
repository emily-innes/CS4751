/**************
This is some kind of stingray/eel hybrid. Stingrays don't actually move their tails when
they swim, but I thought the tail waggle was cute
**************/

//#include <windows.h>
#include <stdio.h>
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

static GLfloat angle[]={21,108,0};
static GLfloat pos[]={-1,-0.8,-4};


GLfloat armHeight=0.0;
GLfloat perStep= -.02;
GLfloat waggle=0.0;
GLfloat wagPS=-0.04;

/* Function for updating the perspective*/
void updatePerspective(int w, int h){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0,w/h, 0.1, 20);
}
void
initlights(double r, double g, double b)
{
    GLfloat ambient[] = {1, 1, 1, 1.0};
    GLfloat position[] = {0.0, 0.2, 3.0, 1.0};
    GLfloat mat_diffuse[] = {r,g, b, 1.0};
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
void drawStingray(){
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
   //initlights();       /* for lighted version only */
}
void
display(void)
{
	glMatrixMode(GL_MODELVIEW);
	    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor4f(1.0,0.0,1.0,1.0);
	glPushMatrix();

	glTranslatef(pos[0],pos[1],pos[2]);
	glRotatef(angle[0],1.0,0.0,0.0);
	glRotatef(angle[1],0.0,1.0,0.0);
	glRotatef(angle[2],0.0,0.0,1.0);
	/*glPushMatrix();
	glTranslatef(1,1.5,-1);
	glScalef(1.5,1.5,1.5);
	initlights(.8,.4,.6);
	drawStingray();
	glPopMatrix();
	glTranslatef(0,-.5,0);
	initlights(.5,.6,.7);
	drawStingray();
	glPopMatrix();*/
	initlights(.5,.6,.7);
	drawStingray();
	glPopMatrix();
	updateStingray();
	glFlush();
	glutSwapBuffers();
	glutPostRedisplay();
}
void keyboard(unsigned char key, int x, int y){
/*****WASDQE for movement ******/
	if (key =='W' | key =='w'){
		pos[1]-=0.1;
				


	}
	if( key=='S'| key=='s'){
		pos[1]+=0.1;

	}

	if (key =='D' | key =='d'){
		pos[0]-=0.1;

	}
	if (key =='A' | key =='a'){
		pos[0]+=0.1;

	}
	if (key =='Q' | key =='q'){
		pos[2]+=0.1;
	}
	if (key =='E' | key =='e'){
		pos[2]-=0.1;
	}
	/****Rotate the camera with IJKLUO****/
	if (key =='I' | key =='i'){
		if(angle[0]>=360.0)angle[0]=0;
			angle[0]+=3.0;


	}
	if( key=='K'| key=='k'){
		if(angle[0]<=0)angle[0]=360;
			angle[0]-=3.0;


	}

	if (key =='J' | key =='j'){
		if(angle[1]<=0)angle[1]=360;
		angle[1]-=3.0;

	}
	if (key =='L' | key =='l'){
		if(angle[1]>=360.0)angle[1]=0;
			angle[1]+=3.0;


	}
	if(key=='U' | key=='u'){
		if(angle[2]>=360.0)angle[2]=0;
			angle[2]+=3.0;
	}
	if(key=='O'| key=='o'){
		if(angle[2]<=0)angle[2]=360;
			angle[2]-=3.0;
	}
	if(key=='m'){
		printf("Camera position x %f y %f z%f rotation x %f y %f z%f",pos[0],pos[1],pos[2],angle[0],angle[1],angle[2]);
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
    glutCreateWindow(argv[0]);
    myinit();
    glutReshapeFunc(myReshape);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard)
;    glutMainLoop();
    return 0;             /* ANSI C requires main to return int. */
}
