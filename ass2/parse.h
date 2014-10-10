#include <stdio.h>
#include <GL/glut.h>

int readInput(int* x, int* y, int* x2, int* y2, int* r, int* type){
	char str[64];
	int i,j,a,b,c,d,e,f;
	char id[1];
	//while(1){
		scanf("%s",id);
		//printf("%s",id);
		//printf("%d,%d,%d,%d", *u,*v,*w,*x,*y,*z);
		//printf("id %s",id);
		// If a line was inputted
		if(id[0]=='L'||id[0]=='l'){
		scanf("%d,%d,%d,%d", x,y,x2,y2);
			*type=1;
			*r=0;
			return 1;
		}
		//if a circle was inputted
		if(id[0]=='C'||id[0]=='c'){
		scanf("%d,%d,%d", x,y,r);
			*type=2;
			*x2=0;		
			*y2=0;
			return 1;
			
		}
		
		if(id[0]=='Z'||id[0]=='z'){
			return 0;
		}
		
	//}

}

int* readPolygonInput(int* size, int *read){
	static int vertices[128];
	int x,y;
	char id[1];
	scanf ("%s", id);
	if(id[0]=='P' || id[0]=='p'){
		
		/*for(*size=0;*size<128;*size+=2){
			scanf(" %d,%d" ,&x,&y);
			printf("(%d,%d)", x,y);
			vertices[*size]=x;
			vertices[(*size)+1]=y;
			printf("test\n");
		}*/
		char string[128];
		scanf("%s",string);
		printf("%s\n",string);
		while(string[0]!='\n'){
			printf("%s",string);
			scanf(string,"%d,%d" ,&x,&y);
			//printf("(%d,%d)", x,y);
			vertices[*size]=x;
			vertices[(*size)+1]=y;
			*size=*size+2;
			scanf(string,"%c",string);
		}
		return vertices;
	}
	if(id[0]=='Z'||id[0]=='z'){
			*read=0;
			return 0;
	}

}
