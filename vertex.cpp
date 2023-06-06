#include "vertex.h"

vertex::vertex(char nid) {
  id = nid;
}

vertex::~vertex() {
  for(int i = 0; i < size; i++) {
    if(all[i] != NULL) {
      delete all[i];
    }
  }
}
