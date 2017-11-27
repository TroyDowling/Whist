#include <iostream>
using namespace std;



struct node
{
  const char*contents;
  node*last;
  node*next;
};

/*
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
*/
//This code sucks ass and I'll fix it later.
//The point:
//recurse moves through a linked list until it finds a node whose contents match array c
//after which it deletes the subject node, repairs the array, and returns the whole thing.

bool stringEqual(const char * subject, const char * test)
{

  return false;
}

node recurse (node cur, char * c)
{
  int i = 0;
  cout << cur.contents <<" "<< c << endl;
  while ( c[i] == cur.contents[i] ){ ++i;}
  if ( )
    {
      //this node's contents do not match
      return recurse(*cur.next, c);
    }
  else
    {
      //this node's contents match
      cout << "Match found" << endl;
      cur.last->next = cur.next;
      return cur;
    }
}

//This probably doesn't work
int main()
{
  node * Nodes[5];
  const char * fruits[5] = {"apple", "pear", "orange", "banana", "plum"};
  for(int i = 0; i < 5; ++i){
    Nodes[i] = new node;
    Nodes[i]->contents = fruits[i];
  }
  for(int i = 0; i < 4; ++i){
    Nodes[i]->next = &*Nodes[i + 1];
  }
  Nodes[4]->next = NULL;
  Nodes[0]->last = NULL;
  for(int i = 1; i < 4; ++i){
    Nodes[i]->last = &*Nodes[i - 1];
  }
  node newnode = recurse(*Nodes[0],"orange");
  cout << "Found a match: " << newnode.contents << endl;
  return 0;
}
