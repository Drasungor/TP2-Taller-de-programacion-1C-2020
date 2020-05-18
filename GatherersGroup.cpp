#include "GatherersGroup.h"

#include <vector>
#include <unistd.h>
#include <thread>
#include "Inventory.h"
#include "BlockingQueue.h"
#include "ClosedQueueException.h"

#define GATHERER_WORKING_TIME_MICRO 50000

//Pops the elements from the blocking queue and stores them in the  inventory
//until the queue is closed
void GatherersGroup::_gather_resources(BlockingQueue& q, Inventory& inventory){
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
    delete(threads[i]);
  }
}
