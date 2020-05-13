#include "BlockingQueue.h"

#include <condition_variable>
#include <mutex>
//#include <thread>
#include "Resource.h"
#include "ClosedQueueException.h"


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
      //CAMBIAR LA FUNCION POR GUARDAR PUNTEROS Y DEVOLVER NULL
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
  //VER SI NO HACE FALTA ESTE LOCK, ANALIZAR BIEN SI ES
  //UNA CRITICAL SECTION
  std::lock_guard<std::mutex> lk(m);
  is_closed = true;
  cv.notify_all();
}
