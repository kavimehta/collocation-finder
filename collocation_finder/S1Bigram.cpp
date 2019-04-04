#include <bits/stdc++.h>
#include "S1Bigram.h"
using namespace std;

/**
 * A small class to hold a bigram and the results of Stage 1.
 */

S1Bigram::S1Bigram(string w_, string wi_, double strength_, double spread_, std::vector<int> distances_) {
    w = w_;
    wi = wi_;
    strength = strength_;
    spread = spread_;
    distances = distances_;
}

string S1Bigram::getw() {
    return w;
}

string S1Bigram::getwi() {
    return wi;
}

double S1Bigram::getStrength() {
    return strength;
}

double S1Bigram::getSpread() {
    return spread;
}

std::vector<int> S1Bigram::getDistances() {
    return distances;
}