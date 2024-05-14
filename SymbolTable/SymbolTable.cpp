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
    bool insert(string name, string type);
    bool remove(string name);
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
    // cout << "Destructor of Symbol Table Called" << endl;
    delete cur_scp_table;
}

bool SymbolTable::insert(string name, string type) {
    if (cur_scp_table == nullptr) return false;
    return cur_scp_table->insert(name, type);
}

void SymbolTable::enterScope() {
    ScopeTable* scp_table = new ScopeTable(total_buckets);
    scp_table->setParent(cur_scp_table);
    cout << "New ScopeTable with id " << scp_table->getId() << " created" << endl;
    cur_scp_table = scp_table;
}

void SymbolTable::exitScope() {
    if (cur_scp_table == nullptr) {
        return;
    }
    cout << "ScopeTable with id " << cur_scp_table->getId() << " removed" << endl;
    ScopeTable* next_scp_table = cur_scp_table->getParent();
    cur_scp_table->setParent(nullptr);
    delete cur_scp_table;

    cur_scp_table = next_scp_table;
}

bool SymbolTable::remove(string name) {
    if (cur_scp_table->lookUp(name) == nullptr) {
        cout << "Not Found" << endl;
        cout << name << " is not found" << endl;
        return false;
    } 
    // cout << "Found it" << endl;
    bool result = cur_scp_table->delete_key(name);
    return result;
}

SymbolInfo* SymbolTable::lookUp(string name) {
    ScopeTable* scp_table = cur_scp_table;

    while(scp_table != nullptr) {
        SymbolInfo* sym_info = scp_table->lookUp(name);
        if (sym_info != nullptr) {
            return sym_info;
        }
        scp_table = scp_table->getParent();
    }
    cout << "Not Found" << endl;
    return nullptr;
}

void SymbolTable::printCurScopeTable() {
    if (cur_scp_table == nullptr) return;
    cur_scp_table->print();
}

void SymbolTable::printAllScopeTable() {
    ScopeTable* scp_table = cur_scp_table;

    while(scp_table != nullptr) {
        scp_table->print();
        if (scp_table->getParent() == nullptr) break;
        scp_table = scp_table->getParent();
    }
}