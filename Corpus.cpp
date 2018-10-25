#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <string>
#include "Corpus.h"
using namespace std;

/**
 * This class represents the text file that makes up a corpus.
 */

/**
 * Default constructor.
 */
Corpus::Corpus() {}
    
/**
 * Constructor for the Corpus.
 *
 * @param filename_ The text file that contains the corpus.
 */
Corpus::Corpus(string filename_) {
    filename = filename_;
}

/**
 * Count all the lines in the corpus and print to cout.
 */
void Corpus::countLines() {
    //Open the file
    ifstream file;
    file.open(filename);

    int count = 0;
    string line;
    while (getline(file, line)) {
        count++;
    }
    cout << "Lines: " << count;

    //Close the file
    file.close();
}

/**
 * This returns a Vector of Strings, where each String is a sentence in the
 * Corpus that contains the specified word.
 *
 * @param word_ The word that is searched for in the corpus.
 * @return The Vector of Strings with the sentences.
 */
vector<string> Corpus::getSentencesWith(string word_) {
    //Open the file
    ifstream file;
    file.open(filename);

    vector<string> foundSentences;
    string record;
    while (getline(file, record, '.')) {
        // Add spaces so record.find catches word at beginning or end
        string tempRecord = " " + record + " ";
        if (tempRecord.find(" " + word_ + " ") != std::string::npos) {
            foundSentences.push_back(record);
        }
    }
    
    //Close the file
    file.close();

    return foundSentences;
}

/**
 * This returns a Vector of Strings, where each String is a sentence in the
 * Corpus that contains the specified words, with w2 being
 * distance words away from w1.
 *
 * @param w1       The first word
 * @param w2       The second word
 * @param distance The distance between them. -5 to -1 and 1 to 5 are valid values.
 * @return A Vector of Strings with one matched sentence per string.
 */
vector<string> Corpus::getSentencesWith(string w1, string w2, int distance) {
    //Open the file
    ifstream file;
    file.open(filename);

    vector<string> foundSentences;
    string record;
    while (getline(file, record)) {
        // Remove punctuation
        for (int i = 0, len = record.size(); i < len; i++) {
                if (ispunct(record[i])) {
                        record.erase(i--, 1);
                        len = record.size();
                }
            }

        // Split string into words
        istringstream iss(record);
        vector<string> words;
            copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(words));
    
        // Find w1 and check if it is the proper distance from w2
            bool addS = false;
            for (int i = 0; i < words.size(); i++) {
                if (words[i] == w1) {
                        if (i + distance >=0 && i+distance < words.size()) {
                            if (words[i+distance] == w2) {
                                addS = true;
                                break;
                            }
                        }
                }
            }

            // If found a match, add the sentence to the vector
            if (addS) {
                foundSentences.push_back(record);
            }
    }
    
    //Close the file
    file.close();

    return foundSentences;
}

vector<string> Corpus::getFrequentWords(int minFrequency) {
    //Open the file
    ifstream file;
    file.open(filename);

    vector<string> freqWords;
    // Create a map
    map<string, int> m;

    const char* args[] = {"was", "am", "has", "the", "The", "said", "Mr", "a", "and", "be", "but", "by", "can", "such", "could", "do", "for", "have", "him", "her", "i", "is", "we", "he", "she", "it", "may", "might", "mine", "must", "need", "no", "not", "nor", "none", "our", "where", "whether", "while", "which", "you", "your", "to", "of", "on", "with", "in", "so", "or", "my", "its", "if", "his", "hers", "as", "an", "at", "this", "they", "there", "then", "that", "are", "would", "who", "whom", "them", "each", "from", "ourselves", "when", "these"};
    vector<string> stopWords(args, args + sizeof(args)/sizeof(args[0]));

    string record;
    while (getline(file, record)) {
        // Remove punctuation
        for (int i = 0, len = record.size(); i < len; i++) {
            if (ispunct(record[i])) {
                    record.erase(i--, 1);
                    len = record.size();
            }
        }

        // Split string into words
        istringstream iss(record);
        vector<string> words;
        copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(words));

        for (int i = 0; i < words.size(); i++) {
            if (std::find(stopWords.begin(), stopWords.end(), words[i]) == stopWords.end()) {
                map<string,int>::iterator it = m.find(words[i]);
                if (it != m.end()) {
                    m[words[i]]++;
                } else {
                    m[words[i]] = 1;
                }
                
            }
        }
    }

    // Add frequent words to freqWords
    map<string, int>::iterator it;
    for (it = m.begin(); it != m.end(); it++) {
        if (it->second >= minFrequency) {
            freqWords.push_back(it->first);
        }
    }

    //Close the file
    file.close();

    return freqWords;

}