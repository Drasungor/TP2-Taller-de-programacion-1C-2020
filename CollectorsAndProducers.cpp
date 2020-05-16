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
#define OUT_TEXT_BENEFIT_POINTS "Puntos de Beneficio acumulados: "



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


//VER SI SE PUEDE PASAR UNA CONST REFERENCIA AL PROCESSOR

//Reads the resources stored in the resources file and sends them to the resources processor.
//Once the file ends, it se
void CollectorsAndProducers::_load_resources(std::ifstream& resources, ResourcesProcessor& processor){
  std::string buffer;
  while (!resources.eof()) {
    std::getline(resources, buffer);
    processor.store_resources(buffer);
    buffer.clear();
  }
  processor.close_resource_entrance();
}


/*
void CollectorsAndProducers::_load_workers_ammounts(std::ifstream& workers,
                                std::vector<int>& workers_ammounts){
  std::string worker_type;
  std::string number_of_workers;
  while (!workers.eof()) {
    std::getline(workers, worker_type, WORKER_NUMBER_SEPARATOR);
    std::getline(workers, number_of_workers);
    //The file comes without errors so no conversion exception must
    //be catched for stoi
    workers_ammounts[_get_workers_ammounts_index(worker_type)] = std::stoi(number_of_workers);
    worker_type.clear();
    number_of_workers.clear();
  }
}
*/

bool CollectorsAndProducers::_is_gatherer(std::string& worker_text){
  for (size_t i = 0; i < gatherers_text.size(); i++) {
    if (worker_text == gatherers_text[i]) {
      return true;
    }
  }
  return false;
}

bool CollectorsAndProducers::_is_producer(std::string& worker_text){
  for (size_t i = 0; i < producers_text.size(); i++) {
    if (worker_text == producers_text[i]) {
      return true;
    }
  }
  return false;
}

Gatherer CollectorsAndProducers::_convert_to_gatherer(std::string& gatherer_text){
  if (gatherer_text == FARMER_TEXT) {
    return GATHERER_FARMER;
  } else if (gatherer_text == LUMBERJACK_TEXT) {
    return GATHERER_LUMBERJACK;
  } else {
    return GATHERER_MINER;
  }
}

Producer CollectorsAndProducers::_convert_to_producer(std::string& producer_text){
  if (producer_text == COOKER_TEXT) {
    return PRODUCER_COOKER;
  } else if (producer_text == CARPENTER_TEXT) {
    return PRODUCER_CARPENTER;
  } else {
    return PRODUCER_GUNSMITH;
  }
}


void CollectorsAndProducers::_add_worker_ammount(
                                  std::map<Gatherer, int>& gatherers_ammounts,
                                  std::map<Producer, int>& producers_ammounts,
                                  std::string& worker, std::string& ammount){
  //The file comes without errors so no conversion exception must
  //be catched for stoi
  int workers_ammount = std::stoi(ammount);
  if (_is_gatherer(worker)) {
    gatherers_ammounts[_convert_to_gatherer(worker)] = workers_ammount;
  } else if (_is_producer(worker)) {
    producers_ammounts[_convert_to_producer(worker)] = workers_ammount;
  }
}

void CollectorsAndProducers::_load_workers_ammounts(std::ifstream& workers,
                                std::map<Gatherer, int>& gatherers_ammounts,
                                std::map<Producer, int>& producers_ammounts){

  std::string worker_type;
  std::string number_of_workers;
  while (!workers.eof()) {
    std::getline(workers, worker_type, WORKER_NUMBER_SEPARATOR);
    std::getline(workers, number_of_workers);
    _add_worker_ammount(gatherers_ammounts, producers_ammounts, worker_type,
                        number_of_workers);
    worker_type.clear();
    number_of_workers.clear();
  }
}



void CollectorsAndProducers::_print_result(
                        std::map<Resource, int>& unprocessed_resources,
                        int produced_points){
  std::vector<std::pair<Resource, std::string>> strings_to_print = {
  {RESOURCE_WHEAT, OUT_TEXT_WHEAT}, {RESOURCE_WOOD, OUT_TEXT_WOOD},
  {RESOURCE_COAL, OUT_TEXT_COAL}, {RESOURCE_IRON, OUT_TEXT_IRON}};
  std::cout << OUT_TEXT_UNPROCESSED_RESOURCES;

  for (size_t i = 0; i < strings_to_print.size(); i++) {
    std::cout << OUT_TEXT_RESOURCE_PRETEXT << strings_to_print[i].second <<
                 unprocessed_resources[strings_to_print[i].first] << "\n";
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
  std::ifstream resources(arguments[RESOURCES_FILE_INDEX]);
  std::ifstream workers(arguments[WORKERS_FILE_INDEX]);
  if ((!resources.is_open()) || (!workers.is_open())) {
    return INVALID_FILE;
  }
  std::map<Resource, int> unprocessed_resources;
  //std::vector<int> workers_ammounts(NUMBER_OF_WORKER_TYPES);
  std::map<Gatherer, int> gatherers_ammounts;
  std::map<Producer, int> producers_ammounts;

  _load_workers_ammounts(workers, gatherers_ammounts, producers_ammounts);

  ResourcesProcessor processor(gatherers_ammounts, producers_ammounts);


  _load_resources(resources, processor);

  //void ResourcesProcessor::store_resources(const std::string& resources)
  processor.close_resource_entrance();
  produced_points = processor.obtain_process_results(unprocessed_resources);
  /*
  produced_points = processor.process_resources(materials, workers_ammounts,
                              unprocessed_resources);
  */
  //ACA SE EJECUTAN LAS FUNCIONES DE ResourcesProcessor

  _print_result(unprocessed_resources, produced_points);

  //CAMBIAR EL SUCCESS POR EL RETORNO DE LA FUNCION DE ResourcesProcessor
  return SUCCESS;
}


CollectorsAndProducers::CollectorsAndProducers(){
  gatherers_text = {FARMER_TEXT, LUMBERJACK_TEXT, MINER_TEXT};
  producers_text = {COOKER_TEXT, CARPENTER_TEXT, GUNSMITH_TEXT};
}


CollectorsAndProducers::~CollectorsAndProducers(){
}
