#include <GL/glut.h>
#include <math.h>
 struct line{
	int x1,x2,y1,y2;
};
 struct circle{
	int x,y,r;
};
void swap(int* a, int* b){
	int hold;
	hold=*a;
	*a=*b;
	*b=hold;
}
void bresenham(int x0, int y0, int x1, int y1){
	int delx, dely,d,k,x,y;
	int inverse=0;
	k=0;
	if(y0>y1){
		swap(&x0,&x1);
		swap(&y0,&y1);
	}
	
	x=x0;
	y=y0;
	delx=x1-x0;
	dely=y1-y0;
	d=2*dely-delx;
	if(dely>delx){
		//printf("large slope");
		swap(&delx, &dely);
		swap(&x,&y);
		inverse=1;
	}
	glBegin(GL_POINTS);
	//printf("( %d,%d)",x,y);
	glVertex3i(x0,y0,0);
	while(k<abs(delx)){
		//printf("%d\n",k);
		x+=abs(delx)/delx;
		if(d<0){
			d=d+2*dely;
		}
		else{
			y++;
			d=d+2*dely-2*delx;
		}
		//printf("( %d,%d)",x,y);
		if(inverse==0)glVertex3i(x,y,0);
		else{
			glVertex3i(y,x,0);
		}

		k++;
	}
	//printf("( %d,%d)",x1,y1);
	glVertex3i(x1,y1,0);
	glEnd();
}
void midpoint(int x, int y, int r){
//implement pls
}
void clipLine(int x1, int y1, int x2, int y2, int xBound, int yBound){
}
