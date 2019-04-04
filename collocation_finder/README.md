# collocation-finder

This is a C++ implementation of the collocation extraction algorithm described in this paper: [Smadja, F. (1993). Retrieving Collocations From Text: Xtract.](https://www.semanticscholar.org/paper/Retrieving-Collocations-from-Text%3A-Xtract-Smadja/9693056ac1d845a7a1537774fcd758bb14909694) The code is based on a Java implementation, available [here](https://github.com/aag/jxtract).

To compile, run:
```
cd build
cmake ..
make
```

To run, use the following:

For printing the frequencies of words in a text
```
./xtract -source [filename.txt] -printfrequencies -minfrequency [minimum word frequency to be printed, default: 500]
```

For printing the collocations of a given word in a text
```
./xtract -source [filename.txt] -word [word to find collocations for]
```
