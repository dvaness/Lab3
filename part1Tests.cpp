#include "graphm.h"
#include "nodedata.h"
#include <iostream>

#define SIZE 10

using namespace std;

void initDoubleArray(int[][SIZE]);
void printDoubleArray(int[][SIZE]);
void buildDataArray(NodeData[], istream&);
void printDataArray(NodeData[]);
void printFile(istream&);

int main()
{
	
	ifstream infile1("data31.txt");
   if (!infile1) {
      cout << "File could not be opened." << endl;
      return 1;
   }
   
   //for each graph, find the shortest path from every node to all other nodes
   	 GraphM G;
     G.buildGraph(infile1);
     G.printData();
     //G.printAdj();

     int doubleArray[SIZE][SIZE];
     NodeData someData[SIZE];

     //initDoubleArray(doubleArray);
     //buildDataArray(someData, infile1);
     //printDoubleArray(doubleArray);
     //printDataArray(someData);
     //printFile(infile1);

     //delete[] someData;
    string s = "1210";
    cout << s.at(0) << endl;
    cout << s.at(1) << endl;
    cout << s.at(2) << endl;
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


void buildDataArray(NodeData theArray[], istream& infile)
{
	int curPos = 0;
	while(!infile.eof() && curPos < SIZE)
	{
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

void printFile(istream& infile)
{
	while(!infile.eof())
	{
		string s;
		getline(infile, s);
		cout << s << endl;
	}
}