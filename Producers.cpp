#include "Producers.h"

//VER SI HAY QUE BORRAR EL INCLUDE DEL VECTOR PORQUE ESTA SOLO PARA EL CONSTRUCTOR
#include <vector>
#include <map>
#include "FilesConstants.h"


////////////////////PUBLIC//////////////////////////////

Producers(std::map<Producer, int>& producers_ammounts){

  //std::map<Producer, std::map<Resource, int>> resources_needed
  std::vector<Producer> producers = {PRODUCER_COOKER, PRODUCER_CARPENTER,
                                     PRODUCER_GUNSMITH};
//asdasdas
  //CAMBIAR LOS NUMEROS POR CONSTANTES
  //VER SI SE PASA ESTO COMO UN PARAMETRO GUARDADO DE LA CLASE
  std::map<Producer, int> benefit_points = {{PRODUCER_COOKER, 5},
                                            {PRODUCER_CARPENTER, 2},
                                            {PRODUCER_GUNSMITH, 3}};

  for (size_t i = 0; i < producers.size(); i++) {
    resources_needed[producers[i]] = new std::map<Resource, int>();
  }
  resources_needed[PRODUCER_COOKER] = {{}, {}};
}

~Producers(){
  for (std::map<Producer, std::map<Resource, int>*>::iterator
          it = resources_needed.begin(); it != resources_needed.end(); ++it) {
    delete(it->second);
  }
}
