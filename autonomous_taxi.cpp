#include "board.h"
#include "algorithm.h"
#include <cstdio>

void FileData() {        
  std::string filename;
  std::string row_file;
  std::string column_file;
  std::string taxi_file;
  std::string dest_file;
  std::string obst_file;
  std::vector<int> origin_v;
  std::vector<int> dest_v;
  std::vector<int> obst_v;
  std::string file_heuristic;
  std::string file_movements;
  int coord;

  std::cout << "Introduzca el fichero de configuración config.txt" << std::endl;
  std::cin >> filename;
  std::ifstream file(filename.c_str());
  if (!file.good()) {
    std::cerr << "Error en la apertura del fichero" << std::endl;
    exit(1);
  }
  //DIMENSION DEL ENTORNO
  getline(file,row_file);
  getline(file,column_file);
  getline(file,file_heuristic);
  getline(file,file_movements);
  int row = std::stoi(row_file);
  int columns = std::stoi(column_file);
  int int_heuristic = std::stoi(file_heuristic);
  int int_movements = std::stoi(file_movements);
  assert((row > 0 && row < 86 && "Nº filas entre 0 y 85"));
  assert((columns > 0 && columns < 86 && "Nº columnas entre 0 y 85"));
  Board file_board(row,columns);

  //INSERTAR POS DEL COCHE
  getline(file,taxi_file);
  std::istringstream taxi_fileline(taxi_file);
  while(taxi_fileline >> coord) {
    origin_v.push_back(coord);
  }
  int row_taxi = origin_v[0];
  int col_taxi = origin_v[1];
  assert(row_taxi > 0);
  assert(col_taxi > 0);
  file_board.ManualInsertTaxi(row_taxi, col_taxi);

 //INSERTAR DESTINO
 getline(file,dest_file);
 std::istringstream dest_filename(dest_file);
 while (dest_filename >> coord) {
   dest_v.push_back(coord);
 }
  int row_dest = dest_v[0];
  int col_dest = dest_v[1];
  assert(row_dest > 0);
  assert(col_dest > 0);
  file_board.ManualDestination(row_dest,col_dest);

 //INSERTAR OBSTACULOS
 while(!file.eof()) {
  getline(file,obst_file);
  std::istringstream obst_filename(obst_file);
  while (obst_filename >> coord) {
    obst_v.push_back(coord);
  }
    int row_obst = obst_v[0];
    int col_obst = obst_v[1];
    assert(row_obst > -1);
    assert(col_obst > -1);
    file_board.FillManual(row_obst,col_obst);
    obst_v.clear();
 }
 std::cout << "\033[2J\033[1;1H";
 file_board.Write();
 Board aux;
 aux = file_board;
 Algorithm tester(file_board,int_movements, int_heuristic);
 unsigned t0, t1;
 t0=clock();
  tester.A_Star();
  t1 = clock();
 tester.Write();
 
  double time = (double(t1-t0)/CLOCKS_PER_SEC);
  std::cout.precision(5);
  std::cout << "Execution Time: " << std::fixed << time << std::endl;
}


