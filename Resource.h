#ifndef _RESOURCES_H_
#define _RESOURCES_H_

//The invalid resource is used only to check de received resources, it will
//never be part of the ResourcesProcessor logic
enum Resource:char {
  RESOURCE_WHEAT = 'T',
  RESOURCE_WOOD = 'M',
  RESOURCE_IRON = 'H',
  RESOURCE_COAL = 'C',
  RESOURCE_INVALID = -1
};

#endif
