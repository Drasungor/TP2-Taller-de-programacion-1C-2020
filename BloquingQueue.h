#ifndef _BLOQUING_QUEUE_H_
#define _BLOQUING_QUEUE_H_

#include <condition_variable.h>
#include <mutex.h>
#include <queue>

class BloquingQueue {
private:
  bool is_closed;
  std::mutex m;
  std::queue<Resource>;
  std::condition_variable cv;
public:
  BloquingQueue();

	~BloquingQueue();

  pop();

  push();

  close();


};

#endif
