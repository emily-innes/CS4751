#include <GL/glut.h>
#include<math.h>
#include <stdio.h>
double width=250.0;
double height=250.0;
double x1, x2, x3;
double y,y2,y3;
int n=0;
int MAX_LEVEL =5;
void init (void){
	double angle;
	glClearColor (1.0,1.0,0.0,0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0,1.0,0.0,1.0,-1.0,1.0);
	x1=width/4.0;
	x2=width*3.0/4.0;
	//printf("x1 %f x2 %f",x1,x2);
	y=height/4.0;
	double len=x2-x1;
	y2=y;
  	angle=atan((y2-y)/(x2-x1));
	//printf("angle %f",angle);
	x3=x1+len*cos(angle+60*M_PI/180.0);
	y3=y+len*sin(angle+60*M_PI/180.0);
	//printf("{ %f , %f} { %f , %f} { %f , %f}",x1, y, x3, y3, x2, y2);
}
/*void divideSegment(double x1, double y1, double x2, double y2, int level){
	double len=(x2-x1)/3.0;
	double angle=atan((y2-y1)/(x2-x1));
	double x3,y3;
	x1=len*cos(angle);
        x2=len*2.0*cos(angle);
	x3=x1+len*cos((60+angle)*M_PI/180.0);
	y1=len*sin(angle);
	y2=len*2.0*sin(angle);
	y3=y1+len*sin((60+angle)*M_PI/180.0);
	printf("test1");
	//xPoints[n]=x1;
	//yPoints[n]=y1;
	printf("test2");
	//n++;
	if(level>0){
		divideSegment(x1,y1,x3,y3,level-1);
	}
	//xPoints[n]=x3;
	//yPoints[n]=y3;
	//n++;
	if(level>0){
		divideSegment(x3,y3,x2,y2,level-1);
	}
	//xPoints[n]=x2;
	//yPoints[n]=y2;
	//n++;
  
}*/
void drawVertices(double startx, double starty, double endx, double endy, int level){
	double x1,y,midx,midy, x2,y2;
	double len= sqrt(pow((endx-startx),2)+pow((endy-starty),2));
	//printf("length: %f",len);
	double angle=atan((endy-starty)/(endx-startx));
	if(angle==-0.0){
		 angle=M_PI;
	}
	//printf("endy %f starty %f endx %f startx %f", endy, starty, endx, startx);
	//printf("angle %f",angle*180/M_PI);
	//glVertex3f(startx,starty,0.0);
	if(level>0){
		//printf("adding :%f + %f",startx, (len/3.0)*cos(angle*M_PI/180.0));
		
		x1=startx+(len/3.0)*cos(angle);
		y=starty+(len/3.0)*sin(angle);
		drawVertices(startx,starty,x1,y,level-1);
		//printf("Point 2: { %f, %f }",midx,midy);
		glVertex3f(x1,y,0.0);
		//glVertex3f(x1,y,0.0);
		midx=x1+(len/3.0)*cos((angle+60*M_PI/180));
		midy=y+(len/3.0)*sin((angle+60*M_PI/180));
		//printf("Point 3: { %f, %f }",midx,midy);
		drawVertices(x1,y,midx,midy,level-1);
		glVertex3f(midx,midy,0.0);
		//glVertex3f(midx,midy,0.0);
		x2=endx-(len/3.0)*cos(angle);
		y2=endy-(len/3.0)*sin(angle);
		//printf("Point 4: { %f, %f }",midx,midy);
		drawVertices(midx,midy,x2,y2,level-1);
		glVertex3f(x2,y2,0.0);
		//glVertex3f(x2,y2,0.0);
		drawVertices(x2,y2,endx,endy,level-1);
		
	}
	//glVertex3f(endx,endy,0.0);
	//printf("Point 4: { %f, %f }",endx,endy);
	//glVertex3f(endx,endy,0.0);
	
}
void display (void){
  glClear (GL_COLOR_BUFFER_BIT);
  glColor3f(0.0,0.0,1.0);
  //printf("{ %f , %f} { %f , %f} { %f , %f}",x1, y, x2, y, x3, y2);
	glBegin(GL_LINES);
		//printf("Point 1: { %f, %f }",x1,y);	
		drawVertices(x1,y,x3,y3,n);
		//glVertex3f(x3,y3,0.0);
		drawVertices(x3,y3,x2,y2,n);
		//glVertex3f(x2,y2,0.0);
		drawVertices(x2,y2,x1,y,n);
		//glVertex3f(x3,y3,0.0);
		//drawVertices(x3,y3,x2,y2,1);
		//glVertex3f(x2,y2,0.0);
		//drawVertices(x2,y2,x1,y,1);
		//glVertex3f (x3, y3, 0.0);
		//drawVertices(x3,y3,x2,y2,1);
		//glVertex3f (x2, y2, 0.0);
		//drawVertices(x2,y2,x1,y,1);
	glEnd();
  glFlush();
 

}


void mouse(int btn, int state, int x, int y){
	if (btn==GLUT_RIGHT_BUTTON && state==GLUT_DOWN) exit(0);
	if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN){
		n=(n+1)%MAX_LEVEL;
		printf("level %d", n);
		glutPostRedisplay();
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

}
  
int main (int argc, char** argv){

  glutInit(&argc, argv);
  glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(width,height);
  glutInitWindowPosition(100,100);
  glutCreateWindow("Assignment 1");
  glutMouseFunc (mouse);
  glutKeyboardFunc(keyboard);
  glutReshapeFunc(reshape);
  init();
  glutDisplayFunc(display);
  glutMainLoop();
  return 0;
}
