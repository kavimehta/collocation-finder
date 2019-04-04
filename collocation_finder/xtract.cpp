// package jxtract;
using namespace std;
#include "BigramCollection.h"
#include "Corpus.h"
#include "stdc++.h"

class JXtract {

    private:
        Corpus corpus;
        bool getFrequencies;
        bool showHelp;
        int minFrequency;
        string sourcefilename;
        string word;

        /**
         * showHelp
         * Prints the command line help for JXtract.
         */
        static void showHelpDialog() {
            cout << "JXtract: a collocation extractor\n";
            cout << "Usage: JXtract -source filename [-printfrequencies [-minfrequency frequency]] [-word word]\n";
            cout << "Example: JXtract -source ep-00-en.txt -word European\n";
            cout << "\n";
            cout << "Arguments:\n";
            cout << "-source\t\t\tThe corpus file.  Must be English language.\n";
            cout << "-word\t\t\tThe word that will be used to search for collocations\n";
            cout << "-printfrequencies\t(Optional) An alternate mode to finding collocations.  JXtract can also be used to\n";
            cout << "\t\t\tfind the most frequent words in a file\n";
            cout << "-minfrequency\t\t(Optional)If JXtract is used to get word frequencies, this determines the lower\n";
            cout << "\t\t\tfrequency threshold, below which less frequently appearing words will not be reported\n";
        }

        /**
         * getCollocations()
         * This runs the Xtract algorithm on a word and corpus and
         * returns the labelled collocations for that word.
         */
        void getCollocations(string w) {
            cout << "Finding collocations containing the word " + w + "\n";
            transform(w.begin(), w.end(), w.begin(), ::tolower);
            vector<string> foundSentences = corpus.getSentencesWith(w);

            BigramCollection bigrams = BigramCollection();
            try {
                for (vector<string>::iterator it = foundSentences.begin(); it != foundSentences.end(); ++it) {
                    //cout << "Found sentence: " + (*it) + "\n";
                    bigrams.addSentence(w, (*it), false);
                }

            } catch (exception& e) {
                cout << e.what();
            }

            vector<S1Bigram> postStage1 = bigrams.getStageOneBigrams(1, 1, 10); // originally 1,1,10

            for (S1Bigram s1bigram : postStage1) {
                //cout << s1bigram.getw() + "\t" + s1bigram.getwi() + "\t";
                //cout << s1bigram.getStrength() << "\t" << s1bigram.getSpread() << "\n";
                for (int j = 0; j < s1bigram.getDistances().size(); j++) {
                    vector<string> stage2sentences = corpus.getSentencesWith(
                            s1bigram.getw(),
                            s1bigram.getwi(),
                            s1bigram.getDistances()[j]
                    );
                    BigramCollection s2bigrams = BigramCollection();

                    // Add all sentences with this bigram to a collection
                    try {
                        for (string stage2sentence : stage2sentences) {
                            //cout << "Found sentence: " + stage2sentence;
                            s2bigrams.addSentence(w, stage2sentence, true);
                        }
                    } catch (exception& e) {
                        cout << e.what();
                    }
                    s2bigrams.stage2(0.75);
                }

            }

        } // End getCollocations()

        /**
         * printFrequentWords
         * Print frequent words in the corpus
         */
        void printFrequentWords(int freq) {
            vector<string> words = corpus.getFrequentWords(freq);
            for (vector<string>::iterator it = words.begin(); it != words.end(); ++it) {
                // Moved printing to corpus.cpp
                //cout << *it + "\n";
            }
        }

    public:
        /**
         * Constructor
         */
        JXtract() {
            // Corpus is initialized when args are parsed
            getFrequencies = false;
            minFrequency = 100;
            showHelp = false;
            sourcefilename = "";
            word = "";
        }

        /**
         * Set class' variables based on command line arguments.
         *
         * @param args Command line arguments.
         */
        void parseProgArgs(int argc, char *argv[]) {
            for (int i = 1; i < argc; i++) {
                if (std::string(argv[i]) == "-printfrequencies") {
                    getFrequencies = true;
                } else if (std::string(argv[i]) == "-minfrequency") {
                    minFrequency = std::stoi(argv[i + 1]);
                } else if (std::string(argv[i]) == "-source") {
                    sourcefilename = argv[i + 1];
                } else if (std::string(argv[i]) == "-word") {
                    word = argv[i + 1];
                } else if (std::string(argv[i]) == "-h") {
                    showHelp = true;
                } else if (std::string(argv[i]) == "-help") {
                    showHelp = true;
                } else if (std::string(argv[i]) == "--help") {
                    showHelp = true;
                }
            }

            if (showHelp) {
                showHelpDialog();
                exit(0);
            }

            // Make sure source is given
            if (!(sourcefilename.compare("") == 0)) {
                corpus = Corpus(sourcefilename);

                // Either get word frequencies or find collocations
                if (getFrequencies) {
                    printFrequentWords(minFrequency);
                } else if (word.compare("") != 0) {
                    getCollocations(word);
                }

            } else {
                showHelpDialog();
                exit(0);
            }
        }
};

int main(int argc, char *argv[]) {
    JXtract xtractor = JXtract();
    xtractor.parseProgArgs(argc, argv);
}