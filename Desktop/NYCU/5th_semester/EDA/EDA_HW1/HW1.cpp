#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<fstream>
using namespace std;

int main(int argc, char* argv[]){
    string inputfile = argv[1];
    string outputfile = argv[2];
    ifstream input(inputfile);
    ofstream output(outputfile);
    string expression,temp;
    vector<string> ordering;
    getline(input, expression);
    while(!input.eof()){
        getline(input, temp);
        ordering.push_back(temp);
    }

    cout << expression << endl;
    
    cout << "ordering: " << endl;
    for(int i = 0 ; i < ordering.size() ; i++)
        cout << ordering[i] << endl;

}