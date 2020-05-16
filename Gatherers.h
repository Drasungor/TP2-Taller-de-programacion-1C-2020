#ifndef _GATHERERS_H_
#define _GATHERERS_H_

#include <map>
#include "FilesConstants.h"
#include "BlockingQueue.h"
#include "Resource.h"


class Gatherers {
private:

private:
  std::map<Gatherer, BlockingQueue*> queues;
  std::map<Gatherer, GatherersGroup*> gatherers;
public:

  void close_resource_entrance();

  //Pushes the resource in the corresponding BlockingQueue
  void push_resource(Resource resource);

  //Waits for the gatherers to finish loading the resources in the inventory by
  //joining the execution threads
  void wait();

  Gatherers(std::map<Gatherer, int>& gatherers_ammounts);

	~Gatherers();
};

#endif
