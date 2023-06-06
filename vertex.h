
#include <iostream>
#include <cstring>
#include "edge.h"


class vertex {
 public:
  vertex(char nid);
  ~vertex();
  char id;
  class edge* all[20];
  int size;
};
