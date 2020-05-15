#include "CollectorsAndProducers.h"

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include "BlockingQueue.h"
#include "FilesConstants.h"
#include "WorkerIndex.h"
#include "ResourcesProcessor.h"
#include "Resource.h"


#define NUMBER_OF_ARGUMENTS 3
#define RESOURCES_FILE_INDEX 2
#define WORKERS_FILE_INDEX 1

#define SUCCESS 0
#define INVALID_ARGUMENTS 1
#define INVALID_FILE 1

#define OUT_TEXT_UNPROCESSED_RESOURCES "Recursos restantes:\n"
#define OUT_TEXT_RESOURCE_PRETEXT "  - "
#define OUT_TEXT_WHEAT "Trigo: "
#define OUT_TEXT_WOOD "Madera: "
#define OUT_TEXT_COAL "Carbon: "
#define OUT_TEXT_IRON "Hierro: "
#define OUT_TEXT_BENEFIT_POINTS "Puntos de beneficio acumulados: "



int CollectorsAndProducers::_get_workers_ammounts_index(std::string& worker){
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
  while (!workers.eof()) {
    std::getline(workers, worker_type, WORKER_NUMBER_SEPARATOR);
    std::getline(workers, number_of_workers);
    //The file comes without error so no conversion exception must
    //be catched for stoi
    workers_ammounts[_get_workers_ammounts_index(worker_type)] = std::stoi(number_of_workers);
    worker_type.clear();
    worker_type.clear();
  }
}


void CollectorsAndProducers::_print_result(
                        const std::map<Resource, int>& unprocessed_resources,
                        int produced_points){
std::map<Resource, std::string> strings_to_print = {
  {RESOURCE_WHEAT, OUT_TEXT_WHEAT}, {RESOURCE_WOOD, OUT_TEXT_WOOD},
  {RESOURCE_COAL, OUT_TEXT_COAL}, {RESOURCE_IRON, OUT_TEXT_IRON}};

  std::cout << OUT_TEXT_UNPROCESSED_RESOURCES;

  //std::cout << "CANTIDAD DE ELEMENTOS QUE SOBRAN: " << unprocessed_resources.size() << "\n";

  for (std::map<Resource, int>::const_iterator it =
      unprocessed_resources.begin(); it != unprocessed_resources.end(); ++it) {
    std::cout << OUT_TEXT_RESOURCE_PRETEXT << strings_to_print[it->first] <<
                 it->second << "\n";
  }
  std::cout << "\n";
  std::cout << OUT_TEXT_BENEFIT_POINTS << produced_points << "\n";
}

/////////////////PUBLIC////////////////////

int CollectorsAndProducers::execute(const char** arguments,
                                    int number_of_arguments){
//asdasd
  int produced_points = 0;

  if (number_of_arguments != NUMBER_OF_ARGUMENTS) {
    return INVALID_ARGUMENTS;
  }
  std::ifstream materials(arguments[RESOURCES_FILE_INDEX]);
  std::ifstream workers(arguments[WORKERS_FILE_INDEX]);
  if ((!materials.is_open()) || (!workers.is_open())) {
    return INVALID_FILE;
  }
  ResourcesProcessor processor;
  std::map<Resource, int> unprocessed_resources;
  std::vector<int> workers_ammounts(NUMBER_OF_WORKER_TYPES);
  _load_workers_ammounts(workers, workers_ammounts);
  produced_points = processor.process_resources(materials, workers_ammounts,
                              unprocessed_resources);
  //ACA SE EJECUTAN LAS FUNCIONES DE ResourcesProcessor

  _print_result(unprocessed_resources, produced_points);

  //CAMBIAR EL SUCCESS POR EL RETORNO DE LA FUNCION DE ResourcesProcessor
  return SUCCESS;
}


CollectorsAndProducers::CollectorsAndProducers(){
}

CollectorsAndProducers::~CollectorsAndProducers(){
}
