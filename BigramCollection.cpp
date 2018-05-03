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
            for (int i = 0, len = s.size(); i < len; i++) {
                if (ispunct(s[i])) {
                     s.erase(i--, 1);
                     len = s.size();
                }
            }

            // Split string into words
            istringstream iss(s);
            vector<string> words;
            copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(words));

            bool found = false;
            // Find w
            for (int i = 0; i < words.size(); i++) {
                if (words[i] == w) {
                    wIndex = i;
                    found = true;
                }
            }

            // Removed exception for if !found
            if (found) {
                int startIndex = wIndex - 5;
                if (startIndex < 0) {
                    startIndex = 0;
                }

                bool isStopWord = false;
                const char* args[] = {"was", "am", "has", "the", "a", "and", "be", "but", "by", "can", "such", "could", "do", "for", "have", "him", "her", "i", "is", "we", "he", "she", "it", "may", "might", "mine", "must", "need", "no", "not", "nor", "none", "our", "where", "whether", "while", "which", "you", "your", "to", "of", "on", "with", "in", "so", "or", "my", "its", "if", "his", "hers", "as", "an", "at", "this", "they", "there", "then", "that", "are", "would", "who", "whom", "them", "each", "from", "ourselves", "when", "these"};
                vector<string> stopWords(args, args + sizeof(args)/sizeof(args[0]));

                // Loop through the 10 surrounding words, but don't fall off the end
                // of the array
                for (int i = startIndex; (i < words.size()) && (i <= wIndex + 5); i++) {
                    for (int j = 0; j < stopWords.size(); j++) {
                        if (words[i] == words[j]) {
                            isStopWord = true;
                            break;
                        }
                    }
                    if(!(words[i] == w) && (includeClosedClass || !isStopWord)) {
                        if (!containsBigram(words[i])) {
                            bigrams.insert(pair<string, Bigram>(w, new Bigram(w, words[i])));
                        }
                        bigrams[words[i]].addInstance(i - wIndex);
                    }
                    isStopWord = false;
                }
            }
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

        /**
         * Gets a string representing the contents of the BigramCollection similar
         * to the format presented in Table 2 of the Smadja paper.
         *
         * @return The String containing the table-format contents of the bigrams.
         */
        string getTable2() {
            //TODO: complete me
            return "";
        }

        /**
         * Present the results of Step 1.3 in the Smadja algorithm. This is similar
         * to Table 4 in the paper.
         *
         * @return A string containing the table.
         */
        string getTable4() {
            //TODO: complete me
            return "";
        }

        /**
         * Returns a Vector with the bigrams left after Stage 1 of the algorithm
         * and their characteristics.
         *
         * @return A Vector containing all of the S1Bigrams
         */
        vector<S1Bigram> getStageOneBigrams(double k0, double k1, double U0) {
            vector<S1Bigram> passedStage;
            Bigram tempBG;

            //Iterating over all the bigrams
            map<string, Bigram>::iterator it;
            for (it = bigrams.begin(); it != bigrams.end(); it++) {
                tempBG = it->second;

                if (tempBG.getStrength() >= k0 && tempBG.getSpread() >= U0) {
                    vector<int> distances = tempBG.getDistances(k1);
                    passedStage.push_back(new S1Bigram(tempBG.getw(), tempBG.getwi(), tempBG.getStrength(), tempBG.getSpread(), distances));
                }
            }
        }

        void stage2(double T) {
            Bigram tempBG;
            int pos = 0;
            vector<int> freqs(10);
            vector<string> ngram;

            map<string, Bigram>::iterator it;
            for (it = bigrams.begin(); it != bigrams.end(); it++) {
                tempBG = it->second;

                for (int i = 0; i < 10; i++) {
                    if (i < 5) {
                        pos = i - 5;
                    } else if (i >= 5) {
                        pos = i - 4;
                    }
                    freqs[i] += tempBG.getp(pos);
                }
            }

            for (int i = 0; i < 10; i++) {
                bool addedWord = false;
                if (i < 5) {
                    pos = i - 5;
                } else if (i >= 5) {
                    pos = i - 4;
                }
                if (i == 5) {
                    ngram.push_back(tempBG.getw());
                }

                // For each position, go through each wi
                // Iterating over all the Bigrams
                map<string, Bigram>::iterator it;
                for (it = bigrams.begin(); it != bigrams.end(); it++) {
                    tempBG = it->second;
                    if ((freqs[i] > 0) && (((double) tempBG.getp(pos) / (double) freqs[i]) > T)) {
                        // Add
                        //double frequency = (double) tempBG.getp(pos) / (double) freqs[i];
                        ngram.push_back(tempBG.getwi());
                        addedWord = true;
                    }
                }
                if (!addedWord) {
                    ngram.push_back("_");
                }
            }
            for (int i = 0; i < ngram.size(); i++) {
                string aNgram = ngram[i];
                cout << aNgram;
                cout << " ";
            }
            cout << "";
        }

        /**
         * Checks if the collection contains a bigram of w and the given argument.
         *
         * @param wi_ String of the potential collocate of w.
         * @return <code>true</code> if the bigram exists, <code>false</code> otherwise.
         */
        bool containsBigram(string wi_) {
            map<string, Bigram>::iterator it = bigrams.find(wi_);
            return it != bigrams.end();
        }

        /**
         * Removes all bigrams from the collection.
         */
        void clearBigrams() {
            bigrams.clear();
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

    	}; // End class Bigram

}; // End class BigramCollection
