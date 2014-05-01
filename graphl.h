#ifndef GRAPH_L_H_
#define GRAPH_L_H_


#include "nodedata.h"
#include <iostream>
#include "limits.h"
#include <iomanip>

struct EdgeNode;
struct GraphNode
{
	EdgeNode* edgeHead;	//head of the list of Edges
	NodeData data;
};
struct EdgeNode
{
	int adjGraphNode;
	EdgeNode* nextEdge;
	EdgeNode(int adj)
	{
		adjGraphNode = adj;
	}
};

class GraphL
{
	static const int MAXNODES = 100;
public:
	GraphL();
	~GraphL();
	void buildGraph(istream&);
	void makeEmpty();
	void displayGraph()const;
	void depthFirstSearch();
	void addEdge(int, int);

	void printAdjListData()const;
private:
	GraphNode adjList[MAXNODES];
	int size;

};
#endif