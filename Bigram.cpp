#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
using namespace std;
#include "Bigram.h"

Bigram::Bigram() {
    w = "";
    wi = "";
    freq = 0;
    PP = "";
}

Bigram::Bigram(string w_, string wi_) {
    w = w_;
    wi = wi_;
    freq = 0;
    PP = "";
}

string Bigram::getwi() {
    return wi;
}

string Bigram::getw() {
    return w;
}

string Bigram::getPP() {
    return PP;
}

int Bigram::getFreq() {
    return freq;
}

double Bigram::getStrength() {
    return ((freq - getFbar()) / getSigma());
}

double Bigram::getSpread() {
    double u = 0;
    double ps;

    for (int i = 0; i < 10; i++) {
        ps = p[i] - (freq / 10);
        u += (ps * ps);
    }
    u = u / 10;
    return u;
}

vector<int> Bigram::getDistances(double k1) {
    vector<int> distances;
    double minPeak;

    // Equation from Smadja, Step 1.3
    minPeak = (freq / 10) + (k1 * sqrt(getSpread()));

    // Loop through the distances < 0 and > 0 and add the interesting
    // relative positions
    for (int i = 0; i < 5; i++) {
        if (p[i] > minPeak) {
            distances.add(i - 5);
        }
    }

    for (int i = 5; i < 10; i++) {
        if (p[i] > minPeak) {
            distances.add(i - 4);
        }
    }

    return distances;
}

int Bigram::getp(int offset) {

    // Only values of -5 to -1 and 1 to 5 are allowed.
    if (offset < 0 && offset >= -5) {
        return p[offset + 5];
    } else if (offset > 0 && offset <= 5) {
        return p[offset + 4];
    }

    // Invalid offset
    return -1;
}

void Bigram::addInstance(int offset) {
    if ((offset < -5) || (offset > 5) || (offset == 0)) {
        throw exception("Cannot add instance: offset out of bounds");
    } else {
        if (offset < 0) {
            offset += 5;
        } else if (offset > 0) {
            offset += 4;
        }
        p[offset]++;
        freq++;
        wFreq++;
    }
}

int Bigram::compare(Bigram b) {
    return wi.compare(b.getwi());
}