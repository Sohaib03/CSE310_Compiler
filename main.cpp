#include<iostream>
#include<string>
#include "ScopeTable.cpp"

using namespace std;

int main() {
    ScopeTable st(6);
    st.setId("1");

    st.insert("hello", "NUMBER");
    st.insert("world", "NUMBER");
    st.insert("copy", "FUNCTION");
    st.insert("<" , "RELOP");
    st.insert("<=" , "RELOP");
    st.insert(">" , "RELOP");
    st.insert(">=" , "RELOP");

    st.print();

    cout << st.lookUp("hello")->getType() << endl;
}