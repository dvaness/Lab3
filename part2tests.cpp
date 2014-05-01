#include "graphl.h"
#include <iostream>

using namespace std;

int main()
{
	 ifstream infile1("data32.txt");
   if (!infile1) {
      cout << "File could not be opened." << endl;
      return 1;
   }

   GraphL G;
   G.buildGraph(infile1);
   G.printAdjListData();
   G.displayGraph();

   return 0;
}