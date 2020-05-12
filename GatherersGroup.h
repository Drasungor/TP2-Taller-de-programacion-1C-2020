#ifndef _RESOURCES_PROCESSOR_H_
#define _RESOURCES_PROCESSOR_H_

#include <vector>
#include <thread>
#include "BlockingQueue.h"

class GatherersGroup {
private:
  std::vector<std::thread> threads;
public:
  //Starts number_of_gatherers threads for them to start gathering the
  //resources stored in the received blocking queue
  GatherersGroup(Inventory& inventory, BlockingQueue& q, int number_of_gatherers);

	~GatherersGroup();

  //void gather(BlockingQueue& q, int number_of_gatherers);
  void join();
};

#endif
