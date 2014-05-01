//---------------------------------------------------------------------------
// GRAPHL.H
// Class for a Graph using an Adjacency List
// Author: Dallas Van Ess
//---------------------------------------------------------------------------
// GraphL class:  includes a few functions relating to a Graph
//   including:
//   -- allows the graph to be built from a .txt file
//   -- allows for insertion of edges
//   -- includes functionality for a depth-first traversal
//   -- includes display function for the entire graph
//
// Assumptions:
//   -- assumes the .txt file being used includes correctly formatted data
//   -- assumes that there will never be more than 100 nodes in the graph
//
//---------------------------------------------------------------------------

#ifndef GRAPHL_H
#define GRAPHL_H


#include "nodedata.h"
#include <iostream>
#include "limits.h"
#include <iomanip>

struct EdgeNode;
//-------------------------- struct GraphNode ---------------------------------
//
// struct to hold the data of an index in the adjancey list
//
struct GraphNode
{
	EdgeNode* edgeHead;	//head of the list of Edges
	NodeData data;
	bool visited;
};
//-------------------------- struct EdgeNode ----------------------------------
//
// struct to hold the data for an Edge in the adjacency list
//
struct EdgeNode
{
	int adjGraphNode;	//the endpoint of the Edge in the adjacency list
	EdgeNode* nextEdge;	// pointer to the next edge in the list of edges
	//constructor for a GraphNode
	EdgeNode(int adj)
	{
		adjGraphNode = adj;
	}
};

class GraphL
{
	static const int MAXNODES = 100;
public:
	//-------------------------- Constructor ----------------------------------
	// Default constructor for class GraphL
	// Preconditions:   None
	// Postconditions:
	//		-- a new Graph is created. sets all Edge lists to NULL and all 
	//		   GraphNodes in the adjacency list to unvisited
	//
	GraphL();
	//-------------------------- Destructor -----------------------------------
	// Destructor for class GraphL
	// Preconditions:   None
	// Postconditions:
	//		-- All memory allocated during runtime is returned to the OS
	//
	~GraphL();
	//-------------------------- makeEmpty ------------------------------------
	// Empties the Graph of memory
	// Preconditions:   None
	// Postconditions:
	//		-- the Graph has been reset to its original state
	void makeEmpty();
	//-------------------------- buildGraph -----------------------------------
	// Builds the Graph
	// Preconditions:   None
	// Postconditions:
	//		-- the Graph has been built including size and adjList
	void buildGraph(istream&);
	
	//-------------------------- displayGraph ---------------------------------
	// display information relating to the graph including, Node number,
	// Node name, and all edges of the Node
	//
	void displayGraph()const;
	//-------------------------- addEdge -----------------------------------
	// insert an edge into the Graph
	// Preconditions:   None
	// Postconditions:
	//		-- a new Edge from fromNode to toNode is inserted into the 
	// 		   adjacency list
	//
	void addEdge(int fromNode, int toNode);
	//-------------------------- depthFirstTrav -----------------------------------
	//
	// displays the depth-first ordering of the Graph
	//
	void depthFirstTrav();
	
private:
	//-------------------------- dfs ------------------------------------------
	//
	// helper method for the depth-first traversal
	//
	void dfs(int, GraphNode);
	GraphNode adjList[MAXNODES];	//the adjacency list for the Graph
	int size;	//the size of the graph

};
#endif