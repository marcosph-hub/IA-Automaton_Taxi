#include "board.h"
#include "algorithm.h"

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
  int coord;

  std::cout << "Introduzca el fichero de configuración config.txt" << std::endl;
  std::cin >> filename;
  while(filename != "config.txt") {
  std::cout << "Error al introducir el nombre del fichero, porfavor introduzca el fichero de configuración config.txt" << std::endl;
  std::cin >> filename;
  }
  std::ifstream file(filename.c_str());
  if (!file.good()) {
    std::cerr << "Error en la apertura del fichero" << std::endl;
    exit(1);
  }
  //DIMENSION DEL ENTORNO
  getline(file,row_file);
  getline(file,column_file);
  int row = std::stoi(row_file);
  int columns = std::stoi(column_file);
  assert(row > 0);
  assert(columns > 0);
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
    assert(row_obst > 0);
    assert(col_obst > 0);
    file_board.FillManual(row_obst,col_obst);
    obst_v.clear();
 }
 std::cout << "\033[2J\033[1;1H";
 file_board.Write();

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
  int movement;

  std::cout << "Describa como desea que sea los movimientos del taxi: " << std::endl;
  std::cout << "(1) Contempla 4 Movimientos (N, S, E, O)\n(2) Contempla 8 Movimientos (N, S, E, O, NE, SE, NO, SO)" << std::endl;
  std::cin >> movement;
  std::cout << "Elija como desea crear el Entorno: " << std::endl;
  std::cout << "(1) Por Fichero\n(2) Manual\n(0) Salir" << std::endl;
  std::cin >> option;

  if (option == 1) {
    FileData();
  } else {
      std::cout << "Elija como desea que sea las dimensiones del Entorno: " << std::endl;
      std::cout << "(1) Dimension por teclado\n(2) Dimenension Por Defecto" << std::endl;
      std::cin >> dim_option;


      switch (dim_option) {
      case 1: { //Entorno Manual
        std::cout << "Introduzca las dimensiones del entorno.\n Ancho del entorno (filas):\t"; 
        std::cin >> rows;
        assert(rows > 0);
        std::cout << "Largo del entorno (columnas):\t";
        std::cin >> columns;
        assert(columns > 0);
        Board manual_board(rows, columns);
        
        std::cout << "Elija como desea meter los obstaculos\n(1) Manual\n(2) Aleatorio" << std::endl;
        std::cin >> obst_option;
        if (obst_option == 1) { 
          std::cout << "Ponga el %(nº entero) de obstaculos que desea que haya\n" << std::endl;
          std::cin >> percent;
          assert(percent > 0);
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
        //llamada a la clase ALGORITHM
        manual_board.Write();
        Algorithm tester(manual_board);
      }
      break;
    



      case 2: { //Entorno por defecto
        Board default_board;
        std::cout << "Elija como desea meter los obstaculos\n(1) Manual\n(2) Aleatorio" << std::endl;
        std::cin >> obst_option;
        if (obst_option == 1) { 
          std::cout << "Ponga el %(nº entero) de obstaculos que desea que haya\n" << std::endl;
          std::cin >> percent;
          assert(percent > 0);
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
        //llamada a la clase ALGORITHM
        std::cout << "\033[2J\033[1;1H";
        default_board.Write();
        Algorithm alg_test(default_board);
        
      }
      break;
    }
  }

}

/*
        char a = '>';
        std::pair<int,int> c;
        c.first = 2;
        c.second = 4;
        Cell tester(a);
        tester.set_IsVisited(false);
        tester.set_OpenCell(false);
        tester.set_Coordinates(c);
        std::cout << "mostrando cell: " << a << std::endl; 
        std::cout << tester.get_CellValue() << std::endl;
        tester.set_CellValue('^');
        std::cout << tester.get_IsVisited() << tester.get_OpenCell() << 
        tester.get_Coordinates()<< tester.get_XCoord() << std::endl;
*/
