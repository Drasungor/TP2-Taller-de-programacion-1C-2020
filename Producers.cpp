#include "Producers.h"

#include <vector>
#include <map>
#include "Inventory.h"
#include "WorkersConstants.h"
#include "ProducersGroup.h"
#include "Resource.h"


//Stores in the resources_needed map the ammount of each resource each type
//of producer needs
void Producers::_store_resources_needed(const std::vector<Producer>&
                                        producers_indicators){
  for (size_t i = 0; i < producers_indicators.size(); i++) {
    resources_needed[producers_indicators[i]] = new std::map<Resource, int>();
  }
  *resources_needed[PRODUCER_COOKER] =
                              {{RESOURCE_WHEAT, RESOURCE_NEEDED_COOKER_WHEAT},
                               {RESOURCE_COAL, RESOURCE_NEEDED_COOKER_COAL}};
  *resources_needed[PRODUCER_CARPENTER] =
                            {{RESOURCE_WOOD, RESOURCE_NEEDED_CARPENTER_WOOD},
                             {RESOURCE_IRON, RESOURCE_NEEDED_CARPENTER_IRON}};
  *resources_needed[PRODUCER_GUNSMITH] =
                            {{RESOURCE_COAL, RESOURCE_NEEDED_GUNSMITH_COAL},
                             {RESOURCE_IRON, RESOURCE_NEEDED_GUNSMITH_IRON}};
}


////////////////////PUBLIC//////////////////////////////

int Producers::obtain_produced_points(){
  int points = 0;
  for (std::map<Producer, ProducersGroup*>::iterator it = producers.begin();
       it != producers.end(); ++it) {
    points += it->second->obtain_produced_points();
  }
  return points;
}

Producers::Producers(const std::map<Producer, int>& producers_ammounts,
                     Inventory& inventory){
  std::vector<Producer> producers_indicators = {PRODUCER_COOKER,
                                                PRODUCER_CARPENTER,
                                                PRODUCER_GUNSMITH};
  std::map<Producer, ProducerPoints> benefit_points =
                              {{PRODUCER_COOKER, PRODUCER_PONTS_COOKER},
                               {PRODUCER_CARPENTER, PRODUCER_PONTS_CARPENTER},
                               {PRODUCER_GUNSMITH, PRODUCER_PONTS_GUNSMITH}};
  _store_resources_needed(producers_indicators);
  for (std::map<Producer, int>::const_iterator it =
       producers_ammounts.begin(); it != producers_ammounts.end(); ++it) {
    producers[it->first] = new ProducersGroup(inventory,
                                  *resources_needed[it->first], it->second,
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
