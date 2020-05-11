#include "ResourcesProcessor.h"

#include <map>
#include <string>
#include <fstream>
#include <vector>
#include "Resources.h"
#include "BlockingQueue.h"
#include "FilesConstants.h"





std::map<string, int> ResourcesProcessor::process_resources(std::fstream& resources){
  //VER SI HAY QUE BORRAR EL NUMBER_OF_GATHERERS DEL CONSTRUCTOR
  std::vector<BlockingQueue> queues(NUMBER_OF_GATHERERS);
  for (size_t i = 0; i < NUMBER_OF_GATHERERS; i++) {
    queues.emplace_back();
  }

}


ResourcesProcessor::ResourcesProcessor(const std::map<std::string, int>& number_of_workers){

}

ResourcesProcessor::~ResourcesProcessor(){
}
