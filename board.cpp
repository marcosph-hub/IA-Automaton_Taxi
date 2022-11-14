#define RED "\e[0;31m"//
#define GRN "\e[0;92m"//
#define NC "\e[0m"
#define YLW "\e[0;93m" //
#define CYN "\e[1;96m"
#define RR "\e[1;31m"

#include "board.h"

Board::Board() {
  rows = 22;   
  columns = 22;
  tableboard = new Cell*[rows];
  int cell_id = 0;
  for (int iterator = 0; iterator < rows; iterator++) {
    tableboard[iterator] = new Cell[columns];
  }
  for (int row_iterator = 0; row_iterator < rows; ++row_iterator) {
    for (int col_iterator = 0; col_iterator < columns; ++col_iterator) {
      std::pair<int,int> coords;
      coords.first = row_iterator;
      coords.second = col_iterator;
      cell_id = cell_id +1;
      tableboard[row_iterator][col_iterator].set_Coordinates(coords);
      tableboard[row_iterator][col_iterator].set_ID(cell_id);
    }
  }
  Create_Board();
}

Board::Board(int row_parameter, int col_parameter) {
  int xcoord = 0;
  int ycoord = 0;
  rows = row_parameter +2 ;
  columns = col_parameter +2;
  int cell_id = 0;
  tableboard = new Cell*[rows];
  for (int iterator = 0; iterator < rows; iterator++) {
    tableboard[iterator] = new Cell[columns];
  }
  for (int row_iterator = 0; row_iterator < rows; row_iterator++) {
    for (int col_iterator = 0; col_iterator < columns; col_iterator++) {
      std::pair<int,int> coords;
      coords.first = xcoord;
      coords.second = ycoord;
      ycoord++;
      cell_id = cell_id +1;
      tableboard[row_iterator][col_iterator].set_Coordinates(coords);
      tableboard[row_iterator][col_iterator].set_ID(cell_id);
    }
    xcoord ++;
    ycoord = 0;
  }
  Create_Board();
}

Board::~Board(){
  
  for (int iterator = 0; iterator < rows; iterator++) {
    delete [] tableboard[iterator];
  }
  delete [] tableboard;
  
}

Cell**& Board::get_tableboard() {
  return tableboard;
}

Taxi& Board::get_taxi() {
  return car;
}

int Board::get_rows() {
  return rows;
}

int Board::get_columns() {
  return columns;
}

Cell& Board::get_destination() {
  return destination;
}

Cell& Board::get_start() {
  return start;
}

void Board::Create_Board() {

  for (int row_iterator = 0; row_iterator < rows; row_iterator++ ) {
    for (int col_iterator = 0; col_iterator < columns; col_iterator++) {
      if ((col_iterator == 0) || (col_iterator == columns -1)) {
        tableboard[row_iterator][col_iterator].set_CellValue('|') ;
      } else if ((row_iterator == 0) && (col_iterator != 0)) {
        tableboard[row_iterator][col_iterator].set_CellValue('*');
      } else if ((row_iterator == rows-1) && (col_iterator != columns -1)) {
        tableboard[row_iterator][col_iterator].set_CellValue('*');
      } else {
        tableboard[row_iterator][col_iterator].set_CellValue(' ');
      }
    }
  }
}

void Board::FillByPercent(int percent) {
  int dimension = rows * columns;
  float fpercent = percent / 100.0;
  int n_obstacles = dimension * fpercent;

   for (int obst_iterator = 0; obst_iterator < n_obstacles; obst_iterator++) {
    int rand_row = rand() % (rows -1);
    int rand_col = rand() % (columns -1);
    for (int row_iterator = 1; row_iterator < rows -1; row_iterator++ ) {
      for (int col_iterator = 1; col_iterator < columns -1; col_iterator++) {
        if ((row_iterator == rand_row) && (col_iterator == rand_col)) {
          tableboard[rand_row][rand_col].set_CellValue('O');
        }
      }
    }
  }
}


