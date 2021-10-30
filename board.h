#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <assert.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <utility>

#include "taxi.h"
#include "cell.h"


class Board {
  private:
    Cell **tableboard;
    Taxi car;
    Cell start;
    Cell destination;
    int rows;
    int columns;

  public:
    Board();
    Board(int row_parameter, int col_parameter);
    ~Board();
    Cell** get_tableboard();
    Taxi get_taxi();
    int get_rows();
    int get_columns();
    Cell get_destination();
    Cell get_start();
    void Create_Board();
    void Write();
    void RandomFill();
    void FillByPercent(int percent);
    void FillManual(int x, int y);
    void RandomDestination();
    void ManualDestination(int x, int y);
    void ManualInsertTaxi(int x, int y);
    void RandomInsertTaxi();

    //*****DELETE******
    //void WriteCoords();
};
