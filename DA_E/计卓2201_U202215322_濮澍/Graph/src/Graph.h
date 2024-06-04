#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
//#include "Topo_Fi_Heap.h"


#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define MAX_VERTEX_NUM 20
#define MAX_KEY 50
typedef int status;
typedef int KeyType; 
typedef enum {DG,DN,UDG,UDN} GraphKind;//DAG
typedef struct {
	  KeyType  key;
	  char others[20];
} VertexType; //顶点类型定义

typedef KeyType Map[MAX_KEY];

typedef struct ArcNode {         //表结点类型定义
	  int adjvex;              //顶点位置编号 
	  struct ArcNode  *nextarc;	   //下一个表结点指针
} ArcNode;
typedef struct VNode{				//头结点及其数组类型定义
	  VertexType data;       	//顶点信息
	  ArcNode *firstarc;      	 //指向第一条弧
	} VNode,AdjList[MAX_VERTEX_NUM];
typedef  struct {  //邻接表的类型定义
	AdjList vertices;     	 //头结点数组
	int vexnum,arcnum;   	  //顶点数、弧数
	GraphKind  kind;        //图的类型
	} ALGraph;
typedef struct {
	struct{
		char name[20];
		ALGraph G;
	}elem[20];
	int length = 0;
}GRAPHS;

using namespace std;

status CreateGraph(ALGraph &G,VertexType V[],KeyType VR[][2]);
status DestroyGraph(ALGraph &G);
int LocateVex(ALGraph G,KeyType u);
status PutVex(ALGraph &G,KeyType u,VertexType value);
int FirstAdjVex(ALGraph G,KeyType u);
int NextAdjVex(ALGraph G,KeyType v,KeyType w);
status InsertVex(ALGraph &G,VertexType v);
status DeleteVex(ALGraph &G,KeyType v);
status InsertArc(ALGraph &G,KeyType v,KeyType w);
status DeleteArc(ALGraph &G,KeyType v,KeyType w);
status DFSTraverse(ALGraph &G,void (*visit) (VertexType));
status BFSTraverse(ALGraph &G,void (*visit) (VertexType));
void DFS(ALGraph &G,VNode V, int (&a)[1000],int i, void (*visit) (VertexType));
status SaveGraph(ALGraph G, char FileName[]);
status LoadGraph(ALGraph &G, char FileName[]);
int * Path_Length_to_v(ALGraph G,KeyType v);
void DFS_LEN(ALGraph G,int location,int len,int * &path);
int * VerticesSetLessThanK(ALGraph &G,KeyType v,int k);
int ShortestPathLength(ALGraph G,KeyType v,KeyType w);// Using DFS
int ConnectedComponentsNums(ALGraph G);
int Strongly_ConnectedComponentsNums(ALGraph G);
void DFSCount(ALGraph G,VNode V, int (&visited)[1000], int i);
int DFSCountCCP(ALGraph G);
int * TopologicalSort(ALGraph G);
void visit(VertexType v);
status Add_GRAPHS(GRAPHS &P,char GraphName[]);
status Remove_GRAPHS(GRAPHS &P,char GraphName[]);
status Locate_and_Modi_GRAPHS(GRAPHS &P,ALGraph &G,char GraphName[]);
status Traverse_GRAPHS(GRAPHS &P);