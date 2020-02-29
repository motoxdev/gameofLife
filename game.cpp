#include "game.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
using namespace std;

game::game(){
  totalPop = 0.0;
  numX = 0;
}

game:: ~game(){
  delete arr[][];
}

void game::userPrompt(){
  //determining which grid type the user chooses
  cout << "HELLO! Would you like to start with a random configuration, or upload a file with a configuration?" << endl;
  cout << "Type r for random or f for file:" << endl;
  char res;
  cin >> res >> endl;
  //setting up grid based on user response
  if ( res == 'r'){
      cout >> "Please input the # of rows and # of columns you would like:"
      int row;
      int column;
      cin << row << endl;
      cin << column << endl;
      cout >> "Please input the decimal value to represent the initial population" >> endl;
      cout >> "This value must be between zero and one:" >> endl;
      float initialPop;
      cin >> initialPop >> endl;
      randGrid(row,column,initialPop);
  }
  if ( res == "f"){
    cout >> "Please type the EXACT file name of the ENTIRE text file: "
    string gridFile;
    cin << gridFile << endl;
    importGrid(gridFile);
  }
  //now that we set up our grids, having the user pick a mode
  cout << "Please pick from the following modes: " << endl;
  cout << "Type one of the following numbers to pick a mode: " <<;
  cout << "1. Classic Mode  2. Doughnut Mode  3. Mirror Mode" << endl;
  int mode;
  cin >> mode >> endl;
  if (mode == 1){
    emptyBuffer(grid);
    classic();
  }
  if (mode == 2){
    emptyBuffer(grid);
    doughnut();
  }
  if (mode == 3){
    emptyBuffer(grid);
    mirror();
  }

  cout << "Would you like 1. a brief pause between generations?" << endl;
  cout << "               2. press the ENTER key between generations?" << endl;
  cout << "               3. output generations to a file?" <<endl;
  cout << "Please type 1, 2, or 3: " <<;

  int pref;
  cin >> pref;

  if (pref == 1){
    pause();
  }
  if (pref == 2){
    enter();
  }
  if (pref == 3){
    export();
  }



}

void game::randGrid(int row, int column, float initialPop){
  //declaring the rows and columns
  arrRow = row;
  arrColumn = column;
  bufferRow = arrRow + 2;
  bufferColumn = arrColumn + 2;

  //making the actual board by dimensions
  board = newint*[arrRow];
  for (int i = 0; i < arrRow; ++i){
    board[i] = new int*[arrColumn];
  }

  //determining the population within the grid
  if ((initialPop > 0) && (initialPop < 1)){
    int totalPop = (arrRow*arrColumn)*(initialPop);
    //now I am going to make entire grid full of dashes,
    //then fill in with X's with RAND
    for (int i = 0; i < arrRow - 1; ++i){
      for(int j = 0; j < arrColumn -1; ++i){
        board[i][j] = dash;
      }
    }
    //going to randomize where the X's are by
    //picking a random row and column then filling them in
  while(totalPop > 0){
      randomRow = RAND() % arrRow + 1; //picking a random row
      randomColumn = RAND() % arrColumn + 1; //picking a random column
      if (grid[row][column] != x){
        grid[row][column] = x; //assigning x to that random index
        --totalPop; //decrements the value
      }
  }
}

void game::importGrid(string txtFile){
 //copied this section of code from my hw #1
  string line;
  if(grid.is_open())
  {
    while(!grid.eof())
    {
      //making whole file lowercase
      for(int l = 0; l < line.length(); ++l){
        line[l] = tolower(line[l]);
      }
       //gets the first two lines to know grid dimensions
      getline(grid, line);
      arrRow = atoi(line.c_str());
      getline (grid, line);
      arrColumn = atoi(line.c_str());
      bufferRow = arrRow;
      bufferColumn = arrColumn;
      board = newint*[arrRow][arrColumn];
      //transferring from text file to array in game
      for (int i = 0; i < arrRow - 1; ++i){
        for (int j = 0; j < arrColumn - 1; ++j){
          if(line[j - 1] == 'x'){
            board[i][j] = x;
          }
          if (line[b-1] == '-'){
            board[i][j] = dash;
          }
        }
      }


    grid.close();
}

void game::emptyBuffer(int **grid){
  for (int i = 0; i < arrRow; ++i){
    for( int j = 0; j < arrColumn; ++j){
      if((i == 0) || (i == arrRow - 1)){
        grid[i][j] = dash;
      }
      if((j == 0) || (j == arrColumns -1)){
        grid[i][j] = dash;
      }
    }
  }
}

void game::classic(){

}

void game::doughnut(){

}

void game::mirror(){

}

void game::pause(){

}

void game::enter(){

}

void game::export(){

}
