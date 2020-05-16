#ifndef _PRODUCERS_H_
#define _PRODUCERS_H_

#include <map>
#include "ProducersGroup.h"
#include "FilesConstants.h"
#include "Resource.h"

class Producers {
private:
  std::map<Producer, std::map<Resource, int>*> resources_needed;
  //std::map<Producer, int> benefit_points;
  std::map<Producer, ProducersGroup*> producers;
private:

public:
  //Waits for the producers to finish their work and returns the total
  //number of benefit points produced
  int obtain_produced_benefit_points();


  //Starts the ammounts of Producers of each type of produced indicated in
  //producers_ammounts and stores the necessary information that the producers
  //need for their work
  Producers(const std::map<Producer, int>& producers_ammounts);

	~Producers();

};

#endif
