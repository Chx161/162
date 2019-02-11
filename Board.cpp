/************************************************
 * Author: Chenxing Liu
 * Date: Jan 30, 2019
 * Description: Implementation file of class Board
************************************************/
#include "Board.hpp"

//Constructor. Init the board with 2D array allocation
Board::Board()
{
  _totalRows = _totalClmns = 0;
  _firstPlay = true;
  _totalSteps = 0;
  _antNum = _doodlebugNum = _totalCritters = 0;
  ptrC = NULL;
}

/***********************************************************
This function displays start menu and gets user input
***********************************************************/
void Board::startMenu()
{
  //Set up game with user input
  cout << "Welcome to Predator-Prey Game" << endl;

  cout << "Please set the size of board." << endl;
  cout << "How many rows do you want?" << endl;
  cout << "Please enter an integer between 5 and 50: ";
  cin >> _totalRows;

  cout << "How many columns do you want?" << endl;
  cout << "Please enter an integer between 5 and 50: ";
  cin >> _totalClmns;

  cout << "How many steps do you want to play?" << endl;
  cout << "Please enter an integer between 1 and 32767: ";
  cin >> _totalSteps;

  cout << "How many ants do you want?" << endl;
  cout << "Please enter a positive integer no larger than "
       << _totalRows*_totalClmns-2 << ": ";
  cin >> _antNum;

  cout << "How many doodlebugs do you want?" << endl;
  cout << "Please enter a positive integer no larger than "
       << _totalRows*_totalClmns-_antNum << ": ";
  cin >> _doodlebugNum;

  _totalCritters = _antNum + _doodlebugNum;
}

//This function initializes board with user input info
void Board::initBoard()
{
  //Create the 2D array
  //Each element in the 2D array is a Critter*
  ptrC = new Critter**[_totalRows];
  for (int i = 0; i < _totalRows; i++)
    ptrC[i] = new Critter*[_totalClmns];

  //Init each every element in the board to NULL
  for (int i = 0; i < _totalRows; i++)
    for (int j = 0; j < _totalClmns; j++)
      ptrC[i][j] = NULL;
}

//This function generates and returns a random number within range [lo, hi]
int Board::getRand(int lo, int hi)
{
  int randomN = rand()%(hi-lo+1) + lo;
  return randomN;
}

/***********************************************************
This function generates a specified number of random numbers
within range [1, gridsCount] and stores them in a vector(data
member of Board class). All random numbers are different.
***********************************************************/
void Board::getAllRands()
{
  //requirement not met yet, generate more randoms
  while(randomNums.size() < _totalCritters)
  {
    //Get one random num
    int oneRand = getRand(0, _totalRows*_totalClmns-1);
    //Loop thru the vector, check if num is already in the vector
    bool inVec = false;
    for (unsigned i = 0; i < randomNums.size(); i++)
      if (randomNums[i] == oneRand)
        inVec = true;
    if (!inVec)
      randomNums.push_back(oneRand);
  }
}

/***********************************************************
This function receives a parameter of random number and
translates it into a grid's row index on board.
***********************************************************/
int Board::transRandToRow(int randomN)
{
  return randomN/_totalClmns;
}

/***********************************************************
This function receives a parameter of random number and
translates it into a grid's column index on board.
***********************************************************/
int Board::transRandToCol(int randomN)
{
  return randomN%_totalClmns;
}

/***********************************************************
This function initializes board with 5 doodlebugs and 100
ants randomly placed.
***********************************************************/
void Board::placeCritterOnBoard()
{
  initBoard();
  getAllRands();
  //Initialize each Critter on Board
  //Initialize doodlebugs
  for (unsigned i = 0; i < _doodlebugNum; i++)
  {
    int row = transRandToRow(randomNums[i]);
    int col = transRandToCol(randomNums[i]);
    ptrC[row][col] = new Doodlebug(row, col, this);
  }
  //Initialize ants
  for (unsigned i = _doodlebugNum; i < randomNums.size(); i++)
  {
    int row = transRandToRow(randomNums[i]);
    int col = transRandToCol(randomNums[i]);
    ptrC[row][col] = new Ant(row, col, this);
  }
}

