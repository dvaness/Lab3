#include "graphm.h"


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

void GraphM::buildGraph(istream& infile) {
   int fromNode, toNode, distance;              // from and to node ends of edge

   makeEmpty();                       // clear the graph of memory

   infile >> size;                    // read the number of nodes
   cout << "Graph Size: " << size << endl;
   if (infile.eof()) return;          // stop if no more data

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
	   if(fromNode > 0 && fromNode <= size && toNode > 0 && toNode <= size)
	   adjMatrix[fromNode][toNode] = distance;
	   // insert the edge into the adjacency list for fromNode
   }
}

//int GraphM::findMin(int src)const
//{
//	int min_index = src + 1;
//	int min_value = T[src][src+1].dist;
//	cout << "min_index: " << min_index << endl;
//	cout << "min_value: " << min_value << endl;
//	for(int i = min_index; i <= size; i++)
//	{
//
//		if(!T[src][i].visited)
//		{
//			cout << "checking " << i << ": " <<  T[src][i].dist << endl;
//			if(T[src][i].dist <= min_value)
//			{
//				min_index = i;
//				min_value = T[src][i].dist;
//			}
//		}
//	}
//	cout << "returning " << min_index << endl;
//	if(!T[src][min_index].visited)
//		return min_index;
//	else
//		return 0;
//}

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

bool GraphM::insertEdge(int fromNode, int toNode, int distance)
{
	if(fromNode > size || fromNode < 1 || toNode > size || toNode < 1)
		return false;

		adjMatrix[fromNode][toNode] = distance;
		return true;

}

bool GraphM::removeEdge(int fromNode, int toNode)
{
	if(fromNode > size || fromNode < 1 || toNode > size || toNode < 1)
			return false;

	adjMatrix[fromNode][toNode] = INT_MAX;
	return true;

}

void GraphM::displayAll()const
{
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

void GraphM::display(int fromNode, int toNode)const
{
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
	displayPath(fromNode, toNode);
	cout << endl;
}

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
