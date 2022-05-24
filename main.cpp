#include<iostream>
#include<string>
#include "SymbolInfo.cpp"

using namespace std;

int main() {
    SymbolInfo* ptr = new SymbolInfo("Hello", "World");
    ptr->createNext("Bye", "World")->createNext("Crazy", "World");

    SymbolInfo* cpyPtr = ptr;

    while(ptr != nullptr) {
        cout << ptr->getName() << " : " << ptr->getType() << endl;

        ptr = ptr->getNext();
    }

    cpyPtr->createNext("Santa", "Claus");
    delete cpyPtr;
}