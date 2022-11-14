#pragma once

#include <iostream>
#include <vector>
#include <utility>
#include <cmath>
#include <ctime>
#include <climits>
#include <algorithm>
#include <cstdlib>
#include <math.h>


#include "cell.h"
#include "board.h"

class Algorithm {
  private:
    Board map;
    Cell** map_;
    std::vector<Cell> open_cells_list;
    std::vector<Cell> close_cells_list;
    std::vector<Cell> aux_open_list;
    std::vector<Cell> Result;
    Cell start;
    Cell destination;
    int user_heuristic;
    int user_movements;
    int iterations;

  public:
    Algorithm(Board& tableboard, int movements, int fheuristic);
    void A_Star();
    bool is_destination(Cell cell_);
    bool is_start(Cell cell_);
    void functions_update(Cell& current_cell, int param_cost);
    int Manhattan(Cell current_cell);
    int Euclidean(Cell current_cell);
    bool obstacle_comprobation(Cell current_cell);
    bool is_in_close_list(Cell current_cell);
    void SelectionSort();
    bool RepeatedCell(Cell& cell_);
    Cell& ID_to_coords(int id);
    void Write();
    
};