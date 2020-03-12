#include "game.h"
#include <iostream>
#include <cstring>
#include <locale>
#include <fstream>
#include <string>
#include <chrono>
#include <streambuf>
#include <thread>
#include <time.h>
#include <cstdlib>
#include <stdio.h>
#include <math.h>

using namespace std;

game::game(){
  totalPop = 0;
  numX = 0;
}

game:: ~game(){
  //deleting the board
  for (int i = 0; i < arrRow; ++i){
    delete[] board[i];
  }
  delete[] board;
}

void game::userPrompt(){
  //determining which grid type the user chooses
  cout << "HELLO! Would you like to start with a random configuration, or upload a file with a configuration?" << endl;
  cout << "Type r for random or f for file:" << endl;
  char res;
  cin >> res;
  cout << " " << endl;
  //setting up grid based on user response
  if ( res == 'r'){
      cout << "Please input the # of rows and # of columns you would like:" << endl;
      cin >> row;
      cout << " " << endl;
      cin >> column;
      cout << " " << endl;
      cout << "Please input the decimal value to represent the initial population" << endl;
      cout << "This value must be between zero and one:" << endl;
      cin >> initialPop;
      cout << " " << endl;
      randGrid(row,column,initialPop);
  }
  if ( res == 'f'){
    cout << "Please type the EXACT file name of the ENTIRE text file: " << endl;
    string txtFile;
    cin >> txtFile;
    cout << " " << endl;
    generate(txtFile);
  }
  //now that we set up our grids, having the user pick a mode
  cout << "Please pick from the following modes: " << endl;
  cout << "Type one of the following numbers to pick a mode: " << endl;
  cout << "1. Classic Mode  2. Doughnut Mode  3. Mirror Mode" << endl;
  int mode;
  cin >> mode;
  cout << " " << endl;
  cout << "Would you like 1. a brief pause between generations?" << endl;
  cout << "               2. press the ENTER key between generations?" << endl;
  cout << "               3. output generations to a file?" <<endl;
  cout << "Please type 1, 2, or 3: " << endl;
  cin >> pref;
  if (mode == 1){
    classic();
    neighbor();
  }
  if (mode == 2){
    doughnut();
    neighbor();
  }
  if (mode == 3){
    cout << "Please enter the name of the text file you want to output to: " << endl;
    cin >> outputFile;
    cout << " " << endl;
    mirror();
    neighbor();
  }
}

void game::randGrid(int row, int column, double initialPop){
  //declaring the rows and columns
  arrRow = row;
  arrColumn = column;
  bufferRow = arrRow + 2;
  bufferColumn = arrColumn + 2;

  //making the actual board by dimensions
  board = new char*[arrRow];
  for (int i = 0; i < arrRow; ++i){
    board[i] = new char[arrColumn];
  }

  //determining the population within the grid
  if ((initialPop > 0) && (initialPop <= 1)){
    int answer = arrRow*arrColumn;
    totalPop = answer*initialPop;
    //now I am going to make entire grid full of dashes,
    //then fill in with X's with RAND
    for (int i = 0; i < arrRow - 1; ++i){
      for(int j = 0; j < arrColumn - 1; ++i){
        board[i][j] = '-';
      }
    }
    //going to randomize where the X's are by
    //picking a random row and column then filling them in
  while(totalPop > 0){
      randomRow = rand() % arrRow + 1; //picking a random row
      randomColumn = rand() % arrColumn + 1; //picking a random column
      if (board[randomRow][randomColumn] != 'x'){
        board[randomRow][randomColumn] = 'x'; //assigning x to that random index
        --totalPop; //decrements the value
      }
    }
  }
  for(int i = 0; i < arrRow; ++i){
      for(int j = 0; i < arrColumn; ++j){
          cout << board[i][j];
      }
  }
}


void game::generate(string txtFile){
 //copied this section of code from my hw #1
  string line;
  ifstream grid(txtFile);
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
      board = new char*[arrRow];
      //transferring from text file to array in game
      for (int i = 0; i < arrRow - 1; ++i){
        for (int j = 0; j < arrColumn - 1; ++j){
          if(line[j - 1] == 'x'){
            board[i][j] = 'x';
          }
          if (line[j - 1] == '-'){
            board[i][j] = dash;
          }
        }
      }


    grid.close();
  }
 }
}
//boards are now ready

void game::classic(){
  //clearing the buffer rows since it is classic mode
  for (int i = 0; i < arrRow; ++i){
    for( int j = 0; j < arrColumn; ++j){
      if((i == 0) || (i == arrRow - 1)){
        board[i][j] = dash;
      }
      if((j == 0) || (j == arrColumn - 1)){
        board[i][j] = dash;
      }
    }
  }
}

