#ifndef _INVENTORY_H_
#define _INVENTORY_H_

#include <condition_variable>
#include <mutex>
#include <map>
#include "Resource.h"

class Inventory {
private:
  std::mutex m;
  std::condition_variable cv;
  std::map<Resource, int> resources_quantities;
  bool is_entrance_closed;
private:
  bool _are_resources_available(std::map<Resource, int>& requested_resources);
  void _consume_resources(std::map<Resource, int>& requested_resources);
public:
  Inventory();

	~Inventory();

  //Returns true if the resources were consumed, otherwise returns false
  //The requested_resources map is not modified
  bool consume_resources(std::map<Resource, int>& requested_resources);

  //Increments the received resource stored ammount by 1
  void add_resource(Resource resource);

  //Indicates that the inventory will not receive any other resource so that
  //consume_resources doesn't block the thread forever if there are no
  //resources
  void close_entrance();

  //Returns a refference to the map that stores the ammount of each resource
  //This function is not thread safe,
  void copy_stored_resources(std::map<Resource, int>& buffer) const;

};

#endif
