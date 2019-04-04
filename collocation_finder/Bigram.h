#include "stdc++.h"
#include <iostream>
#include <fstream>
using namespace std;

class Bigram {
    private:
		string w;
		string wi;
		string PP;
		int freq;
		vector<int> p;

    public:
        Bigram();
		Bigram(string w_, string wi_);
		string getwi();
		string getw();
		string getPP();
		int getFreq();
        double getStrength();
        double getSpread();
        vector<int> getDistances(double k1);
        int getp(int offset);
        void addInstance(int offset);
        int compare(Bigram b);

}; // End class Bigram