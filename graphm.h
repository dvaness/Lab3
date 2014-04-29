#ifndef GRAPHM_H
#define GRAPHM_H

#include "nodedata.h"
#include <iostream>
#include <limits.h>
#include <iomanip>

class GraphM
{
	static const int MAXNODES = 100;
public:
	GraphM();
	void makeEmpty();
	void buildGraph(istream&);
	void insertEdge(int,int,int);
	void removeEdge(int,int);
	void findShortestPath();
	void displayAll()const;
	void display(int,int)const;
	void printData()const;
	void printAdj()const;

private:
	int findMin(int)const;
	void shortestPathHelper(int);
	struct TableType
	{
		bool visited;	//whether or not the node has been visited
		int dist;		//current known shortest distance from source
		int path;		//previous node in path of min dist
	};
	
	NodeData data[MAXNODES];			//data for graph nodes information
	int adjMatrix[MAXNODES][MAXNODES];	//Cost array, the adjacency matrix
	int size;					//number of nodes in the graph
	TableType T[MAXNODES][MAXNODES];	//stores visited, distance, path
};
#endif
