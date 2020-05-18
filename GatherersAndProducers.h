#ifndef _GATHERERS_AND_PRODUCERS_H_
#define _GATHERERS_AND_PRODUCERS_H_

#include <string>
#include <vector>
#include <map>
#include <fstream>
#include "BlockingQueue.h"
#include "ResourcesProcessor.h"
#include "FilesConstants.h"

//This class starts the execution of the program
class GatherersAndProducers {
private:
  std::vector<std::string> gatherers_text;
  std::vector<std::string> producers_text;
private:
  void _load_resources(std::ifstream& resources, ResourcesProcessor& processor);
  int _get_workers_ammounts_index(std::string& worker);
  bool _is_gatherer(std::string& worker_text);
  bool _is_producer(std::string& worker_text);
  Gatherer _convert_to_gatherer(std::string& gatherer_text);
  Producer _convert_to_producer(std::string& producer_text);
  void _add_worker_ammount(std::map<Gatherer, int>& gatherers_ammounts,
                           std::map<Producer, int>& producers_ammounts,
                           std::string& worker, std::string& ammount);
  void _load_workers_ammounts(std::ifstream& workers,
                              std::map<Gatherer, int>& gatherers_ammounts,
                              std::map<Producer, int>& producers_ammounts);
  void _print_result(std::map<Resource, int>& unprocessed_resources,
                     int produced_points);
public:
  GatherersAndProducers();

	~GatherersAndProducers();

  //Runs the program, returns 0 if successful and 1 if there is an error
  int execute(const char** arguments, int number_of_arguments);
};

#endif
