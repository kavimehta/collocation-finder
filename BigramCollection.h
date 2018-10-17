#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
using namespace std;
#include "S1Bigram.h"
#include "Bigram.h"

/**
 * BigramCollection is the data structure that contains information about a word
 * and all of the bigrams that are within a distance of 5 words from it in any
 * sentence in the corpus.
 */
class BigramCollection {
    public:
    	map<string, Bigram> bigrams;
        double wFreq;

        BigramCollection();
        void addSentence(string w, string s, bool includeClosedClass);
        double getFbar();
        double getSigma();
        double getStrength(Bigram b);
        string getTable2();
        string getTable4();
        vector<S1Bigram*> getStageOneBigrams(double k0, double k1, double U0);
        void stage2(double T);
        bool containsBigram(string wi_);
        void clearBigrams();

}; // End class BigramCollection
