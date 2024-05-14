#include <string>
#include <iostream>
using namespace std;

class SymbolInfo
{
private:
    string name, type;
    SymbolInfo *next;
public:
    SymbolInfo(string name, string type);
    ~SymbolInfo();

    SymbolInfo* createNext(string name, string type);
    SymbolInfo* getNext();
    void setNext(SymbolInfo* nextPtr);
    string getName();
    string getType();
};

SymbolInfo::SymbolInfo(string name, string type)
{
    this->name = name;
    this->type = type;
    this->next = nullptr;
}

SymbolInfo::~SymbolInfo()
{

    if (next != nullptr) {
        delete next;
    }
    // cout << "Destructor Called -> " << name << " : [" << type << "]" << endl;
}

string SymbolInfo::getName() {
    return name;
}

string SymbolInfo::getType() {
    return type;
}

SymbolInfo* SymbolInfo::getNext() {
    return next;
}

void SymbolInfo::setNext(SymbolInfo* nextPtr) {
    this->next = nextPtr;
}

SymbolInfo* SymbolInfo::createNext(string name, string type) {
    if (next != nullptr) {
        delete next;
    }
    next = new SymbolInfo(name, type);
    return next;
}
