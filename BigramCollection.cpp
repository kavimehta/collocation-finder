#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
using namespace std;
#include "BigramCollection.h"

/**
 * BigramCollection is the data structure that contains information about a word
 * and all of the bigrams that are within a distance of 5 words from it in any
 * sentence in the corpus.
 */

BigramCollection::BigramCollection() {
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
void BigramCollection::addSentence(string w, string s, bool includeClosedClass) {
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

        ifstream stopWordsFile("stopWordsList.txt");
        vector<string> stopWords;
        string word;
        while (stopWordsFile >> word) {
            stopWords.push_back(word);
        }

        // Loop through the 10 surrounding words, but don't fall off the end
        // of the array
        for (int i = startIndex; (i < words.size()) && (i <= wIndex + 5); i++) {
            string lowerW = words[i];
            transform (lowerW.begin(), lowerW.end(), lowerW.begin(), ::tolower);
            if (includeClosedClass || std::find(stopWords.begin(), stopWords.end(), lowerW) == stopWords.end()) {
                if(!(words[i] == w)) {
                    if (!containsBigram(words[i])) {
                        bigrams[words[i]] = *(new Bigram(w, words[i]));
                    }
                    bigrams[words[i]].addInstance(i - wIndex);
                    wFreq++;
                }
            }
        }
    }
}

/**
 * Returns fbar, the average frequency of all bigrams for this word.
 *
 * @return fbar, the average frequency
 */
double BigramCollection::getFbar() {
    return (wFreq / bigrams.size());
}

/**
 * Returns sigma, the standard deviation of the frequency of all bigrams for
 * this word.
 *
 * @return sigma, the standard deviation
 */
double BigramCollection::getSigma() {
    double fbar = getFbar();
    Bigram tempBG;

    double term1 = (1 / (double) (bigrams.size() - 1));
    double term2 = 0;
    double x;

    //Iterate through bigrams and perform calculation
    map<string, Bigram>::iterator it;
    for (it = bigrams.begin(); it != bigrams.end(); it++) {
         x = (it->second).getFreq() - fbar;
         term2 += (x * x);
    }

    // This should be the standard deviation. Implementation of a formula
    // from Wikipedia
    return sqrt(term1 * term2);
}

/**
 * Returns a Vector with the bigrams left after Stage 1 of the algorithm
 * and their characteristics.
 *
 * @return A Vector containing all of the S1Bigrams
 */
vector<S1Bigram> BigramCollection::getStageOneBigrams(double k0, double k1, double U0) {
    vector<S1Bigram> passedStage;
    Bigram tempBG;

    //Iterating over all the bigrams
    map<string, Bigram>::iterator it;
    for (it = bigrams.begin(); it != bigrams.end(); it++) {
        tempBG = it->second;

        if (getStrength(tempBG) >= k0 && tempBG.getSpread() >= U0) {
            vector<int> distances = tempBG.getDistances(k1);
            passedStage.push_back(*(new S1Bigram(tempBG.getw(), tempBG.getwi(), getStrength(tempBG), tempBG.getSpread(), distances)));
        }
    }

    return passedStage;
}

double BigramCollection::getStrength(Bigram b) {
    return ((b.getFreq() - getFbar()) / getSigma());
}

void BigramCollection::stage2(double T) {
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
    cout << "\n";
}

/**
 * Checks if the collection contains a bigram of w and the given argument.
 *
 * @param wi_ String of the potential collocate of w.
 * @return <code>true</code> if the bigram exists, <code>false</code> otherwise.
 */
bool BigramCollection::containsBigram(string wi_) {
    map<string, Bigram>::iterator it = bigrams.find(wi_);
    return it != bigrams.end();
}

/**
 * Removes all bigrams from the collection.
 */
void BigramCollection::clearBigrams() {
    bigrams.clear();
}
