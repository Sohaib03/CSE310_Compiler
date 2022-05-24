#include "SymbolInfo.cpp"
#include <vector>
#include <string>
#include <iostream>
using namespace std;

class ScopeTable
{
private:
    int total_buckets, child_count;
    string id;
    vector< SymbolInfo* > hashTable;
    ScopeTable* parent;

public:
    ScopeTable(int n);
    ~ScopeTable();

    unsigned long long hash(string s);
    static unsigned long long sdbm(string s);
    void setParent(ScopeTable* parent);
    ScopeTable* getParent();
    void setId(string id);
    bool insert(string name, string type);
    SymbolInfo* lookUp(string name);
    bool delete_key(string name);
    void print();
};

ScopeTable::ScopeTable(int n)
{
    this->total_buckets = n;
    hashTable.assign(total_buckets, nullptr);
    child_count = 0;
}

ScopeTable::~ScopeTable()
{
    delete parent;
    for (int i=0; i<total_buckets; i++) {
        if (hashTable[i] != nullptr) delete hashTable[i];
    }
}

bool ScopeTable::insert(string name, string type) {
    SymbolInfo* sym_info = lookUp(name);
    if (sym_info != nullptr) return false;

    unsigned long long hash_value = hash(name);

    if (hashTable[hash_value] == nullptr) {
        hashTable[hash_value] = new SymbolInfo(name, type);
    } else {
        SymbolInfo* sym_cur = hashTable[hash_value];
        while(sym_cur->getNext() != nullptr) {
            sym_cur = sym_cur->getNext();
        }
        sym_cur->createNext(name, type);
    }

    return true;
}

SymbolInfo* ScopeTable::lookUp(string name) {
    unsigned long long hash_value = hash(name);

    SymbolInfo* sym_info = hashTable[hash_value];

    while(sym_info != nullptr) {
        if (sym_info->getName() == name) break;
        sym_info = sym_info->getNext();
    }

    return sym_info;
}

bool ScopeTable::delete_key(string name) {

    unsigned long long hash_value = hash(name);
    SymbolInfo* sym_info = hashTable[hash_value];

    if (sym_info == nullptr) return false;
    else if (sym_info->getName() == name) {
        hashTable[hash_value] = sym_info->getNext();
        sym_info->setNext(nullptr);
        delete sym_info;

        return true;
    } else {

        while(sym_info->getNext() != nullptr and sym_info->getNext()->getName() != name) {
            sym_info = sym_info->getNext();
        }
        if (sym_info->getNext() == nullptr) return false;
        else {
            SymbolInfo* to_be_deleted = sym_info->getNext();
            sym_info->setNext(to_be_deleted->getNext());
            to_be_deleted->setNext(nullptr);
            delete to_be_deleted;
            return true;
        }
    }

}

void ScopeTable::print() {
    cout << "ScopeTable # "  << id << endl;
    for (int i=0; i<total_buckets; i++) {
        cout << i << " --> ";

        SymbolInfo* sym_info = hashTable[i];
        while(sym_info != nullptr) {
            cout << "< " << sym_info->getName() << " : " << sym_info->getType() << " > ";
            sym_info = sym_info->getNext();
        }
        cout << endl;
    }
}


void ScopeTable::setParent(ScopeTable* parent) {
    this->id = parent->id + "." + to_string(parent->child_count);
    this->parent = parent;
}

void ScopeTable::setId(string id)  {
    this->id = id;
}

unsigned long long ScopeTable::hash(string str) {
    return sdbm(str) % total_buckets;
}

unsigned long long ScopeTable::sdbm(string str) {
    unsigned long long hash = 0;
    for (char c: str) {
        hash = c + (hash << 6) + (hash << 16) - hash;
    }
    return hash;
}

