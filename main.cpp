#include <iostream>
#include <cstring>
#include <vector>
#include <climits>
#include "vertex.h"
#include "edge.h"
/* Name: Ishaan Varma
   Date: 6/9/2023
   Purpose: Where the graph creator program is run
 */

using namespace std;

struct path {
  vertex* destination;
  vertex* last;
  int dist;
};

//prototypes
void singlelowercase(char sentence[]);
void swap(vertex* all[], vertex* first, vertex* second);
void swap(edge* all[], edge* first, edge* second);
void shortest(vertex* start, vector<vertex*> graph);
void pathfind(path* start, vector<path*> visited, vector<path*> unvisited);

//main
int main() {
  //for testing purposes
  //cout << "done." << endl;
  //stores the vertices
  vector<vertex*> graph;
  //stores the user's gommand
  char command[15];
  //runs the program
  while(true) {
    //gets input
    cout << "Type add, delete, print, shortest, or quit." << endl;
    cin >> command;
    singlelowercase(command);
    //get out of the program if quit
    if(strcmp(command, "quit") == 0) {
      break;
    }
    //adds a vertex of edge
    if(strcmp(command, "add") == 0) {
      //gets if the user wants to input a vertex or edge
      cout << "Would you like to add a vertex, or and edge?" << endl;
      cin >> command;
      //if the user wants to add a vertex
      if(strcmp(command, "vertex") == 0) {
	//if the size isn't too great
	if(graph.size() >= 20) {
	  cout << "The maximum amount of vertices has been reached. Please delete a vertex before adding another one.";
	}
	//add the node by making a new vector with the desired label and adding it to the graph
	else {
	  char label;
	  cout << "What letter would you like to be the label?" << endl;
	  cin >> label;
	  graph.push_back(new vertex(label));
	}
      }
      //If the user wants to add an edge, and there are enough vertices to add an edge, then add an edge (See line 61 for more details)
      else if(strcmp(command, "edge") == 0) {
	if(graph.size() < 2) {
	  cout << "There are not enough vertices to make an edge. Please add one before attempting to make an edge." << endl;
	}
	//get the two vertices that the edge connects while giving the user a chance to reenter input if they entered invalid input, give the edge a weight, and add it to the two vertices' arrays of edges
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
	    //keeps track of proper size since the size is the index of the first NULL space in the array, so the increment should happen after the edge is added
	    first->all[first->size++] = temp;
	    second->all[second->size++] = temp;
	  }
	}
      }
    }
    //If the user wants to delete something, first see if the user would like to delete a Vertex or an edge
    else if(strcmp(command, "delete") == 0) {
      //cout << "Vector size before deleting: " << graph.size() << endl;
      cout << "Would you like to delete an edge, or an entire vertex?" << endl;
      char type[10];
      cin >> type;
      //if the user wants to delete a vertex, then get the vertex's id and delete all edges within the vertex's array of edges, then delete the vertex and remove it from the vector of all verticies.
      if(strcmp(type, "vertex") == 0) {
	char label;
	cout << "Which vertex would you like to delete?" << endl;
	bool there = false;
	cin >> label;
	for(auto i = graph.begin(); i != graph.end(); i++) {
	  if((*i)->id == label) {
	    vertex* temp = *i;
	    //graph.erase(i);
	    for(int i = 0; i < graph.size(); i++) {
	      if(temp->all[i] != NULL) {
		vertex* other = temp->all[i]->otherPoint(temp);
		for(int j = 0; j < other->size; j++) {
		  if(other->all[j] = temp->all[i]) {
		    if(j != other->size - 1) {
		      swap(other->all, other->all[j], other->all[other->size-1]);
		    }
		    other->all[other->size - 1] = NULL;
		    other->size--;
		  }
		}
		delete temp->all[i];
	      }
	    }
	    
	    delete temp;
	    graph.erase(i);
	    cout << "Vector size after deleting: " << graph.size() << endl;
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
      //if the user wants to delete an edge, get the two vertices that it connects,then find those vertices, get the edge in a temporary variable, remove the edge from the two vertices' array, and delete the edge. 
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
	      first->all[first->size-1] = NULL;
	      first->size--;
	    }
	  }
	  if(exists) {
	    for(int i = 0; i< second->size; i++) {
	      if(second->all[i]->otherPoint(second) == first) {
		if(i != second->size - 1) {
		  swap(second->all, second->all[i], second->all[second->size - 1]);
		}
		second->all[second->size-1] = NULL;
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
    //prints out the graph by printing out a vertex, and then all of its edges.
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
    else if(strcmp(command, "shortest") == 0) {
      char label;
      cout << "Which vertex is the starting point? Please enter the one letter label of the vertex." << endl;
      cin >> label;
      bool exists = false;
      vertex* start;
      for(auto i = graph.begin(); i != graph.end(); i++) {
	if((*i)->id == label) {
	  exists = true;
	  start = *i;
	  break;
	}
      }
      if(exists) {
	shortest(start, graph);
      }
      else {
	cout << "Please enter a valid vertex as a starting point next time." << endl;
	continue;
      }
    }
  }
  return 0;
}

//removes all non-letter characters and makes all letters lowercase
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

//swaps two edges in an edge array
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

//swaps two vertices in a vertex array
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


//djikstra's algorithm
void shortest(vertex* start, vector<vertex*> graph) {
  vector<path*> visited;
  vector<path*> unvisited;
  for(auto i = graph.begin(); i != graph.end(); i++) {
    path* temp;
    temp->destination = *i;
    temp->last = start;
    temp->dist = 0;
  }
  path* nstart;
  for(auto i = unvisited.begin(); i < unvisited.end(); i++) {
    if((*i)->destination == start) {
      nstart->destination = start;
      nstart->last = start;
      nstart->dist = 0;
      visited.push_back(*i);
      unvisited.erase(i);
    }
  }
  pathfind(nstart, visited, unvisited);
  cout << "Vertex: \t Last: \t Distance: " << endl;
  for(auto itr = visited.begin(); itr != visited.end(); itr++) {
    cout << (*itr)->destination->id << "      \t " << (*itr)->last->id << "   " << (*itr)->dist << endl;
  }
}


void pathfind(path* start, vector<path*> visited, vector<path*> unvisited) {
  if(unvisited.size() == 0) {
    return;
  }
  vector<path*> processed;
  bool handled = false;
  for(auto i = unvisited.begin(); i != unvisited.end(); i++) {
    if(handled) {
      i--;
    }
    handled = false;
    for(int j = 0; j < start->destination->size; j++) {
      if((*i)->destination == start->destination->all[j]->otherPoint(start->destination)) {
	int newdist = start->dist + start->destination->all[j]->weight;
	if(newdist < (*i)->dist || (*i)->dist == 0) {
	  (*i)->dist = newdist;
	  (*i)->last = start->destination;
	  processed.push_back(*i);
	}
	visited.push_back(*i);
	unvisited.erase(i);
	handled = true;
      }
    }
  }
  path* lowest;
  int shortest = INT_MAX;
  for(auto i = processed.begin(); i != processed.end(); i++) {
    if((*i)->dist < shortest) {
      lowest = *i;
      shortest = (*i)->dist;
    }
  }
  pathfind(lowest, visited, unvisited);
}
