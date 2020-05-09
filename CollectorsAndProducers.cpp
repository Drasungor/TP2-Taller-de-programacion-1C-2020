#include "CollectorsAndProducers.h"

//#include <iostream>
#include <fstream>

#define NUMBER_OF_ARGUMENTS 3
#define MATERIALS_FILE_INDEX 1
#define WORKERS_FILE_INDEX 2

#define SUCCESS 0
#define INVALID_ARGUMENTS 1
#define INVALID_FILE 1







int execute(const char** arguments, int number_of_arguments){
  if (number_of_arguments != NUMBER_OF_ARGUMENTS) {
    return INVALID_ARGUMENTS;
  }
  std::ifstream materials(arguments[MATERIALS_FILE_INDEX]);
  std::ifstream workers(arguments[WORKERS_FILE_INDEX]);
  if ((!materials.is_open()) || (!workers.is_open())) {
    return INVALID_FILE;
  }

  //ACA SE TIRAN LOS THREADS DE RECOLECTORES

  



  return SUCCESS;
}


CollectorsAndProducers::CollectorsAndProducers(){
}

CollectorsAndProducers::~CollectorsAndProducers(){
}
