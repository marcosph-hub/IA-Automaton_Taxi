#include "algorithm.h"
#define RED "\e[0;31m"//
#define GRN "\e[0;92m"//
#define NC "\e[0m"
#define YLW "\e[0;93m" //
#define CYN "\e[1;96m"
#define RR "\e[1;31m"

Algorithm::Algorithm(Board& tableboard_, int movements, int fheuristic) {
  map = tableboard_;
  start.set_XCoord(tableboard_.get_taxi().GetXCoord()); 
  start.set_YCoord(tableboard_.get_taxi().GetYCoord());
  start.set_CellValue(tableboard_.get_taxi().GetBody());
  destination = tableboard_.get_destination();
  user_heuristic = fheuristic;
  user_movements = movements;
  iterations = 0;
}


void Algorithm::A_Star() {

  Cell current_cell = map.ExtractCell(start);
  int iteration = 0;
  bool is_the_end = false;
  open_cells_list.push_back(current_cell);
  while((iteration < 1000) && (!is_the_end)) {
    if(is_destination(current_cell)) {
      is_the_end = true;
    }

    if (obstacle_comprobation(map.get_tableboard()[current_cell.get_XCoord()+1][current_cell.get_YCoord()])) {
      if(!map.get_tableboard()[current_cell.get_XCoord()+1][current_cell.get_YCoord()].get_IsVisited()) {
        if(!RepeatedCell(map.get_tableboard()[current_cell.get_XCoord()+1][current_cell.get_YCoord()])) {
          map.get_tableboard()[current_cell.get_XCoord()+1][current_cell.get_YCoord()].set_AntecessorID(current_cell.get_ID());
          functions_update(map.ExtractCell(map.get_tableboard()[current_cell.get_XCoord()+1][current_cell.get_YCoord()]), 1);
          open_cells_list.push_back(map.get_tableboard()[current_cell.get_XCoord()+1][current_cell.get_YCoord()]);
        }
      }
    }
    if (obstacle_comprobation(map.get_tableboard()[current_cell.get_XCoord()-1][current_cell.get_YCoord()])) {
      if(!map.get_tableboard()[current_cell.get_XCoord()-1][current_cell.get_YCoord()].get_IsVisited()) {
        if(!RepeatedCell(map.get_tableboard()[current_cell.get_XCoord()-1][current_cell.get_YCoord()])) {
          map.get_tableboard()[current_cell.get_XCoord()-1][current_cell.get_YCoord()].set_AntecessorID(current_cell.get_ID());
          functions_update(map.ExtractCell(map.get_tableboard()[current_cell.get_XCoord()-1][current_cell.get_YCoord()]), 1);
          open_cells_list.push_back(map.get_tableboard()[current_cell.get_XCoord()-1][current_cell.get_YCoord()]);
        }
      }
    }
    if (obstacle_comprobation(map.get_tableboard()[current_cell.get_XCoord()][current_cell.get_YCoord()+1])) {
      if(!map.get_tableboard()[current_cell.get_XCoord()][current_cell.get_YCoord()+1].get_IsVisited()) {
        if(!RepeatedCell(map.get_tableboard()[current_cell.get_XCoord()][current_cell.get_YCoord()+1])) {
          map.get_tableboard()[current_cell.get_XCoord()][current_cell.get_YCoord()+1].set_AntecessorID(current_cell.get_ID());
          functions_update(map.ExtractCell(map.get_tableboard()[current_cell.get_XCoord()][current_cell.get_YCoord()+1]), 1);
          open_cells_list.push_back(map.get_tableboard()[current_cell.get_XCoord()][current_cell.get_YCoord()+1]);
        }
      }
    }
    if (obstacle_comprobation(map.get_tableboard()[current_cell.get_XCoord()][current_cell.get_YCoord()-1])) {
      if(!map.get_tableboard()[current_cell.get_XCoord()][current_cell.get_YCoord()-1].get_IsVisited()) {
        if(!RepeatedCell(map.get_tableboard()[current_cell.get_XCoord()][current_cell.get_YCoord()-1])) {
          map.get_tableboard()[current_cell.get_XCoord()][current_cell.get_YCoord()-1].set_AntecessorID(current_cell.get_ID());
          functions_update(map.ExtractCell(map.get_tableboard()[current_cell.get_XCoord()][current_cell.get_YCoord()-1]), 1);
          open_cells_list.push_back(map.get_tableboard()[current_cell.get_XCoord()][current_cell.get_YCoord()-1]);
        }
      }
    }
    if(user_movements == 2) {
      if (obstacle_comprobation(map.get_tableboard()[current_cell.get_XCoord()+1][current_cell.get_YCoord()+1])) {
        if(!map.get_tableboard()[current_cell.get_XCoord()+1][current_cell.get_YCoord()+1].get_IsVisited()) {
          if(!RepeatedCell(map.get_tableboard()[current_cell.get_XCoord()][current_cell.get_YCoord()-1])) {
            map.get_tableboard()[current_cell.get_XCoord()+1][current_cell.get_YCoord()+1].set_AntecessorID(current_cell.get_ID());
            functions_update(map.ExtractCell(map.get_tableboard()[current_cell.get_XCoord()+1][current_cell.get_YCoord()+1]), 2);
            open_cells_list.push_back(map.get_tableboard()[current_cell.get_XCoord()+1][current_cell.get_YCoord()+1]);
          }
        }
      } if (obstacle_comprobation(map.get_tableboard()[current_cell.get_XCoord()-1][current_cell.get_YCoord()-1])) {
        if(!map.get_tableboard()[current_cell.get_XCoord()-1][current_cell.get_YCoord()-1].get_IsVisited()) {
          if(!RepeatedCell(map.get_tableboard()[current_cell.get_XCoord()-1][current_cell.get_YCoord()-1])) {
            map.get_tableboard()[current_cell.get_XCoord()-1][current_cell.get_YCoord()-1].set_AntecessorID(current_cell.get_ID());
            functions_update(map.ExtractCell(map.get_tableboard()[current_cell.get_XCoord()-1][current_cell.get_YCoord()-1]), 2);
            open_cells_list.push_back(map.get_tableboard()[current_cell.get_XCoord()-1][current_cell.get_YCoord()-1]);
          }
        }
      } if (obstacle_comprobation(map.get_tableboard()[current_cell.get_XCoord()+1][current_cell.get_YCoord()-1])) {
        if(!map.get_tableboard()[current_cell.get_XCoord()+1][current_cell.get_YCoord()-1].get_IsVisited()) {
          if(!RepeatedCell(map.get_tableboard()[current_cell.get_XCoord()+1][current_cell.get_YCoord()-1])) {
            map.get_tableboard()[current_cell.get_XCoord()+1][current_cell.get_YCoord()-1].set_AntecessorID(current_cell.get_ID());
            functions_update(map.ExtractCell(map.get_tableboard()[current_cell.get_XCoord()+1][current_cell.get_YCoord()-1]), 2);
            open_cells_list.push_back(map.get_tableboard()[current_cell.get_XCoord()+1][current_cell.get_YCoord()-1]);
          }
        }
      } if (obstacle_comprobation(map.get_tableboard()[current_cell.get_XCoord()-1][current_cell.get_YCoord()+1])) {
        if(!map.get_tableboard()[current_cell.get_XCoord()-1][current_cell.get_YCoord()+1].get_IsVisited()) {
          if(!RepeatedCell(map.get_tableboard()[current_cell.get_XCoord()-1][current_cell.get_YCoord()+1])) {
            map.get_tableboard()[current_cell.get_XCoord()-1][current_cell.get_YCoord()+1].set_AntecessorID(current_cell.get_ID());
            functions_update(map.ExtractCell(map.get_tableboard()[current_cell.get_XCoord()-1][current_cell.get_YCoord()+1]), 2);
            open_cells_list.push_back(map.get_tableboard()[current_cell.get_XCoord()-1][current_cell.get_YCoord()+1]);
          }
        }
      }
    }
    

    map.ExtractCell(current_cell).set_IsVisited(true);
    open_cells_list.erase(open_cells_list.begin());
    close_cells_list.push_back(current_cell);
    std::sort(open_cells_list.begin(), open_cells_list.end());
    current_cell = map.ExtractCell(open_cells_list[0]);

    if (open_cells_list.size() != 0) {
      current_cell = map.ExtractCell(open_cells_list[0]);
    } else { 
      is_the_end = true;}
    iteration++;

  }
  iterations = iteration;
  Cell aux;
  aux = close_cells_list[close_cells_list.size()-1];
  bool detention = false;

  while(!detention) {
    if(aux == start) {
      Result.insert(Result.begin(), aux);
      detention = true;
    } else {
      Result.insert(Result.begin(), aux);
      aux = ID_to_coords(aux.get_AntecessorID());
    }
  }
}


