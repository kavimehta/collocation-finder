import nltk
from nltk.collocations import *
bigram_measures = nltk.collocations.BigramAssocMeasures()
trigram_measures = nltk.collocations.TrigramAssocMeasures()
file_content = open("merged.txt").read()
tokens = nltk.wordpunct_tokenize(file_content)
finder = BigramCollocationFinder.from_words(
         tokens, 5)
ignored_words = nltk.corpus.stopwords.words('english')
finder.apply_word_filter(lambda w: len(w) < 3 or w.lower() in ignored_words)
finder.apply_freq_filter(5)
print finder.nbest(bigram_measures.likelihood_ratio, 20)
finder = TrigramCollocationFinder.from_words(
         tokens, 5)
ignored_words = nltk.corpus.stopwords.words('english')
finder.apply_word_filter(lambda w: len(w) < 3 or w.lower() in ignored_words)
finder.apply_freq_filter(5)
print finder.nbest(trigram_measures.likelihood_ratio, 20)
