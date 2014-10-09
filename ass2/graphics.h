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
	int i,j,x0,y0,d1,d2;
	x0=r;
	y0=0;
	glBegin(GL_POINTS);
		//plot all of the points at npi/2
		glVertex3i(0+x,r+y,0);
		glVertex3i(0+x,-1*r+y,0);
		glVertex3i(r+x,0+y,0);
		glVertex3i(-1*r+x,0+y,0);
		//calculate points for one octant
		while(x0>=y0){
			//decision variables
			d1=abs(pow(x0-1,2)+pow(y0+1,2)-pow(r,2));
			d2=abs(pow(x0,2)+pow(y0+1,2)-pow(r,2));
			y0++;
			if(d1<d2){
				x0--;
			}
			//draw points in each octant
			glVertex3i(x0+x,y0+y,0);
			glVertex3i(-1*x0+x,y0+y,0);
			glVertex3i(-1*x0+x,-1*y0+y,0);
			glVertex3i(x0+x,-1*y0+y,0);
			
			glVertex3i(y0+x,x0+y,0);
			glVertex3i(-1*y0+x, x0+y,0);
			glVertex3i(-1*y0+x,-1*x0+y,0);
			glVertex3i(y0+x,-1*x0+y,0);
		}

	glEnd();
}

void clipLine(int x1, int y1, int x2, int y2, int xmax, int ymax, int xmin, int ymin){
	int noClip=0;
	int lClip=1;
	int rClip=2;
	int bClip=4;
	int tClip=8;
	int clip1=0;
	int clip2=0;
	if(x1<xmin) clip1|=lClip;
	else if (x1>xmax) clip1|=rClip;
	if(y1<ymin) clip1|=bClip;
	else if (y1>ymax) clip1|=tClip;
	if(x2<xmin) clip2|=lClip;
	else if (x2>xmax) clip1|=rClip;
	if(y2<ymin) clip2|=bClip;
	else if (y2>ymax) clip2|=tClip;
	printf("outcode 1: %d outcode 2: %d", clip1,clip2);
	if(!(clip1|clip2)){
		//trivially accepted
		bresenham(x1,y1,x2,y2);
	}
	else{
		if(!(clip1&clip2)){//and is 0
			int xclip, yclip, code, m;
			m=(y2-y1)/(x2-x1);
			if(clip1) code=clip1;
			else code=clip2;
			if(code&tClip){
				yclip=ymax;
				xclip=x1+ (1/m)*(ymax-y1);
			}
			if(code&bClip){
				yclip=ymin;
				xclip=x1+(1/m)*(ymin-y1);
			}
			if(code&rClip){
				xclip=xmax;
				yclip=y1+m*(xmax-x1);
			}
			if(code&lClip){
				xclip=xmin;
				yclip=y1+m*(xmin-x1);
			}
			if(clip1==code){ 
				clipLine(xclip,yclip,x2,y2, xmax, ymax, 			xmin,ymin);
			}
			else{
				clipLine(x1,x2,xclip, yclip,xmax, ymax, 			xmin,ymin);
			}
		}
	}
			
				
}



