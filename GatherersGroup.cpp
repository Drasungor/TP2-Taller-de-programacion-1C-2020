#include "GatherersGroup.h"

#include <vector>
#include <unistd.h>
#include <thread>
#include "Inventory.h"
#include "ClosedQueueException.h"

#define GATHERER_WORKING_TIME_MICRO 50000



//BORRAR INCLUDE
#include <iostream>

void GatherersGroup::_gather_resources(BlockingQueue& q, Inventory& inventory){
  //VER SI SE CAMBIA POR EL RESOURCE_NULL
  bool keeps_iterating = true;
  Resource resource;
  while (keeps_iterating) {
    try {
      resource = q.pop();
    } catch (ClosedQueueException e) {
      keeps_iterating = false;
    }
    if (keeps_iterating) {
      usleep(GATHERER_WORKING_TIME_MICRO);


      //BORRAR PRINT
      std::cout << "Voy a agregar " << char(resource) << " al inventario\n";


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


//BORRAR INCLUDE
#include <iostream>


GatherersGroup::GatherersGroup(Inventory& inventory, BlockingQueue& q,
                               int number_of_gatherers){

//
//BORRAR PRINT
  std::cout << "Voy a tirar threads\n";


  for (int i = 0; i < number_of_gatherers; i++) {


    //BORRAR PRINT
    std::cout << "Tiro thread\n";


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
