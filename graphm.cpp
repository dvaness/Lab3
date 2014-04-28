#include "graphm.h"

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
	delete[] data;
}

void GraphM::buildGraph(istream& infile) {
   int fromNode, toNode;              // from and to node ends of edge

   //makeEmpty();                       // clear the graph of memory 
   if (infile.eof()) return;          // stop if no more data
   infile >> size;                    // read the number of nodes
   cout << "Graph Size: " << size << endl;
   int currPos = 0;
   while(currPos <= size)
   {
   		//building data array
   		data[currPos].setData(infile);
   		cout << "added " << data[currPos] << endl;
   		currPos++;
   	}
   	//building adjacency array
   	
   	while(!infile.eof())
   	{
   		string s;
   		getline(infile, s);
   		if(s.compare("0 0 0") == 0) break;
   		cout << "s: " << s << endl;
   		//sets values, accounting for spaces
   		fromNode = s.at(0);
   		toNode = s.at(2);
   		cout << "(" << fromNode <<", " << toNode << ")" << endl;
   		//adjMatrix[fromNode][toNode] = (int)s.at(3);	
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
	for(int i = 0; i < size; i++)
	{
		cout << "[ ";
		for(int j = 0; j < size; j++)
		{
			if(j != size - 1)
				cout << adjMatrix[i][j] << ", ";
			else
				cout << adjMatrix[i][j];
		}
		cout << " ]" << endl;
	}
}