#include<iostream>
#include<string>
#include "SymbolTable.cpp"

using namespace std;

int main() {
    freopen("input.txt", "r", stdin);
    int n; cin >> n;
    SymbolTable st(n);

    char cmd;
    while(cin >> cmd) {

        if (cmd == 'I') {
            string name, type;
            cin >> name >> type;            
            st.insert(name, type);
        } 
        else if (cmd == 'L') {
            string name; cin >> name;
            SymbolInfo* sym_info = st.lookUp(name);
        } 
        else if (cmd == 'D') {
            string name; cin >> name;
            st.remove(name);
        } 
        else if (cmd == 'P') {
            char type; cin >> type;
            if (type == 'A') {
                st.printAllScopeTable();
            } else {
                st.printCurScopeTable();
            }
        } 
        else if (cmd == 'S') {
            st.enterScope();
        } 
        else if (cmd == 'E') {
            st.exitScope();
        } 
        cout << endl;
    }

}