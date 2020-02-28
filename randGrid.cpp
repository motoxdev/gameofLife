#include "randGrid.h"

randGrid::randGrid(){
  grid = new char*[0];
  for (int i = 0; i < 0; ++i){
    grid[i] = new char[0];
  }
}

randGrid::randGrid(int row, int column){
  grid = new char*[row];
  for (int i = 0; i < row; ++i){
    grid[i] = new char[column];
  }
}
