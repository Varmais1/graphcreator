#include "vertex.h"
/* Name: Ishaan Varma
   Date: 6/9/2023
   Purpose: where the vertex class is implemented
 */

void swap1(edge* all[], edge* first, edge* second);
void swap1(vertex* all[], vertex* first, vertex* second);

vertex::vertex(char nid) {
  id = nid;
  size = 0;
  for(int i = 0; i < 20; i++) {
    all[i] = NULL;
  }
}

vertex::~vertex() {
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
