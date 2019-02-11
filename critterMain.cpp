/************************************************
 * Author: Chenxing Liu
 * Date: Jan 30, 2019
 * Description: Main file of Group Project
************************************************/
#include <iostream>
#include <algorithm>
#include <vector>
#include "Critter.hpp"
#include "Board.hpp"
using namespace std;

//****Extra credit part done****

int main()
{
  srand(time(0));

  //Create board
  Board critterBoard;
  //Start game
  critterBoard.startMenu();
  critterBoard.startGame();

  return 0;
}
