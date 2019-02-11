/************************************************
 * Author: Chenxing Liu
 * Date: Jan 30, 2019
 * Description: Implementation file of class Critter
************************************************/
#include "Critter.hpp"

//Constructor
Critter::Critter(int row, int col, Board* board)
{
  _type = 0;
  _currRow = row;
  _currClmn = col;
  _survivalRequired = 3;
  _survivalCount = 0;
  _board = board;
  _justMoved = 0;
}

//This function generates and returns a random number within range [lo, hi]
int Critter::getRand(int lo, int hi)
{
  int randomN = rand()%(hi-lo+1) + lo;
  return randomN;
}

//This function moves a critter one grid up
void Critter::moveUp()
{
  if (_currRow >= 1)     //In edge cases, don't move (THis check is redundant)
  {
    //Get the next location's ptr
    Critter** temp = &_board->getBoard()[_currRow-1][_currClmn];
    //Copy the current ptr to next location's ptr
    *temp = _board->getBoard()[_currRow][_currClmn];
    //Set the first pointer to null
    _board->getBoard()[_currRow][_currClmn] = NULL;
    //Update critter's location
    _currRow--;
  }
}

//This function moves a critter one grid down
void Critter::moveDown()
{
  int totalRows = _board->getTotalRows();
  if (_currRow <= totalRows-2)     //In edge cases, don't move
  {
    Critter** temp = &_board->getBoard()[_currRow+1][_currClmn];
    //Copy the current ptr to next location's ptr
    *temp = _board->getBoard()[_currRow][_currClmn];
    //Set the first pointer to null
    _board->getBoard()[_currRow][_currClmn] = NULL;
    //Update critter's location
    _currRow++;
  }
}

//This function moves a critter one grid left
void Critter::moveLeft()
{
  if (_currClmn >= 1)
  {
    //Get the next location's ptr
    Critter** temp = &_board->getBoard()[_currRow][_currClmn-1];
    //Copy the current ptr to next location's ptr
    *temp = _board->getBoard()[_currRow][_currClmn];
    //Set the first pointer to null
    _board->getBoard()[_currRow][_currClmn] = NULL;
    //Update critter's location
    _currClmn--;
  }
}

//This function moves a critter one grid right
void Critter::moveRight()
{
  int totalClmns = _board->getTotalColmns();
  if (_currClmn <= totalClmns-2)
  {
    //Get the next location's ptr
    Critter** temp = &_board->getBoard()[_currRow][_currClmn+1];
    //Copy the current ptr to next location's ptr
    *temp = _board->getBoard()[_currRow][_currClmn];
    //Set the first pointer to null
    _board->getBoard()[_currRow][_currClmn] = NULL;
    //Update critter's location
    _currClmn++;
  }
}

/*****************************************************************
If an ant survives three time steps (not been eaten by doodlebugs),
after the third step the ant will breed by creating a new ant in an
empty adjacent cell. If the cell that is randomly picked is not empty,
pick another one. If no empty cell available, no breeding occurs.
Once an offspring is produced, an ant cannot produce an offspring again
until it has survived three more time steps.
*****************************************************************/
void Critter::breed()
{
  //Check if survival count requirement is met
  if (_survivalCount >= _survivalRequired)
  {
    //Survival requirement met. Pick a direction
    vector<int> randDirVec = {1, 2, 3, 4};
    bool haveSpace = false;
    int index;
    //Pick random direction repeatedly, until find an empty grid
    while (!haveSpace && !randDirVec.empty())
    {
      //Get a random index from the vector
      index = getRand(0, randDirVec.size()-1);
      //Get direction thru index, check if the grid is empty
      //If grid empty, no need to pick another dir, move on to breed
      if (_board->isEmpty(this, randDirVec[index]))
        haveSpace = true;
      //Grid not empty, remove this dir from vec. Pick another one
      else
        randDirVec.erase(remove(randDirVec.begin(), randDirVec.end(),
        randDirVec[index]), randDirVec.end());
    }
    //Space available, breed. Else, no breeding
    if (haveSpace)
    {
      //Only reset survival count when breeding actually happens
      _survivalCount = 0;
      //Get the empty direction
      int dir = randDirVec[index];
      if (dir == 1)     //Breed direction: up
      {
        if (_type == 1)   //new ant
          _board->getBoard()[_currRow-1][_currClmn]
          = new Ant(_currRow-1, _currClmn, _board);
        else              //new doodlebug
          _board->getBoard()[_currRow-1][_currClmn]
          = new Doodlebug(_currRow-1, _currClmn, _board);
      }
      if (dir == 2)     //Breed direction: right
      {
        if (_type == 1)
          _board->getBoard()[_currRow][_currClmn+1]
          = new Ant(_currRow, _currClmn+1, _board);
        else
          _board->getBoard()[_currRow][_currClmn+1]
          = new Doodlebug(_currRow, _currClmn+1, _board);
      }
      if (dir == 3)     //Breed direction: down
      {
        if (_type == 1)
          _board->getBoard()[_currRow+1][_currClmn]
          = new Ant(_currRow+1, _currClmn, _board);
        else
          _board->getBoard()[_currRow+1][_currClmn]
          = new Doodlebug(_currRow+1, _currClmn, _board);
      }
      if (dir == 4)     //Breed direction: left
      {
        if (_type == 1)
          _board->getBoard()[_currRow][_currClmn-1]
          = new Ant(_currRow, _currClmn-1, _board);
        else
          _board->getBoard()[_currRow][_currClmn-1]
          = new Doodlebug(_currRow, _currClmn-1, _board);
      }
    }
  }
}

