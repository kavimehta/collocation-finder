#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
using namespace std;

class Corpus {
    public:
        string filename;
        ifstream file;
        Corpus(string filename_);
        bool openFile();
        bool closeFile();
        void countLines();
        vector<string> getSentencesWith(string word_);
        vector<string> getSentencesWith(string w1, string w2, int distance);
        vector<string> getFrequentWords(int minFrequency);
};
