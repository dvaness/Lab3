#include "graphm.h"

GraphM::GraphM()
{
	size = 0; 
	for(int i = 0; i < MAXNODES; i++)
		for(int j = 0; j < MAXNODES; j++)
		{
			T[i][j].visited = false;
			T[i][j].path = 0;
		}
		adjMatrix[0][0] = 0;
		for(int k = 1; k < MAXNODES; k++)
			adjMatrix[k][k] = INT_MAX;
}

void GraphM::makeEmpty()
{
	delete[] data;
}

void GraphM::buildGraph(istream& infile) {
   int fromNode, toNode;              // from and to node ends of edge

   makeEmpty();                       // clear the graph of memory 
   if (infile.eof()) return;          // stop if no more data
   infile >> size;                    // read the number of nodes
   int currPos = 0;
   while(!infile.eof() && currPos <= size)
   {
   		string s;                          // used to read through to end of line
   		data[currPos].setData(infile);
   		currPos++;
   }
  
}

void GraphM::printData()const
{
	for(int i = 0; i < size; i++)
	{
		cout << data[i] << endl;
	}
}
