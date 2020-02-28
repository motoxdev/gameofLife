#include <iostream>
#include <cstdlib>
using namespace std;

class randGrid{
  public:
    char** grid;
    randGrid();
    randGrid(int row, int column);
    ~randGrid();
};
