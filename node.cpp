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

//
bool stringEqual(const char * subject, const char * test)
{
  int i = 0, len = 0;
  while(test[len] != '\0') ++len;
  while(test[i] == subject[i] && test[i] != '\0') ++i;
  if (len == i) return true;
  else return false;
}

node recurse (node cur, char * c)
{
  int i = 0;
  //cout << cur.contents <<" "<< c << endl;
  while ( c[i] == cur.contents[i] ){ ++i;}
  cout << stringEqual(c,cur.contents) <<endl;
  if ( stringEqual(c,cur.contents) )
  {
	//this node's contents match
    cout << "Match found" << endl;
    cur.last->next = cur.next;
    return cur;	
  }
  else
  {
    //this node's contents do not match
	if (cur.next != NULL)
	  return recurse(*cur.next, c);
    else return *cur.last;
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
