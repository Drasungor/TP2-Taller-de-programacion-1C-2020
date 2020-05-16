#ifndef _PRODUCERS_H_
#define _PRODUCERS_H_

#include <map>
#include "FilesConstants.h"
#include "Resource.h"

class Producers {
private:
  std::map<Producer, std::map<Resource, int>*> resources_needed;
private:

public:
  Producers(std::map<Producer, int>& producers_ammounts);

	~Producers();

};

#endif