void game::doughnut(){
  //filling the buffer rows with doughnut mode rules
  for (int i = 1; i < arrRow - 1; ++i){
    for (int j = 1; j < arrColumn - 1; ++j){
      //(0,0) of board
      if ((i == arrRow - 2) && (j == 1)){
        board[i + 1][j - 1] = board[1][arrColumn - 2];
      }
      //(0,1) of board
      if((i == arrRow - 2) &&(arrColumn - 2 > j) && (j > 1)){
        board[i + 1][j - 1] = board[i + 1][arrColumn - 2];
        board[i][j - 1] = board [i][arrColumn - 2];
        board[i - 1][j - 1] = board[i - 1][arrColumn - 2];
      }
      //(0,2) of board
      if((i == 1) && (j == 1)){
        board[i - 1][j - 1] = board[arrRow - 2][arrColumn - 2];
      }
      //(1,2) of board
      if((i == 1) && (j > 1) && (arrColumn - 2 > j)){
        board[i - 1][j - 1] = board[arrRow - 2][j - 1];
        board[i - 1][j] = board[arrRow - 2][j];
        board[i - 1][j + 1] = board[arrRow - 2][j + 1];
      }
      //(2,2) of board
      if((i == 1) && (j = arrColumn - 2)){
        board[i - 1][j + 1] = board[arrRow - 2][1];
      }
      //(2,1) of board
      if((i > 1) && (j < arrRow - 2) && (j == arrColumn - 2)){
        board[i - 1][j + 1] = board[i - 1][1];
        board[i][i + 1] = board[i][1];
        board[i + 1][j + 1] = board[i + 1][1];
      }
      //(2,0) of board
      if((i == arrRow - 2) && (j == arrColumn - 2)){
        board[i + 1][j + 1] = board[1][1];
      }
      //(1,0) of board
      if ((i == arrRow - 2) && (j < arrColumn - 2) && (j > 1)){
        board[i + 1][j + 1] = board[1][j + 1];
        board[i + 1][j] = board[1][j];
        board[i + 1][j - 1] = board[1][j - 1];
      }
    }
  }
}

void game::mirror(){
  //filling the buffer rows with mirror mode rules
  for (int i = 1; i < arrRow - 1; ++i){
    for (int j = 1; j < arrColumn - 1; ++j){
      //(0,0) of board
      if ((i == arrRow - 2) && (j == 1)){
        board[i + 1][j] = board[i][j];
        board[i + 1][j - 1] = board[i][j];
        board[i][j - 1] = board[i][j];
      }
      //(0,1) of board
      if((i == arrRow - 2) && (arrColumn - 2 > j) && (j > 1)){
        board[i][j - 1] = board[i][j];
      }
      //(0,2) of board
      if((i == 1) && (j == 1)){
        board[i - 1][j - 1] = board[i][j];
        board[i - 1][j] = board[i][j];
        board[i][j - 1] = board[i][j];
      }
      //(1,2) of board
      if((i == 1) && (j > 1) && (arrColumn - 2 > j)){
        board[i - 1][j] = board[i][j];
      }
      //(2,2) of board
      if((i == 1) && (j = arrColumn - 2)){
        board[i - 1][j] = board[i][j];
        board[i - 1][j + 1] = board[i][j];
        board[i][j + 1] = board[i][j];
      }
      //(2,1) of board
      if((i > 1) && (j < arrRow - 2) && (j == arrColumn - 2)){
        board[i][j + 1] = board[i][j];
      }
      //(2,0) of board
      if((i == arrRow - 2) && (j == arrColumn - 2)){
        board[i][j + 1] = board[i][j];
        board[i + 1][j + 1] = board[i][j];
        board[i + 1][j] = board[i][j];
      }
      //(1,0) of board
      if ((i == arrRow - 2) && (j < arrColumn - 2) && (j > 1)){
        board[i + 1][j] = board[i][j];
      }
    }
  }
}

void game::pause(int numSeconds){
  //converts time to milliseconds
  int milli_seconds = 1000 * numSeconds;
  //storing start time
  clock_t start_time = clock();
  //looping till required time is not achieved
  while(clock() < start_time + milli_seconds);
}

void game::enter(){
  string temp;
  cout << "Press ENTER to go to the next generation: " << endl;
  cin >> temp;
  cout << " " << endl;
}

void game::boardExport(string outputFile){
  ofstream out("outputFile");
}

void game::neighbor(){
  //the "neighbor" portion of the game
    while (numX != 0){
      for (int i = 1; i <= arrRow; ++i){
        for(int j = 1; j <= arrColumn; ++j){
          //4 neighbors
          if((board[i - 1][j]) + (board[i - 1][j + 1]) + (board[i][j + 1]) + (board[i + 1][j + 1]) + (board[i + 1][j]) +
            (board[i + 1][j - 1]) + (board[i][j - 1]) + (board[i - 1][j - 1]) >= 4){
              board[i][j] = '-';
          }
          //3 neighbors
          if((board[i - 1][j]) + (board[i - 1][j + 1]) + (board[i][j + 1]) + (board[i + 1][j] +
            (board[i + 1][j - 1]) + (board[i][j - 1]) + (board[i - 1][j - 1]) ==3)){
              board[i][j] = 'x';
            }
          //2 neighbors
          if((board[i - 1][j]) + (board[i - 1][j + 1]) + (board[i][j + 1]) + (board[i + 1][j + 1]) + (board[i + 1][j]) +
            (board[i + 1][j - 1]) + (board[i][j - 1]) + (board[i - 1][j - 1] == 2)){
              //I DON'T KNOW//STAYS THE SAME
            }
          //1 neighbor
          if((board[i - 1][j]) + (board[i - 1][j + 1]) + (board[i][j + 1]) + (board[i + 1][j]) +
            (board[i + 1][j - 1]) + (board[i][j - 1]) + (board[i - 1][j - 1]) == 1){
              board[i][j] = '-';
            }
        }
      }
      cout << board << endl;
      if (pref == 1){
        pause(5);
      }
      if (pref == 2){
        enter();
      }
      if (pref == 3){
        boardExport(outputFile);
      }
    }
}
