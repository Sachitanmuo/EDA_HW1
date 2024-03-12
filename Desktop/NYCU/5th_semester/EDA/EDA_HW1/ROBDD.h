#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<unordered_map>

using namespace std;

struct Node{
char var;
Node* high;
Node* low;
Node(char v, Node* l, Node* h) : var(v), low(l), high(h);
};


class ROBDD{
private:
    Node* root;
    unordered_map<char, Node> variables;
    vector<Node*> points;
public:
    Node* CreateNode(const char var, Node* low, Node* high);
};







Node* old_or_new(string &equation, Node *a, Node *b){


}

Node* ROBDD::CreateNode(const char var, Node* low, Node* high){
    Node* node = new Node(var, low, high);
    return node;
}

Node* ROBDD_Build(const string &equation, const string &ordering, int idx){
    if(idx >= ordering.size()) return nullptr;
    Node *high, *low;
    char var = ordering[idx++];
    int pos = equation.find(var);
    if(pos)

}