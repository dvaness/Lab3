#ifndef GRAPHM_H
#define GRAPHM_H

#include "nodedata.h"

class GraphM
{
public:
	GraphM();
	buildGraph();
	insertEdge();
	removeEdge();
	findShortestPath();
	displayAll();
	display();

private:
	struct TableType
	{
		bool visited;	//whether or not the node has been visited
		int dist;		//current known shortest distance from source
		int path;		//previous node in path of min dist
	}

	NodeData[MAXNODES]			//data for graph nodes information
	int C[MAXNODES][MAXNODES];	//Cost array, the adjacency matrix
	int size;					//number of nodes in the graph
	TableType T[MAXNODES][MAXNODES];	//stores visited, distance, path
};
#endif