void Board::RandomFill() {
  srand (time(NULL));
  int total_cells = rows * columns;
  int nobstacles = rand() % total_cells;
  for (int obst_iterator = 0; obst_iterator < nobstacles; obst_iterator++) {
    int rand_row = rand() % (rows -1);
    int rand_col = rand() % (columns -1);
    for (int row_iterator = 1; row_iterator < rows -1; row_iterator++ ) {
      for (int col_iterator = 1; col_iterator < columns -1; col_iterator++) {
        if ((row_iterator == rand_row) && (col_iterator == rand_col)) {
          tableboard[rand_row][rand_col].set_CellValue('O');
        }
      }
    }
  }
}

void Board::FillManual(int x, int y){
  if (tableboard[x][y].get_CellValue() == ' '){
    tableboard[x][y].set_CellValue('O');
  }
}

void Board::RandomDestination() {
  int rand_row = 1 + rand() % (rows -2);
  int rand_col = 1 + rand() % (columns -2);
  tableboard[rand_row][rand_col].set_CellValue('F');
  destination.set_CellValue('F');
  destination.set_XCoord(rand_row);
  destination.set_YCoord(rand_col);
}

void Board::ManualDestination(int x, int y){
  tableboard[x][y].set_CellValue('F');
  destination.set_CellValue('F');
  destination.set_XCoord(x);
  destination.set_YCoord(y);
}

void Board::ManualInsertTaxi(int x, int y) {
  car.SetTaxiPlace(x,y);
  start.set_XCoord(x);
  start.set_YCoord(y);
  start.set_CellValue(car.GetBody());
  tableboard[x][y].set_CellValue(car.GetBody());
}

void Board::RandomInsertTaxi(){
  srand(time(NULL));
  int rand_row;
  int rand_col;
  rand_row = 1 + rand() % (rows -2);
  rand_col = 1 + rand() % (columns -2);
  car.SetTaxiPlace(rand_row, rand_col);
  start.set_XCoord(rand_row);
  start.set_YCoord(rand_col);
  start.set_CellValue(car.GetBody());
  tableboard[rand_row][rand_col].set_CellValue(car.GetBody());
}


void Board::Write() {
  for (int i=0; i < rows; i++){
    for (int j=0; j < columns; j++){
      if ((i == car.GetXCoord()) && (j == car.GetYCoord())) {
          std::cout << YLW << car.GetBody() << ' ';
      } else if (tableboard[i][j].get_CellValue() == 'F') {
          std::cout << GRN << tableboard[i][j].get_CellValue() << ' ';
      } else if((tableboard[i][j].get_CellValue() == '*') || (tableboard[i][j].get_CellValue() == '|')) {
          std::cout << CYN << tableboard[i][j].get_CellValue() << ' ';
      } else if (tableboard[i][j].get_CellValue() == 'O') {
          std::cout << RR << tableboard[i][j].get_CellValue() << ' ';
      } else {
          std::cout << NC << tableboard[i][j].get_CellValue() << ' ';
      }
    }
    std::cout << std::endl;
  }
}
Board& Board::operator=(const Board &parametre) {
  this->tableboard = parametre.tableboard;
  this->car = parametre.car;
  this->start = parametre.start;
  this->destination = parametre.destination;
  this->rows = parametre.rows;
  this->columns = parametre.columns;
  return *this;
}



Cell& Board::ExtractCell(Cell parametre) {
  for(int i = 1; i < rows-1; ++i) {
    for (int j = 1; j < columns-1; ++j) {
      if(tableboard[i][j] == parametre) {
        return tableboard[i][j];
      }
    }
  }
  return tableboard[0][0];
}

Cell& Board::ExtractByID(int id) {
  for(int i = 1; i < rows-1; ++i) {
    for (int j = 1; j < columns-1; ++j) {
      if(tableboard[i][j].get_ID() == id) {
        return tableboard[i][j];
      }
    }
  }
  return tableboard[0][0];
}

