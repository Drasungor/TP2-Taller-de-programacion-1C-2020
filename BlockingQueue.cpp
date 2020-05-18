#include "BlockingQueue.h"

#include <condition_variable>
#include <mutex>
#include "Resource.h"
#include "ClosedQueueException.h"


/////////////////////////////////PUBLIC///////////////////////////////////////

BlockingQueue::BlockingQueue(){
  is_closed = false;
}

BlockingQueue::~BlockingQueue(){
}

Resource BlockingQueue::pop(){
  std::unique_lock<std::mutex> lk(m);
  Resource resource;
  while (q.empty()) {
    if (is_closed) {
      throw ClosedQueueException();
    }
    cv.wait(lk);
  }
  resource = q.front();
  q.pop();
  return resource;
}

void BlockingQueue::push(Resource resource){
  std::lock_guard<std::mutex> lk(m);
  q.push(resource);
  cv.notify_all();
}

void BlockingQueue::close(){
  std::lock_guard<std::mutex> lk(m);
  is_closed = true;
  cv.notify_all();
}
