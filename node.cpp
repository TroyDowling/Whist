#include <iostream>
using namespace std;

struct node
{
  const char*contents;
  node*last;
  node*next;
};

<<<<<<< HEAD

=======
>>>>>>> baabd0c5d56b2145f2f05b29605230409e720be8
bool stringEqual(const char * subject, const char * test)
{
  int i = 0, len = 0;
  while(test[len] != '\0') ++len;
  while(test[i] == subject[i] && test[i] != '\0') ++i;
  if (len == i) return true;
  else return false;
}


node recurse (node cur, const char * c)
{
  int i = 0;
<<<<<<< HEAD
  cout << cur.contents <<" "<< c << endl;
  //cout << stringEqual(c,cur.contents) <<endl;
=======
>>>>>>> baabd0c5d56b2145f2f05b29605230409e720be8
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

<<<<<<< HEAD

=======
>>>>>>> baabd0c5d56b2145f2f05b29605230409e720be8
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
