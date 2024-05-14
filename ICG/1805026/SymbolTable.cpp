#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "parameter.cpp"

using namespace std;

class SymbolInfo
{
private:
    string name, type;
    SymbolInfo *next;
public:
    vector<Parameter> paramList;
    int size;
    bool defined;
    bool isFunction = false, isArray = false, isVar = true;
    bool isGlobal = false;
    int offset;

    SymbolInfo(string name, string type)
    {
        this->name = name;
        this->type = type;
        this->next = nullptr;
        this->size = 1;
    }

    SymbolInfo(const SymbolInfo &sym_info) {
        name = sym_info.name;
        type = sym_info.type;
        next = sym_info.next;
        paramList = sym_info.paramList;
        size = sym_info.size;
        defined = sym_info.defined;
        isFunction = sym_info.isFunction;
        isArray = sym_info.isArray;
        isVar = sym_info.isVar;
        offset = sym_info.offset;
        isGlobal = sym_info.isGlobal;
    }
    ~SymbolInfo()
    {
        if (next != nullptr) {
            delete next;
        }
    }
    SymbolInfo* createNext(string name, string type) {
        if (next != nullptr) {
            delete next;
        }
        next = new SymbolInfo(name, type);
        return next;
    }
    SymbolInfo* createNext(SymbolInfo sym_info) {
        if (next != nullptr) {
            delete next;
        }
        next = new SymbolInfo(sym_info);
        return next;
    }
    SymbolInfo* getNext() {
        return next;
    }
    void setNext(SymbolInfo* nextPtr) {
        this->next = nextPtr;
    }
    void setName(string s) {
        this->name = s;
    }
    void setType(string s) {
        this->type = s;
    }
    string getName() {
        return name;
    }
    string getType() {
        return type;
    }

    void setAsArray(string name, string type, int sz) {
        this->name = name;
        this->type = type;
        this->size = sz;
        next = nullptr;
        defined = false;
        isArray = true;
        isVar = isFunction = false;
    }

    void setAsFunction(string name, string type, vector<Parameter> paramList) {
        this->name = name;
        this->type = type;
        this->paramList = paramList;
        isFunction = true;
        isVar = isArray = false;
    }
};


class ScopeTable
{
private:
    int total_buckets, child_count;
    string id;
    vector< SymbolInfo* > hashTable;
    ScopeTable* parent;
    ofstream* logfile;

    int offset = 0;

public:
    ScopeTable(int n, ofstream *file)
    {
        parent = nullptr;
        this->logfile = file;
        this->total_buckets = n;
        hashTable.assign(total_buckets, nullptr);
        child_count = 0;
    }
    ~ScopeTable()
    {
        // cout << "Destructor of Scope table called" << endl;
        if (parent != nullptr) 
            delete parent;
        for (int i=0; i<total_buckets; i++) {
            if (hashTable[i] != nullptr) delete hashTable[i];
        }
    }

    bool insert(string name, string type) {

        unsigned long long hash_value = hash(name);
        int cnt = 0;

        if (hashTable[hash_value] == nullptr) {
            hashTable[hash_value] = new SymbolInfo(name, type);
        } else {
            SymbolInfo* sym_cur = hashTable[hash_value];
            cnt++;
            if (sym_cur->getName() == name) {
                // (*logfile) << "< "  << name << "," << type << " > already exists in current ScopeTable"  << endl;
                return false;
            }
            while(sym_cur->getNext() != nullptr) {
                sym_cur = sym_cur->getNext();
                if (sym_cur->getName() == name) {
                    // (*logfile) << "< "  << name << "," << type << " > already exists in current ScopeTable"  << endl;
                    return false;
                }
                cnt++;
            }
            sym_cur->createNext(name, type);
        }

        // (*logfile) << "Inserted in ScopeTable# " << getId() << " at position " << hash_value << ", " << cnt << endl;
        return true;
    }

    bool insertSymbol(SymbolInfo sym_info) {
        unsigned long long hash_value = hash(sym_info.getName());
        int cnt = 0;

        if (hashTable[hash_value] == nullptr) {
            hashTable[hash_value] = new SymbolInfo(sym_info);
        } else {
            SymbolInfo* sym_cur = hashTable[hash_value];
            cnt++;
            if (sym_cur->getName() == sym_info.getName()) {
                // (*logfile) << "< "  << sym_info.getName() << "," << sym_info.getType() << " > already exists in current ScopeTable"  << endl;
                return false;
            }
            while(sym_cur->getNext() != nullptr) {
                sym_cur = sym_cur->getNext();
                if (sym_cur->getName() == sym_info.getName()) {
                    // (*logfile) << "< "  << name << "," << type << " > already exists in current ScopeTable"  << endl;
                    return false;
                }
                cnt++;
            }
            sym_cur->createNext(sym_info);
        }

        // (*logfile) << "Inserted in ScopeTable# " << getId() << " at position " << hash_value << ", " << cnt << endl;
        return true;

    }

