#ifndef _FILES_CONSTANTS_H_
#define  _FILES_CONSTANTS_H_


//This strings must be present in the files
#define FARMER_TEXT "Agricultores"
#define LUMBERJACK_TEXT "Leniadores"
#define MINER_TEXT "Mineros"
#define COOKER_TEXT "Cocineros"
#define CARPENTER_TEXT "Carpinteros"
#define GUNSMITH_TEXT "Armeros"
#define WORKER_NUMBER_SEPARATOR '='

#define NUMBER_OF_RESOURCES 4
#define NUMBER_OF_GATHERER_TYPES 3
#define NUMBER_OF_WORKER_TYPES 6

//VER SI HAY QUE BORRAR ESTE DEFINE PORQUE POR AHORA NO SE USA
//#define NUMBER_OF_PRODUCER_TYPES 3


enum Gatherer{
  GATHERER_FARMER, GATHERER_LUMBERJACK, GATHERER_MINER
};

enum Producer{
  PRODUCER_COOKER, PRODUCER_CARPENTER, PRODUCER_GUNSMITH
};



#endif
