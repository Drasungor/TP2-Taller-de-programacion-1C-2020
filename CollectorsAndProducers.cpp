#include "CollectorsAndProducers.h"

#include <fstream>
#include <string>
#include "BlockingQueue.h"
#include "FilesConstants.h"
#include "WorkerIndex.h"
#include "ResourcesProcessor.h"

#define NUMBER_OF_ARGUMENTS 3
#define RESOURCES_FILE_INDEX 2
#define WORKERS_FILE_INDEX 1


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

void CollectorsAndProducers::_load_workers_ammounts(std::ifstream& workers,
                                std::vector<int>& workers_ammounts){
  std::string worker_type;
  std::string number_of_workers;
  /*
  std::getline(workers, worker_type, WORKER_NUMBER_SEPARATOR);
  std::getline(workers, number_of_workers);
  */
  while (!workers.eof()) {
    std::getline(workers, worker_type, WORKER_NUMBER_SEPARATOR);
    std::getline(workers, number_of_workers);
    //The file comes without error so no conversion exception must
    //be catched for stoi
    workers_ammounts[_get_workers_ammounts_index(worker_type)] = std::stoi(number_of_workers);
    worker_type.clear();
    worker_type.clear();
    /*
    std::getline(workers, worker_type, WORKER_NUMBER_SEPARATOR);
    std::getline(workers, number_of_workers);
    */
  }
}


/////////////////PUBLIC////////////////////

//BORRAR ESTE INCLUDE
#include <iostream>


int CollectorsAndProducers::execute(const char** arguments,
                                    int number_of_arguments){

  if (number_of_arguments != NUMBER_OF_ARGUMENTS) {
    return INVALID_ARGUMENTS;
  }
  std::ifstream materials(arguments[RESOURCES_FILE_INDEX]);
  std::ifstream workers(arguments[WORKERS_FILE_INDEX]);
  if ((!materials.is_open()) || (!workers.is_open())) {
    return INVALID_FILE;
  }
  ResourcesProcessor processor;
  std::vector<int> workers_ammounts(NUMBER_OF_WORKER_TYPES);
  _load_workers_ammounts(workers, workers_ammounts);

  //BORRAR PTINT
  std::cout << "TRABAJADORES:\n";
  std::cout << "Agricultores: "<< workers_ammounts[WORKER_INDEX_FARMER] << "\n";
  std::cout << "Leniadores: "<< workers_ammounts[WORKER_INDEX_LUMBERJACK] << "\n";
  std::cout << "Mineros: "<< workers_ammounts[WORKER_INDEX_MINER] << "\n";
  std::cout << "Cocineros: "<< workers_ammounts[WORKER_INDEX_COOKER] << "\n";
  std::cout << "Carpinteros: "<< workers_ammounts[WORKER_INDEX_CARPENTER] << "\n";
  std::cout << "Armeros: "<< workers_ammounts[WORKER_INDEX_GUNSMITH] << "\n";
  std::cout << "\n\n";

  processor.process_resources(materials, workers_ammounts);
  //ACA SE EJECUTAN LAS FUNCIONES DE ResourcesProcessor

  //CAMBIAR EL SUCCESS POR EL RETORNO DE LA FUNCION DE ResourcesProcessor
  return SUCCESS;
}


CollectorsAndProducers::CollectorsAndProducers(){
}

CollectorsAndProducers::~CollectorsAndProducers(){
}
