#include "GatherersGroup.h"

#include <unistd.h>

#define GATHERER_WORKING_TIME_MICRO 50000

void GatherersGroup::_gather_resources(BlockingQueue& q, Inventory& inventory){
  //VER SI SE CAMBIA POR EL RESOURCE_NULL
  bool keeps_iterating = true;
  Resource resource;
  while (keeps_iterating) {
    try {
      resource = q.pop();
    } catch (/*AGREGAR EXCEPTION*/) {
      keeps_iterating = false;
    }
    if (keeps_iterating) {
      usleep(GATHERER_WORKING_TIME_MICRO);
      inventory.add_resource(resource);
    }
  }
}


/////////////////////PUBLIC//////////////////////////////

void GatherersGroup::join(){
  for (size_t i = 0; i < threads.size(); i++) {
    threads[i]->join();
  }
}


GatherersGroup::GatherersGroup(Inventory& inventory, BlockingQueue& q,
                               int number_of_gatherers){
  for (int i = 0; i < number_of_gatherers; i++) {
    threads.push_back(new std::thread(&GatherersGroup::_gather_resources, this,
                                      std::ref(q), std::ref(inventory)));
  }
}

GatherersGroup::~GatherersGroup(){
  for (size_t i = 0; i < threads.size(); i++) {
    //VER SI EN VEZ DE ITERAR POR EL VECTOR CONVIENEIR VACIANDOLO Y LIBERAR
    //CADA THREAD VACIADO, PERO SI SE HACE ESO HAY QUE OBTENER EL SIZE ANTES
    //DE ITERAR
    delete(threads[i]);
  }
}
