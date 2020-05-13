#include "ResourcesProcessor.h"

#include <map>
#include <string>
#include <fstream>
#include <vector>
#include "Resource.h"
#include "BlockingQueue.h"
#include "FilesConstants.h"
#include "GatherersGroup.h"
#include "ProducersGroup.h"
#include "WorkerIndex.h"

enum GathererQueueIndex{
  GATHERER_QUEUE_INDEX_FARMER = WORKER_INDEX_FARMER,
  GATHERER_QUEUE_INDEX_LUMBERJACK = WORKER_INDEX_LUMBERJACK,
  GATHERER_QUEUE_INDEX_MINER = WORKER_INDEX_MINER
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

int ResourcesProcessor::_get_gatherer_queue_index(Resource resource){
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

/*
int ResourcesProcessor::_get_gatherer_queue_index(std::string gatherer_type){
  if (gatherer_type == FARMER_TEXT) {
    return GATHERER_QUEUE_INDEX_FARMER;
  } else if (gatherer_type == LUMBERJACK_TEXT) {
    return GATHERER_QUEUE_INDEX_LUMBERJACK;
  } else {
    return GATHERER_QUEUE_INDEX_MINER;
  }
}
*/

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


//BORRAR INCLUDE
#include <iostream>

//Stores the resources in the respective queue and closes every queue one the
//resources run out
void ResourcesProcessor::_store_resources(std::ifstream& resources,
                                          std::vector<BlockingQueue*>& queues){
  std::string buffer;
  Resource resource;

  //std::getline(resources, buffer);
  while (!resources.eof()) {

    std::getline(resources, buffer);

    //BORRAR ESTE PRINT
    std::cout << buffer << "\n" << std::flush;

    for (size_t i = 0; i < buffer.length(); i++) {
      resource = _convert_to_resource(buffer[i]);
      //CAMBIAR ESTO PARA QUE COINCIDA CON LOS INDICES DE LOS GATHERERS
      queues[_get_gatherer_queue_index(resource)]->push(resource);
    }
    buffer.clear();
  }
  //VER SI HAY QUE BORRAR ESTE CLOSE DE ACA Y CERRARLAS DE AFUERA
  _close_blocking_queues(queues);


  //BORRAR ESTE PRINT
  std::cout << "\n\n";


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
  for (size_t i = 0; i < NUMBER_OF_GATHERER_TYPES; i++) {
    queues[i]->close();
  }
}


//CAMBIAR LA IMPLEMENTACION DE ESTA FUNCION, VER SI HAY Q SACAR LOS MAPS DEL TP
/*
void ResourcesProcessor::_create_gatherers(
                          std::vector<GatherersGroup*>& gatherers_groups,
                          std::map<std::string, int>& number_of_workers,
                          const std::vector<BlockingQueue*> queues){
  const std::vector<std::string> gatherers_keys = {FARMER_TEXT,
                                                   LUMBERJACK_TEXT,
                                                   MINER_TEXT};

//asdasd
  std::string current_gatherer;
  int current_number_of_workers;
  for (size_t i = 0; i < gatherers_keys.size(); i++) {
    current_gatherer = gatherers_keys[i];
    current_number_of_workers = number_of_workers[current_gatherer];
    gatherers_groups.push_back(new GatherersGroup(
                        *queues[_get_gatherer_queue_index(current_gatherer)],
                        current_number_of_workers));
  }
}
*/

//VER SI PUEDO CAMBIAR ESTO POR UN EMPLACE BACK EN LA FUNCION PRINCIPAL PORQUE
//NO SE ESTA GUARDANDO COSAS NO COPIABLES
void ResourcesProcessor::_create_gatherers(Inventory& inventory,
                          std::vector<GatherersGroup*>& gatherers_groups,
                          const std::vector<int>& number_of_workers,
                          const std::vector<BlockingQueue*> queues){
  std::string current_gatherer;
  //CAMBIAR POR emplace_back Y BORRAR LA FUNCION DE DELETE
  for (size_t i = 0; i < NUMBER_OF_GATHERER_TYPES; i++) {
    gatherers_groups.push_back(new GatherersGroup(inventory, *queues[i],
                                                  number_of_workers[i]));
  }
}




void ResourcesProcessor::_destroy_gatherers(std::vector<GatherersGroup*>& gatherers_groups){
  for (size_t i = 0; i < gatherers_groups.size(); i++) {
    delete(gatherers_groups[i]);
  }
}




//VER SI PUEDO CAMBIAR ESTO POR UN EMPLACE BACK EN LA FUNCION PRINCIPAL PORQUE
//NO SE ESTA GUARDANDO COSAS NO COPIABLES
void ResourcesProcessor::_create_producers(Inventory& inventory,
                          std::vector<ProducersGroup*>& producers_groups,
                          const std::vector<int>& number_of_workers){
  //asdasdasd
  //REFACTORIZAR TODA ESTA FUNCION


  /*
  ProducersGroup(Inventory& inventory,
                 std::map<Resource, int>& resources_needed,
                 int number_of_producers, int points_produced)
  */
  std::map<Resource, int> resources_cooker = {std::pair<Resource, int>(RESOURCE_WHEAT, 2),
                                              std::pair<Resource, int>(RESOURCE_COAL, 1)};
  std::map<Resource, int> resources_carpenter = {std::pair<Resource, int>(RESOURCE_WOOD, 3),
                                                 std::pair<Resource, int>(RESOURCE_IRON, 1)};
  std::map<Resource, int> resources_gunsmith = {std::pair<Resource, int>(RESOURCE_COAL, 2),
                                                std::pair<Resource, int>(RESOURCE_IRON, 2)};
  //CAMBIAR POR emplace_back Y BORRAR LA FUNCION DE DELETE
  std::vector<std::map<Resource, int>> resources = {resources_cooker, resources_carpenter,
                                                    resources_gunsmith};
//asdasdasd
  std::vector<int> points_produced = {5, 2, 3};
  for (size_t i = NUMBER_OF_GATHERER_TYPES; i < NUMBER_OF_WORKER_TYPES; i++) {
    producers_groups.push_back(new ProducersGroup(inventory, resources[i - NUMBER_OF_GATHERER_TYPES],
                                                  number_of_workers[i],
                                                  points_produced[i - NUMBER_OF_GATHERER_TYPES]));
  }
}

void ResourcesProcessor::_destroy_producers(std::vector<ProducersGroup*>& producers_groups){
//asdasd
  for (size_t i = 0; i < producers_groups.size(); i++) {
    delete(producers_groups[i]);
  }
}


/////////////////////PUBLIC//////////////////////////////

//BORRAR INCLUDE, ES PARA DEBUGGEAR
#include <iostream>


/*
std::map<std::string, int> ResourcesProcessor::
        process_resources(std::fstream& resources,
                          const std::map<std::string, int>& number_of_workers){
*/
std::map<std::string, int> ResourcesProcessor::
        process_resources(std::ifstream& resources,
                          const std::vector<int>& number_of_workers){
//asdasdsad
  Inventory inventory;
  std::vector<ProducersGroup*> producers_groups;
  std::vector<GatherersGroup*> gatherers_groups;
  std::vector<BlockingQueue*> queues;

  _create_blocking_queues(queues);


  //VER SI SE CAMBIAN LAS OPERACIONES DE GATHERERS POR UNA DE UNA SOLA CLASE
  //QUE CONTENGA A TODOS LOS GATHERERS
  _create_gatherers(inventory, gatherers_groups, number_of_workers, queues);
  _create_producers(inventory, producers_groups, number_of_workers);

  //ACA SE TIRAN LOS PRODUCERS

  //VER SI HAY QUE PASAR ESTO AFUERA DE LA CLASE PORQUE EL ARCHIVO
  //DE TRABAJADORES SE LLAMA AFUERA
  _store_resources(resources, queues);
  //VER SI HAY Q LLAMAR A UN CLOSE DE LAS QUEUES AFUERA DE STORE
  inventory.close_entrance();

  //BORRAR ESTO ES PARA DEBUGGING
  int total_number_of_points = 0;

  //VER SI SE PASA EL FOR A UNA FUNCION QUE HAGA JOIN
  for (size_t i = 0; i < gatherers_groups.size(); i++) {
    gatherers_groups[i]->join();
  }
  for (size_t i = 0; i < producers_groups.size(); i++) {
    //BORRAR LA ASIGNACION, ES PARA DEBUGGING
    total_number_of_points += producers_groups[i]->join();
  }

  //BORRAR ESTE METODO, ES SOLO PARA DEBUGGEAR
  inventory.PRINT_STORED_RESOURCES();

  _destroy_producers(producers_groups);
  _destroy_gatherers(gatherers_groups);
  _destroy_blocking_queues(queues);


  //BORRAR PRINT, ES PARA DEBUGGEAR
  std::cout << "La cantidad de puntos es: " << total_number_of_points << "\n";


  //BORRAR: ESTA SOLO PARA QUE COMPILE
  std::map<std::string, int> compila;
  //PONER RETURN
  return compila;
}


ResourcesProcessor::ResourcesProcessor(){

}

ResourcesProcessor::~ResourcesProcessor(){
}
