#include <iostream>
#include <string>
#include <fstream>


const char x = 'x';
const char dash  = '-';

class game{
public: //all the methods I am using in my game
  game(); //constuctor
  ~game(); //destructor deletes new at the end


  //SETTING UP THE NEEDED INFORMATION
  void userPrompt();
  void randGrid(int row, int column, double initialPop);
  void generate(std::string txtFile);

  //MODES
  void classic();
  void doughnut();
  void mirror();
  void neighbor();
  //PREFERENCE
  void pause(int seconds);
  void enter();
  void boardExport(std::string outputFile);
  void copy();
  void stabilize();

private: //all the vars I will be using in my game
          int numX;
          double initialPop;
          int totalPop;
          int pref;
          int arr;
          int arrRow;
          int arrColumn;
          int bufferRow;
          int bufferColumn;
          int randomRow;
          int randomColumn;
          char **board;
          char **boardTwo;
          int row;
          int column;
          int generation;
          std::string outputFile;


};
