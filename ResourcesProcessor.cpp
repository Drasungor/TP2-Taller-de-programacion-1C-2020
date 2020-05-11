#include "ResourcesProcessor.h"

#include <map>
#include <string>
#include <fstream>
#include <vector>
#include "Resource.h"
#include "BlockingQueue.h"
#include "FilesConstants.h"


enum GathererQueueIndex{
  GATHERER_QUEUE_INDEX_FARMER,
  GATHERER_QUEUE_INDEX_LUMBERJACK,
  GATHERER_QUEUE_INDEX_MINER
};

/*
//Loads the resources from the materials file into the
//different gatherers' blocking queues
void ResourcesProcessor::_load_resources(std::ifstream& materials,
                                         std::vector<BlockingQueue>& queues){
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
  //CERRAR TODAS LAS COLAS BLOQUEANTES
}
*/

int _get_gatherer_queue_index(Resource resource){
  switch (resource) {
    case RESOURCE_WHEAT:
      return GATHERER_QUEUE_INDEX_FARMER;
    case RESOURCE_WOOD:
      return GATHERER_QUEUE_INDEX_LUMBERJACK;
    case RESOURCE_COAL:
    default:
      return GATHERER_QUEUE_INDEX_MINER;
  }
}


Resource ResourcesProcessor::_convert_to_resource(char resource){
  switch (resource) {
    case RESOURCE_WOOD:
    return RESOURCE_WOOD;
    case RESOURCE_WHEAT:
    return RESOURCE_WHEAT;
    case RESOURCE_COAL:
    return RESOURCE_COAL;
    default:
    return RESOURCE_IRON;
  }
}


void ResourcesProcessor::_store_resources(std::fstream& resources, std::vector<BlockingQueue>& queues){
  std::string buffer;
  Resource resource;
  //VER SI GETLINE TIRA EOF DESPUES DE INTENTAR LEER
  //LEER AL FINAL DEL WHILE O USAR PEEK
  while (!resources.eof()) {
    std::getline(resources, buffer);
    for (size_t i = 0; i < buffer.length(); i++) {
      resource = _convert_to_resource(buffer[i]);
      queues[_get_gatherer_queue_index(resource)].push(resource);
    }
    buffer.clear();
  }
}


//Ver si puedo cambiar estas funciones por una sola que itere por la lista de
void ResourcesProcessor::_create_blocking_queues(std::vector<BlockingQueue*>& queues){
  for (size_t i = 0; i < NUMBER_OF_GATHERER_TYPES; i++) {
    queues.push_back(new BlockingQueue());
  }
}

void ResourcesProcessor::_destroy_blocking_queues(std::vector<BlockingQueue*>& queues){
  for (size_t i = 0; i < NUMBER_OF_GATHERER_TYPES; i++) {
    delete(queues[i]);
  }
}

void ResourcesProcessor::_close_blocking_queues(std::vector<BlockingQueue*>& queues){

}


/////////////////////PUBLIC//////////////////////////////

std::map<std::string, int> ResourcesProcessor::
        process_resources(std::fstream& resources,
                          const std::map<std::string, int>& number_of_workers){
  std::vector<BlockingQueue*> queues;
  _create_blocking_queues(queues);

  for (size_t i = 0; i < queues.size(); i++) {
    /* code */
  }



  _destroy_blocking_queues(queues);

  //BORRAR: ESTA SOLO PARA QUE COMPILE
  std::map<std::string, int> compila;
  //PONER RETURN
  return compila;
}


ResourcesProcessor::ResourcesProcessor(){

}

ResourcesProcessor::~ResourcesProcessor(){
}
