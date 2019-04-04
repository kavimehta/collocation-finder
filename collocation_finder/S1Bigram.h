#include "stdc++.h"
using namespace std;

/**
 * A small class to hold a bigram and the results of Stage 1.
 */
class S1Bigram {
public:
 
    string w;
    string wi;
    double strength;
    double spread;
    vector<int> distances;

    S1Bigram(string w_, string wi_, double strength_, double spread_, std::vector<int> distances_);
    string getw();
    string getwi();
    double getStrength();
    double getSpread();
    std::vector<int> getDistances();
    
};