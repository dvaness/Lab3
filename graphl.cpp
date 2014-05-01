//---------------------------------------------------------------------------
// GRAPHL.CPP
// Implementation for the GraphL class
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

#include "graphl.h"
//-------------------------- Constructor ----------------------------------
// Default constructor for class GraphL
// Preconditions:   None
// Postconditions:
//		-- a new Graph is created. sets all Edge lists to NULL and all 
//		   GraphNodes in the adjacency list to unvisited
//
GraphL::GraphL()
{
	size = 0;
	for(int i = 0; i < MAXNODES; i++)
	{
		adjList[i].edgeHead = NULL;
		adjList[i].visited = false;
	}
}
//-------------------------- Destructor -----------------------------------
// Destructor for class GraphL
// Preconditions:   None
// Postconditions:
//		-- All memory allocated during runtime is returned to the OS
//
GraphL::~GraphL()
{
	makeEmpty();
}
//-------------------------- makeEmpty ------------------------------------
// Empties the Graph of memory
// Preconditions:   None
// Postconditions:
//		-- the Graph has been reset to its original state
void GraphL::makeEmpty()
{
	EdgeNode* current = NULL;
	for(int i = 1; i <= size; i++)
	{
		while(adjList[i].edgeHead != NULL)
		{
			current = adjList[i].edgeHead->nextEdge;
			delete adjList[i].edgeHead;
			adjList[i].edgeHead = current;
		}
		
	}
	size = 0;
}
//-------------------------- buildGraph -----------------------------------
// Builds the Graph
// Preconditions:   None
// Postconditions:
//		-- the Graph has been built including size and adjList
void GraphL::buildGraph(istream& infile) 
{
   int fromNode, toNode;              // from and to node ends of edge

   makeEmpty();                       // clear the graph of memory 

   infile >> size;                    // read the number of nodes
   if (infile.eof()) return;          // stop if no more data
   
   string s;                          // used to read through to end of line
   getline(infile, s);
   
   // read graph node information
   for (int i=1; i <= size; i++) 
   	{
    	adjList[i].data.setData(infile);
    }

   // read the edge data and add to the adjacency list
   for (;;) {
      infile >> fromNode >> toNode;
      if (fromNode ==0 && toNode ==0) return;     // end of edge data
      // insert the edge into the adjacency list for fromNode
      addEdge(fromNode, toNode);
   }
}
//-------------------------- displayGraph ---------------------------------
// display information relating to the graph including, Node number,
// Node name, and all edges of the Node
//
void GraphL::displayGraph()const
{
	cout << "Graph:" << endl;
	for(int i = 1; i <= size; i++)
	{
		cout << "Node " << i << "	" << adjList[i].data << endl;
		EdgeNode* current = adjList[i].edgeHead;
		while(current != NULL)
		{
			cout << "edge " << i <<" " << current->adjGraphNode << endl;
			current = current->nextEdge;
		}
	}
}
//-------------------------- addEdge -----------------------------------
// insert an edge into the Graph
// Preconditions:   None
// Postconditions:
//		-- a new Edge from fromNode to toNode is inserted into the 
// 		   adjacency list
//
void GraphL::addEdge(int fromNode, int toNode)
{
	EdgeNode* newNode = new EdgeNode(toNode);
	newNode->nextEdge = adjList[fromNode].edgeHead;
	adjList[fromNode].edgeHead = newNode;
}
//-------------------------- depthFirstTrav -----------------------------------
//
// displays the depth-first ordering of the Graph
//
void GraphL::depthFirstTrav()
{
	for(int i = 1; i <= size; i++)
	{
		adjList[i].visited = false;
	}

	cout << "Depth-first ordering: ";
	for(int v = 1; v <= size; v++)
	{
		if(!adjList[v].visited)
			dfs(v, adjList[v]);
	}
	cout << endl;
}
//-------------------------- dfs ------------------------------------------
//
// helper method for the depth-first traversal
//
void GraphL::dfs(int vIndex, GraphNode v)
{
	
	adjList[vIndex].visited = true;
	cout << vIndex << " ";
	EdgeNode* current = v.edgeHead;
	while(current != NULL)
	{
		if(!adjList[current->adjGraphNode].visited)
		{
			dfs(current->adjGraphNode, adjList[current->adjGraphNode]);
		}
			
		current = current->nextEdge;	
	}
}
