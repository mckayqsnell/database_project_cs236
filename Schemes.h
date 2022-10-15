#ifndef PROJECT1_SCHEMES_H
#define PROJECT1_SCHEMES_H

#include <string>
#include <vector>
#include "Stuff.h"

using namespace std;

class Schemes: public Stuff {
private:
    int num_Schemes;
public:
    Schemes();
    ~Schemes();
    void setNumSchemes(int numSchemes);
    int getNumSchemes();
    string toString();
};


#endif //PROJECT1_SCHEMES_H
