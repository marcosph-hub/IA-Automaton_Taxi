#include "algorithm.h"

Algorithm::Algorithm(Board& tableboard) {
  /*
  for(int i = 0; i < tableboard.get_rows(); ++i){
    for(int j = 0; j < tableboard.get_columns(); ++j) {
      std::cout << "[" << tableboard.get_tableboard()[i][j].get_XCoord() << ","
      << tableboard.get_tableboard()[i][j].get_YCoord() << "]" << std::endl;
    }
  }
*/

  start = tableboard.get_start();
  destination = tableboard.get_destination();
  cost = 0;
//open_cells_list.push_back(start);
}

void Algorithm::A_Star(Cell current_cell) {
  //for()
  open_cells_list.push_back(current_cell);
  if (is_destination(current_cell)) {
    //terminar
    std::cout << "final" << std::endl;
  } Antecessor = current_cell;
  //expandir hijos
  current_cell = functions_update(current_cell);
}

bool Algorithm::is_destination(Cell cell_) {
  if (cell_ == destination){
    return true;
  } return false;
}

Cell Algorithm::functions_update(Cell current_cell) {
  heuristic = Manhattan(current_cell);
  evaluative_function = cost + heuristic;
  cost = cost +1; //acceder al coste padre
  current_cell.set_Cost(cost);
  current_cell.set_Heuristic_Value(heuristic);
  current_cell.set_Evaluation_Function(evaluative_function);
  return current_cell;
}

int Algorithm::Manhattan(Cell current_cell) {
  int manhattan_value = ((abs(current_cell.get_XCoord() - destination.get_XCoord())) + (abs(current_cell.get_YCoord() - destination.get_YCoord())));
  return manhattan_value;
}

bool Algorithm::obstacle_comprobation(Cell current_cell) {
  //current_cell.get_Coordinates().first +1???????????
  if(current_cell.get_CellValue() == ' ') {
    open_cells_list.push_back(current_cell);
  }
}

void Algorithm::sort_vector() {
  int max_value = Manhattan(start);
  for (int iterator = 0; iterator < open_cells_list.size(); ++iterator) {
    if (open_cells_list[iterator].get_Evaluation_Function < max_value) {
      open_cells_list[0] = open_cells_list[iterator];
    }
  }
}