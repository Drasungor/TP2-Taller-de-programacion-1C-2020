#ifndef _COLLECTORS_AND_PRODUCERS_H_
#define _COLLECTORS_AND_PRODUCERS_H_

#include "Resource.h"
#include "BlockingQueue.h"
#include <string>
#include <vector>

class CollectorsAndProducers {
private:

  //TODO: AGREGAR TODAS LAS FUNCIONES PRIVADAS
//asdasdasdasddasdasdasd
  int get_gatherer_index(Resource resource);
  Resource convert_to_resource(char r);
  void load_resources(std::ifstream& materials,
                      std::vector<BlockingQueue&> &queues);
//asdasd
  void destroy_gatherers_queues(std::vector<BlockingQueue>& queues);

public:
  CollectorsAndProducers();

	~CollectorsAndProducers();

  //Runs the program, returns 0 if successful and 1 if there is an error
  int execute(const char** arguments, int number_of_arguments);
};

#endif
