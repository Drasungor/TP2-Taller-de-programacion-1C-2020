#ifndef _RESOURCES_PROCESSOR_H_
#define _RESOURCES_PROCESSOR_H_

#include <map>
#include <string>
#include <fstream>
#include <vector>
#include "Resources.h"
#include "BlockingQueue.h"

//This class receives the resources and the number of each type of worker
//and processes the resources to produce the benefit points
class ResourcesProcessor {
private:
  //std::vector<BlockingQueue> queues;
public:
  //The keys provided must be in the workers file and must be defined
  ResourcesProcessor(const std::map<std::string, int>& number_of_workers);

	~ResourcesProcessor();

  /*
  //Adds resources so that they can be processed
  void add_resources(const string& resources);

  //Notifies the ResourcesProcessor that it will no longer receive resources
  void notify_resource_absence();
  */

  //Processes the resources stored in the file passed, the file must be valid
  std::map<string, int> process_resources(std::fstream& resources);

};

#endif
