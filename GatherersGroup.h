#ifndef _GATHERERS_GROUP_H_
#define _GATHERERS_GROUP_H_

#include <vector>
#include <thread>
#include "BlockingQueue.h"
#include "Inventory.h"

class GatherersGroup {
private:
  std::vector<std::thread> threads;
private:
  void gather_resources(BlockingQueue& q, Inventory& inventory);
public:
  //Starts number_of_gatherers threads for them to start gathering the
  //resources stored in the received blocking queue
  GatherersGroup(Inventory& inventory, BlockingQueue& q, int number_of_gatherers);

	~GatherersGroup();

  //void gather(BlockingQueue& q, int number_of_gatherers);
  void join();
};

#endif
