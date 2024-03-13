#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<fstream>
#include"BDD.h"
#include"BDD.cpp"
using namespace std;

int main(int argc, char* argv[]){
    string inputfile = argv[1];
    string outputfile = argv[2];
    ifstream input(inputfile);
    ofstream output(outputfile);
    string expression,temp;
    vector<string> ordering;
    getline(input, expression);
    expression.pop_back();
    while(getline(input, temp)){
        temp.pop_back();
        ordering.push_back(temp);
    }

    Node* a = new Node('x', NULL, NULL);
    Node* b = new Node('x', NULL, NULL);
    cout << "The two nodes are the same." << (*a == *b) << endl;

    cout << expression << endl;
    
    cout << "ordering: " << endl;
    for(int i = 0 ; i < ordering.size() ; i++)
        cout << ordering[i] << endl;

    //Initialize BDD
    BDD bdd(expression, ordering);
    int minimum = bdd.process();
    cout << minimum << endl;
    output << minimum << endl;
}