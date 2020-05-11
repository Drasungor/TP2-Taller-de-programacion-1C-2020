#include "CollectorsAndProducers.h"

//#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include "Resource.h"
#include "BlockingQueue.h"
#include "FilesConstants.h"

#define NUMBER_OF_ARGUMENTS 3
#define MATERIALS_FILE_INDEX 1
#define WORKERS_FILE_INDEX 2
#define NUMBER_OF_GATHERER_TYPES 3
#define NUMBER_OF_WORKER_TYPES 6

#define SUCCESS 0
#define INVALID_ARGUMENTS 1
#define INVALID_FILE 1

enum WorkerIndex{
  WORKER_INDEX_FARMER, WORKER_INDEX_LUMBERJACK, WORKER_INDEX_MINER,
  WORKER_INDEX_COOKER, WORKER_INDEX_CARPENTER, WORKER_INDEX_GUNSMITH
};

//Returns the index for the gatherer in the gatherers vector
int CollectorsAndProducers::get_gatherer_index(Resource resource){
  switch (resource) {
    case RESOURCE_WHEAT:
      return GATHERER_INDEX_FARMER;
    case RESOURCE_WOOD:
      return GATHERER_INDEX_LUMBERJACK;
    default:
      return GATHERER_INDEX_MINER;
  }
}


//VER SI HAY QUE SACAR ESTA FUNCION
Resource CollectorsAndProducers::convert_to_resource(char r){
  switch (r) {
    case RESOURCE_WHEAT:
      return RESOURCE_WHEAT;
    case RESOURCE_WOOD:
      return RESOURCE_WOOD;
    case RESOURCE_COAL:
      return RESOURCE_COAL;
    default:
      return RESOURCE_IRON;
  }
}

//Loads the resources from the materials file into the
//different gatherers' blocking queues
void CollectorsAndProducers::load_resources(std::ifstream& materials,
                    std::vector<BlockingQueue&> &queues){
  std::string buffer;
  Resource aux;
  while (!materials.eof()) {
    std::getline(materials, buffer);
    for (size_t i = 0; i < buffer.length(); i++) {
      aux = convert_to_resource(buffer[i]);
      queues[get_gatherer_index(aux)].push(aux);
    }
    buffer.clear();
  }
}

//Stores blocking quques in the vector
void CollectorsAndProducers::build_gatherers_queues(std::vector<BlockingQueue>& queues){
  BlockingQueue* q;
    for (size_t i = 0; i < NUMBER_OF_GATHERER_TYPES; i++) {
      q = new BlockingQueue();
      queues.push_back(q);
    }
}
//Stores blocking quques in the vector
void CollectorsAndProducers::destroy_gatherers_queues
                              (std::vector<BlockingQueue>& queues){
    for (size_t i = 0; i < NUMBER_OF_GATHERER_TYPES; i++) {
      queues.push_back(q);
    }
}


WorkerIndex CollectorsAndProducers::get_worker_index(string worker){
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

void CollectorsAndProducers::load_workers_ammounts(std::ifstream& workers,
                                  std::vector<int>& workers_ammounts){
  std::string buffer;
  int index;
  while (!workers.eof()) {
    std::getline(workers, buffer, WORKER_NUMBER_SEPARATOR);
    index = get_worker_index(buffer);
    buffer.clear();
    std::getline(workers, buffer);
    workers_ammounts[index] = std::stoi(buffer);
    buffer.clear();
  }
}



/////////////////PUBLIC////////////////////

int CollectorsAndProducers::execute(const char** arguments, int number_of_arguments){
  if (number_of_arguments != NUMBER_OF_ARGUMENTS) {
    return INVALID_ARGUMENTS;
  }
  //PASAR A FUNCION A PARTE DONDE SE INICIALICEN LOS GATHERERS
  //O PRODUCERS
  std::ifstream materials(arguments[MATERIALS_FILE_INDEX]);
  std::ifstream workers(arguments[WORKERS_FILE_INDEX]);
  if ((!materials.is_open()) || (!workers.is_open())) {
    return INVALID_FILE;
  }



  //ACA SE TIRAN LOS THREADS DE RECOLECTORES
  //VER SI SE PUEDE CAMBIAR EL VECTOR POR UN MAP
  std::vector<BlockingQueue> resources_queues;
  build_gatherers_queues(resources_queues);
  std::vector<std::thread> threads;

  //Stores the ammount of each type of worker
  std::vector<int> workers_ammounts(NUMBER_OF_WORKER_TYPES, 0);
  //std::map<string, int> workers_ammounts;

  load_resources(materials, resources_queues);
  destroy_gatherers_queues(resources_queues);

  return SUCCESS;
}


CollectorsAndProducers::CollectorsAndProducers(){
}

CollectorsAndProducers::~CollectorsAndProducers(){
}
