#include <string>
#include <stdint.h>
#include <stdio.h>

#define ALPHALEN 255
#define NUMPOS 20

using namespace std;

struct Node
{
    char c;
    int pos[NUMPOS];
    int curPos;
    Node * branch[ALPHALEN];
    int numBranches;

    Node(char ch)
    : c(ch), curPos(0), numBranches(0)
    {
	for(int i = 0; i < ALPHALEN; ++i)
	    branch[i] = nullptr;
    }

    int getBranchPos(string s, int * pos, int * numPos)
    {
	uint8_t c = s[0];
	printf("entering node %c looking for %c\n", this->c, c);
        if(s.length() != 0)
	{
	  if(branch[c] == nullptr)
	    *numPos = 0;
	  else
	    branch[c]->getBranchPos(s.substr(1), pos, numPos); 
	}
	else
	{
          *numPos = curPos;
          for(int i = 0; i < curPos; ++i)
	    pos[i] = this->pos[i];	  
	}

	return 0;
    }

    int addBranch(string s, int pos)
    {
      if (s.length() != 0)
      {
        uint8_t c = s[0];
	if (branch[c] == nullptr)
	{
	  branch[c] = new Node(c);
	  numBranches++;
	}
        branch[c]->addBranch(s.substr(1), pos);	  
      }
      else
      {
        if(curPos < NUMPOS)
	  this->pos[curPos++] = pos;	
      } 
      
      return 0;
    }

    // find child of last node with >= 2 branches off and delete
    int removeBranch(string s);
    bool hasBranch(string s)
    {
	if (s.length() == 0)
	  return true;
	int firstChar = s[0];
        return branch[firstChar] != nullptr && branch[firstChar]->hasBranch(s.substr(1));
    }
    int print()
    {
      printf("node char: %c\n", c);
      return 0;
    }
    void addCharToLeaves(char ch, int pos)
    {
	  bool hasBranch = false;
	  for(int i = 0; i < ALPHALEN; ++i)
	  {
	    if(branch[i] != nullptr)
	    {
	      branch[i]->addCharToLeaves(ch,pos);
	      hasBranch = true;
            } 
	  }
	  if(!hasBranch)
          {
	      string str = "";
	      str += ch;
	      addBranch(str, pos);
	  }
    }
    void preOrderTraversal()
    {
	  print();
	  for(int i = 0; i < ALPHALEN; ++i)
	  {
	      if(branch[i] != nullptr)
	        branch[i]->preOrderTraversal();
	  }
    }
    void deleteNodeWithChildren()
    {
        for(int i = 0; i < ALPHALEN; ++i)
	{
	    if(branch[i] != NULL)
	      branch[i]->deleteNodeWithChildren();
	}
	delete this;
    }
};

class Trie
{
  public:
    Trie()
    {
        root = new Node(0);
    }
    ~Trie()
    {
       root->deleteNodeWithChildren();
    }
    int insert(string s, int pos)
    {
       root->addBranch(s, pos); 
       return 0;
    }
    bool hasString(string s)
    {
        return root->hasBranch(s);
    }
    int remove(string s);
    int getPos(string s, int * pos, int *numPos)
    {
       root->getBranchPos(s,pos,numPos); 
       return 0;
    }
    int findLongestSubstring(string s, string substr, int pos);
    void preOrderTrav()
    {
	printf("preOrderTraversal called \n");
        root->preOrderTraversal();
    }
    int addCharToAllLeaves(char c)
    {
        root->addCharToLeaves(c, 0);
	return 0;
    }
  
  private:
    Node * root;
};
