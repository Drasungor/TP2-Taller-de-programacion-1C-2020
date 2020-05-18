#ifndef _BLOCKING_QUEUE_H_
#define _BLOCKING_QUEUE_H_

#include <condition_variable>
#include <mutex>
#include <queue>
#include "Resource.h"

//This class is a thread safe queue that blocks the thread that tries to pop
//an element from it until there is at least one element stored
class BlockingQueue {
private:
  bool is_closed;
  std::mutex m;
  std::queue<Resource> q;
  std::condition_variable cv;
public:
  BlockingQueue();

	~BlockingQueue();

  //Returns and removes the "oldest" element from the queue
  //If the queue is empty and closed it throws a ClosedQueueException
  Resource pop();

  //Stores a copy of the resource in the queue
  void push(Resource resource);

  //Indicates that the queue will not receive any other resource so that
  void close();

  BlockingQueue(const BlockingQueue&) = delete;
};

#endif
