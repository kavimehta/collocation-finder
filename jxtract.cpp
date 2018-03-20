/**
 * JXtract.java
 * JXtract is a Java implementation of the Xtract
 * tool described by Frank Smadja in his 1993
 * ACL paper "Retrieving Collocations from Text: Xtract"
 * <p/>
 * Written by: Adam Goforth
 * Started on: Dec 4, 2005
 */


// package jxtract;
#include<bits/stdc++.h>
using namespace std;


/**
 * @author Adam Goforth
 */

public class JXtract {

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
        static void showHelp() {
            cout << "JXtract: a collocation extractor";
            cout << "Usage: JXtract -source filename [-printfrequencies [-minfrequency frequency]] [-word word]";
            cout << "Example: JXtract -source ep-00-en.txt -word European";
            cout << "";
            cout << "Arguments:";
            cout << "-source\t\t\tThe corpus file.  Must be English language.";
            cout << "-word\t\t\tThe word that will be used to search for collocations";
            cout << "-printfrequencies\t(Optional) An alternate mode to finding collocations.  JXtract can also be used to";
            cout << "\t\t\tfind the most frequent words in a file";
            cout << "-minfrequency\t\t(Optional)If JXtract is used to get word frequencies, this determines the lower";
            cout << "\t\t\tfrequency threshold, below which less frequently appearing words will not be reported";
        }

        /**
         * getCollocations()
         * This runs the Xtract algorithm on a word and corpus and
         * returns the labelled collocations for that word.
         */
        void getCollocations(string w) {
            cout << "Finding collocations containing the word " + w;
            transform(w.begin(), w.end(), w.begin(), ::tolower);
            vector<string> foundSentences = corpus.getSentencesWith(w);

            BigramCollection bigrams;
            try {
                for (vector<string>::iterator it = foundSentences.begin(); it != foundSentences.end(); ++it) {
                    //cout << "Found sentence: " + foundSentences.get(i);
                    bigrams.addSentence(w, *it, false);
                }

            } catch (exception& e) {
                cout << e.what();
            }
            //cout << "\n" + bigrams.getTable4();
            vector<S1Bigram> postStage1 = bigrams.getStageOneBigrams(1, 1, 10);

            //DEBUG cout << "w\twi\tstrength\t\tspread\tdistance";
            for (vector<S1Bigram>::iterator it = postStage1.begin(); it != postStage1.end(); ++it) {
                for (int j = 0; j < *it.getDistances().size(); j++) {
                    //DEBUG cout << *it.getw() + "\t" + *it.getwi() + "\t" + *it.getStrength() + "\t" + *it.getSpread() + "\t" + *it.getDistances().get(j);
                    vector<string> stage2sentences = corpus.getSentencesWith(
                            *it.getw(),
                            *it.getwi(),
                            *it.getDistances().get(j)
                    );
                    BigramCollection s2bigrams;

                    // Add all sentences with this bigram to a collection
                    try {
                        for (string stage2sentence : stage2sentences) {
                            //cout << "Found sentence: " + stage2sentences.get(k);
                            s2bigrams.addSentence(w, stage2sentence, true);
                        }
                    } catch (exception& e) {
                        cout << e.what();
                    }
                    //cout << "\n" + s2bigrams.getTable2();
                    //cout << "^-- " + *it.getw() + " " + *it.getwi();
                    s2bigrams.stage2(0.75);
                    //cout << " ";
                }

            }

        } // End getCollocations()

        /**
         * printFrequentWords
         * Print frequent words in the corpus
         */
        private void printFrequentWords(int freq) {
            vector<string> words = corpus.getFrequentWords(freq);
            for (vector<string>::iterator it = words.begin(); it != words.end(); ++it) {
                cout << *it;
            }
        }

    public:
        /**
         * Constructor
         */
        JXtract() {
            getFrequencies = false;
            minFrequency = 1000;
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
                switch (argv[i]) {
                    case "-printfrequencies":
                        getFrequencies = true;
                        break;
                    case "-minfrequency":
                        minFrequency = Integer.parseInt(argv[i + 1]);
                        break;
                    case "-source":
                        sourcefilename = argv[i + 1];
                        break;
                    case "-word":
                        word = argv[i + 1];
                        break;
                    case "-h":
                    case "-help":
                    case "--help":
                        showHelp = true;
                        break;
                }
            }

            if (showHelp) {
                showHelp();
                exit(0);
            }

            // Make sure source is given
            if (!sourcefilename.compare("") == 0) {
                corpus(sourcefilename);

                // Either get word frequencies or find collocations
                if (getFrequencies) {
                    printFrequentWords(minFrequency);
                } else if (word.compare("") != 0) {
                    getCollocations(word);
                }

            } else {
                showHelp();
                exit(0);
            }
        }
}

int main(int argc, char *argv[]) {
    JXtract xtractor;
    xtractor.parseProgArgs(argc, argv);
}