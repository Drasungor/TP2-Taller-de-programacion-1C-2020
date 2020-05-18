#ifndef _RESOURCES_PROCESSOR_H_
#define _RESOURCES_PROCESSOR_H_

#include <map>
#include <string>
#include "Gatherers.h"
#include "Producers.h"
#include "Resource.h"
#include "FilesConstants.h"
#include "Inventory.h"

//This class receives the resources and the number of each type of worker
//and processes the resources to produce the benefit points
class ResourcesProcessor {
private:
  Inventory inventory;
  Producers producers;
  Gatherers gatherers;
private:
  Resource _convert_to_resource(char resource);
public:
  ResourcesProcessor(const std::map<Gatherer, int>& gatherers_ammounts,
                     const std::map<Producer, int>& producers_ammounts);

	~ResourcesProcessor();


  //Stores the received resources in their respective blocking queues
  void store_resources(const std::string& resources);

  //Indicates the processor that no more resources will be stored so that
  //the blocking queues can be closed
  void close_resource_entrance();


  int obtain_process_results(std::map<Resource, int>& unprocessed_resources);
};

#endif
