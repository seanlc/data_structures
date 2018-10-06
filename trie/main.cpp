#include <stdio.h>
#include <iostream>
#include "Trie.h"

using namespace std;

void testConstrDestr()
{
  Trie myT;
}

void testInsert()
{
  Trie myT;
  myT.insert("test", 0);
  myT.insert("tets", 0);
}

void testGet()
{
  int posArr[20];
  int numPos = -1;
  Trie myT;
  myT.insert("string",7);
  myT.insert("sean",6);
  myT.getPos("strings",posArr, &numPos);
  printf("numPos is %d\n", numPos);
  for(int i = 0; i < numPos; ++i)
    printf("pos: %d\n", posArr[i]);
}

void testPreOrder()
{
  Trie myT;
  myT.insert("alligator", 0);
  myT.insert("almanac", 1);
  myT.preOrderTrav();
}

void testAddToLeaves()
{
  Trie myT;
  char x = 'x';
  myT.insert("salad",0);
  myT.insert("steak",1);
  myT.insert("manga",2);  
  myT.preOrderTrav();
  myT.addCharToAllLeaves(x);
  myT.preOrderTrav();
}

void testHasString()
{
  Trie myT;
  string str = "test";
  myT.insert("Rocklin", 0);
  myT.insert("California", 1);
  myT.insert("Sac", 2);

  cout << "string in tree: " << myT.hasString("Sac") << endl;
  cout << "string not in tree: " << myT.hasString(str) << endl;
}

int main()
{
//  testConstrDestr();
//  testInsert();
//  testGet();
//  testPreOrder();
//  testAddToLeaves();
  testHasString();
  return 0;
}
