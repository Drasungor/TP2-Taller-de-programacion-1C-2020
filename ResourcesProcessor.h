#ifndef _RESOURCES_PROCESSOR_H_
#define _RESOURCES_PROCESSOR_H_

//#include <vector>
#include <map>

class ResourcesProcessor {
private:

public:
  //The keys provided must be in the workers file and must be defined
  ResourcesProcessor(const std::map<string, int>& number_of_workers);

	~ResourcesProcessor();

  //Runs the program, returns 0 if successful and 1 if there is an error
  int execute(const char** arguments, int number_of_arguments);
};

#endif
