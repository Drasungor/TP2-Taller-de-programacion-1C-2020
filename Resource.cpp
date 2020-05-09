#include "CollectorsAndProducers.h"

Resource::Resource(){
}

Resource(char resource_indicator){
  indicator = resource_indicator;
}

Resource::~Resource(){
}

char Resource::get_resource_indicator(){
  return indicator;
}
