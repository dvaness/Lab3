#include "graphm.h"
#include <iomanip>

GraphM::GraphM()
{
	size = 0; 
	for(int i = 1; i < MAXNODES; i++)
	{
		T[0][i].visited = false;
		T[0][i].dist = INT_MAX;
		T[0][i].path = 0;
	}
}

void GraphM::makeEmpty()
{
}

void GraphM::buildGraph(istream& infile) {
   int fromNode = 0, toNode = 0, distance = 0;              // from and to node ends of edge

   //makeEmpty();                       // clear the graph of memory
   if (infile.eof()) return;          // stop if no more data
   infile >> size;                    // read the number of nodes
   cout << "Graph Size: " << size << endl;

   	//building adjacency array

   //makeEmpty();                       // clear the graph of memory

   string s;                          // used to read through to end of line
   getline(infile, s);
   // read graph node information
   for (int i=1; i <= size; i++) {
	   // read using setData of the NodeData class,
	   // something like:
	   //    adjList[i].data.setData(infile);
	   data[i].setData(infile);
	   // where adjList is the array of GraphNodes and
	   // data is the NodeData object inside of GraphNode
   }

   // read the edge data and add to the adjacency list
   for (;;) {
	   infile >> fromNode >> toNode >> distance;
	   if (fromNode ==0 && toNode ==0) return;     // end of edge data
	   adjMatrix[fromNode][toNode] = distance;
	   // insert the edge into the adjacency list for fromNode
   }
}

void GraphM::printData()const
{
	for(int i = 0; i <= size; i++)
	{
		cout << data[i] << endl;
	}
}

void GraphM::printAdj()const
{
	for(int i = 0; i <= size; i++)
	{
		for(int j = 0; j <= size; j++)
		{
			if(adjMatrix[i][j] != 0)
				cout << "[" << i << ", " << j << "]: " << adjMatrix[i][j] << endl;
		}
	}
}
