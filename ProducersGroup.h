#ifndef _PRODUCERS_GROUP_H_
#define  _PRODUCERS_GROUP_H_

#include <thread>
#include <vector>
#include <map>
#include <mutex>
#include "Inventory.h"

class ProducersGroup {
private:
  std::vector<std::thread*> threads;
  int total_points_produced;
  //std::mutex m;
private:
  void _produce_points(Inventory& inventory,
                 std::map<Resource, int>& resources_needed,
                 int points_produced, std::mutex& m);
public:
  ProducersGroup(Inventory& inventory,
                 std::map<Resource, int>& resources_needed,
                 int number_of_producers, int points_produced);

	~ProducersGroup();

  //void gather(BlockingQueue& q, int number_of_gatherers);
  int join();
};


#endif
