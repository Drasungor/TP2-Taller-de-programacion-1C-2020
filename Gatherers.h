#ifndef _GATHERERS_H_
#define _GATHERERS_H_

#include <map>
#include "FilesConstants.h"
#include "BlockingQueue.h"

class Gatherers {
private:

private:

public:
  Gatherers(std::map<Gatherer, int>& gatherers_ammounts);

	~Gatherers();
};

#endif
