#include "Gatherers.h"

#include <vector>
#include "Inventory.h"
#include "Resource.h"


//VER SI CAMBIO POR UN MAP CON CLAVE RESOURCE Y VALOR GATHERER
Gatherer Gatherers::_get_gatherer(Resource resource){
  switch (resource) {
    case RESOURCE_WHEAT:
      return GATHERER_FARMER;
    case RESOURCE_WOOD:
      return GATHERER_LUMBERJACK;
    default:
      return GATHERER_MINER;
  }
}


////////////////////////////////////PUBLIC///////////////////

void Gatherers::close_resource_entrance(){
  for (size_t i = 0; i < queues.size(); i++) {
    queues[i].close();
  }
}


void Gatherers::push_resource(Resource resource){
  queues[_get_gatherer(resource)]->push(resource);
}

void Gatherers::wait(){
  for (size_t i = 0; i < gatherers.size(); i++) {
    gatherers[i]->join();
  }
}


Gatherers::Gatherers(const std::map<Gatherer, int>& gatherers_ammounts, Inventory& inventory){
  std::vector<Gatherer> gatherers_indicators = {GATHERER_FARMER, GATHERER_LUMBERJACK,
                                     GATHERER_MINER};
  //asdasdasd
  for (size_t i = 0; i < gatherers.size(); i++) {
    queues[gatherers_indicators[i]] = new BlockingQueue();
  }
  //gatherers
  for (std::map<Gatherer, int>::constant_iterator it =
       gatherers_ammounts.begin(); it != gatherers_ammounts.end(); ++it) {
//asdasdasd
  //asdasdasd
    //GatherersGroup(Inventory& inventory, BlockingQueue& q, int number_of_gatherers);
    gatherers[it->first] = new GatherersGroup(inventory, *queues[it->first], it->second);
  }
}

Gatherers::~Gatherers(){
  for (std::map<Gatherer, BlockingQueue*>::iterator it = queues.begin();
       it != queues.end(); ++it) {
    delete(it->second);
  }
  for (std::map<Gatherer, GatherersGroup*>::iterator it = gatherers.begin();
       it != gatherers.end(); ++it) {
    delete(it->second);
  }
}
