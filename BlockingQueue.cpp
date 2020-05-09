#include "BloquingQueue.h"

BloquingQueue::BloquingQueue(){
  is_closed = false;
}

BloquingQueue::~BloquingQueue(){
}

Resource BloquingQueue::pop(){
  while (!is_closed) {
  }
  
}

void BloquingQueue::push(Resource resource){
  std::lock_guard<std::mutex> lk(m);
  q.push(resource);
  cv.notify_all();
}

void BloquingQueue::close(){
  //VER SI NO HACE FALTA ESTE LOCK, ANALIZAR BIEN SI ES
  //UNA CRITICAL SECTION
  std::lock_guard<std::mutex> lk(m);
  is_closed = true;
  cv.notify_all();
}
