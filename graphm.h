#ifndef GRAPHM_H
#define GRAPHM_H

#include "nodedata.h"
#include <iostream>
#include <climits>

class GraphM
{
	static const int MAXNODES = 100;
public:
	GraphM();
	void makeEmpty();
	void buildGraph(istream&);
	void insertEdge();
	void removeEdge();
	void findShortestPath(int[][MAXNODES], int);
	void displayAll();
	void display();
	void printData()const;

private:
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