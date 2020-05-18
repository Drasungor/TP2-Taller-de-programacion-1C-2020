#ifndef _PRODUCERS_GROUP_H_
#define _PRODUCERS_GROUP_H_

#include <thread>
#include <vector>
#include <map>
#include <mutex>
#include "Inventory.h"

//This class represents a group of a specific type of gatherer
class ProducersGroup {
private:
  std::vector<std::thread*> threads;
  int total_points_produced;
  int points_per_product;
  std::mutex m;
private:
  void _produce_points(Inventory& inventory,
                 std::map<Resource, int>& resources_needed,
                 int points_produced/*, std::mutex& m*/);
public:
  //Initialized the necessary variables and starts the execution of the
  //indicated number of threads in number_of_producers
  ProducersGroup(Inventory& inventory,
                 std::map<Resource, int>& resources_needed,
                 int number_of_producers, int points_produced);

  ProducersGroup(const ProducersGroup&) = delete;

  ~ProducersGroup();

  //Waits for the threads to finish their executions and returns the number
  //of benefit points produced
  int obtain_produced_points();
};


#endif
