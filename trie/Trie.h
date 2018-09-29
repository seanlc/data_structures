#include <string>

#define ALPHALEN 255
#define NUMPOS 20

using namespace std;

struct Node
{
    char c;
    int pos[20];
    int curPos;
    Node * branch[ALPHALEN];
    Node()
    {
        curPos = 0;
	for(int i = 0; i < ALPHALEN; ++i)
	    branch[i] = nullptr;
    }
    void getBranchPos(string s);
    int addBranch(string s, int pos)
    {
      if (s.length() != 0)
      {
        int c = s[0];
	if (branch[c] == nullptr)
	  branch[c] = new Node();

        branch[c]->addBranch(s.substr(1), pos);	  
      }
      else
      {
        if(curPos < NUMPOS)
	  this->pos[curPos] = pos;	
      } 
      
      return 0;
    }
    int removeBranch(char c);
};

class Trie
{
  public:
    Trie()
    {
        root = new Node();
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
    int getPos(string s);
    int print();
  
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
