#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<unordered_map>
#include<<sstream>
using namespace std;

struct Node{
char var;
Node* high;
Node* low;
Node(char v, Node* l, Node* h) : var(v), low(l), high(h);
};


class BDD{
private:
    Node* root;
    unordered_map<char, Node*> variables;
    vector<Node*> points;
    string equations;
    vector<string> ordering;
    Node v0 = Node('0',nullptr, nullptr);
    Node v1 = Node('1',nullptr, nullptr);
public:
    BDD(string& eq, vector<string> ord): equations(eq), ordering(ord){};
    Node* CreateNode(const char var, Node* low, Node* high);
    Node* BDD_Build(const string &equation, const string &ordering, int idx, int iteration);
    Node* old_or_new(char var, Node *a, Node *b);
    Node* get_v0();
    Node* get_v1();
    void add(char, Node*);
};









