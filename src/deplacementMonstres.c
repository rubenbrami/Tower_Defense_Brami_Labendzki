#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <string.h>


//#include "deplacementMontres.h"

static float varx = 0.;
static float vary = 0.;
static float varx2 = 0.;
static float vary2 = 0.;
static float speed = 1;

static float curx = -4;
static float cury = 1;

static float route_x = 0;
static float route_y = 0;


static int dest1 = 4;
static int dest2 = 3;
static int dest3 = 3;

static float px = 0.013333;
static float x_in ,y_in ;
static float x_out, y_out;
static float x_1, y_1;
static float x_2, y_2;
static float x_4, y_4;


static float traductionX(float x){
	return (x-400)/75.0;
}

static float traductionY(float y){
	return -(y-300)/75.0;
}

	x_in=traductionX(100.0);
	y_in=traductionY(225.0);
	x_out=traductionX(700.0);
	y_out=traductionY(225.0);
	x_1=traductionX(400.0);
	y_1=traductionY(225.0);
	x_2=traductionX(400.0);
	y_2=traductionY(75.0);
	x_4=traductionX(400);
	y_4=traductionY(525);



void MoveMonster(){
if (curx==x_in && cury==y_in)
        {
        	if (dest1==1){
	        	route_x = x_1 - curx;
	        	route_y = y_1 - cury;
	        	if(varx<=route_x-px){
	        		varx += route_x/84*speed;
	        	}
	        	if (varx>= route_x){
	        		curx= x_1;
	        		cury= y_1;
	        		printf("arrivé en 1 depuis 0 \n");;
	        	}
        	}

	        if (dest1==2){
	        	route_x = x_2 - curx;
	        	route_y = y_2 - cury;
	        	if(varx<=route_x-px && vary<=route_y-px){
	        		varx += route_x/100;
	        		vary += route_y/100;
	        	}
	        	if(varx>=route_x-0.001 && vary>=route_y-0.001){
	        		curx= x_2;
	        		cury= y_2;
	        		printf("arrivé en 2 depuis 0 \n");
	        	}
	        }
	        if (dest1==4){
	        	route_x = x_4 - curx;
	        	route_y = y_4 - cury;
	        	if(varx<=route_x-px && vary>=route_y-px){
	        		varx += route_x/126*speed;
	        		vary += route_y/126;
	        	}
	        	if(varx>=route_x-0.001 && vary>=route_y-0.001){
	        		curx= x_4;
	        		cury= y_4;
	        		printf("arrivé en 4 depuis 0 \n");
	        	}
	        }
        }
         
        if (curx==x_2 && cury==y_2){
        	
        	if (dest2 == 1){
        		route_x = x_1 - curx;
        		route_y = y_1 - cury;
        		if(varx2<=route_x && vary2>=route_y+px){
	        		varx += route_x/45*speed;
	        		vary2 += route_y/45*speed;
	        	}
	        	if(varx2==route_x && vary2==route_y){
	        		curx= x_1;
	        		cury= y_1;
	        		printf("arrivé en 1 depuis 2 \n");
	        	}
	        	varx=varx2+(x_2-x_in);
	        	vary=vary2+(y_2-y_in);
        	}
        	if (dest2 == 3 ){
        		route_x = x_out - curx;
        		route_y = y_out - cury;
        		if(varx2<=route_x-px && vary2>=route_y){
	        		varx2 += route_x/100*speed;
	        		vary2 += route_y/100*speed;
	        	}
	        	if(varx2>=route_x-px && vary2<=route_y+px){
	        		curx= x_out;
	        		cury= y_out;
	        		printf("arrivé en 3 depuis 2 \n");
	        	}
	        	varx=varx2+(x_2-x_in);
	        	vary=vary2+(y_2-y_in);
        	}
        	
        }
        
        if (curx==x_4 && cury==y_4){
        	if (dest2 == 3){
        		route_x = x_out - curx;
        		route_y = y_out - cury;
        		if(varx2<=route_x && vary2<=route_y-px){
	        		varx2 += route_x/126*speed;
	        		vary2 += route_y/126*speed;
	        	}
	        	if(varx2>=route_x && vary2>=route_y-px){
	        		curx= x_out;
	        		cury= y_out;
	        		printf("arrivé en 3 depuis 4 \n");
	        	}
	        	varx=varx2+(x_1-x_in);
	        	vary=vary2-4;

        	}	        	
        }
        if (dest3 == 3){
        	if(dest2==2 && (curx==x_2 && cury==y_2)){
        		route_x = x_out - curx;
        		route_y = y_out - cury;
        		if(varx2<=route_x-px && vary2>=route_y-px){
	        		varx2 += route_x/100*speed;
	        		vary2 += route_y/100*speed;
	        	}
	        	if(varx2>=route_x-px && vary2>=route_y-px){
	        		curx= x_out;
	        		cury= y_out;
	        		printf("arrivé en 3 depuis 2(et1)\n");
	        	}
	        	varx=varx2+(x_2-x_in);
	        	vary=vary2;
        	}
        	if(dest2==1 && (curx==x_1 && cury==y_1)){
        		route_x = x_out - curx;
        		route_y = y_out - cury;
        		if(varx2<=route_x-px && vary2<=route_y){
	        		varx2 += route_x/84*speed;
	        		vary2 += route_y/84*speed;
	        	}
	        	if(varx2>=route_x && vary2==route_y-2){
	        		curx= x_out;
	        		cury= y_out;
	        		printf("arrivé en 3 depuis 1(et2) \n");
	        	}
	        	varx=varx2+(x_2-x_in);
	        	vary=vary2+(y_2-y_in);
        	}
        	if(dest2==4 && (curx==x_4 && cury==y_4)){
        		route_x = x_out - curx;
        		route_y = y_out - cury;
        		if(varx2<=route_x-px && vary2<=route_y){
	        		varx2 += route_x/84*speed;
	        		vary2 += route_y/84*speed;
	        	}
	        	if(varx2>=route_x && vary2==route_y-2){
	        		curx= x_out;
	        		cury= y_out;
	        		printf("arrivé en 3 depuis 4(et1) \n");
	        	}
	        	varx=varx2+(x_2-x_in);
	        	vary=vary2+(y_2-y_in);
        	}
        }
    }
