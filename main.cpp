#include "CollectorsAndProducers.h"

/*
#include <string>
#include <vector>
#include <iostream>
class Algo{
  private:
    std::string* estring;
  public:
    Algo(std::string estring);

  	~Algo();

    std::string _get_string();
};

Algo::Algo(std::string estring){
  this->estring = new std::string(estring);
}

Algo::~Algo(){
  delete(estring);
}

std::string Algo::_get_string(){
  return *estring;
}


void funcion(std::vector<Algo>& algos){
  Algo algo("Buenas");
  algos.push_back(algo);
  //algos.emplace_back("Buenas");
}
*/

int main(int argc, char const *argv[]) {
  /*
  std::vector<Algo> algos;
  funcion(algos);
  std::cout << algos[0]._get_string();
  return 0;
  */
  CollectorsAndProducers program;
  return program.execute(argv, argc);
}
