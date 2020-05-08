#ifndef _COLLECTORS_AND_PRODUCERS_H_
#define _COLLECTORS_AND_PRODUCERS_H_


class CollectorsAndProducers {
private:

public:
  CollectorsAndProducers();

	~CollectorsAndProducers();

  //Runs the program, returns 0 if successful and 1 if there is an error
  int execute(const char** arguments, int number_of_arguments);
};

#endif
