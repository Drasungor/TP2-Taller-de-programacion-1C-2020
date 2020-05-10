#include "CollectorsAndProducers.h"

//#include <iostream>
#include <fstream>
#include <string>
//#include <map>
#include "Resource.h"
#include "BlockingQueue.h"

#define NUMBER_OF_ARGUMENTS 3
#define MATERIALS_FILE_INDEX 1
#define WORKERS_FILE_INDEX 2
#define NUMBER_OF_GATHERER_TYPES 3

#define SUCCESS 0
#define INVALID_ARGUMENTS 1
#define INVALID_FILE 1

/*
const char FARMER_RESOURCES[] = {RESOURCE_WHEAT, '\0'};
const char LUMBERJACK_RESOURCES[] = {RESOURCE_WOOD, '\0'};
const char MINER_RESOURCES[] = {RESOURCE_IRON, RESOURCE_COAL, '\0'};
const std::vector<std::string> gatherers_resources = {"buenas"};
*/
enum GathererIndex{
  GATHERER_INDEX_FARMER, GATHERER_INDEX_LUMBERJACK, GATHERER_INDEX_MINER
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
void build_gatherers_queues(std::vector<BlockingQueue>& queues){
  BlockingQueue* q;
    for (size_t i = 0; i < NUMBER_OF_GATHERER_TYPES; i++) {
      q = new BlockingQueue();
      queues.push_back(q);
    }
}
//Stores blocking quques in the vector
void destroy_gatherers_queues(std::vector<BlockingQueue>& queues){
    for (size_t i = 0; i < NUMBER_OF_GATHERER_TYPES; i++) {
      queues.push_back(q);
    }
}


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

  //VER SI CONVIENE O NO HACER UN MAP DE REFERENCIAS
  build_gatherers_queues(queues);
  /*
  std::map<Resource, BlockingQueue&> gatherers_queues;
  BlockingQueue q;
  gatherers_queues.insert(std::pair<Resource, BlockingQueue&>());
  */
  //esto se hace despues de cargar los chars en las colas
  load_resources(materials, queues);

  return SUCCESS;
}


CollectorsAndProducers::CollectorsAndProducers(){
}

CollectorsAndProducers::~CollectorsAndProducers(){
}
