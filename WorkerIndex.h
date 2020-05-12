#ifndef _WORKER_INDEX_H_
#define  _WORKER_INDEX_H_

//Defines the index for each type of worker for the workers numbers vector.
//The constants were purposely defined in this order: gatherers - producers
enum WorkerIndex{
  WORKER_INDEX_FARMER,
  WORKER_INDEX_LUMBERJACK,
  WORKER_INDEX_MINER,
  WORKER_INDEX_COOKER,
  WORKER_INDEX_CARPENTER,
  WORKER_INDEX_GUNSMITH
}


#endif
