#ifndef _RESOURCES_PROCESSOR_H_
#define _RESOURCES_PROCESSOR_H_

#include <map>
#include <string>
#include <fstream>
#include <vector>
#include "Resource.h"
#include "BlockingQueue.h"
#include "GatherersGroup.h"

//This class receives the resources and the number of each type of worker
//and processes the resources to produce the benefit points
class ResourcesProcessor {
private:
  void _create_gatherers(std::vector<GatherersGroup>& gatherers_groups);
  void _destroy_gatherers(std::vector<GatherersGroup>& gatherers_groups);
  void _close_blocking_queues(std::vector<BlockingQueue*>& queues);
  void _create_blocking_queues(std::vector<BlockingQueue*>& queues);
  void _destroy_blocking_queues(std::vector<BlockingQueue*>& queues);
  void _store_resources(std::fstream& resources,
                        std::vector<BlockingQueue>& queues);
  Resource _convert_to_resource(char resource);
  void _load_resources(std::ifstream& materials,
                      std::vector<BlockingQueue>& queues);
//asdasd
public:
  //The keys provided must be in the workers file and must be defined
  ResourcesProcessor();

	~ResourcesProcessor();

  /*
  //Adds resources so that they can be processed
  void add_resources(const string& resources);

  //Notifies the ResourcesProcessor that it will no longer receive resources
  void notify_resource_absence();
  */

  //Processes the resources stored in the file passed, the file must be valid
  std::map<std::string, int> process_resources(std::fstream& resources,
                          const std::map<std::string, int>& number_of_workers);
//asdasd
};

#endif
