#include <GL/glut.h>
#include <vector>
#include <string>
using namespace std;
//g++ Obj_Graphics.cpp ~/Documents/CPP/My_H/2D_GL/GL_2D_BASIC.cpp -lGL -lglut -lGLU
struct vertex2i{int x,y;};
struct vertex2f{float x,y;};
struct vertex3f{float x,y,z;};
int iSpeed;
void displayCB();
class Object2D;
class Vertex2i
{
	private:
		vertex2i V;
	public:
		Vertex2i(int a,int b){V.x=a;V.y=b;}
		Vertex2i(vertex2i x){V=x;}
		Vertex2i operator+(Vertex2i operand)
		{return Vertex2i(this->V.x+operand.V.x,this->V.y+operand.V.y);}
		friend class Object2D;
		friend void ::keyCB(unsigned char key, int x, int y);
		friend void ::translate2D(Object2D *Obj,vertex2i direction);
		friend void ::basicMove(Object2D *Obj,unsigned char key);
};
class Object2D
{
	private:
		string name;
		string tag;
		vector<vertex2i> polygon;
		vertex3f colour;
		vector<unsigned char> actionKeys;
	public:
		Object2D(vector<Vertex2i> set, string _name)
		{
			name=_name;
			for(int i =0;i<set.size();i++)
				polygon.push_back(set[i].V);
		}
		Object2D(vector<vertex2i> set, string _name)
		{
			name=_name;
			for(int i =0;i<set.size();i++)
				polygon.push_back(set[i]);
		}
		void setColour(float r,float g,float b)
		{
			colour.x=r;
			colour.y=g;
			colour.z=b;
		}
		void setActionKey(unsigned char key){actionKeys.push_back(key);}
		void setTag(string T){tag=T;}
		string getTag(){return tag;}
		short isMe(string _name){if(name==_name)return 1;return 0;}
		friend void ::displayCB();
		friend void ::setProperty(string property,Object2D Obj,float values);
		friend void ::keyCB(unsigned char key, int x, int y);
		friend void ::motion2D(Object2D *Obj,vertex2i motion,vertex2i direction);
		friend void ::translate2D(Object2D *Obj,vertex2i direction);
		friend void ::basicMove(Object2D *Obj,unsigned char key);
};
vector<Object2D> WorldObjects;
void Create_Object(vector<Vertex2i> set,string name)
{
	WorldObjects.push_back(Object2D(set,name));
}
//---------------------OBJECT PROPERTY ASSIGNERS-------
void setProperty(string property,Object2D *Obj,float values[]=NULL,int N=0)
{
	if(property=="colour")
		Obj->setColour(values[0],values[1],values[2]);
	else if(property=="actionKey")
		while(N>0)
		{
			Obj->setActionKey((unsigned char)((int)(values[N-1])));
			N--;
		}
	else if(property.substr(0,4)=="tag:")
		Obj->setTag(property.substr(4));
	else if(property=="speed")
		iSpeed=values[0];
}
void SET(string ObjName,string property,float values[]=NULL,int N=0)
{
	for(int i=0;i<WorldObjects.size();i++)
		if(WorldObjects[i].isMe(ObjName))
			setProperty(property,&WorldObjects[i],values,N);
}
//------------------------STANDARD POLYGONS--------------
vector<Vertex2i> square(int size,int x,int y) 
{
	vertex2i start_coord={x,y};
	vector<Vertex2i> square;
	square.push_back(Vertex2i(start_coord));
	square.push_back(Vertex2i(start_coord)+Vertex2i(size,0));
	square.push_back(Vertex2i(start_coord)+Vertex2i(size,size));
	square.push_back(Vertex2i(start_coord)+Vertex2i(0,size));
	return square;
}
vector<Vertex2i> rect(int length,int breadth,int x,int y)
{
	vertex2i start_coord={x,y};
	vector<Vertex2i> rect;
	rect.push_back(Vertex2i(start_coord));
	rect.push_back(Vertex2i(start_coord)+Vertex2i(length,0));
	rect.push_back(Vertex2i(start_coord)+Vertex2i(length,breadth));
	rect.push_back(Vertex2i(start_coord)+Vertex2i(0,breadth));
	return rect;
}
//-----------------------------STANDARD ACTION FUNCTIONS
void motion2D(Object2D *Obj,vertex2i motion,vertex2i direction)
{
	;
}
void translate2D(Object2D *Obj,vertex2i direction)
{
	for(int i=0;i<Obj->polygon.size();i++)
	{
		Obj->polygon[i]=(Vertex2i(Obj->polygon[i])+Vertex2i(direction)).V;
	}
}
//----------------------STANDARD PLAYER FUNCTION----
void basicMove(Object2D *Obj,unsigned char key)
{
	if(key=='d'|key=='D')
		translate2D(Obj,Vertex2i(iSpeed,0).V);
	if(key=='w'|key=='W')
		translate2D(Obj,Vertex2i(0,iSpeed).V);
	if(key=='s'|key=='S')
		translate2D(Obj,Vertex2i(0,-iSpeed).V);
	if(key=='a'|key=='A')
		translate2D(Obj,Vertex2i(-iSpeed,0).V);
	displayCB();
}
//-----------------------------------RENDERING PATHS AND ROUTINES-------
void displayCB()
{
	glClear(GL_COLOR_BUFFER_BIT);
	for(int x=0;x<WorldObjects.size();x++)
	{

		glColor3f(WorldObjects[x].colour.x,WorldObjects[x].colour.y,WorldObjects[x].colour.z);
		glBegin(GL_POLYGON);	
		for(int i=0;i<WorldObjects[x].polygon.size();i++)
			glVertex2i(WorldObjects[x].polygon[i].x,WorldObjects[x].polygon[i].y);
		glEnd();
		glutSwapBuffers();
	}
	//glFlush();
}
void keyCB(unsigned char key, int x, int y)
{
	if( key == 'q' )exit(0);
	for( int i =0;i<WorldObjects.size();i++)
	{
		if(WorldObjects[i].getTag()=="Player")
			basicMove(&WorldObjects[i],key);
	}
	
}
/*	g++ <file>.cpp -lGL -lglut -lGLU */
void GL_main(int argc, char *argv[],int x,int y,float background[])
{
	int win;
	glutInit(&argc, argv);	
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(x,y);
	win = glutCreateWindow("Polygon");	
	glClearColor(background[0],background[1],background[2],background[3]);	
	gluOrtho2D(0,x,0,y);		
	glutDisplayFunc(displayCB);
	glutKeyboardFunc(keyCB);		
	glutMainLoop();		
}
void Run_Engine(int x,int y,int argc, char *argv[],float background[])
{
	GL_main(argc,argv,x,y,background);
}
