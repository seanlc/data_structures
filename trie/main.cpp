#include <stdio.h>
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

int main()
{
//  testConstrDestr();
//  testInsert();
  testGet();
  return 0;
}
