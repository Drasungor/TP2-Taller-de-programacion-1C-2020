#ifndef _BLOCKING_QUEUE_H_
#define _BLOCKING_QUEUE_H_

#include <condition_variable>
#include <mutex>
#include <queue>
#include "Resource.h"


class BlockingQueue {
private:
  bool is_closed;
  std::mutex m;
  std::queue<Resource> q;
  std::condition_variable cv;
private:
  void is_empty();

public:
  BlockingQueue();

	~BlockingQueue();

  Resource pop();

  void push(Resource resource);

  void close();
};

#endif
