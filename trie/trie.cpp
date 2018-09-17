#include <string>

#define ALPHALEN 26

using namespace std;

struct Node
{
    char c;
    int key;
    Node * branch[ALPHALEN];
    Node * getBranch(char c);
    int addBranch(char c, Node * n);
    int removeBranch(char c);
};

class Trie
{
    Trie();
    ~Trie();
    int insert(string s);
    int remove(string s);
    bool isMember(string s);
    int print();
};