//getters
int Critter::getCurrRow()
{
  return _currRow;
}

int Critter::getCurrClmn()
{
  return _currClmn;
}

int Critter::getType()
{
  return _type;
}

int Critter::getJustMoved()
{
  return _justMoved;
}

//Rest move status back to not moved yet
void Critter::setJustMoved()
{
  _justMoved = 0;
}

//Destructor
Critter::~Critter()
{}



//*********Derived classes*************
//Constructor
Ant::Ant(int row, int col, Board* board):
Critter(row, col, board)
{
  _type = 1;
}

/************************************************
Ant's version of move().
This function gets a random number for ant to move
in that direction.
If the adjacent cell in the selected direction is
occupied or would move the ant off the grid,
then the ant stays in the current cell.
************************************************/
void Ant::move()
{
  //Get a random direction
  int dir = getRand(1, 4);
  //cout << "In Ant move, dir:  " << dir << endl;
  //Dir = 1, move up. Check if grid up is empty
  if (dir == 1 && _board->isEmpty(this, dir))
    moveUp();
  //Dir = 2, move right. Check if grid right is empty
  if (dir == 2 && _board->isEmpty(this, dir))
    moveRight();
  //Dir = 3, move down. Check if grid on the right is empty
  if (dir == 3 && _board->isEmpty(this, dir))
    moveDown();
  //Dir = 4, move left. Check if grid on the left is empty
  if (dir == 4 && _board->isEmpty(this, dir))
    moveLeft();
  //Update _survivalCount and move status
  _survivalCount++;
  _justMoved++;
}

//Ant's version of breed()
void Ant::breed()
{
  Critter::breed();
}

//Ants do not starve. Do nothing
void Ant::starve()
{
  //cout << "in ant starve" << endl;
}


//*********Derived classes*************
//Constructor
Doodlebug::Doodlebug(int row, int col, Board* board):
Critter(row, col, board), _starveLimit(3), _starveCount(0)
{
  _type = 2;
  _survivalRequired = 8;
}

/******************************************************
Doodlebug's version of move()
The doodlebug will firstly try to move to an adjacent
cell containing an ant and eat the ant. If there are
no ants in adjacent cells, the doodlebug moves according
to the same rules as the ant.
******************************************************/
void Doodlebug::move()
{
  //Find and eat ants
  if (_board->findAnts(this) != 0)
  {
    //Ants found. Store ant's direction in an int
    int dir = _board->findAnts(this);
    //cout << "got ants" << endl;
    //Ant is up
    if (dir == 1)
    {
      //delete ant obj before copying doodlebug ptr
      delete _board->getBoard()[_currRow-1][_currClmn];
      //move doodlebug and update doodlebug's location
      moveUp();
    }
    //Ant is on the right
    else if (dir == 2)
    {
      delete _board->getBoard()[_currRow][_currClmn+1];
      moveRight();
    }
    //Ant is down
    else if (dir == 3)
    {
      delete _board->getBoard()[_currRow+1][_currClmn];
      moveDown();
    }
    //Ant is on the left
    else
    {
      delete _board->getBoard()[_currRow][_currClmn-1];
      moveLeft();
    }
    //Ants eaten. Reset Doodlebug's _starveCount
    _starveCount = 0;
  }
  //No ants present. Move as usual
  else
  {
    int dir = getRand(1, 4);
    //cout << "no ants" << endl;
    //cout << "Doodlebug move. Dir:  " << dir << endl;
    if (dir == 1 && _board->isEmpty(this, dir))
      moveUp();
    if (dir == 2 && _board->isEmpty(this, dir))
      moveRight();
    if (dir == 3 && _board->isEmpty(this, dir))
      moveDown();
    if (dir == 4 && _board->isEmpty(this, dir))
      moveLeft();
    //Update _starveCount
    _starveCount++;
  }
  //Update _survivalCount and move status
  _survivalCount++;
  _justMoved++;
}

//Doodlebug's version of breed()
void Doodlebug::breed()
{
  Critter::breed();
}

/*********************************************************
If a doodlebug has not eaten an ant within three time steps,
at the end of the third step it will starve and die.
The doodlebug is removed from the grid of cells.
**********************************************************/
void Doodlebug::starve()
{
  //cout << "in doodlebug starve" << endl;
  //If starve requirement met, remove this doodlebug
  if (_starveCount == _starveLimit)
  {
    //Free up memory
    delete this;
    //Set corresponding ptr on board to null
    _board->getBoard()[_currRow][_currClmn] = NULL;
  }
}
