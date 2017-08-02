#ifndef GL_2D_BASIC_H
#define GL_2D_BASIC_H
/*g++ OpenGL.cpp GL_2D_BASIC.cpp -lGL -lglut -lGLU*/
#include <GL/glut.h>
#include <vector>
#include <string>
using namespace std;
//g++ Obj_Graphics.cpp ~/Documents/CPP/My_H/2D_GL/GL_2D_BASIC.cpp -lGL -lglut -lGLU
#include <GL/glut.h>
#include <vector>
#include <string>
using namespace std;
//g++ Obj_Graphics.cpp ~/Documents/CPP/My_H/2D_GL/GL_2D_BASIC.cpp -lGL -lglut -lGLU
struct vertex2i{int x,y;};
struct vertex2f{float x,y;};
struct vertex3f{float x,y,z;};
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
void Create_Object(vector<Vertex2i> set,string name);
//---------------------OBJECT PROPERTY ASSIGNERS-------
void setProperty(string property,Object2D *Obj,float values[]=NULL,int N=0);
void SET(string ObjName,string property,float values[]=NULL,int N=0);
//------------------------STANDARD POLYGONS--------------
vector<Vertex2i> square(int size,int x,int y);
vector<Vertex2i> rect(int length,int breadth,int x,int y);
//-----------------------------STANDARD ACTION FUNCTIONS
void motion2D(Object2D *Obj,vertex2i motion,vertex2i direction);
void translate2D(Object2D *Obj,vertex2i direction);
//----------------------STANDARD PLAYER FUNCTION----
void basicMove(Object2D *Obj,unsigned char key);
//-----------------------------------RENDERING PATHS AND ROUTINES-------
//void displayCB();
void keyCB(unsigned char key, int x, int y);
/*	g++ <file>.cpp -lGL -lglut -lGLU */
void GL_main(int argc, char *argv[],int x,int y,float background[]);
void Run_Engine(int x,int y,int argc, char *argv[],float background[]);
#endif
