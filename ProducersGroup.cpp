#include "ProducersGroup.h"

#include <thread>
#include <vector>
#include <map>
#include <mutex>
#include <unistd.h>
#include "Inventory.h"

#define PRODUCER_WORKING_TIME_MICRO 60000

//Asks the inventory for the resources needed and produces the corresponding
//ammount of benefit points, adding them to the total of points produced
void ProducersGroup::_produce_points(Inventory& inventory,
               std::map<Resource, int>& resources_needed, int points_produced){

  while (inventory.consume_resources(resources_needed)) {
    usleep(PRODUCER_WORKING_TIME_MICRO);
    m.lock();
    total_points_produced += points_produced;
    m.unlock();
  }
}



//////////////////////PUBLIC/////////////////////

//VER SI SE CAMBIA POR UN GET POINTS Y DEVUELVO LOS PUNTOS TOTALES GENERADOS ACA
int ProducersGroup::join(){
  for (size_t i = 0; i < threads.size(); i++) {
    threads[i]->join();
  }
  return total_points_produced;
}


ProducersGroup::ProducersGroup(Inventory& inventory,
               std::map<Resource, int>& resources_needed,
               int number_of_producers, int points_produced){

  total_points_produced = 0;
  points_per_product = points_produced;
  for (int i = 0; i < number_of_producers; i++) {
    threads.push_back(new std::thread(&ProducersGroup::_produce_points, this,
                               std::ref(inventory), std::ref(resources_needed),
                               std::ref(points_per_product)/*, std::ref(m)*/));
  }
}

ProducersGroup::~ProducersGroup(){
  for (size_t i = 0; i < threads.size(); i++) {
    delete(threads[i]);
  }
}
