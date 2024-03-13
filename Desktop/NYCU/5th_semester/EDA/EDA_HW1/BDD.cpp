#include"BDD.h"

Node* BDD::CreateNode(const char var, Node* low, Node* high){
    Node* node = new Node(var, low, high);
    return node;
}

Node* BDD::BDD_Build(const string &equation, const string &ordering, int idx, int iteration){
    //initialize variables
    Node *high, *low;
    char variable = ordering[idx++];
    char complement = isupper(variable)? tolower(variable):toupper(variable);
    bool exist = false;
    //Terminal case:
    if(equation == "1") {std::cout << "v1" <<endl; return get_v1(); }
    if(equation == "0") {std::cout << "v0" <<endl; return get_v0(); }
    for(int i = 0; i < equations.size() ; i++){
        if(equations[i] == variable || equations[i] == complement) exist = true;
    }
    if(!exist) return BDD_Build(equation, ordering, idx, iteration + 1);
    //tokenize the equation
    vector<string> tokens;
    string token, temp;
    stringstream ss(equation);
    while(getline(ss, token, '+'))
        tokens.push_back(token);

    string phi = "", phi_bar = "";
    //if the token has only one character and it's equal to variable
    bool phi_one = false, phi_bar_one = false;
        
    for(int i = 0; i < tokens.size() ; i++){
        bool hasVariable = false, hasComplement = false;
        for(int j = 0; j < tokens[i].size(); j++){
            if(tokens[i][j] == complement){
                hasComplement = true;
                if(tokens[i].size() == 1) phi_bar_one = true;
                temp = tokens[i].erase(j, 1);
            }
            if(tokens[i][j] == variable){
                hasVariable = true;
                if(tokens[i].size() == 1) phi_one = true;
                temp = tokens[i].erase(j, 1);
            } 
        }
        if(!hasVariable && ! hasComplement){
            phi += tokens[i] + "+";
            phi_bar += tokens[i] + "+";
        }
        else if(!hasVariable) phi_bar += temp + "+";
        else if(!hasComplement) phi += temp + "+";
    }
    //erase the "+" at the end
    if(!phi.empty()) phi.erase(phi.size()-1);
    if(!phi_bar.empty()) phi_bar.erase(phi_bar.size()-1);
    if(phi_one) phi = "1";
    if(phi_bar_one) phi_bar = "0";
    if(phi.empty()) phi ="1";
    if(phi_bar.empty()) phi_bar = "0";
    if(phi[0] == '+') phi.erase(0,1);
    if(phi_bar[0] == '+') phi_bar.erase(0,1);
    std::cout << "high: BDD_Build( " << phi     << ", " << variable << ", " << idx << ", " << iteration + 1 << " )" << endl;
    high = BDD_Build(phi, ordering, idx, iteration+1);
    std::cout << "low: BDD_Build( " << phi_bar << ", " << variable << ", " << idx << ", " << iteration + 1 << " )" << endl;
    low = BDD_Build(phi_bar, ordering, idx, iteration+1);
    if(*high == *low){
        std::cout << "high == low" << endl;
        return high;
    }
    else{
        std::cout << "check old or new:" << endl;
        return old_or_new(variable, high, low);
    }
    
}

Node* BDD::old_or_new(char var, Node *high, Node *low){
    for(int i = 0; i < points.size(); i++){
        if(var == points[i]->var && *high == *(points[i]->high) && *low == *(points[i]->low)){
            cout << "The point " << var << " already exists.";
            return points[i];
        }
    }
    //if not exist
    std::cout << var << " is not in the list, create a new node." << endl;
    std::cout << "New node" << "( " << var << ", " << high->var << ", " << low->var << " )" <<endl;  
    Node* x = new Node(var, high, low);
    points.push_back(x);
    node_count++;
    return x;
}

Node* BDD::get_v0(){
    return v0;
}
Node* BDD::get_v1(){
    return v1;
}


int BDD::process(){
    vector<Node*> list;
    vector<int> node_counts;
    int min = INT_MAX;
    int max = INT_MIN;
    for(int i = 0 ; i < ordering.size() ; i++){
        node_count = 2; //including v0 and v1
        points.clear();
        BDD_Build(equations, ordering[i], 0, 1);
        node_counts.push_back(node_count);
        if(node_count < min) min = node_count;
        if(node_count > max) max = node_count;
        cout << "===================================" <<endl;
    }
    std:: cout << "Max: " << max <<", Min: " << min << endl;
    return min;
}


