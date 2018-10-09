#include <string>
#include <stdint.h>
#include <stdio.h>

#define ALPHALEN 255
#define NUMPOS 20

using namespace std;

struct Node
{
    uint8_t c;
    // TODO: remove pos array and just store single pos
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

    // TODO: change to return single pos and use pass by reference
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
    
    // TODO: assign pos to every node, not just end
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
    Node * removeBranch(string str)
    {
      Node * last_node = nullptr;
      if(str.length() > 0)
      {
	uint8_t curChar = str[0];
        Node * targetChild = branch[curChar];
	if(targetChild != nullptr)
        {
          last_node = targetChild->removeBranch(str.substr(1));
	  if(last_node == nullptr && 
	     numBranches > 1 && 
	     !( str.length() == 1 && targetChild->numBranches > 0))
	  {
	    last_node = this;
	  }
	}
        if (last_node == this)
        {
          uint8_t delete_char = targetChild->c;
          printf("deleting target child with char %c\n", targetChild->c);
          targetChild->deleteNodeWithChildren();
	  branch[delete_char] = nullptr;
        }
      }
      return last_node;
    }
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
	    branch[i] = nullptr;
	}
	delete this;
    }
    int findSubstring(string str, int &length, int &pos)
    {
	if(str.length() > 0)
	{
	    uint8_t currentChar = str[0];
            if(branch[currentChar] != nullptr)
	    {
	      ++length;
              pos = this->pos[0];
	      branch[currentChar]->findSubstring(str.substr(1), length, pos);
	    }
	}
	return 0;
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
    int remove(string s)
    {
	root->removeBranch(s);
	return 0;
    }
    // TODO: return single pos instead of multiple
    int getPos(string s, int * pos, int *numPos)
    {
       root->getBranchPos(s,pos,numPos); 
       return 0;
    }
    int findLongestSubstring(string s, int  &length, int &pos)
    {
        root->findSubstring(s, length, pos);
	return 0;
    }
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
