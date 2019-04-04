cmake_minimum_required (VERSION 2.6)
project (collocatoin_finder)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Application source
set(APPLICATION_SOURCE
        xtract.cpp

        Bigram.cpp
        BigramCollection.cpp
        Corpus.cpp
        S1Bigram.cpp

        Bigram.h
        BigramCollection.h
        Corpus.h
        S1Bigram.h
        )

add_executable (xtract ${APPLICATION_SOURCE})