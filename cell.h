#pragma once

#include <iostream>
#include <utility>

class Cell {

  private:
    //Cell& Antecessor;
    int ID;
    int AntecessorID;
    char cell_value;
    bool open_cell;
    bool is_visited;
    std::pair<int,int> coordinates;
    int cost;
    int heuristic_value;
    int evaluation_function;
  
  public:
    Cell();
    Cell(char new_cell_value);
    ~Cell();
    char& get_CellValue();
    bool& get_OpenCell();
    bool& get_IsVisited();
    std::pair<int,int>& get_Coordinates();
    int& get_XCoord();
    int& get_YCoord();
    int& get_Cost();
    int& get_Heuristic_Value();
    int& get_Evaluation_Function();
    int& get_ID();
    int& get_AntecessorID();
    
    void set_AntecessorID(int parametre);
    void set_ID(int id_param);
    void set_CellValue(char parametre);
    void set_OpenCell(bool parametre);
    void set_IsVisited(bool parametre);
    void set_Coordinates(std::pair<int,int>& param_coords);
    void set_XCoord(int x_param);
    void set_YCoord(int y_param);
    void set_Cost(int cost_param);
    void set_Heuristic_Value(int heur_param);
    void set_Evaluation_Function(int eval_param);   
    friend std::ostream& operator<<(std::ostream &os, Cell &cell_ );
    Cell& operator=(const Cell &cell_);
    bool operator==(const Cell &cell_)const;
    bool operator<(const Cell &cell_)const;
    bool operator!=(const Cell &cell_)const;
};

