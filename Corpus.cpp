#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
using namespace std;

/**
 * This class represents the text file that makes up a corpus.
 */
class Corpus {
public:

	string filename;
	ofstream file;

	/**
     * Constructor for the Corpus.
     *
     * @param filename_ The text file that contains the corpus.
     */
	Corpus(string filename_) {
		filename = filename_;
	}

	/**
     * Open the file for reading.
     *
     * @return true if the open succeeded, false if the open failed.
     */
	bool openFile() {
		file.open(filename);
		return not f.fail();
	}

    /**
     * Close the file if it was open.
     *
     * @return true if the file was already closed or the operation closed it. false if the
     * file is still open after execution.
     */
	bool closeFile() {
		if (f.is_open()) {
			f.close()
			return not f.fail();
		}
		return true;
	}

    /**
     * Count all the lines in the corpus and print to cout.
     */
	void countLines() {
		int count = 0;
		string line;
		while (getline(file, line)) {
			count++;
		}
		cout << "Lines: " << count;
	}

    /**
     * This returns a Vector of Strings, where each String is a sentence in the
     * Corpus that contains the specified word.
     *
     * @param word_ The word that is searched for in the corpus.
     * @return The Vector of Strings with the sentences.
     */
	vector<string> getSentencesWith(string word_) {
		vector<string> foundSentences;
		openFile();
		string record;
		while (getline(myfile, record)) {
			// Add spaces so record.find catches word at beginning or end
			string tempRecord = " " + record + " ";
			if (tempRecord.find(" " + word_ + " ")) {
				foundSentences.push_back(record);
			}
		}
		closeFile();
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
     vector<string> getSentencesWith(string w1, string w2, int distance) {
     	vector<string> foundSentences;
     	openFile();
     	string record;
     	while (getline(myfile, record)) {
     		// Remove punctuation
     		record.erase(remove_if(text.begin(), text.end(), ispunct), text.end());

     		// Split string into words
     		istringstream iss(record);
     		vector<string> words{istream_iterator<string>{iss}, istream_iterator<string>{}};
     	
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
     	closeFile();
     	return foundSentences;
     }

     vector<string> getFrequentWords(int minFrequency) {
          vector<string> freqWords;
          // Create a map
          map<string, int> m;

          bool isStopWord = false;
          vector<string> stopWords = {"was", "am", "has", "the", "a", "and", "be", "but", "by", "can", "such", "could", "do", "for", "have", "him", "her", "i", "is", "we", "he", "she", "it", "may", "might", "mine", "must", "need", "no", "not", "nor", "none", "our", "where", "whether", "while", "which", "you", "your", "to", "of", "on", "with", "in", "so", "or", "my", "its", "if", "his", "hers", "as", "an", "at", "this", "they", "there", "then", "that", "are", "would", "who", "whom", "them", "each", "from", "ourselves", "when", "these"}

          openFile();
          string record;
          while (getline(myfile, record)) {
               // Remove punctuation
               record.erase(remove_if(text.begin(), text.end(), ispunct), text.end());

               // Split string into words
               istringstream iss(record);
               vector<string> words{istream_iterator<string>{iss}, istream_iterator<string>{}};
               
               for (int i = 0; i < words.size(); i++) {
                    for (int j = 0; j < stopWords.size(); j++) {
                         if (words[i] == words[j]) {
                              isStopWord = true;
                              break;
                         }
                    }

                    if (!isStopWord) {
                         m[words[i]]++;
                    }

                    isStopWord = false;
               }

               // Add frequent words to freqWords
               map<sring, int>::iterator it;
               for (it = m.begin(); it != m.end(); it++) {
                    if (it->second >= minFrequency) {
                         freqWords.push_back(it->first);
                    }
               }
          }

          closeFile();
          return freqWords;

     }
}