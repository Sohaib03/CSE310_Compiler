#include<string>
#include<iostream>
#include "ScopeTable.cpp"

using namespace std;

class SymbolTable
{
private:
    ScopeTable* cur_scp_table;
    int total_buckets;
public:
    SymbolTable(int n);
    ~SymbolTable();

    void enterScope();
    void exitScope();
    void insert(string name, string type);
    void remove(string name);
    SymbolInfo* lookUp(string name);
    void printCurScopeTable();
    void printAllScopeTable();
};

SymbolTable::SymbolTable(int n)
{
    this->total_buckets = n;
    cur_scp_table = new ScopeTable(total_buckets);
    cur_scp_table->setId("1");
}

SymbolTable::~SymbolTable()
{
    delete cur_scp_table;
}

void SymbolTable::insert(string name, string type) {

}

void SymbolTable::enterScope() {
    ScopeTable* scp_table = new ScopeTable(total_buckets);
    scp_table->setParent(cur_scp_table);
    cur_scp_table = scp_table;
}

void SymbolTable::exitScope() {
    if (cur_scp_table == nullptr) {
        return;
    }
    ScopeTable* next_scp_table = cur_scp_table->getParent();
    cur_scp_table->setParent(nullptr);
    delete cur_scp_table;

    cur_scp_table = next_scp_table;
}

void SymbolTable::remove(string name) {

}