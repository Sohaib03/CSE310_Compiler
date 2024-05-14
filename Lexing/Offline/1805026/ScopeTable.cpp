#include "SymbolInfo.cpp"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

class ScopeTable
{
private:
    int total_buckets, child_count;
    string id;
    vector< SymbolInfo* > hashTable;
    ScopeTable* parent;
    ofstream* logfile;

public:
    ScopeTable(int n, ofstream* file);
    ~ScopeTable();

    unsigned long hash(string s);
    static unsigned long sdbm(string s);
    void setParent(ScopeTable* parent);
    ScopeTable* getParent();
    void setId(string id);
    string getId();
    bool insert(string name, string type);
    SymbolInfo* lookUp(string name);
    bool delete_key(string name);
    void print();
};

ScopeTable::ScopeTable(int n, ofstream *file)
{
    parent = nullptr;
    this->logfile = file;
    this->total_buckets = n;
    hashTable.assign(total_buckets, nullptr);
    child_count = 0;
}

ScopeTable::~ScopeTable()
{
    // cout << "Destructor of Scope table called" << endl;
    if (parent != nullptr) 
        delete parent;
    for (int i=0; i<total_buckets; i++) {
        if (hashTable[i] != nullptr) delete hashTable[i];
    }
}

bool ScopeTable::insert(string name, string type) {

    unsigned long long hash_value = hash(name);
    int cnt = 0;

    if (hashTable[hash_value] == nullptr) {
        hashTable[hash_value] = new SymbolInfo(name, type);
    } else {
        SymbolInfo* sym_cur = hashTable[hash_value];
        cnt++;
        if (sym_cur->getName() == name) {
            (*logfile) << "< "  << name << "," << type << " > already exists in current ScopeTable"  << endl;
            return false;
        }
        while(sym_cur->getNext() != nullptr) {
            sym_cur = sym_cur->getNext();
            if (sym_cur->getName() == name) {
                (*logfile) << "< "  << name << "," << type << " > already exists in current ScopeTable"  << endl;
                return false;
            }
            cnt++;
        }
        sym_cur->createNext(name, type);
    }

    (*logfile) << "Inserted in ScopeTable# " << getId() << " at position " << hash_value << ", " << cnt << endl;
    return true;
}

SymbolInfo* ScopeTable::lookUp(string name) {
    unsigned long long hash_value = hash(name);

    SymbolInfo* sym_info = hashTable[hash_value];
    int cnt = 0;
    while(sym_info != nullptr) {
        if (sym_info->getName() == name) {
            (*logfile) << "Found in ScopeTable# " << getId() << " at position " << hash_value << ", " << cnt << endl;
            break;
        }
        sym_info = sym_info->getNext();
        cnt++;
    }

    return sym_info;
}

bool ScopeTable::delete_key(string name) {

    unsigned long long hash_value = hash(name);
    SymbolInfo* sym_info = hashTable[hash_value];
    int cnt = 0;
    if (sym_info == nullptr) return false;
    else if (sym_info->getName() == name) {
        hashTable[hash_value] = sym_info->getNext();
        sym_info->setNext(nullptr);
        delete sym_info;
        (*logfile) << "Deleted entry at "  << hash_value << "," << cnt << " in the current scopetable" << endl;
        return true;
    } else {

        while(sym_info->getNext() != nullptr and sym_info->getNext()->getName() != name) {
            sym_info = sym_info->getNext();
            cnt++;
        }
        if (sym_info->getNext() == nullptr) return false;
        else {
            SymbolInfo* to_be_deleted = sym_info->getNext();
            sym_info->setNext(to_be_deleted->getNext());
            to_be_deleted->setNext(nullptr);
            delete to_be_deleted;
            (*logfile)  << "Deleted entry at "  << hash_value << "," << cnt << " in the current scopetable" << endl;
            return true;
        }
    }

}

void ScopeTable::print() {
    (*logfile)  << "ScopeTable # "  << id << endl;
    for (int i=0; i<total_buckets; i++) {
        if (hashTable[i] == nullptr) continue;
        (*logfile)  << i << " --> ";

        SymbolInfo* sym_info = hashTable[i];
        while(sym_info != nullptr) {
            (*logfile)  << "< " << sym_info->getName() << " : " << sym_info->getType() << " > ";
            sym_info = sym_info->getNext();
        }
        (*logfile) << endl;
    }
}


void ScopeTable::setParent(ScopeTable* parent) {
    if (parent != nullptr) {
        parent->child_count++;
        this->id = parent->id + "." + to_string(parent->child_count);
    }
    this->parent = parent;
}

ScopeTable* ScopeTable::getParent() {
    return parent;
}

void ScopeTable::setId(string id)  {
    this->id = id;
}

string ScopeTable::getId() {
    return id;
}


unsigned long ScopeTable::hash(string str) {
    return sdbm(str) % total_buckets;
}

unsigned long ScopeTable::sdbm(string str) {
    unsigned long hash = 0;
    for (char c: str) {
        hash = c + (hash << 6) + (hash << 16) - hash;
    }
    return hash;
}