Cell& Algorithm::ID_to_coords(int id) {
  int x = id / map.get_rows();
  int y = (id % map.get_columns())-1;
  return map.get_tableboard()[x][y];
}

bool Algorithm::RepeatedCell(Cell& cell_) {
  for (unsigned int i = 0; i < open_cells_list.size(); ++i) {
    if(cell_ == open_cells_list[i])
    return true;
    }
  return false;
}

bool Algorithm::is_start(Cell cell_) {
  if (cell_ == start) { return true; }
  return false;
}

bool Algorithm::is_in_close_list(Cell current_cell) {

  for(unsigned int iterator = 0; iterator < close_cells_list.size(); ++iterator){
    if(current_cell == close_cells_list[iterator]) { 
      return true; }
  }
  return false;
}

bool Algorithm::is_destination(Cell cell_) {
  if (cell_.get_Coordinates() == destination.get_Coordinates()){
    return true;
  } else {return false;}
}


void Algorithm::functions_update(Cell& current_cell, int param_cost) {
  int heuristic = 0;
  if(current_cell == start) {
    int cost = 0;
    if (user_heuristic == 1) {
       heuristic = Manhattan(current_cell);
    } else {
       heuristic = Euclidean(current_cell);
    }
    int evaluative_function = cost + heuristic;
    current_cell.set_Cost(cost);
    
    current_cell.set_Evaluation_Function(evaluative_function);
  } else {
    int AntecessorCost = ID_to_coords(current_cell.get_AntecessorID()).get_Cost();
    int cost = AntecessorCost + param_cost;
    if (user_heuristic == 1) {
       heuristic = Manhattan(current_cell);

    } else {
       heuristic = Euclidean(current_cell);
    }
    int evaluative_function = cost + heuristic;
    current_cell.set_Cost(AntecessorCost+1);
    current_cell.set_Heuristic_Value(heuristic);
    current_cell.set_Evaluation_Function(evaluative_function);
  }
  
}

