#include "vertex.h"

void swap1(edge* all[], edge* first, edge* second);
void swap1(vertex* all[], vertex* first, vertex* second);

vertex::vertex(char nid) {
  id = nid;
}

vertex::~vertex() {
  for(int i = 0; i < size; i++) {
    if(all[i] != NULL) {
      vertex* other = all[i]->otherPoint(this);
      for(int j = 0; j < other->size; j++) {
	if(other->all[j] = all[i]) {
	  if(j != other->size - 1) {
	    swap1(other->all, other->all[j], other->all[other->size-1]);
	  }
	  other->all[size - 1] = NULL;
	  other->size--;
	}
      }
      delete all[i];
    }
  }
}



void swap1(edge* all[], edge* first, edge* second) {
  int firstPos;
  int secondPos;
  for(int i = 0; i < 20; i++) {
    if(all[i] == first) {
      firstPos = i;
    }
    else if(all[i] == second) {
      secondPos = i;
    }
  }
  all[firstPos] = second;
  all[secondPos] = first;
}

void swap1(vertex* all[], vertex* first, vertex* second) {
  int firstPos;
  int secondPos;
  for(int i = 0; i < 20; i++) {
    if(all[i] == first) {
      firstPos = i;
    }
    else if(all[i] == second) {
      secondPos = i;
    }
  }
  all[firstPos] = second;
  all[secondPos] = first;

}
