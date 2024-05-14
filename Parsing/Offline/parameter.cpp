#include <iostream>
#include <string>

using namespace std;

#ifndef PARAMETER_CPP
#define PARAMETER_CPP

struct Parameter {
    string name, type;

    Parameter(string name, string type) {
        this->name = name;
        this->type = type;
    }
};

#endif