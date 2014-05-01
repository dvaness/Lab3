//---------------------------------------------------------------------------
// GRAPHM.CPP
// Implementation of the GraphM class
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

#include "graphm.h"
//-------------------------- Constructor ----------------------------------
// Default constructor for class GraphM
// Preconditions:   None
// Postconditions:
//		-- a new Graph is created. sets size to 0, all values of the
//		-- adjacency matrix to INT_MAX(infinity), and properly 
//		-- initializes all members of the TableType structs in
//		-- the T array
GraphM::GraphM()
{
	size = 0;
	for(int i = 0; i < MAXNODES; i++)
	{
		for(int j = 0; j < MAXNODES; j++)
		{
			adjMatrix[i][j] = INT_MAX;

			T[i][j].visited = false;
			T[i][j].dist = INT_MAX;
			T[i][j].path = 0;
		}

	}
}
//-------------------------- makeEmpty ------------------------------------
// Empties the Graph of memory
// Preconditions:   None
// Postconditions:
//		-- the Graph has been reset to its original state
void GraphM::makeEmpty()
{
	for(int i = 1; i <= size; i++)
	{
		for(int j = 1; j <= size; j++)
		{
			adjMatrix[i][j] = INT_MAX;

			T[i][j].visited = false;
			T[i][j].dist = INT_MAX;
			T[i][j].path = 0;
		}

	}
	size = 0;
}
//-------------------------- buildGraph -----------------------------------
// Builds the Graph
// Preconditions:   None
// Postconditions:
//		-- the Graph has been built including size and adjMatrix
void GraphM::buildGraph(istream& infile) {
   int fromNode, toNode, distance;              // from and to node ends of edge

   makeEmpty();                       // clear the graph of memory

   infile >> size;                    // read the number of nodes
   
   if (infile.eof())
	   {
	   	   cout << "at end of file" << endl;
	   	   return;          // stop if no more data
	   }

   string s;                          // used to read through to end of line
   getline(infile, s);
   
   // read graph node information
   for (int i=1; i <= size; i++)
	{
		data[i].setData(infile);
	}

   // read the edge data and add to the adjacency list
   for (;;) {
	   infile >> fromNode >> toNode >> distance;
	   if (fromNode ==0 && toNode ==0) return;     // end of edge data
	   if(fromNode <= size && toNode <= size)
	   adjMatrix[fromNode][toNode] = distance;
	   // insert the edge into the adjacency list for fromNode
   }
}
//-------------------------- findShortestPath -----------------------------
// use Dijakstra's algorithm to find the shortest path from every node to 
// every other node
// Preconditions:   None
// Postconditions:  
//		-- the TableType array is modified with correct values for the dist
//		   member and the path member.
void GraphM::findShortestPath()
{
	for (int source = 1; source <= size; source++) {
	 		T[source][source].dist = 0;

	 		//find the shortest distance from source to all other nodes
	 		for (int i = 1; i <= size; i++) {
	 			int v = -1;

	 			//find the node with smallest distance not visited
	 			int minDist = INT_MAX;
	 			for (int j = 1; j <= size; j++) {
	 				if ( T[source][j].dist < minDist && !T[source][j].visited ) {
	 					minDist = T[source][j].dist;
	 					v = j; //and store the index in v
	 				}
	 			}

	 			//all nodes are either visited or have no paths from source
	 			if (v == -1)	break;

	 			T[source][v].visited = true;

	 			//for each adjacent node not visited
	 			for (int w = 1; w <= size; w++) {
	 				if (adjMatrix[v][w] < INT_MAX && !T[source][w].visited) {

	 					//if going through v is better
	 					if (T[source][v].dist + adjMatrix[v][w] < T[source][w].dist) {

	 						//change dist between source and w to go through v
	 						T[source][w].dist = T[source][v].dist + adjMatrix[v][w];

	 						//change path between source and w to go through v
	 						T[source][w].path = v;
	 					}
	 				}
	 			}
	 		}
	 	}

	 	//reset visit values so you can call this method again if you want
	 	//like maybe you add an edge later on and want to recalculate
		for (int i = 1; i <= size; i++)
			for (int j = 1; j <= size; j++)
				T[i][j].visited = false;
}
//-------------------------- insertEdge -----------------------------------
// insert an edge into the Graph
// Preconditions:   None
// Postconditions:
//		-- a new Edge from fromNode to toNode with a weight of distance
//		   is inserted into the adjacency matrix
bool GraphM::insertEdge(int fromNode, int toNode, int distance)
{
	if(fromNode > size || fromNode < 1 || toNode > size || toNode < 1)
		return false;

		adjMatrix[fromNode][toNode] = distance;
		return true;

}
//-------------------------- removeEdge -----------------------------------
// remove an edge from the Graph
// Preconditions:   None
// Postconditions:
//		-- the edge from fromNode to toNode is removed from the adjacency 
//		   matrix
bool GraphM::removeEdge(int fromNode, int toNode)
{
	if(fromNode > size || fromNode < 1 || toNode > size || toNode < 1)
			return false;

	adjMatrix[fromNode][toNode] = INT_MAX;
	return true;

}
//-------------------------- displayAll -----------------------------------
// display a formatted table showing starting node, ending node, the
// shortest path from the starting node to the ending node, and the path
// connected to the shortest path.
void GraphM::displayAll()const
{
	cout << endl;
	cout << "Description         From node   To node   Dijkstra's   Path"
		     << endl;

		for (int fromNode = 1; fromNode <= size; fromNode++) {
			//print name of fromNode
			cout << data[fromNode] << endl;

			//print all path information of fromNode
			for (int toNode = 1; toNode <= size; toNode++) {
				if (fromNode != toNode) {

					//display fromNode and toNode
					cout << setw(25) << fromNode << setw(12)  << toNode;

					//display distance
					if (T[fromNode][toNode].dist < INT_MAX) //if there is a path
						cout << setw(12) << T[fromNode][toNode].dist;
					else //if no path
						cout << setw(12) << "----";

					//display pathing
					cout << "      ";
					displayPath(fromNode, toNode);
					cout << endl;
				}
			}
		}
		cout << endl;//extra blank line

}
//-------------------------- display --------------------------------------
// display the path from one node to another found through the shortest
// path function
void GraphM::display(int fromNode, int toNode)const
{
	cout << "path from " << fromNode << " to " << toNode << endl;
	cout << "-----------------" << endl;
	//if the nodes inputted are not in GraphM
	if (fromNode > size || fromNode < 1 || toNode > size || toNode < 1)
		return;

	//display fromNode and toNode
	cout  << fromNode << setw(5) << toNode;

	//display distance
	if (T[fromNode][toNode].dist < INT_MAX) //if there is a path
		cout << setw(5) << T[fromNode][toNode].dist;
	else //if no path
		cout << setw(5) << "----";

	//display pathing
	cout << setw(5);
	displayPath(fromNode, toNode);
	cout << endl;
	displayNames(fromNode, toNode);
}
//-------------------------- displayPath ----------------------------------
//
// helper method for displaying a single path
//
void GraphM::displayPath(int source, int w)const
{
	int v = T[source][w].path;
	if(v != 0)
	{
		displayPath(source, v);
		//cout << data[w] << endl;
		cout << w << " ";
	}
	else if(source == w)
	{
		cout << w << " ";
	}

}
//-------------------------- displayNames -------------------------------------
//
// helper method for displaying the NodeData objects for a path
//
void GraphM::displayNames(int source, int w)const
{
	int v = T[source][w].path;
	if(v != 0)
	{
		displayNames(source, v);
		cout << data[w] << endl;
		//cout << w << " ";
	}

	else if(source == w)
	{
		cout << data[w] << endl;
	}

}
