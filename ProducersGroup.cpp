#include "ProducersGroup.h"

#include <thread>
#include <vector>
#include <map>
#include <mutex>
#include <unistd.h>
#include "Inventory.h"

#define PRODUCER_WORKING_TIME_MICRO 60000

//BORRAR INCLUDE
#include <iostream>

void ProducersGroup::_produce_points(Inventory& inventory,
               std::map<Resource, int>& resources_needed, int points_produced/*,
               std::mutex& m*/){

  //BORRAR PRINT
  std::cout << "VOY A INTENTAR CONSUMIR RECURSOS\n";


  while (inventory.consume_resources(resources_needed)) {



    //BORRAR PRINT
    std::cout << "PUDE CONSUMIR RECURSOS\n";



    usleep(PRODUCER_WORKING_TIME_MICRO);
    m.lock();

    //BORRAR PRINT
    std::cout << "ASDASD POINTS PRODUCED VALE: " << points_produced << "\n";


    total_points_produced += points_produced;


    //BORRAR PRINT
    std::cout << "Los puntos producidos actualmente son: " << total_points_produced << "\n";


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
  //BORRAR PRINT
  std::cout << "LOS PUNTOS ACTUALES SON " << total_points_produced << "\n";
  std::cout << "LOS PUNTOS QUE VA A PODUCIR ESTE PRODUCTOR SON " << points_produced << "\n";


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
