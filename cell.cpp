#include "cell.h"

Cell::Cell() {
  cell_value = ' ';
  open_cell = false;
  is_visited = false;
  cost = 0;
  heuristic_value = 0;
  evaluation_function = 0;
}

Cell::Cell(char new_cell_value) {
  cell_value = new_cell_value;
  open_cell = false;
  is_visited = false;
  cost = 0;
  heuristic_value = 0;
  evaluation_function = 0;
}

Cell::~Cell() {}

char& Cell::get_CellValue() {
  return cell_value;
}

bool& Cell::get_OpenCell() {
  return open_cell;
}

bool& Cell::get_IsVisited() {
  return is_visited;
}

std::pair<int,int>& Cell::get_Coordinates() {
  ////std::cout << "get_coordinate [" << coordinates.first << " " << coordinates.second << "]" << std::endl;
  return coordinates;
}

int& Cell::get_XCoord() {
  ////std::cout << "getXcoord [" << coordinates.first << "]" << std::endl;
  return coordinates.first;
}

int& Cell::get_YCoord() {
  ////std::cout << "getYcoord [" << coordinates.second << "]" << std::endl;
  return coordinates.second;
}

int& Cell::get_Cost() {
  return cost;
}

int& Cell::get_Heuristic_Value() {
  return heuristic_value;
}

int& Cell::get_Evaluation_Function() {
  return evaluation_function;
}

int& Cell::get_ID() {
  return ID;
}

int& Cell::get_AntecessorID() {
  return AntecessorID;
}

void Cell::set_AntecessorID(int parametre) {
  AntecessorID = parametre;
}

void Cell::set_ID(int id_param) {
  ID = id_param;
}

void Cell::set_Coordinates(std::pair<int,int>& param_coords) {
  ////std::cout << "set_coordinates ->" << param_coords.first << " " << param_coords.second << std::endl;
  coordinates = param_coords;
}

void Cell::set_XCoord(int x_param) {
  ////std::cout << "set_Xcoord ->" << x_param << std::endl;
  coordinates.first = x_param;
}

void Cell::set_YCoord(int y_param) {
  ////std::cout << "set_Ycoord ->" << y_param << std::endl;
  coordinates.second = y_param;
}

void Cell::set_CellValue(char parametre) {
  cell_value = parametre;
}

void Cell::set_OpenCell(bool parametre) {
  open_cell = parametre;
}

void Cell::set_IsVisited(bool parametre) {
  is_visited = parametre;
}

void Cell::set_Cost(int cost_param) {
  cost = cost_param;
}

void Cell::set_Heuristic_Value(int heur_param) {
  heuristic_value = heur_param;
}

void Cell::set_Evaluation_Function(int eval_param) {
  evaluation_function = eval_param;
}

std::ostream& operator<<(std::ostream &os, Cell &cell_) {
  os << "Valor -> " << cell_.get_CellValue() << std::endl;
  //os << "AntecesorID -> "<< cell_.get_AntecessorID() << std::endl;
  //os << "ID -> " << cell_.get_ID() << std::endl;
  //os << "isvisited -> " << cell_.get_IsVisited() << std::endl;
  //os << "Coords -> " << cell_.get_Coordinates().first << " " << cell_.get_Coordinates().second << std::endl;;
  //os << "g(n) -> " << cell_.get_Cost() << std::endl;
  //os << "h(n) -> " << cell_.get_Heuristic_Value() << std::endl;
 // os << "f(n) -> " << cell_.get_Evaluation_Function() << std::endl;
  //os << "___________";
  return os;
}

Cell& Cell::operator=(const Cell &cell_) {
  this->cell_value = cell_.cell_value;
  this->is_visited = cell_.is_visited;
  this->open_cell = cell_.open_cell;
  this->coordinates.first = cell_.coordinates.first;
  this->ID = cell_.ID;
  this->AntecessorID = cell_.AntecessorID;
  this->coordinates.second = cell_.coordinates.second;
  this->cost = cell_.cost;
  this->heuristic_value = cell_.heuristic_value;
  this->evaluation_function = cell_.evaluation_function;
  return *this;
}

bool Cell::operator==(const Cell &cell_) const {
  if(
    this->coordinates.first == cell_.coordinates.first &&
    this->coordinates.second == cell_.coordinates.second ) { return true; }
    return false;
}

bool Cell::operator!=(const Cell &cell_) const {
  if(
    this->coordinates.first != cell_.coordinates.first &&
    this->coordinates.second != cell_.coordinates.second ) { return true; }
    return false;
}

bool Cell::operator<(const Cell &cell_) const{
  if (this->evaluation_function < cell_.evaluation_function) {return true; }
  return false;
}
