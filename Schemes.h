#ifndef PROJECT1_SCHEMES_H
#define PROJECT1_SCHEMES_H

#include <string>
#include <vector>

using namespace std;

class Schemes {
private:
    string tmp;
    int num_Schemes;
public:
    Schemes();
    ~Schemes();
    void setNumSchemes(int numSchemes);
    int getNumSchemes();
    string toString();
};


#endif //PROJECT1_SCHEMES_H
