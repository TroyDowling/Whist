#include <iostream>
using namespace std;

struct node{
  char*contents;
  node*next;
};

node recurse(node current, char* c){
  if(current.next == NULL){
    return n;
  }
  else{
    if(current.contents == c){
      current.next++;
      recurse(current.next, c);
    }
    else{
      rec2(current.next, c);
    }
  }
}

//This code sucks ass and I'll fix it later.
//The point:
//recurse moves through a linked list until it finds a node whose contents match array c
//after which it deletes the subject node, repairs the array, and returns the whole thing.