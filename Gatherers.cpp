#include "Gatherers.h"

#include <vector>
#include "Inventory.h"



////////////////////////////////////PUBLIC///////////////////

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
    gatherers[it->first] = new GatherersGroup(inventory, );
  }
}

Gatherers::~Gatherers(){
  for (size_t i = 0; i < queues.size(); i++) {
    delete(queues[i]);
  }
}
