#ifndef _BLOCKING_QUEUE_H_
#define _BLOCKING_QUEUE_H_

#include <condition_variable>
#include <mutex>
#include <queue>

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

  void push();

  void close();
};

#endif
