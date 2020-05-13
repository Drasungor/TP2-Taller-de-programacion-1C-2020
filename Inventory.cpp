#include "Inventory.h"

//VER SI HAY QUE BORRARLO POR EL COSNTRUCTOR
#include <vector>
#include <map>

#define RESOURCES_INITIAL_QUANTITY 0

//Returns true if the requested resources are available, if there is less than
//the requested ammount of any of the resources returns false
//The requested resources map is not modified
bool Inventory::_are_resources_available(std::map<Resource, int>& requested_resources){
  for (std::map<Resource, int>::iterator it = requested_resources.begin(); it != requested_resources.end(); ++it) {
    if (requested_resources[it->first] > resources_quantities[it->first]) {
      return false;
    }
  }
  return true;
}

//Reduces the ammount of requested resources from the stored map
//The requested resources map is not modified
void Inventory::_consume_resources(std::map<Resource, int>& requested_resources){
  for (std::map<Resource, int>::iterator it = requested_resources.begin(); it != requested_resources.end(); ++it) {
    resources_quantities[it->first] -= requested_resources[it->first];
  }
}

/////////////////////PUBLIC//////////////////////////////



//BORRAR ESTE METODO E INCLUDE, ES PARA DEBUGGEAR
#include <iostream>
void Inventory::PRINT_STORED_RESOURCES(){
  std::cout << "RECURSOS:\n";
  std::cout << "Trigo: " << resources_quantities[RESOURCE_WHEAT] << "\n";
  std::cout << "Madera: " << resources_quantities[RESOURCE_WOOD] << "\n";
  std::cout << "Carbon: " << resources_quantities[RESOURCE_COAL] << "\n";
  std::cout << "Hierro: " << resources_quantities[RESOURCE_IRON] << "\n";
  std::cout << "\n\n";
}







//CAMBIAR TODOS LOS MAPS POR UNORDERED_MAPS
bool Inventory::consume_resources(std::map<Resource, int>& requested_resources){
  std::unique_lock<std::mutex> lk(m);
  /*
  bool are_resources_available = false;
  while (!are_resources_available) {
    //The spurious wakeups won't modify the program execution because the
    //output of _are_resources_available can only change if a resource
    //is added, and each resource adition calls cv.notifyall()
    cv.wait(lk);
    are_resources_available = _are_resources_available(requested_resources);
  }
  */
  while (!_are_resources_available(requested_resources)) {
    if (is_entrance_closed) {
      return false;
    }
    //The spurious wakeups won't modify the program execution because the
    //output of _are_resources_available can only change if a resource
    //is added, and each resource adition calls cv.notifyall()
    cv.wait(lk);
  }
  _consume_resources(requested_resources);
  return true;
}


//BORRAR INCLUDE
#include <iostream>

void Inventory::add_resource(Resource resource){
  std::lock_guard<std::mutex> lk(m);
  resources_quantities[resource]++;

  //BORRAR PRINT
  std::cout << "Hay " << resources_quantities[resource] << " " << char(resource) << "\n";

  cv.notify_all();
}

void Inventory::close_entrance(){
  std::lock_guard<std::mutex> lk(m);
  is_entrance_closed = true;
  cv.notify_all();
}

Inventory::Inventory(){
  //VER SI SE CAMBIA ESTE VECTOR Y SE INICIALIZA CADA UNO EN UNA LINEA DISTINTA
  std::vector<Resource> resources = {RESOURCE_WHEAT, RESOURCE_WOOD, RESOURCE_COAL,
                                RESOURCE_IRON};
  for (size_t i = 0; i < resources.size(); i++) {
      resources_quantities.insert(std::pair<Resource, int>(resources[i],
                                              RESOURCES_INITIAL_QUANTITY));
  }
  is_entrance_closed = false;
}

Inventory::~Inventory(){
}
