#ifndef TEXT_H
#define TEXT_H
#include <vector>
#include <iostream>
#include <utility>
#include <string>
#include "subject.h"
using std::vector;
using std::ostream;

class TextDisplay {
        vector<vector<char>> grid;
        vector<vector<std::pair<char, std::string>>> links;
        vector<vector<bool>> knownLinks;
    public:
        void notify(Subject&);
        friend ostream& operator<< (ostream&, TextDisplay&);
};


#endif
