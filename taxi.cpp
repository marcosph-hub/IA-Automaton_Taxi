#include "taxi.h"

Taxi::Taxi() {
  body = '>';
  taxi_place.first = -1;
  taxi_place.second = -1;
}

Taxi::Taxi(int x, int y) {
  body = '>';
  taxi_place.first = x;
  taxi_place.second = y;
}

Taxi::~Taxi() {}

void Taxi::SetBody(char body_parametre){
  body = body_parametre;
}

char Taxi::GetBody() {
  return body;
}

void Taxi::SetTaxiPlace(int x, int y) {
  taxi_place.first = x;
  taxi_place.second = y;
}

int Taxi::GetXCoord() {
  return taxi_place.first;
}

int Taxi::GetYCoord() {
  return taxi_place.second;
}

std::pair<int,int> Taxi::get_TaxiPlace() {
  return taxi_place;
}

