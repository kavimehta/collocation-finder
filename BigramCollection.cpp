#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
using namespace std;

/**
 * BigramCollection is the data structure that contains information about a word
 * and all of the bigrams that are within a distance of 5 words from it in any
 * sentence in the corpus.
 */
class BigramCollection {
public:
	map<string, Bigram> bigrams;
	double wFreq;

	BigramCollection() {
		wFreq = 0;
	}

	class Bigram {
		string w;
		string wi;
		string PP;
		int freq;
		vector<int> p;

		public Bigram(string w_, string wi_) {
			w = w_;
			wi = wi_;
			freq = 0;
			PP = "";
			p = arr(10);
		}

		string getwi() {
			return wi;
		}

		string getw() {
			return w;
		}

		string getPP() {
			return PP;
		}

		int getFreq() {
			return freq;
		}

	}
}