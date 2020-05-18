#ifndef _GATHERERS_H_
#define _GATHERERS_H_

#include <map>
#include "WorkersConstants.h"
#include "Resource.h"
#include "BlockingQueue.h"
#include "GatherersGroup.h"


class Gatherers {
private:
  std::map<Gatherer, BlockingQueue*> queues;
  std::map<Gatherer, GatherersGroup*> gatherers;
private:
  Gatherer _get_gatherer(Resource resource);
public:


  void close_resource_entrance();

  //Pushes the resource in the corresponding BlockingQueue
  void push_resource(Resource resource);

  //Waits for the gatherers to finish loading the resources in the inventory by
  //joining the execution threads
  void wait();

  Gatherers(const std::map<Gatherer, int>& gatherers_ammounts, Inventory& inventory);

  Gatherers(const Gatherers&) = delete;

	~Gatherers();
};

#endif
