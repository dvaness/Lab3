#include "graphl.h"

GraphL::GraphL()
{
	for(int i = 0; i < MAXNODES; i++)
	{
		adjList[i].edgeHead = NULL;
	}
}

GraphL::~GraphL()
{
	makeEmpty();
}

void GraphL::makeEmpty()
{
	for(int i = i; i <= size; i++)
	{
		EdgeNode* current = adjList[i].edgeHead;
		while(current->nextEdge != NULL)
		{
			EdgeNode* temp = current;
			current = current->nextEdge;
			temp = NULL;
			delete temp;
		}
	}
}

void GraphL::buildGraph(istream& infile) 
{
   int fromNode, toNode;              // from and to node ends of edge

   //makeEmpty();                       // clear the graph of memory 

   infile >> size;                    // read the number of nodes
   cout << "Graph Size: " << size << endl;
   if (infile.eof()) return;          // stop if no more data
   
   string s;                          // used to read through to end of line
   getline(infile, s);
   cout << s << endl;

   // read graph node information
   for (int i=1; i <= size; i++) 
   {
      // read using setData of the NodeData class,
      // something like: 
      adjList[i].data.setData(infile);
      // where adjList is the array of GraphNodes and
      // data is the NodeData object inside of GraphNode
   }

   // read the edge data and add to the adjacency list
   for (;;) {
      infile >> fromNode >> toNode;
      if (fromNode ==0 && toNode ==0) return;     // end of edge data
      addEdge(fromNode, toNode);
      // insert the edge into the adjacency list for fromNode
   }
}

void GraphL::displayGraph()const
{
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

void GraphL::addEdge(int fromNode, int toNode)
{
	cout << "adding an edge from " << fromNode << " to " << toNode << endl;
	EdgeNode* newNode = new EdgeNode(toNode);
	
	cout << newNode->adjGraphNode << endl;
	newNode->nextEdge = adjList[fromNode].edgeHead;
	if(newNode->nextEdge != NULL)
		cout << newNode->nextEdge->adjGraphNode << endl;
	adjList[fromNode].edgeHead = newNode;
}

void GraphL::printAdjListData()const
{
	for(int i = 1; i <= size; i++)
	{
		cout << "[" << i << "]: " << adjList[i].data << endl;
	}
}