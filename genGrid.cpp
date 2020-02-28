#include "genGrid.h"
#include <fstream>

genGrid::genGrid(){
  grid = new char*[0];
  for (int i = 0; i < 0; ++i){
    grid[i] = new char[0];
  }
}

genGrid::genGrid(int row, int column){
  grid = new char*[row];
  for (int i = 0; i < row; ++i){
    grid[i] = new char[column];
  }
}

genGrid::~genGrid(){
  delete grid;
}

genGrid::importGrid(string gridFile){
  if(gridFile.is_open()){
    //read in the grid
  }

}
