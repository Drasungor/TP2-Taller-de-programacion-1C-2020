#ifndef _RESOURCES_PROCESSOR_H_
#define _RESOURCES_PROCESSOR_H_

#include "BlockingQueue.h"

class GatherersGroup {
private:

public:
  GatherersGroup();

	~GatherersGroup();

  void gather(BlockingQueue& q, int number_of_gatherers);
};

#endif
