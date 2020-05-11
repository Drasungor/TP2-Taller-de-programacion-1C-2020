#include "Inventory.h"

//VER SI HAY QUE BORRARLO POR EL COSNTRUCTOR
#include <vector>


#define RESOURCES_INITIAL_QUANTITY 0

/////////////////////PUBLIC//////////////////////////////


void Inventory::add_resource(Resource resource){
}


Inventory::Inventory(){
  //VER SI SE CAMBIA ESTE VECTOR Y SE INICIALIZA CADA UNO EN UNA LINEA DISTINTA
  std::vector<int> resources = {RESOURCE_WHEAT, RESOURCE_WOOD, RESOURCE_COAL,
                                RESOURCE_IRON};
//asdasdas
  for (size_t i = 0; i < resources.size(); i++) {
      resources_quantities.insert(resources[i], RESOURCES_INITIAL_QUANTITY);
  }
  /*
  resources_quantities.insert(RESOURCE_WHEAT, RESOURCES_INITIAL_QUANTITY);
  resources_quantities.insert(RESOURCE_WOOD, RESOURCES_INITIAL_QUANTITY);
  resources_quantities.insert(RESOURCE_WHEAT, RESOURCES_INITIAL_QUANTITY);
  resources_quantities.insert(RESOURCE_WHEAT, RESOURCES_INITIAL_QUANTITY);
  */
}

Inventory::~Inventory(){
}
