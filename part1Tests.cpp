//#include "graphm.h"
#include "nodedata.h"
#include <iostream>

#define SIZE 10

using namespace std;

void initDoubleArray(int[][SIZE]);
void printDoubleArray(int[][SIZE]);
void buildDataArray(NodeData[], ifstream&);
void printDataArray(NodeData[]);
int main()
{
	
	ifstream infile1("data31.txt");
   if (!infile1) {
      cout << "File could not be opened." << endl;
      return 1;
   }
   /*
   //for each graph, find the shortest path from every node to all other nodes
   	 GraphM G;
     G.buildGraph(infile1);
     G.printData();*/
     int doubleArray[SIZE][SIZE];
     NodeData someData[SIZE];

     initDoubleArray(doubleArray);
     buildDataArray(someData, infile1);
     printDoubleArray(doubleArray);
     printDataArray(someData);

     //delete[] someData;
    
	return 0;
}

void initDoubleArray(int theArray[][SIZE])
{
	for(int i = 0; i < SIZE; i++)
	{
		theArray[0][i] = 1;
	}
	for(int i = 1; i < SIZE; i++)
		for(int j = 0; j < SIZE; j++)
		{
			theArray[i][j] = 0;
		}
}

void printDoubleArray(int theArray[][SIZE])
{
	for(int i = 0; i < SIZE; i++)
	{
		cout << "[ ";
		for(int j = 0; j < SIZE; j++)
		{
			if(j != SIZE - 1)
				cout << theArray[i][j] << ", ";
			else
				cout << theArray[i][j];
		}
		cout << " ]" << endl;
	}
		
}

void buildDataArray(NodeData theArray[], ifstream& infile)
{
	int curPos = 0;
	while(!infile.eof() && curPos <= SIZE)
	{
		if(infile.eof()) break;
		theArray[curPos].setData(infile);
		curPos++;
	}

}

void printDataArray(NodeData theArray[])
{
	for(int i = 0; i < SIZE; i++)
	{
		cout << "[" << i << "]: " << theArray[i] << endl;
	}
}