/***********************************************************
This function simulates game flow.
Initialize board with specified number of critters and start game.
For each step, doodlebugs move -> ants move ->
Ants and Doodlebugs Breed -> Doodlebugs starve.
Print board with each step.
***********************************************************/
void Board::startGame()
{
  bool end = false;
  while (!end)
  {
    //If first play, initialize board
    if (_firstPlay)
      placeCritterOnBoard();
    //Start game
    int stepCount = 1;    //Init step counter
    while (stepCount <= _totalSteps)
    {
      cout << "Step " << stepCount << endl;

      //****Move: Doodlebug move first, then ants move
      //Loop thru 2D array, get each ptr, move each Critter
      //First condition: exclude null ptrs
      //Second condition: check type, ant or doodlebug
      //Third condition: check move status. Exclude Critters just moved
      //***Doodlebugs move
      for (int i = 0; i < _totalRows; i++)
        for (int j = 0; j < _totalClmns; j++)
          if (ptrC[i][j])
            if (ptrC[i][j]->getType() == 2)
              if (ptrC[i][j]->getJustMoved() == 0)
                ptrC[i][j]->move();

      //***Ants move
      for (int i = 0; i < _totalRows; i++)
        for (int j = 0; j < _totalClmns; j++)
          if (ptrC[i][j])
            if (ptrC[i][j]->getType() == 1)
              if (ptrC[i][j]->getJustMoved() == 0)
                ptrC[i][j]->move();

      //Ants and Doodlebugs Breed
      for (int i = 0; i < _totalRows; i++)
        for (int j = 0; j < _totalClmns; j++)
          if (ptrC[i][j])
              ptrC[i][j]->breed();

      //Doodlebugs starve
      for (int i = 0; i < _totalRows; i++)
        for (int j = 0; j < _totalClmns; j++)
          if (ptrC[i][j])
            ptrC[i][j]->starve();

      //Print each step's board
      printBoard();

      //Reset _justMoved
      //Loop thru 2D array, get each ptr, reset _justMoved
      for (int i = 0; i < _totalRows; i++)
        for (int j = 0; j < _totalClmns; j++)
          if (ptrC[i][j])
            ptrC[i][j]->setJustMoved();
      //Update step counter
      stepCount++;
    }
    if (!playAgain())
      end = true;
  }
}

//This function checks if a grid in a specified direction is occupied
bool Board::isEmpty(Critter* critter, int dir)
{
  //Get this critter's current location
  int row = critter->getCurrRow();
  int col = critter->getCurrClmn();

  //Check up direction, excluding edge cases
  if (dir == 1 && row > 0)
    if (ptrC[row-1][col] == NULL)
      return true;
  //Check right direction, excluding edge cases
  if (dir == 2 && col < _totalClmns-1)
    if (ptrC[row][col+1] == NULL)
      return true;
  //Check down direction, excluding edge cases
  if (dir == 3 && row < _totalRows-1)
    if (ptrC[row+1][col] == NULL)
      return true;
  //Check left direction, excluding edge cases
  if (dir == 4 && col > 0)
    if (ptrC[row][col-1] == NULL)
      return true;

  //Catch-all else
  return false;
}

//This function checks if surrouding grids have ants present
int Board::findAnts(Critter* critter)
{
  //Get this critter's current location
  int row = critter->getCurrRow();
  int col = critter->getCurrClmn();
  //Check up direction
  //First condition: excluding edge cases
  //Second condition: exclude null ptrs
  //Third condition: Critter type match
  if (row > 0 && ptrC[row-1][col] && ptrC[row-1][col]->getType() == 1)
    return 1;
  //Check right direction
  if (col < _totalClmns-1 && ptrC[row][col+1] && ptrC[row][col+1]->getType() == 1)
    return 2;
  //Check down direction
  if (row < _totalRows-1 && ptrC[row+1][col] && ptrC[row+1][col]->getType() == 1)
    return 3;
  //Check left direction
  if (col > 0 && ptrC[row][col-1] && ptrC[row][col-1]->getType() == 1)
    return 4;
  //No ants in surrouding grids present. Return false
  return 0;
}


/************************************************
This function prints the board, using ASCII chars
of “O” for an ant, “X” for a doodlebug and
blank space for an empty space.
************************************************/
void Board::printBoard()
{
  char ant = '0';
  char doodlebug = 'x';
  char blank = ' ';
  //Print a border
  for (int i = 0; i < 32; i++)
    cout << "--";
  cout << endl;
  //Loop thru the 2D array, get each ptr to Critter
  for (int i = 0; i <_totalRows; i++)
  {
    cout << "|";    //Border
    for (int j = 0; j <_totalClmns; j++)
    {
      //if ptr to critter is null, blank space
      if (!ptrC[i][j])
        cout << blank << "  ";
      //ptr to critter is not null, print the critter
      else
      {
        if (ptrC[i][j]->getType() == 1)
          cout << ant << "  ";
        else
          cout << doodlebug << "  ";
      }
    }
    cout << "|" << endl;    //border
  }
  //Print a border
  for (int i = 0; i < 32; i++)
    cout << "--";
  cout << endl;
}

//This function asks user whether to play again and return a bool
bool Board::playAgain()
{
  //At least one game completed. Set _firstPlay status to false;
  _firstPlay = false;
  //Get user choice: 1 for yes, 0 for exit
  int choice;
  cout << endl << "--------------------------" << endl;
  cout << "Play again?" << endl;
  cout << "Enter 1 to play again, or enter 0 to exit: ";
  cin >> choice;
  //Play again. Get number of steps
  if (choice == 1)
  {
    cout << "How many steps do you want to play?" << endl;
    cout << "Please enter an integer between 1 and 32767: ";
    cin >> _totalSteps;
    return true;
  }
  else
  {
    cout << "Goodbye." << endl;
    return false;
  }
}

//getters
Critter*** Board::getBoard()
{
  return ptrC;
}

int Board::getTotalRows()
{
  return _totalRows;
}

int Board::getTotalColmns()
{
  return _totalClmns;
}

//Destructor
Board::~Board()
{
  for (int i = 0; i < _totalRows; i++)
    for (int j = 0; j < _totalClmns; j++)
      if (ptrC[i][j])
        delete ptrC[i][j];
}
