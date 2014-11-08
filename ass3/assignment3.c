#include <GL/glut.h>


#define HEAD_HEIGHT 0.25
#define HEAD_RADIUS 0.125
#define BODY_WIDTH 0.5
#define BODY_HEIGHT 0.75
#define LOWER_ARM_LENGTH 0.4
#define LOWER_ARM_WIDTH 0.125
#define UPPER_ARM_LENGTH 0.3
#define UPPER_ARM_WIDTH 0.125
#define FLOOR_HEIGHT -0.7


GLUquadricObj *obj;
static GLfloat angle[]={0.0,0.0,0.0};
static GLuint head, body;
int mode=0;
int part;
double headRotation=0;
double LarmRotation=0;
double RarmRotation=0;
double bodyY=0;
double cameraX=0;
double cameraY=0;
double cameraZoom=0;
/**** Function which draws the robot's head****/
void createHead(int rotation){
	glColor3f(0.5, 0.75, 0.0);
	glPushMatrix();
		glTranslatef(0,0.0,BODY_HEIGHT);
		glScalef(HEAD_RADIUS, HEAD_RADIUS, HEAD_HEIGHT);
		glRotatef(rotation, 0,0,1.0);
		gluCylinder(obj, 1.0, 1.0,1.0, 8, 8);
	glPopMatrix();
}
/**** Function which draws the objects on the ground ****/
void placeObjects(){
gluQuadricDrawStyle(obj,GLU_FILL);
glColor3f(1.0,0,0);
glPushMatrix();
glTranslatef(0.8,0.15,0);
glScalef(0.05,0.05,0.05);
gluCylinder(obj,1.0,1.0,1.0,6,6);
glPopMatrix();

glColor3f(0.0,1.0,0);
glPushMatrix();
glTranslatef(0.12,0.5,0);
glScalef(0.05,0.05,0.05);
gluCylinder(obj,1.0,1.0,1.0,6,6);
glPopMatrix();

glColor3f(0.0,0,1.0);
glPushMatrix();
glTranslatef(-0.8,0.25,0);
glScalef(0.05,0.05,0.05);
gluCylinder(obj,1.0,1.0,1.0,6,6);
glPopMatrix();
}
/**** Function to draw the robot's body****/
void createBody(){
	glColor3f(0,0.5,0.75);
	glPushMatrix();
		glTranslatef(0,0,BODY_HEIGHT/2.0);
		glScalef(BODY_WIDTH, BODY_WIDTH, BODY_HEIGHT);
		glutWireCube(1.0);
	glPopMatrix();
}
/**** Function to draw an arm****/
void createArm(double rotation, int i){
	glColor3f(0.75,0,0.5);
	

	//rotation for whole arm system	
	glPushMatrix();
	glTranslatef(i*BODY_WIDTH/3, 0,BODY_HEIGHT);
	
	glRotatef(rotation, 0,1.0,0);
	//just for lower arm
	glPushMatrix();
	glTranslatef(i*UPPER_ARM_LENGTH*BODY_HEIGHT,0.0,-1.0*UPPER_ARM_LENGTH/2);
	glScalef(UPPER_ARM_WIDTH,UPPER_ARM_WIDTH,UPPER_ARM_LENGTH);
	glutWireCube(1.0);
	glPopMatrix();
	//upper Arm
	glPushMatrix();
	glScalef(UPPER_ARM_LENGTH, UPPER_ARM_WIDTH, UPPER_ARM_WIDTH);
	glutWireCube(1.0);
	glPopMatrix();
	glPopMatrix();

}
void display(void){
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	gluQuadricDrawStyle(obj,GLU_LINE);
	glPushMatrix();
		//camera controls
		glRotatef(angle[0],1.0,0.0,0.0);
		glRotatef(angle[1],0.0,1.0,0.0);
		glRotatef(angle[2],0.0,0.0,1.0);
		//for first person robo-view
		if(mode==1){
			gluLookAt(0,0,(BODY_HEIGHT/2)+(HEAD_HEIGHT/2),1,1,1,0,0,1);
		}
		//moves the scene to a more sensible location
		glTranslatef(cameraX,cameraZoom,FLOOR_HEIGHT+cameraY);
		glPushMatrix();
		glTranslatef(0,0,bodyY);
		createHead(headRotation);
		
		createBody();
		createArm(LarmRotation,1);
		createArm(RarmRotation,-1);
		glPopMatrix();
		placeObjects();
	glPopMatrix();

	
	glFlush();
	glutSwapBuffers();

}


