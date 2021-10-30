#pragma once
#include <iostream>
#include <utility>

class Taxi {
  private:
    char body;
    std::pair<int,int> taxi_place;
  
  public:
    Taxi();
    Taxi(int x, int y);
    ~Taxi();
    void SetBody(char body_parametre);
    void SetTaxiPlace(int x, int y);
    char GetBody();
    std::pair<int,int> get_TaxiPlace();
    int GetXCoord();
    int GetYCoord();
};