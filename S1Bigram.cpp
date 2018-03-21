#include <bits/stdc++.h>
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

    S1Bigram(string w_, string wi_, double strength_, double spread_, std::vector<int> distances_) {
        w = w_;
        wi = wi_;
        strength = strength_;
        spread = spread_;
        distances = distances_;
    }

    string getw() {
    	return w;
    }

    string getwi() {
    	return wi;
    }

    double getStrength() {
    	return strength;
    }

    double getSpread() {
    	return spread;
    }

    std::vector<int> getDistances() {
    	return distances;
    }
    
}