int Algorithm::Manhattan(Cell current_cell) {
  int manhattan_value = ((abs(current_cell.get_XCoord() - destination.get_XCoord())) + (abs(current_cell.get_YCoord() - destination.get_YCoord())));
  return manhattan_value;
}

int Algorithm::Euclidean(Cell current_cell) {
  int euclidean_value = sqrt(pow((current_cell.get_XCoord() - destination.get_XCoord()),2) + pow((current_cell.get_YCoord() - destination.get_YCoord()),2));
  return euclidean_value;
}

bool Algorithm::obstacle_comprobation(Cell current_cell) {
  if((current_cell.get_CellValue() == ' ') || current_cell.get_CellValue() == destination.get_CellValue() ) {
    return true;
  } return false;
}

void Algorithm::Write() { 

  if(Result[Result.size()-1] == destination){
    usleep(30000);
    std::cout << "\033[2J\033[1;1H"; 
    Cell current_cell;
    unsigned int iterator = 0;
      map.get_taxi().SetTaxiPlace(Result[iterator].get_XCoord(), Result[iterator].get_YCoord());
      map.Write();

      iterator++;
    while(iterator < Result.size()){
      usleep(300000);
      std::cout << "\033[2J\033[1;1H"; 
      map.get_taxi().SetTaxiPlace(Result[iterator].get_XCoord(), Result[iterator].get_YCoord());
      map.ExtractCell(ID_to_coords(map.ExtractCell(Result[iterator]).get_AntecessorID())).set_CellValue('.');
      iterator++;
      map.Write(); 
    }
  } else {
    map.Write();
    std::cout << RED << "El destino es inaccesible" << std::endl;
  }
 std::cout << YLW << "Number of Iterations: " << GRN << iterations << std::endl;
 std::cout << YLW << "Camino minimo:" << std::endl;
  for (unsigned int i = 0; i < close_cells_list.size(); ++i) {
    std::cout << NC << "[" << close_cells_list[i].get_Coordinates().first << "," << close_cells_list[i].get_Coordinates().second << "] ";
  }
  std::cout << std::endl;
}
