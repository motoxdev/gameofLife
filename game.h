#include <iostream>
#include <string>
#include <fstream>


int x = 1;
int dash  = 0;

class game{
public: //all the methods I am using in my game
  game(); //constuctor
  ~game(); //destructor deletes new at the end


  //SETTING UP THE NEEDED INFORMATION
  void userPrompt();
  void randGrid(int row, int column, float initialPop);
  void generate(std::string txtFile);

  //MODES
  void classic();
  void doughnut();
  void mirror();

  //PREFERENCE
  void pause();
  void enter();
  void boardExport();

private: //all the vars I will be using in my game
          int numX;
          float totalPop;
          int arr;
          int arrRow;
          int arrColumn;
          int bufferRow;
          int bufferColumn;
          int randomRow;
          int randomColumn;
          int **board;
          int row;
          int column;
          int generation;


};
