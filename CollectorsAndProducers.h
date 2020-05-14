#ifndef _COLLECTORS_AND_PRODUCERS_H_
#define _COLLECTORS_AND_PRODUCERS_H_

#include <string>
#include <vector>
//#include <map>
#include <fstream>
#include "BlockingQueue.h"

class CollectorsAndProducers {
private:

  //TODO: AGREGAR TODAS LAS FUNCIONES PRIVADAS
  //int get_gatherer_index(Resource resource);
  //Resource convert_to_resource(char r);
  /*
  void load_resources(std::ifstream& materials,
                      std::vector<BlockingQueue&> &queues);
  void destroy_gatherers_queues(std::vector<BlockingQueue>& queues);
  */
  /*
  void _load_workers_ammounts(std::ifstream& workers,
                              std::map<std::string, int>& workers_ammounts);
  */
  int _get_workers_ammounts_index(std::string& worker);
  void _load_workers_ammounts(std::ifstream& workers,
                              std::vector<int>& workers_ammounts);
public:
  CollectorsAndProducers();

	~CollectorsAndProducers();

  //Runs the program, returns 0 if successful and 1 if there is an error
  int execute(const char** arguments, int number_of_arguments);
};

#endif
