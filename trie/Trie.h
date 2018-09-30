#include <string>
#include <stdint.h>

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
    {
	c = ch;
        curPos = 0;
	numBranches = 0;
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
    int removeBranch(char c);
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
       deleteNode(root); 
    }
    int insert(string s, int pos)
    {
       root->addBranch(s, pos); 
       return 0;
    }
    int remove(string s);
    int getPos(string s, int * pos, int *numPos)
    {
       root->getBranchPos(s,pos,numPos); 
       return 0;
    }
    int findLongestSubstring(string s, string substr, int pos);
    int addCharToAll(char c);
  
  private:
    Node * root;
    void deleteNode(Node * nd)
    {
        for(int i = 0; i < ALPHALEN; ++i)
	{
	    if(nd->branch[i] != NULL)
	      deleteNode(nd->branch[i]);
	}
	delete nd;
    }
};
