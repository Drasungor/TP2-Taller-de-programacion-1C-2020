#include "Inventory.h"

//VER SI HAY QUE BORRARLO POR EL COSNTRUCTOR
#include <vector>

#define RESOURCES_INITIAL_QUANTITY 0

/////////////////////PUBLIC//////////////////////////////

void Inventory::add_resource(Resource resource){
  std::lock_guard<std::mutex> lk(m);
  resources_quantities[resource]++;
}


Inventory::Inventory(){
  //VER SI SE CAMBIA ESTE VECTOR Y SE INICIALIZA CADA UNO EN UNA LINEA DISTINTA
  std::vector<Resource> resources = {RESOURCE_WHEAT, RESOURCE_WOOD, RESOURCE_COAL,
                                RESOURCE_IRON};
  for (size_t i = 0; i < resources.size(); i++) {
      resources_quantities.insert(std::pair<Resource, int>(resources[i],
                                              RESOURCES_INITIAL_QUANTITY));
  }
}

Inventory::~Inventory(){
}
