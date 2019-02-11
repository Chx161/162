/************************************************
 * Author: Chenxing Liu
 * Date: Jan 30, 2019
 * Description: Header file of class Critter
************************************************/
#ifndef CRITTER_HPP
#define CRITTER_HPP

#include "Board.hpp"
#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <time.h>
using std::vector;
using std::sort;
using std::cout;
using std::endl;

//forward declaring
class Board;

class Critter
{
  protected:
    Board* _board;
    int _type;    //Critter = 0; Ant = 1; Doodlebug = 2
    int _survivalRequired;
    int _survivalCount;
    int _currRow;
    int _currClmn;
    int _justMoved;

  public:
    Critter(int, int, Board*);   //Constructor
    int getRand(int, int);
    virtual void move() = 0;          //Pure virtual
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    virtual void breed();
    virtual void starve() = 0;        //Pure virtual
    int getCurrRow();
    int getCurrClmn();
    int getType();
    int getJustMoved();
    void setJustMoved();
    virtual ~Critter();         //Destructor
};


//*******Derived classes********
class Ant: public Critter
{
  public:
    Ant(int, int, Board*);          //Constructor
    virtual void move();
    virtual void breed();
    virtual void starve();
};

class Doodlebug: public Critter
{
  private:
    int _starveLimit;
    int _starveCount;       //Only Doodlebugs starve

  public:
    Doodlebug(int, int, Board*);     //Constructor
    virtual void move();
    virtual void breed();
    virtual void starve();
};
#endif
