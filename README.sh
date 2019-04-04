#!/bin/bash

printf "Compiling collocation_finder code...\n\n"

cd ./collocation_finder/build/
cmake ..
make

printf "\n"

printf "Using ./texts/articles_fall_2018.txt\n\n"

./xtract -source ../../texts/articles_fall_2018.txt -word women