int main () {
  int option;
  int dim_option;
  int obst_option;
  int dest_option;
  int orig_option;
  int rows; 
  int columns;
  int percent;
  int xcoord;
  int ycoord;
  int heuristic;
  int movement;
  unsigned t0, t1;



  std::cout << "Elija como desea crear el Entorno: " << std::endl;
  std::cout << "(1) Por Fichero\n(2) Manual\n(0) Salir" << std::endl;
  std::cin >> option;

  if (option == 1) {
    FileData();
    exit(-1);
  } else {
      std::cout << "Describa como desea que sea los movimientos del taxi: " << std::endl;
      std::cout << "(1) Contempla 4 Movimientos (N, S, E, O)\n(2) Contempla 8 Movimientos (N, S, E, O, NE, SE, NO, SO)" << std::endl;
      std::cin >> movement;

      std::cout << "Elija la Función Heurística que desea usar: \n(1) D. Manhattan\n(2) Euclídea" << std::endl;
      std::cin >> heuristic;

      std::cout << "Elija como desea que sea las dimensiones del Entorno: " << std::endl;
      std::cout << "(1) Dimension por teclado\n(2) Dimenension Por Defecto" << std::endl;
      std::cin >> dim_option;

      switch (dim_option) {
      case 1: { //Entorno Manual
        std::cout << "Introduzca las dimensiones del entorno.\n Ancho del entorno (filas):\t"; 
        std::cin >> rows;
        assert((rows > 0 && rows < 86 && "Nº filas entre 0 y 85"));
  
        std::cout << "Largo del entorno (columnas):\t";
        std::cin >> columns;
        assert((columns > 0 && columns < 86 && "Nº columnas entre 0 y 85"));
        Board manual_board(rows, columns);
        
        std::cout << "Elija como desea meter los obstaculos\n(1) Manual\n(2) Aleatorio" << std::endl;
        std::cin >> obst_option;
        if (obst_option == 1) { 
          std::cout << "Ponga el %(nº entero) de obstaculos que desea que haya\n" << std::endl;
          std::cin >> percent;
          manual_board.FillByPercent(percent);
        } else  {
          manual_board.RandomFill();
          std::cout << std::endl;
        }

        std::cout << "Elija como desea introducir el Destino\n(1) Destino Manual\n(2) Destino Aleatorio" << std::endl;
        std::cin >> dest_option;
        if (dest_option == 1) {
          std::cout << "Introduzca donde quiere que se encuentre el destino:\nIntroduzca la coordenada 'x': ";
          std::cin >> xcoord;
          assert(xcoord > 0);
          std::cout << " y la coordenada 'y': ";
          std::cin >> ycoord;
          assert(ycoord > 0);
          std::cout << std::endl;
          manual_board.ManualDestination(xcoord, ycoord);
        } else {
          manual_board.RandomDestination();
        }
        std::cout << "Elija como desea introducir el Origen:\n(1) Origen Manual\n(2) Origen Aleatorio" << std::endl;
        std::cin >> orig_option;
        if (orig_option == 1) {
          std::cout << "Introduzca donde quiere que se encuentre el origen:\nIntroduzca la coordenada 'x': ";
          std::cin >> xcoord;
          assert(xcoord > 0);
          std::cout << " y la coordenada 'y': ";
          std::cin >> ycoord;
          assert(ycoord > 0);
          std::cout << std::endl;
          manual_board.ManualInsertTaxi(xcoord, ycoord);
        } else {
          manual_board.RandomInsertTaxi();
        }
        std::cout << "\033[2J\033[1;1H";
        Algorithm tester(manual_board,movement, heuristic);
        t0=clock();
        tester.A_Star();
        t1 = clock();
        tester.Write();
        double time = (double(t1-t0)/CLOCKS_PER_SEC);
        std::cout.precision(5);
        std::cout << "Execution Time: " << std::fixed << time << std::endl;
      }
      break;
    



      case 2: { //Entorno por defecto
      Board default_board;
    
      std::cout << "Elija como desea meter los obstaculos\n(1) Manual\n(2) Aleatorio" << std::endl;
      std::cin >> obst_option;
      if (obst_option == 1) { 
        std::cout << "Ponga el %(nº entero) de obstaculos que desea que haya\n" << std::endl;
        std::cin >> percent;
        assert(percent > -1);
        default_board.FillByPercent(percent);
      } else  {
        default_board.RandomFill();
        std::cout << std::endl;
      }

      std::cout << "Elija como desea introducir el Destino\n(1) Destino Manual\n(2) Destino Aleatorio" << std::endl;
      std::cin >> dest_option;
      if (dest_option == 1) {
        std::cout << "Introduzca donde quiere que se encuentre el destino:\nIntroduzca la coordenada 'x': ";
        std::cin >> xcoord;
        assert(xcoord > 0);
        std::cout << " y la coordenada 'y': ";
        std::cin >> ycoord;
        assert(ycoord > 0);
        std::cout << std::endl;
        default_board.ManualDestination(xcoord, ycoord);
      } else {
        default_board.RandomDestination();
      }
        std::cout << "Elija como desea introducir el Origen:\n(1) Origen Manual\n(2) Origen Aleatorio" << std::endl;
        std::cin >> orig_option;
        if (orig_option == 1) {
          std::cout << "Introduzca donde quiere que se encuentre el origen:\nIntroduzca la coordenada 'x': ";
          std::cin >> xcoord;
          assert(xcoord > 0);
          std::cout << " y la coordenada 'y': ";
          std::cin >> ycoord;
          assert(ycoord > 0);
          std::cout << std::endl;
          default_board.ManualInsertTaxi(xcoord, ycoord);
        } else {
          default_board.RandomInsertTaxi();
        }
        Algorithm tester(default_board, movement, heuristic);
        t0=clock();
        tester.A_Star();
        t1 = clock();
        tester.Write();
        double time = (double(t1-t0)/CLOCKS_PER_SEC);
        std::cout.precision(5);
        std::cout << "Execution Time: " << std::fixed << time << std::endl;
        exit(-1);
      }
      break;
    }
  }
  exit(-1);
}

