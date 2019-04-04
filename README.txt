Author: Kavi Mehta, 2019, ICSI, UC Berkeley


---File structure---
collocation_finder - repository containing c++ implementation of Xtract, https://github.com/kavimehta/collocation-finder
data_collection - python scripts for retrieving political articles and converting to .txt files
misc - administrative documents and notes
texts - .txt files to be used as data for running experiments
jxtract - java implementation of Xtract, https://github.com/aag/jxtract
smadja_xtract.pdf - original Xtract paper describing the collocation finder algorithm


---Running Experiments---
In the collocation_finder directory, do the following

Compile the code:
	cd build
    cmake ..
    make

Print word frequencies:
	./xtract -source [../texts/filename.txt] -printfrequencies -minfrequency [value, default: 500]

Find collocations for word:
	./xtract -source [../texts/filename.txt] -word [word]

Find collocations and output to a file, example:
	./xtract -source ../../texts/NP_articles_2018-2019.txt -word women | tee NP_collocations_women.txt
	