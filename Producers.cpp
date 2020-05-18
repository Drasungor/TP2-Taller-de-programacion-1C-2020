#include "Producers.h"

//VER SI HAY QUE BORRAR EL INCLUDE DEL VECTOR PORQUE ESTA SOLO PARA EL CONSTRUCTOR
#include <vector>
#include <map>
#include "Inventory.h"
#include "FilesConstants.h"
#include "ProducersGroup.h"
#include "Resource.h"


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

  //std::map<Producer, std::map<Resource, int>> resources_needed
  std::vector<Producer> producers_indicators = {PRODUCER_COOKER,
                                                PRODUCER_CARPENTER,
                                                PRODUCER_GUNSMITH};
  //PASAR LOS NUMEROS A CONSTANTES
  std::map<Producer, int> benefit_points = {{PRODUCER_COOKER, 5},
                                            {PRODUCER_CARPENTER, 2},
                                            {PRODUCER_GUNSMITH, 3}};
  for (size_t i = 0; i < producers_indicators.size(); i++) {
    resources_needed[producers_indicators[i]] = new std::map<Resource, int>();
  }

  //PASAR LA INICIALIZACION DE LOS RECURSOS NECESITADOS A UNA FUNCION A PARTE
  *resources_needed[PRODUCER_COOKER] = {{RESOURCE_WHEAT, 2}, {RESOURCE_COAL, 1}};
  *resources_needed[PRODUCER_CARPENTER] = {{RESOURCE_WOOD, 3}, {RESOURCE_IRON, 1}};
  *resources_needed[PRODUCER_GUNSMITH] = {{RESOURCE_COAL, 2}, {RESOURCE_IRON, 2}};


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
