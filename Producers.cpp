#include "Producers.h"

#include <vector>
#include <map>
#include "Inventory.h"
#include "FilesConstants.h"
#include "ProducersGroup.h"
#include "Resource.h"



void Producers::_store_resources_needed(const std::vector<Producer>&
                                        producers_indicators){
  for (size_t i = 0; i < producers_indicators.size(); i++) {
    resources_needed[producers_indicators[i]] = new std::map<Resource, int>();
  }
  *resources_needed[PRODUCER_COOKER] = {{RESOURCE_WHEAT, 2},
                                        {RESOURCE_COAL, 1}};
  *resources_needed[PRODUCER_CARPENTER] = {{RESOURCE_WOOD, 3},
                                           {RESOURCE_IRON, 1}};
  *resources_needed[PRODUCER_GUNSMITH] = {{RESOURCE_COAL, 2},
                                          {RESOURCE_IRON, 2}};
}


////////////////////PUBLIC//////////////////////////////


int Producers::obtain_produced_benefit_points(){
  int points = 0;
  for (std::map<Producer, ProducersGroup*>::iterator it = producers.begin();
       it != producers.end(); ++it) {
    points += it->second->join();
  }
  return points;
}


Producers::Producers(const std::map<Producer, int>& producers_ammounts, Inventory& inventory){
  std::vector<Producer> producers_indicators = {PRODUCER_COOKER,
                                                PRODUCER_CARPENTER,
                                                PRODUCER_GUNSMITH};
  //PASAR LOS NUMEROS A CONSTANTES
  std::map<Producer, int> benefit_points = {{PRODUCER_COOKER, 5},
                                            {PRODUCER_CARPENTER, 2},
                                            {PRODUCER_GUNSMITH, 3}};
/*
  for (size_t i = 0; i < producers_indicators.size(); i++) {
    resources_needed[producers_indicators[i]] = new std::map<Resource, int>();
  }

  *resources_needed[PRODUCER_COOKER] = {{RESOURCE_WHEAT, 2}, {RESOURCE_COAL, 1}};
  *resources_needed[PRODUCER_CARPENTER] = {{RESOURCE_WOOD, 3}, {RESOURCE_IRON, 1}};
  *resources_needed[PRODUCER_GUNSMITH] = {{RESOURCE_COAL, 2}, {RESOURCE_IRON, 2}};
*/
  _store_resources_needed(producers_indicators);


  for (std::map<Producer, int>::const_iterator it =
       producers_ammounts.begin(); it != producers_ammounts.end(); ++it) {
    //VER SI HAY QUE CAMBIAR benefit_points POR UN UNORDERED MAP
    producers[it->first] = new ProducersGroup(inventory,
                                              *resources_needed[it->first],
                                               it->second,
                                               benefit_points[it->first]);
  }
}

Producers::~Producers(){
  for (std::map<Producer, std::map<Resource, int>*>::iterator
          it = resources_needed.begin(); it != resources_needed.end(); ++it) {
    delete(it->second);
  }
  for (std::map<Producer, ProducersGroup*>::iterator it = producers.begin();
       it != producers.end(); ++it) {
    delete(it->second);
  }
}
