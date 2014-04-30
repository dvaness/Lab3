//-----------------------------------------------------------------------//
// GRAPHM.CPP                                                            //
// Author: Luke Selbeck                                                  //
// Date: April 30th, 2014                                                //
// Class: CSS 343                                                        //
//                                                                       //
// GraphM holds a graph with edges between nodes.  Uses Dijkstra's       //
// short path algorithm to find the shortest path between nodes          //
//-----------------------------------------------------------------------//
// Graph: defined as a stucture consisting of a finite set of ordered    //
//        pairs of vertices, called nodes, with edges connecting them.   //
//        An edge is said to point from one node to another.  Edges      //
//        between nodes also have costs/distances.								 //
//                                                                       //
// Implementation and assumptions:                                       //
//    -- input data file has correctly formatted data (see buildGraph)   //
//		-- all arrays start storing data at index 1, so that node numbers  //
//			are equal to index number                                       //
//      																					    //
//-----------------------------------------------------------------------//

#include "graphm.h"

//-------------------------- Constructor ----------------------------------
// Default constructor for class GraphM
// Preconditions:   makeEmpty re-initializes the data
// Postconditions:  all array are initialized and size is 0
GraphM::GraphM() {
	makeEmpty();
}

//----------------------------- buildGraph --------------------------------
// Builds a tree given a .txt file as input.
// assumed input example:
//       5 							//number of nodes	
//       Aurora and 85th 		//names of each node	
//		   Green Lake Starbucks //equal to number of nodes
//			Woodland Park Zoo 					
//			Troll under bridge 			
//			PCC 				
//			1 2 50 					//edges between each node
//			1 3 20 					//[node1] [node2] [distance]
//			1 5 30 		
//			2 4 10 
//			3 2 20 
//			3 4 40 
//			5 2 20 
//			5 4 25 
//			0 0 0						//input 0 0 0 to end input
// Preconditions:   none
// Assumptions: node names are less than 51 characters in length
// Postconditions:  nodes and edges are inputted into GraphM
void GraphM::buildGraph(istream& infile) {
   int fromNode, toNode;      // from and to node ends of edge
   int distance;					// distance between the nodes

   makeEmpty();               // clear the graph of memory 

   infile >> size;            // read the number of nodes
   if (infile.eof()) return;  // stop if no more data
   
   string s;                  // used to read through to end of line
   getline(infile, s);

   // read graph node information
   for (int i=1; i <= size; i++)
   	data[i].setData(infile);

   // read the edge data and add to the adjacency list
   for (;;) {
      infile >> fromNode >> toNode >> distance;
      if (fromNode ==0 && toNode ==0) return;     // end of edge data

      if ( fromNode > 0 && fromNode <= size && //only accept valid values
      	  toNode   > 0 && toNode   <= size) {
      	C[fromNode][toNode] = distance;
   	}
   }
}

//---------------------------- makeEmpty ----------------------------------
// All data members in GraphM are set back to their original values upon
// upon construction
// Preconditions:   none
// Postconditions:  all data is set to construction values
void GraphM::makeEmpty() {
	size = 0;
	for (int i = 0; i < MAXNODES; i++) {
		for (int j = 0; j < MAXNODES; j++){
			C[i][j] = INT_MAX;			//set cost to "infinity"

			T[i][j].dist = INT_MAX;		//intitial distances are "infinity"
			T[i][j].visited = false;
			T[i][j].path = 0;
		}
	}
}

//----------------------------- insertEdge --------------------------------
// Add an edge to GraphM, returns true if successful
// Preconditions: no negative values allowed, and only edges to and from
//			edges that already are in GraphM
// Postconditions: the new edge is added to the graph. if there already was
//			an edge from node to node, the distance is overwritten
bool GraphM::insertEdge(int fromNode, int toNode, int distance) {
	//if the nodes inputted are not in GraphM
	if (fromNode > size || fromNode < 1 || toNode > size || toNode < 1)
		return false;

	C[fromNode][toNode] = distance;
	return true;
}

//----------------------------- removeEdge --------------------------------
// Remove an edge from GraphM, returns true if to and from nodes were in
// GraphM
// Preconditions: no negative values allowed, and only edges to and from
//			edges that already are in GraphM
// Postconditions: the edge between the two nodes is removed from the
//			graph AKA reset to infinity
bool GraphM::removeEdge(int fromNode, int toNode) {
	//if the nodes inputted are not in GraphM
	if (fromNode > size || fromNode < 1 || toNode > size || toNode < 1)
		return false;

	C[fromNode][toNode] = INT_MAX;
	return true;
}

//-------------------------- findShortestPath -----------------------------
// Find the shortest path from all nodes to all nodes, and fills T with
// all the information
// Preconditions: none
// Postconditions: T is filled with all pathing information between all
//			nodes
void GraphM::findShortestPath() {
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
 				if (C[v][w] < INT_MAX && !T[source][w].visited) {
 					
 					//if going through v is better
 					if (T[source][v].dist + C[v][w] < T[source][w].dist) {
 						
 						//change dist between source and w to go through v
 						T[source][w].dist = T[source][v].dist + C[v][w];
 						
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

//------------------------------ displayAll -------------------------------
// Displays through cout all of the nodes and the paths inbetween them.
// includes extra blank line at end
// Preconditions: none
// Postconditions: none
void GraphM::displayAll() const {
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
				displayPathHelper(fromNode, toNode);
				cout << endl;
			}
		}
	}
	cout << endl;//extra blank line
}

//-------------------------------- display --------------------------------
// Displays one path from one node to another.  In order, 
// [node1] [node2] [distance] [pathing]
// [names of path nodes]
// Sample output:
// display(1, 2);
//		1    2    9         1 3 2
// Preconditions: no negative values allowed, and only edges to and from
//			nodes that already are in GraphM
// Postconditions: none
void GraphM::display(int fromNode, int toNode) const {
	//if the nodes inputted are not in GraphM
	if (fromNode > size || fromNode < 1 || toNode > size || toNode < 1)
		return;

	//display fromNode and toNode
	cout << setw(5) << fromNode << setw(5) << toNode;

	//display distance
	if (T[fromNode][toNode].dist < INT_MAX) //if there is a path
		cout << setw(10) << T[fromNode][toNode].dist;
	else //if no path
		cout << setw(10) << "----";

	//display pathing
	displayPathHelper(fromNode, toNode);
	cout << endl;
	displayPathNamesHelper(fromNode, toNode);
	cout << endl;
}

//--------------------------- displayPathHelper ---------------------------
// Helper function for display. Displays one path from one node to another.
// Preconditions: no negative values allowed, and only edges to and from
//			nodes that already are in GraphM
// Postconditions: none
void GraphM::displayPathHelper(int source, int w) const {
	int v = T[source][w].path;
	if (v != 0) {
		displayPathHelper(source, v);
		cout << w << " ";
	} else if (source == w)
		cout << w << " ";
}

//------------------------- displayPathNamesHelper ------------------------
// Helper function for display. Displays the names of the nodes on the path
// from one node to another. Includes a trailing endl.
// Preconditions: none
// Postconditions: none
void GraphM::displayPathNamesHelper(int source, int w) const {
	int v = T[source][w].path;
	if (v != 0) {
		displayPathNamesHelper(source, v);
		cout << data[w] << endl;
	} else if (source == w)
		cout << data[w] << endl;
}
