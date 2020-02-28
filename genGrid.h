#include <iostream>
#include <cstdlib>
using namespace std;

class genGrid{
  public:
    char** grid;
    ifstream importGrid(inputFile);
    genGrid();
    genGrid(int row, int column);
    ~genGrid();
};
