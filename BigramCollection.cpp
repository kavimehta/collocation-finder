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

    	/**
         * Takes a sentence and adds all bigrams in the "phrase" (+/- 5 words) to
         * the collection. Note: The p value of the wi word is determined based on
         * the examples in Table 2 of the Smadja paper, not the examples in the Step
         * 1.2 description. These examples seem to be contradictory, and the
         * convention of "p+1 means wi is one word to the right of w" seems more
         * intuitive.
         *
         * @param s The sentence to be added.
         * @throws Exception If given sentence does not contain the word this
         *                   BigramCollection tracks.
         */
        void addSentence(string w, string s, bool includeClosedClass) {
        	int wIndex = 0;

        	// Remove punctuation
            s.erase(remove_if(text.begin(), text.end(), ispunct), text.end());

            // Split string into words
            istringstream iss(record);
            vector<string> words{istream_iterator<string>{iss}, istream_iterator<string>{}};
        }

    	/**
         * Returns fbar, the average frequency of all bigrams for this word.
         *
         * @return fbar, the average frequency
         */
        double getFbar() {
            return (wFreq / bigrams.size());
        }

        /**
         * Returns sigma, the standard deviation of the frequency of all bigrams for
         * this word.
         *
         * @return sigma, the standard deviation
         */
        double getSigma() {
            double fbar = getFbar();
            Bigram tempBG;

            double term1 = (1 / (double) (bigrams.size() - 1));
            double term2 = 0;
            double x;

            //Iterate through bigrams and perform calculation
            map<string, Bigram>::iterator it;
            for (it = bigrams.begin(); it != bigrams.end(); it++) {
                 x = (it->second).getFreq() - fbar;
                 term2 += x * x;
            }

            // This should be the standard deviation. Implementation of a formula
            // from Wikipedia
            return sqrt(term1 * term2);
        }

    private:
    	class Bigram {
            private:
        		string w;
        		string wi;
        		string PP;
        		int freq;
        		vector<int> p(10);

            public:
        		Bigram(string w_, string wi_) {
        			w = w_;
        			wi = wi_;
        			freq = 0;
        			PP = "";
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

                double getStrength() {
                    return ((freq - getFbar()) / getSigma());
                }

                double getSpread() {
                    double u = 0;
                    double ps;

                    for (int i = 0; i < 10; i++) {
                        ps = p[i] - (freq / 10);
                        u += (ps * ps);
                    }
                    u = u / 10;
                    return u;
                }

                vector<int> getDistances(double k1) {
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

                int getp(int offset) {

                    // Only values of -5 to -1 and 1 to 5 are allowed.
                    if (offset < 0 && offset >= -5) {
                        return p[offset + 5];
                    } else if (offset > 0 && offset <= 5) {
                        return p[offset + 4];
                    }

                    // Invalid offset
                    return -1;
                }

                void addInstance(int offset) {
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

                int compare(Bigram b) {
                    return wi.compare(b.getwi());
                }

    	} // End class Bigram

} // End class BigramCollection