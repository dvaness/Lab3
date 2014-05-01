//---------------------------------------------------------------------------
// GRAPHM.H
// Class for a Graph using an Adjacency Matrix
// Author: Dallas Van Ess
//---------------------------------------------------------------------------
// GraphM class:  includes a few functions relating to a Graph
//   including:
//   -- allows the graph to be built from a .txt file
//   -- allows for insertion of edges
//   -- allows for removal of edges
//   -- includes functionality to find the shortest path from every node
//	 -- to every other node in the graph
//   -- includes display functions both for the entire graph and for a single
//	 -- path
//
// Assumptions:
//   -- assumes the .txt file being used includes correctly formatted data
//   -- shortest path algorithm does not handle negative path costs
//   -- assumes that there will never be more than 100 nodes in the graph
//
//---------------------------------------------------------------------------

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
	//-------------------------- Constructor ----------------------------------
	// Default constructor for class GraphM
	// Preconditions:   None
	// Postconditions:
	//		-- a new Graph is created. sets size to 0, all values of the
	//		-- adjacency matrix to INT_MAX(infinity), and properly 
	//		-- initializes all members of the TableType structs in
	//		-- the T array
	GraphM();
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
	//		-- the Graph has been built including size and adjMatrix
	void buildGraph(istream&);
	//-------------------------- findShortestPath -----------------------------
	// use Dijakstra's algorithm to find the shortest path from every node to 
	// every other node
	// Preconditions:   None
	// Postconditions:  
	//		-- the TableType array is modified with correct values for the dist
	//		   member and the path member.
	void findShortestPath();
	//-------------------------- insertEdge -----------------------------------
	// insert an edge into the Graph
	// Preconditions:   None
	// Postconditions:
	//		-- a new Edge from fromNode to toNode with a weight of distance
	//		   is inserted into the adjacency matrix
	bool insertEdge(int fromNode,int toNode,int distance);
	//-------------------------- removeEdge -----------------------------------
	// remove an edge from the Graph
	// Preconditions:   None
	// Postconditions:
	//		-- the edge from fromNode to toNode is removed from the adjacency 
	//		   matrix
	bool removeEdge(int fromNode,int toNode);
	
	//-------------------------- displayAll -----------------------------------
	// display a formatted table showing starting node, ending node, the
	// shortest path from the starting node to the ending node, and the path
	// connected to the shortest path.
	void displayAll()const;
	//-------------------------- display --------------------------------------
	// display the path from one node to another found through the shortest
	// path function
	void display(int,int)const;
	
private:
	//-------------------------- displayPath ----------------------------------
	//
	// helper method for displaying a single path
	//
	void displayPath(int, int)const;
	//-------------------------- displayNames ---------------------------------
	//
	// helper method for displaying the NodeData objects for a path
	//
	void displayNames(int,int)const;
	//-------------------------- struct TableType -----------------------------
	//
	// struct to handle necessary data for the shortest path algorithm
	//
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
