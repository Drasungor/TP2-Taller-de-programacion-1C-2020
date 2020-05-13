#ifndef _PRODUCERS_GROUP_H_
#define  _PRODUCERS_GROUP_H_

#include <threads>
#include <vector>


class ProducersGroup {
private:
  std::vector<std::thread> threads;
private:
public:
  GatherersGroup(Inventory& inventory, BlockingQueue& q,
                 std::map<Resource, int> materials_needed,
                 int number_of_producers, int points_produced);

	~GatherersGroup();

  //void gather(BlockingQueue& q, int number_of_gatherers);
  void join();
};


#endif
