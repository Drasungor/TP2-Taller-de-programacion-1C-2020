#include "ResourcesProcessor.h"

#include <map>
#include <string>
#include "Inventory.h"
#include "Gatherers.h"
#include "Producers.h"
#include "Resource.h"
#include "WorkersConstants.h"

Resource ResourcesProcessor::_convert_to_resource(char resource){
  switch (resource) {
    case RESOURCE_WOOD:
      return RESOURCE_WOOD;
    case RESOURCE_WHEAT:
      return RESOURCE_WHEAT;
    case RESOURCE_COAL:
      return RESOURCE_COAL;
    default:
      return RESOURCE_IRON;
  }
}


/////////////////////PUBLIC//////////////////////////////

int ResourcesProcessor::obtain_process_results(std::map<Resource, int>&
                                               unprocessed_resources){
  int benefit_points = 0;
  gatherers.wait();
  inventory.close_entrance();
  benefit_points = producers.obtain_produced_points();
  inventory.copy_stored_resources(unprocessed_resources);
  return benefit_points;
}

void ResourcesProcessor::store_resources(const std::string& resources){
  Resource resource;
  for (size_t i = 0; i < resources.size(); i++) {
    resource = _convert_to_resource(resources[i]);
    gatherers.push_resource(resource);
  }
}

void ResourcesProcessor::close_resource_entrance(){
  gatherers.close_resource_entrance();
}

ResourcesProcessor::ResourcesProcessor(
                    const std::map<Gatherer, int>& gatherers_ammounts,
                    const std::map<Producer, int>& producers_ammounts):
                    producers(producers_ammounts, inventory),
                    gatherers(gatherers_ammounts, inventory){
}

ResourcesProcessor::~ResourcesProcessor(){
}
