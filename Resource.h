#ifndef _RESOURCE_H_
#define _RESOURCE_H_


class Resource {
private:
  char indicator;
public:
  //VER SI HAY QYE BORRAR ESTE CONSTRUCTOR Y HACER UNO QUE RECIBA OTRO RESOURCE
  Resource();

  Resource(char resource_indicator);

  ~Resource();

  char get_resource_indicator();
};

#endif
