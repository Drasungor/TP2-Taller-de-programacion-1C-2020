#ifndef _INVENTORY_H_
#define _INVENTORY_H_

#include <condition_variable>
#include <mutex>
#include <map>
#include "Resource.h"

class Inventory {
private:
  std::mutex m;
  std::condition_variable v;
  std::map<Resource, int> resources_quantities;
public:
  Inventory();

	~Inventory();

  void add_resource(Resource resource);
};

#endif
