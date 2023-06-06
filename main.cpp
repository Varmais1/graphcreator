#include <iostream>
#include <cstring>
#include <vector>
#include "vertex.h"
#include "edge.h"

using namespace std;

void singlelowercase(char sentence[]);
void swap(vertex* all[], vertex* first, vertex* second);
void swap(edge* all[], edge* first, edge* second);

int main() {
  vector<vertex*> graph;
  int size = 0;
  char command[15];
  while(true) {
    cout << "Type add, delete, shortest, or quit.";
    cin >> command;
    singlelowercase(command);
    if(strcmp(command, "quit") == 0) {
      break;
    }
    if(strcmp(command, "add") == 0) {
      cout << "Would you like to add a vertex, or and edge?" << endl;
      cin >> command;
      if(strcmp(command, "vertex") == 0) {
	if(size >= 20) {
	  cout << "The maximum amount of vertices has been reached. Please delete a vertex before adding another one.";
	}
	else {
	  char label;
	  cout << "What letter would you like to be the label?" << endl;
	  cin >> label;
	  graph.push(new vertex(label));
	  size++;
	}
      }
      else if(strcmp(command, "edge") == 0) {
	if(size < 2) {
	  cout << "There are not enough vertices to make an edge. Please add one before attempting to make an edge." << endl;
	}
	else {
	  vertex* first;
	  vertex* second;
	  int weight = 0;
	  char label[5];
	  bool valid = false;
	  while(!valid) {
	    cout << "Please enter the label of the first vertex of the edge. You can quit out of here with \"quit\" " << endl;
	    cin >> label;
	    if(strcmp(label, "quit") == 0) {
	      break;
	    }
	    for(auto i = graph.begin(); i !=graph.end(); i++) {
	      if(*i->id == label[0]) {
		first = *i;
		valid = true;
	      }
	    }
	  }
	  valid = false;
	  while(!valid) {
	    cout << "Please enter the label of the second vertex of the edge. You can quit out of here with \"quit.\" " << endl;
	    cin >> label;
	    if(strcmp(label, "quit") == 0) {
	      break;
	    }
	    for(auto i = graph.begin(); i != graph.end(); i++) {
	      if(*i->id == label[0]) {
		second = *i;
		valid = true;
	      }
	    }
	  }
	  cout << "Give the weight of this edge." << endl;
	  cin >> weight;
	  if(first != NULL && second != NULL) {
	    edge* temp = new edge(first, second, weight);
	    first->all[first->size++] = temp;
	    second->all[second->size++] = temp;
	  }
	}
      }
    }
    else if(strcmp(command, "delete") == 0) {

    }
  }
  return 0;
}

void singlelowercase(char sentence[]) {
  //iterating variable
   int i = 0;
   //go through the char array
   while(true) {
     int charVal = (int) sentence[i];
     //if the letter is capital, make it lowercase using ASCII
     if(65<=charVal && charVal <= 90) {
       sentence[i] = (char)(charVal+32);
     }
     //if the character is the null character, 
     else if(sentence[i] == '\0') {
       break;
     }
     //increment the variable
     i++;
   }
   
   
}

void swap(edge* all[], edge* first, edge* second) {
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

void swap(vertex* all[], vertex* first, vertex* second) {
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