    SymbolInfo* lookUp(string name) {
        unsigned long long hash_value = hash(name);

        SymbolInfo* sym_info = hashTable[hash_value];
        int cnt = 0;
        while(sym_info != nullptr) {
            if (sym_info->getName() == name) {
                // (*logfile) << "Found in ScopeTable# " << getId() << " at position " << hash_value << ", " << cnt << endl;
                break;
            }
            sym_info = sym_info->getNext();
            cnt++;
        }

        return sym_info;
    }
    bool delete_key(string name) {

        unsigned long long hash_value = hash(name);
        SymbolInfo* sym_info = hashTable[hash_value];
        int cnt = 0;
        if (sym_info == nullptr) return false;
        else if (sym_info->getName() == name) {
            hashTable[hash_value] = sym_info->getNext();
            sym_info->setNext(nullptr);
            delete sym_info;
            // (*logfile) << "Deleted entry at "  << hash_value << "," << cnt << " in the current scopetable" << endl;
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
                // (*logfile)  << "Deleted entry at "  << hash_value << "," << cnt << " in the current scopetable" << endl;
                return true;
            }
        }

    }
    void print() {
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
    void setParent(ScopeTable* parent) {
        if (parent != nullptr) {
            parent->child_count++;
            this->id = parent->id + "." + to_string(parent->child_count);
        }
        this->parent = parent;
    }

    ScopeTable* getParent() {
        return parent;
    }

    void setId(string id)  {
        this->id = id;
    }

    string getId() {
        return id;
    }


    unsigned long hash(string str) {
        return sdbm(str) % total_buckets;
    }

    unsigned long sdbm(string str) {
        unsigned long hash = 0;
        for (char c: str) {
            hash = c + (hash << 6) + (hash << 16) - hash;
        }
        return hash;
    }

};

class SymbolTable
{
private:
    ScopeTable* cur_scp_table;
    int total_buckets;
    ofstream* logfile;
public:
    int offset = 0;

    SymbolTable(int n, ofstream* file)
    {
        this->total_buckets = n;
        this->logfile = file;
        cur_scp_table = new ScopeTable(total_buckets, logfile);
        cur_scp_table->setId("1");
    }

    ~SymbolTable()
    {
        // cout << "Destructor of Symbol Table Called" << endl;
        delete cur_scp_table;
    }

    bool insert(string name, string type) {
        if (cur_scp_table == nullptr) return false;
        return cur_scp_table->insert(name, type);
    }

    bool insertSymbol(SymbolInfo sym_info) {
        sym_info.offset = offset;
        offset += 2*sym_info.size;
        if (cur_scp_table == nullptr) return false;
        return cur_scp_table->insertSymbol(sym_info);
    }

    bool insertSymbol(SymbolInfo sym_info, int offset) {
        sym_info.offset = offset;
        if (cur_scp_table == nullptr) return false;
        return cur_scp_table->insertSymbol(sym_info);
    }

    void enterScope() {
        ScopeTable* scp_table = new ScopeTable(total_buckets, logfile);
        scp_table->setParent(cur_scp_table);
        // (*logfile) << "New ScopeTable with id " << scp_table->getId() << " created" << endl;
        cur_scp_table = scp_table;
    }

    void exitScope() {
        if (cur_scp_table == nullptr) {
            return;
        }
        // (*logfile) << "ScopeTable with id " << cur_scp_table->getId() << " removed" << endl;
        ScopeTable* next_scp_table = cur_scp_table->getParent();
        cur_scp_table->setParent(nullptr);
        delete cur_scp_table;

        cur_scp_table = next_scp_table;
    }

    bool remove(string name) {
        if (cur_scp_table->lookUp(name) == nullptr) {
            // (*logfile) << "Not Found" << endl;
            // (*logfile) << name << " is not found" << endl;
            return false;
        } 
        // cout << "Found it" << endl;
        bool result = cur_scp_table->delete_key(name);
        return result;
    }

    SymbolInfo* lookUp(string name) {
        ScopeTable* scp_table = cur_scp_table;

        while(scp_table != nullptr) {
            SymbolInfo* sym_info = scp_table->lookUp(name);
            if (sym_info != nullptr) {
                return sym_info;
            }
            scp_table = scp_table->getParent();
        }
        // (*logfile) << "Not Found" << endl;
        return nullptr;
    }

    void printCurScopeTable() {
        if (cur_scp_table == nullptr) return;
        cur_scp_table->print();
    }

    void printAllScopeTable() {
        ScopeTable* scp_table = cur_scp_table;

        while(scp_table != nullptr) {
            scp_table->print();
            if (scp_table->getParent() == nullptr) break;
            scp_table = scp_table->getParent();
        }
    }

    string getId() {
        return cur_scp_table->getId();
    }
};
