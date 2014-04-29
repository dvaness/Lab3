#include "graphm.h"


GraphM::GraphM()
{
	makeEmpty();
}

void GraphM::makeEmpty()
{
	size = 0; 
	for(int i = 1; i < MAXNODES; i++)
	{
		for(int j = 1; j < MAXNODES; j++)
		{
			T[i][j].visited = false;
			T[i][j].dist = INT_MAX;
			adjMatrix[i][j] = INT_MAX;
			T[i][j].path = 0;	
		}
		
	}
}

void GraphM::buildGraph(istream& infile) {
   int fromNode = 0, toNode = 0, distance = 0;              // from and to node ends of edge

   makeEmpty();                       // clear the graph of memory
   if (infile.eof()) return;          // stop if no more data
   infile >> size;                    // read the number of nodes
   cout << "Graph Size: " << size << endl;

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
	   insertEdge(fromNode, toNode, distance);
	   // insert the edge into the adjacency list for fromNode
   }
}

int GraphM::findMin(int src)const
{
	int min_index = src + 1;
	int min_value = T[src][src+1].dist;
	cout << "min_index: " << min_index << endl;
	cout << "min_value: " << min_value << endl;
	for(int i = min_index; i <= size; i++)
	{

		if(!T[src][i].visited)
		{
			cout << "checking " << i << ": " <<  T[src][i].dist << endl;
			if(T[src][i].dist <= min_value)
			{
				min_index = i;
				min_value = T[src][i].dist;
			}
		}
	}
	cout << "returning " << min_index << endl;
	if(!T[src][min_index].visited)
		return min_index;
	else
		return 0;
}

void GraphM::findShortestPath()
{
	for(int source = 1; source <= size; source++)
	{
		T[source][source].dist = 0;
		T[source][source].visited = true;
		shortestPathHelper(source);
	}		
}

void GraphM::shortestPathHelper(int src)
{
	cout << "Checking all values for " << src << endl;
	cout << "---------------------------" << endl;

	for(int i = 1; i <= size - 1; i++)
	{
		int v = findMin(src);
		if(v == 0) break;
		else
		{
			cout << "min is currently: " << v << endl;
			cout << "------------------" << endl;
			T[src][v].visited = true;
			for(int w = 1; w <= size; w++)
			{
				if(!T[src][w].visited)
				{
					if(adjMatrix[v][w] != INT_MAX)	//w is adjacent to v
					{
						int firstDist = T[src][w].dist;
						int secondDist = (adjMatrix[src][v] + adjMatrix[v][w]);
						cout << w << " is adjacent to " << v << " with a cost of " << adjMatrix[v][w] << endl;
						cout << "going from " << src << " to " << w << " without using " << v << " costs " << 
								firstDist << endl;
					cout << "going from " << src << " to " << w << " using " << v << " costs " << 
							secondDist << endl;

						T[src][w].dist = min(firstDist, secondDist);
						if(T[src][w].dist == secondDist)
							T[src][w].path = v;
						cout << "set the cost of going from " << src << " to " << w << " to " << T[src][w].dist << endl;
				}
			}
			
		}
		}
		
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
	for(int i = 1; i <= size; i++)
	{
		// if(T[i][i].visited == true)
		// 	cout << "Visited." << endl;
		// else
		// 	cout << "Not visited." << endl;
		for(int j = 1; j <= size; j++)
		{
			if(adjMatrix[i][j] != INT_MAX)
			{
				cout << "[" << i << ", " << j << "]: " << adjMatrix[i][j] << endl;
			// if(T[i][j].visited == true)
			// 	cout << "Visited." << endl;
			// else
			// 	cout << "Not visited." << endl;
			}				
		}
	}
}

void GraphM::insertEdge(int fromNode, int toNode, int distance)
{
	if(fromNode <= size && toNode <= size)
	{
		adjMatrix[fromNode][toNode] = distance;
		T[fromNode][toNode].dist = distance;
	}
		
}

void GraphM::removeEdge(int fromNode, int toNode)
{
	if(fromNode <= size && toNode <= size)
	{
		adjMatrix[fromNode][toNode] = INT_MAX;
		T[fromNode][toNode].dist = INT_MAX;
	}
		
}

void GraphM::displayAll()const
{
	for(int i = 1; i <= size; i++)
	{
		// if(T[i][i].visited == true)
		// 	cout << "Visited." << endl;
		// else
		// 	cout << "Not visited." << endl;
		for(int j = 1; j <= size; j++)
		{
			if(T[i][j].dist != INT_MAX && T[i][j].dist > 0)
			{
				cout << "[" << i << ", " << j << "]: " << T[i][j].dist << endl;
			// if(T[i][j].visited == true)
			// 	cout << "Visited." << endl;
			// else
			// 	cout << "Not visited." << endl;
			}
			else
			{
				if(j != i)
					cout << "[" << i << ", " << j << "]: -----" << endl;
			}				
		}
		cout << endl;
	}

}