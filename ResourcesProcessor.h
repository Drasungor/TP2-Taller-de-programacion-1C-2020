#ifndef _RESOURCES_PROCESSOR_H_
#define _RESOURCES_PROCESSOR_H_

#include <map>
#include <string>
#include <fstream>
#include <vector>
#include "Resource.h"
#include "BlockingQueue.h"
#include "GatherersGroup.h"
#include "ProducersGroup.h"
#include "Inventory.h"

//This class receives the resources and the number of each type of worker
//and processes the resources to produce the benefit points
class ResourcesProcessor {
  Producers producers;
  Gatherers gatherers;
private:
  int _get_gatherer_queue_index(Resource resource);
  /*
  void _create_gatherers(std::vector<GatherersGroup*>& gatherers_groups,
                         std::map<std::string, int>& number_of_workers,
                         const std::vector<BlockingQueue*> queues);
  */
  void _create_producers(Inventory& inventory,
                            std::vector<ProducersGroup*>& producers_groups,
                            const std::vector<int>& number_of_workers,
                            //SACAR ESTE ULTIMO PARAMETRO, ES PARA VER SI EL ERROR
                            //ES POR DESTRUIR EL VECTOR DE LOS MAPS QUE SE PASA
                            //A LOS THREADS
                            std::vector<std::map<Resource, int>>& resources_vec);
  void _destroy_producers(std::vector<ProducersGroup*>& producers_groups);
  void _create_gatherers(Inventory& inventory,
                         std::vector<GatherersGroup*>& gatherers_groups,
                         const std::vector<int>& number_of_workers,
                         const std::vector<BlockingQueue*> queues);
  void _destroy_gatherers(std::vector<GatherersGroup*>& gatherers_groups);
  void _close_blocking_queues(std::vector<BlockingQueue*>& queues);
  void _create_blocking_queues(std::vector<BlockingQueue*>& queues);
  void _destroy_blocking_queues(std::vector<BlockingQueue*>& queues);
  /*
  void _store_resources(std::ifstream& resources,
                        std::vector<BlockingQueue*>& queues);
  void _store_resources(const std::string& resources,
                        std::vector<BlockingQueue*>& queues);
  */
  Resource _convert_to_resource(char resource);
  void _load_resources(std::ifstream& materials,
                      std::vector<BlockingQueue>& queues);
//asdasd
public:
  //The keys provided must be in the workers file and must be defined
  //ResourcesProcessor();
  //ResourcesProcessor();

  ResourcesProcessor(const std::map<Gatherer, int>& gatherers_ammounts,
                     const std::map<Producer, int>& producers_ammounts)


	~ResourcesProcessor();


  //Stores the received resources in their respective blocking queues
  void store_resources(const std::string& resources);

  //Indicates the processor that no more resources will be stored so that
  //the blocking queues can be closed
  void close_resource_entrance();


  int obtain_process_results(std::map<Resource, int>& unprocessed_resources);

  /*
  //Processes the resources stored in the file passed, the file must be valid
  std::map<std::string, int> process_resources(std::fstream& resources,
                          const std::map<std::string, int>& number_of_workers);
  */
  /*
  int process_resources(std::ifstream& resources,
                         const std::map<Gatherer, int>& gatherers_ammounts,
                         const std::map<Producer, int>& producers_ammounts,
                         std::map<Resource, int>& unprocessed_resources);
  */
  /*
  int process_resources(std::ifstream& resources,
                         const std::vector<int>& number_of_workers,
                         std::map<Resource, int>& unprocessed_resources);
  */
};

#endif
