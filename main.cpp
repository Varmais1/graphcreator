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
  cout << "done." << endl;
  vector<vertex*> graph;
  int size = 0;
  char command[15];
  while(true) {
    cout << "Type add, delete, shortest, or quit." << endl;
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
	  graph.push_back(new vertex(label));
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
	      if((*i)->id == label[0]) {
		first = *i;
		valid = true;
	      }
	    }
	  }
	  if(!valid) {
	    continue;
	  }
	  valid = false;
	  while(!valid) {
	    cout << "Please enter the label of the second vertex of the edge. You can quit out of here with \"quit.\" " << endl;
	    cin >> label;
	    if(strcmp(label, "quit") == 0) {
	      break;
	    }
	    for(auto i = graph.begin(); i != graph.end(); i++) {
	      if((*i)->id == label[0]) {
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
      cout << "Would you like to delete an edge, or an entire vertex?" << endl;
      char type[10];
      if(strcmp(type, "vertex") == 0) {
	char label;
	cout << "Which vertex would you like to delete?" << endl;
	bool there = false;
	cin >> label;
	for(auto i = graph.begin(); i != graph.end(); i++) {
	  if((*i)->id == label) {
	    graph.erase(i);
	    there = true;
	    break;
	  }
	}
	if(there) {
	  continue;
	}
	else {
	  cout << "That vertex does not exists." << endl;
	  continue;
	}
      }
      else if(strcmp(type, "edge") == 0) {
	cout << "Which vertices does the edge connect?" << endl;
	vertex* first;
	vertex* second;
	char label1;
	char label2;
	cin >> label1;
	cin >> label2;
	bool valid1 = false;
	bool valid2 = false;
	for(auto i = graph.begin(); i != graph.end(); i++) {
	  if((*i)->id == label1) {
	    first = *i;
	    valid1 = true;
	  }
	  else if((*i)->id == label2) {
	    second = *i;
	    valid2 = true;
	  }
	}
	if(valid1 && valid2) {
	  bool exists = false;
	  edge* temp;
	  for(int i = 0; i < first->size; i++) {
	    if(first->all[i]->otherPoint(first) == second) {
	      temp = first->all[i];
	      exists = true;
	      if(i != first->size - 1) {
		swap(first->all, first->all[i], first->all[first->size-1]);
	      }
	      first->all[size-1] = NULL;
	      first->size--;
	    }
	  }
	  if(exists) {
	    for(int i = 0; i< second->size; i++) {
	      if(second->all[i]->otherPoint(second) == first) {
		if(i != second->size - 1) {
		  swap(second->all, second->all[i], second->all[second->size - 1]);
		}
		second->all[size-1] = NULL;
		second->size--;
		delete temp;
	      }
	    }
	  }
	  else {
	    cout << "These vertices don't have an edge between them." << endl;
	  }
	}
	else {
	  cout << "Please enter 2 valid vertices." << endl;
	}
      }
      else {
	cout << "Please enter a valid input of edge or vertex." << endl; 
      }
    }
    else if(strcmp(command, "print") == 0) {
      if(graph.empty()) {
	cout << "There are no vertices, please add at least one." << endl;
	continue;
      }
      for(auto i = graph.begin(); i != graph.end(); i++) {
	cout << "Vertex: " << (*i)->id << endl;
	for(int j = 0; j < (*i)->size; j++) {
	  cout << (*i)->all[j]->otherPoint(*i)->id << ": " << (*i)->all[j]->weight << "\t"; 
	}
	cout << endl;
      }
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
