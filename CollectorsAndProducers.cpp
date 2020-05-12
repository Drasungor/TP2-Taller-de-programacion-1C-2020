#include "CollectorsAndProducers.h"

//#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include "BlockingQueue.h"
#include "FilesConstants.h"
#include "WorkerIndex.h"

#define NUMBER_OF_ARGUMENTS 3
#define RESOURCES_FILE_INDEX 1
#define WORKERS_FILE_INDEX 2


#define SUCCESS 0
#define INVALID_ARGUMENTS 1
#define INVALID_FILE 1


int _get_workers_ammounts_index(std::string worker){
  if (worker == FARMER_TEXT) {
    return WORKER_INDEX_FARMER;
  } else if (worker == LUMBERJACK_TEXT) {
    return WORKER_INDEX_LUMBERJACK;
  } else if (worker == MINER_TEXT) {
    return WORKER_INDEX_MINER;
  } else if (worker == COOKER_TEXT) {
    return WORKER_INDEX_COOKER;
  } else if (worker == CARPENTER_TEXT) {
    return WORKER_INDEX_CARPENTER;
  } else {
    return WORKER_INDEX_GUNSMITH;
  }
}


//Loads the ammount of each worker
void CollectorsAndProducers::_load_workers_ammounts(std::ifstream& workers,
                                std::map<std::string, int>& workers_ammounts){
  std::string worker_type;
  std::string number_of_workers;
  //VER SI GETLINE TIRA EOF DESPUES DE INTENTAR LEER
  //LEER AL FINAL DEL WHILE O USAR PEEK
  while (!workers.eof()) {
    std::getline(workers, worker_type, WORKER_NUMBER_SEPARATOR);
    std::getline(workers, number_of_workers);
    //The file comes without error so no conversion exception must
    //be catched for stoi
    workers_ammounts.insert(std::pair<std::string, int>(worker_type,
                            std::stoi(number_of_workers)));
    worker_type.clear();
    worker_type.clear();
  }
}

/////////////////PUBLIC////////////////////

int CollectorsAndProducers::execute(const char** arguments, int number_of_arguments){
  if (number_of_arguments != NUMBER_OF_ARGUMENTS) {
    return INVALID_ARGUMENTS;
  }
  //PASAR A FUNCION A PARTE DONDE SE INICIALICEN LOS GATHERERS
  //O PRODUCERS
  std::ifstream materials(arguments[RESOURCES_FILE_INDEX]);
  std::ifstream workers(arguments[WORKERS_FILE_INDEX]);
  if ((!materials.is_open()) || (!workers.is_open())) {
    return INVALID_FILE;
  }

  std::map<std::string, int> workers_ammounts;
  _load_workers_ammounts(workers, workers_ammounts);

  //ACA SE EJECUTAN LAS FUNCIONES DE ResourcesProcessor

  //CAMBIAR EL SUCCESS POR EL RETORNO DE LA FUNCION DE ResourcesProcessor
  return SUCCESS;
}


CollectorsAndProducers::CollectorsAndProducers(){
}

CollectorsAndProducers::~CollectorsAndProducers(){
}
