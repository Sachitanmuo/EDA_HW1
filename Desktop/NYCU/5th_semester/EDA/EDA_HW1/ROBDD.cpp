#include<ROBDD.h>

Node* BDD::CreateNode(const char var, Node* low, Node* high){
    Node* node = new Node(var, low, high);
    return node;
}

Node* BDD::BDD_Build(const string &equation, const string &ordering, int idx, int iteraion){
    //initialize variables
    Node *high, *low;
    char variable = ordering[idx++];
    char complement = isupper(variable)? tolower(variable):toupper(variable);
    //Terminal case:
    if(idx >= ordering.size()) return nullptr;
    if(equation == "1") return get_v1();
    if(equation == "0") return get_v0();


    //tokenize the equation
    vector<string> tokens;
    string token, temp;
    stringstream ss(equation);
    while(getline(ss, token, '+'))
        tokens.push_back(token);

    string phi = "", phi_bar = "";
    for(i = 0; i < tokens.size() ; i++){
        for(int j = 0; j < tokens[i].size();j++){
            if(tokens[i][j] == complement){
                temp = tokens[i];
                phi_bar +=(temp.erase(j) + "+");
            }
    
            else if(tokens[i][j] == variable){
                temp = tokens[i];
                phi += (temp.erase(j) + "+");
            }
            else{
                phi += (tokens[i] + "+");
                phi_bar += (tokens[i]+ "+");
            }
        }
    }
    //erase the "+" in the end
    phi.erase(phi.size()-1);
    phi_bar.erase(phi.size()-1);

    if(phi == "") phi ="0";
    if(phi_bar == "") phi_bar = "0";

    high = BDD_Build(phi, ordering, idx, iteration+1);
    low = BDD_Build(phi_bar, ordering, idx, iteration+1);
    if(high->var == low->var && high->high == low->high && high->low == low->low){
        return high;
    }
    else{
        return old_or_new(var, high, low);
    }
    
}

Node* BDD::old_or_new(char var, Node *a, Node *b){
    if(variables.find(var) != variables.end()){
        return variables[i];
    }
    else{
        Node* x = new Node(var, a, b);
        variables[var] = x;
        return x;
    }

}

Node* BDD::get_v0(){
    return v0;
}
Node* BDD::get_v1(){
    return v1;
}

void BDD::add(char var, Node* node){
    variables[var] = node;
}
// 递归函数：构建BDD
    Node* buildBDDRec(const string& equation, const string& ordering, size_t& idx) {
        if (idx >= ordering.size()) return nullptr;

        char var = ordering[idx++];
        Node* low = nullptr;
        Node* high = nullptr;
        char complement = isupper(var) ? tolower(var) : toupper(var);

        // 查找变量在方程中是否存在
        size_t pos = equation.find(var);
        if (pos != string::npos) {
            // 如果存在，则创建对应的低分支
            low = createNode(complement, nullptr, nullptr);
        }

        // 查找变量的补是否在方程中存在
        pos = equation.find(complement);
        if (pos != string::npos) {
            // 如果存在，则创建对应的高分支
            high = createNode(var, nullptr, nullptr);
        }

        // 创建当前变量节点
        Node* current = createNode(var, low, high);
        variables[var] = current;

        // 递归构建下一个变量节点
        current->low = buildBDDRec(equation, ordering, idx);
        current->high = buildBDDRec(equation, ordering, idx);

        return current;
    }

