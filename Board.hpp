/************************************************
 * Author: Chenxing Liu
 * Date: Jan 30, 2019
 * Description: Header file of class Board
************************************************/
#ifndef BOARD_HPP
#define BOARD_HPP

#include "Critter.hpp"
#include <iostream>
#include <vector>
using std::cout;
using std::cin;
using std::endl;
using std::vector;

//forward declaring
class Critter;

class Board
{
  private:
    Critter ***ptrC;    //pointer to 2D array(the board)
    int _totalRows;
    int _totalClmns;
    int _totalSteps;
    unsigned _antNum;
    unsigned _doodlebugNum;
    unsigned _totalCritters;
    bool _firstPlay;
    vector<int> randomNums;

  public:
    Board();           //Constructor
    void startMenu();
    void initBoard();
    int getRand(int, int);
    void getAllRands();
    int transRandToRow(int);
    int transRandToCol(int);
    void placeCritterOnBoard();
    void startGame();
    bool isEmpty(Critter*, int);
    int findAnts(Critter*);
    void printBoard();
    bool playAgain();
    Critter ***getBoard();
    int getTotalRows();
    int getTotalColmns();
    ~Board();         //Destructor
};
#endif
