#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<unordered_map>
#include<sstream>
#include<limits>
#pragma once
using namespace std;

struct Node{
    char var;
    Node* high;
    Node* low;
    Node(char v, Node* h, Node* l) : var(v), high(h), low(l){};
    bool operator==(const Node& n) const {
        return (var == n.var && high == (n.high) && low == (n.low));
    }
};

class BDD{
private:
    vector<Node*> points;
    string equations;
    vector<string> ordering;
    Node* v0;
    Node* v1;
    int node_count;
    bool one = false;
    bool zero = false;
public:
    BDD(string& eq, vector<string> ord): equations(eq), ordering(ord){
        v0 = new Node('0',nullptr, nullptr);
        v1 = new Node('1',nullptr, nullptr);
        node_count = 0;
    };
    Node* CreateNode(const char var, Node* low, Node* high);
    Node* BDD_Build(const string &equation, const string &ordering, int idx, int iteration);
    Node* old_or_new(char var, Node *high, Node *low);
    Node* get_v0();
    Node* get_v1();
    int process();
};










