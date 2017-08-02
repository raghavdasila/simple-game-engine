#include <iostream>
//#include <GL/glut.h>
#include "My_H/2D_GL/GL_2D_BASIC.h"

using namespace std;
//g++ Obj_Graphics.cpp ~/Documents/CPP/My_H/2D_GL/GL_2D_BASIC.cpp -lGL -lglut -lGLU

int main(int argc, char *argv[])
{	
	int x=800,y=600,size=100;
	int length=200,breadth=160;
	
	Create_Object(rect(length,breadth,300,100),"rect1");
	Create_Object(square(size,100,y-200),"square1");
	Create_Object(rect(400,10,10,20),"Platform");	
	Create_Object(square(100,400,300),"sq1");	
	
	float colour1[]={0.20,0.163,0.210};
	float colour2[]={1,0.2,0.3};
	float colour4[]={0.9,0.5,1};
	float colour5[]={0.0,1,0.0};
	float colour3[]={1,1,1,1};
	float keys[]={119,87};
	float speed[]={10};
	
	SET(string("rect1"),string("colour"),colour1);
	SET(string("square1"),string("colour"),colour2);
	SET(string("Platform"),string("colour"),colour4);
	SET(string("square1"),string("actionKey"),keys);
	SET(string("sq1"),string("tag:Player"));
	SET(string("square1"),string("speed"),speed);
	SET(string("sq1"),string("colour"),colour5);
	
	SET(string("sq1"),string("tag:Player"));
	
	Run_Engine(x,y,argc,argv,colour3);
	
	return 0;
}

