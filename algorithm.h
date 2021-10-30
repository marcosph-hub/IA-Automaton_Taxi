#pragma once

#include <iostream>
#include <vector>
#include <utility>
#include <cmath>


#include "cell.h"
#include "board.h"

class Algorithm {
  private:
    std::vector<Cell> open_cells_list;
    std::vector<Cell> close_cells_list;
    Cell start;
    Cell destination;
    Cell Antecessor;
    int cost;
    int heuristic;
    int evaluative_function;

  public:
    Algorithm(Board& tableboard);
    void A_Star(Cell current_cell);

  //private:
    bool is_destination(Cell cell_);
    Cell functions_update(Cell current_cell);
    int Manhattan(Cell current_cell);
    bool obstacle_comprobation(Cell current_cell);
    void sort_vector();
  
};