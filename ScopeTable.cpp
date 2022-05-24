#include "SymbolInfo.cpp"
#include <vector>
#include <string>
using namespace std;

class ScopeTable
{
private:
    int total_buckets;
    vector< SymbolInfo* > hashTable;
public:
    ScopeTable(int n);
    ~ScopeTable();

    unsigned long long hash(string s);
    static unsigned long long sdbm(string s);
};

ScopeTable::ScopeTable(int n)
{
    this->total_buckets = n;
    hashTable.resize(total_buckets);
}

ScopeTable::~ScopeTable()
{
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