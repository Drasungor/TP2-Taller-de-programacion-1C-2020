#include "ResourcesProcessor.h"

#include <map>
#include <string>
#include <fstream>
#include <vector>
#include "Resource.h"
#include "BlockingQueue.h"
#include "FilesConstants.h"


const std::vector<std::string> GATHERERS_IDENTIFIERS =
        {FARMER_TEXT, LUMBERJACK_TEXT, MINER_TEXT};
const std::vector<std::string> PRODUCERS_IDENTIFIERS =
        {COOKER_TEXT, CARPENTER_TEXT, GUNSMITH_TEXT};

//Loads the resources from the materials file into the
//different gatherers' blocking queues
void ResourcesProcessor::load_resources(std::ifstream& materials,
                                        std::vector<BlockingQueue> &queues){
  std::string buffer;
  Resource aux;
  while (!materials.eof()) {
    std::getline(materials, buffer);
    for (size_t i = 0; i < buffer.length(); i++) {
      aux = convert_to_resource(buffer[i]);
      queues[get_gatherer_index(aux)].push(aux);
    }
    buffer.clear();
  }
}


/////////////////////PUBLIC//////////////////////////////

std::map<std::string, int> ResourcesProcessor::
        process_resources(std::fstream& resources,
                          const std::map<std::string, int>& number_of_workers){
  //VER SI HAY QUE BORRAR EL NUMBER_OF_GATHERERS DEL CONSTRUCTOR
  std::vector<BlockingQueue> queues(NUMBER_OF_GATHERERS);
  //for (size_t i = 0; i < NUMBER_OF_GATHERERS; i++) {
  for (size_t i = 0; i < WORKERS_IDENTIFIERS.size(); i++) {
    queues.emplace_back();
  }

}


ResourcesProcessor::ResourcesProcessor(){

}

ResourcesProcessor::~ResourcesProcessor(){
}