void init(){
	glClearColor(0,0,0,1);
	obj=gluNewQuadric();
	
	glOrtho(-2,2,-2,2,-2,2);
	part=8;
	headRotation=0;
	bodyY=0;
	LarmRotation=0;	
	RarmRotation=0;
}
void mouse(int btn, int state, int x, int y){
	//the part variable determines which body part is moving
	switch(part){
		default:break;
		
			//case for the head
		case(0):
			if(btn==GLUT_LEFT_BUTTON&&state==GLUT_DOWN){
				if(headRotation>=360) headRotation=0;
				headRotation+=5.0;
			}
			if(btn==GLUT_RIGHT_BUTTON&&state==GLUT_DOWN){
				if(headRotation<=0) headRotation=360;
				headRotation-=5.0;
			}
		break;
		//case for body movement
		case(1):
			if(btn==GLUT_LEFT_BUTTON&&state==GLUT_DOWN){
			bodyY+=0.05;
			}
			if(btn==GLUT_RIGHT_BUTTON&&state==GLUT_DOWN){
			bodyY-=0.05;
			}
		break;
		//cases for arms
		case(2):
			if(btn==GLUT_LEFT_BUTTON&&state==GLUT_DOWN){
			LarmRotation+=3;
			}
			if(btn==GLUT_RIGHT_BUTTON&&state==GLUT_DOWN){
			LarmRotation-=3;
			}
		break;
		case(3):
			if(btn==GLUT_LEFT_BUTTON&&state==GLUT_DOWN){
			RarmRotation+=3;
			}
			if(btn==GLUT_RIGHT_BUTTON&&state==GLUT_DOWN){
			RarmRotation-=3;
			}
		break;
	}

}
void reshape(){}
void menu(int id){
	if(id == 1 ) part=0;//head
	if(id == 2) part=1;//body
	if(id == 3 ) part=2;//left arm
	if(id==4) part =3;//right arm
	if(id==5) part =4;//left thumb
	if(id==6) part =5;//right thumb
	if(id ==7 ) exit(0);

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

	if (key =='E' | key =='e'){
		switch(mode){
			case(0):
			if(angle[1]>=360.0)angle[1]=0;
			angle[1]+=3.0;
			break;
		}
	}
	if (key =='Q' | key =='q'){
		switch(mode){
			case(0):
			if(angle[1]<=0)angle[1]=360;
			angle[1]-=3.0;
			break;
		}
	}
	if (key =='A' | key =='a'){
		//switch(mode){
			//case(0):
			if(angle[2]>=360.0)angle[2]=0;
			angle[2]+=3.0;
			//break;
		//}
	}
	if (key =='D' | key =='d'){
		//switch(mode){
			//case(0):
			if(angle[2]<=0)angle[2]=360;
			angle[2]-=3.0;
			//break;
		//}
	}
	/****camera position is controlled with ijkl, zoom with YU****/
	if (key =='I' | key =='i'){
		switch(mode){
			case(0):
				cameraY-=0.05;
			break;
		}
			
	}
	if( key=='K'| key=='k'){
		switch(mode){
			case(0):
			cameraY+=0.05;
			break;
				
		}
	}

	if (key =='J' | key =='j'){
		switch(mode){
			case(0):
			cameraX+=0.05;
			break;
		}
	}
	if (key =='L' | key =='l'){
		switch(mode){
			case(0):
			cameraX-=0.05;
			break;
		}
	}
	if(key=='U' | key=='u'){
		cameraZoom+=0.05;
	}
	if(key=='Y'| key=='y') cameraZoom-=0.05;
	/***menus in the lab were broken, so holding these buttons and using the mouse will rotate the head, move the body up and down, or rotate the arms***/
	if(key =='o'|key=='O') menu(1);
	if(key=='p'|key=='P') menu(2);
	if(key=='x'|key=='X') menu(3);
	if(key=='z'|key=='Z') menu(4);
	if(key=='g'|key=='G'){
		 mode=1;
	}
	glutPostRedisplay();

}
void main(int argc, char **argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB| GLUT_DEPTH);
	glutInitWindowSize(500,500);
	glutCreateWindow("Assignment 3");
	init();
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	//glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutCreateMenu(menu);
	glutAddMenuEntry("head", 1);
	glutAddMenuEntry("body",2);
	glutAddMenuEntry("left arm",3);
	glutAddMenuEntry("right arm",4);
	glutAttachMenu(GLUT_MIDDLE_BUTTON);
	glutMainLoop();

}
