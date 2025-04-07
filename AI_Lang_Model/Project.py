# -*- coding: utf-8 -*-


import pandas as pd
import numpy as np
import re
import nltk
import math
import nltk
import matplotlib.pyplot as plt
nltk.download('stopwords')
import scipy.sparse as sp

from numpy.linalg import norm
from sklearn.feature_extraction.text import CountVectorizer

pd.options.display.max_colwidth = 200
#originally written in jupyter notebook, the following line was used to display plots inline
#get_ipython().run_line_magic('matplotlib', 'inline')

fhandFellow = open("The Fellowship Of The Ring.txt")
fhandReadFellow = fhandFellow.read()
fhandTwoTowers = open("The Two Towers.txt")
fhandReadTwoTowers = fhandTwoTowers.read()
fhandReturnOfTheKing = open("The Return Of The King.txt")
fhandReadReturnOfTheKing = fhandReturnOfTheKing.read()
corpus = [fhandReadFellow, fhandReadTwoTowers, fhandReadReturnOfTheKing]

alias = ["One Ring"]
wpt = nltk.WordPunctTokenizer()
stop_words = nltk.corpus.stopwords.words('english')
          
def normalize_document(doc):
    # normalize, all lowercase and remove whitespace
    doc = re.sub(r'[^a-zA-Z\s]', '', doc, re.I|re.A)
    doc = doc.lower()
    doc = doc.strip()
    tokens = wpt.tokenize(doc)
    # filter stopwords out of document
    filtered_tokens = [token for token in tokens if token not in stop_words]
    doc = ' '.join(filtered_tokens)
    return doc

normalize_corpus = np.vectorize(normalize_document)
norm_corpus = normalize_corpus(corpus)
norm_corpus
# unique words for features
unique_words = list(set([word for doc in [doc.split() for doc in norm_corpus] 
                         for word in doc]))
def_feature_dict = {w: 0 for w in unique_words}


from collections import Counter
# bag of words
bow_features = []
for doc in norm_corpus:
    bow_feature_doc = Counter(doc.split()) 
    all_features = Counter(def_feature_dict)
    bow_feature_doc.update(all_features) 
    bow_features.append(bow_feature_doc)
 
bow_features = pd.DataFrame(bow_features)

bow_features




feature_names = list(bow_features.columns)




x = sp.csc_matrix(bow_features, copy=True).indptr
print(x)

# build df matrix
df = np.diff(sp.csc_matrix(bow_features, copy=True).indptr)

df1 = 1 + df # adding 1 to smoothen idf later

# smooth doc
pd.DataFrame([df1], columns=feature_names)


total_docs = 1 + len(norm_corpus)
idf = 1.0 + np.log(float(total_docs) / df1)
# show smoothened idfs
#pd.DataFrame([np.round(idf, 4)], columns=feature_names)

# create tf-idf matrix
tf = np.array(bow_features, dtype='float64')
tfidf = tf * idf
# view raw unsmooth tfidf feature matrix
#pd.DataFrame(np.round(tfidf, 3), columns=feature_names)

from numpy.linalg import norm

norms = norm(tfidf, axis=1)

norm_tfidf = tfidf / norms[:, None]

# show final tfidf feature matrix
#pd.DataFrame(np.round(norm_tfidf, 2), columns=feature_names)


tfidf_df = pd.DataFrame(np.round(norm_tfidf, 2), columns=feature_names)


# Plot the heatmap
#Uncomment the following lines to visualize the TF-IDF matrix
""" plt.figure(figsize=(10, 8))
plt.imshow(tfidf_df, aspect='auto', cmap='viridis')
plt.colorbar(label='TF-IDF Score')
plt.title('TF-IDF Matrix')
plt.xlabel('Features')
plt.ylabel('Documents')
plt.show() """



#bag of words

bv = CountVectorizer(ngram_range=(2,2))
bv_matrix = bv.fit_transform(norm_corpus)

bv_matrix = bv_matrix.toarray()
vocab = bv.get_feature_names_out()
pd.DataFrame(bv_matrix, columns=vocab)




print("first book: ")
print("Number of occurances of ", "'One Ring': ", fhandReadFellow.count("One Ring"))
print("Number of occurances of ", "'the Ring': ", fhandReadFellow.count("the Ring"))
print("Number of occurances of ", "'Bilbo's ring': ", fhandReadFellow.count("Bilbo's ring"))
print("Number of occurances of ", "' Ring': ", fhandReadFellow.count(" Ring"))
print("Number of occurances of ", "' ring': ", fhandReadFellow.count(" ring"))

print("second book: ")
print("Number of occurances of ", "'One Ring': ", fhandReadTwoTowers.count("One Ring"))
print("Number of occurances of ", "'the Ring': ", fhandReadTwoTowers.count("the Ring"))
print("Number of occurances of ", "'Biblo's Ring': ", fhandReadTwoTowers.count("Bilbo's ring"))
print("Number of occurances of ", "' Ring': ", fhandReadTwoTowers.count(" Ring"))
print("Number of occurances of ", "' Ring': ", fhandReadTwoTowers.count(" ring"))

print("third book: ")
print(fhandReadReturnOfTheKing.count("One Ring"))
print(fhandReadReturnOfTheKing.count("the Ring"))
print(fhandReadReturnOfTheKing.count("Bilbo's ring"))
print(fhandReadReturnOfTheKing.count(" Ring"))
print(fhandReadReturnOfTheKing.count(" ring"))



print("Input a word you want to count the number of occurances of: ")
word = input()
wordAllLowerCase = word.casefold()
wordOneLeadSpace = " " + word
wordAllLowerCaseOneLeadSpace = " " + wordAllLowerCase

print("first book: ")
print("Number of occurances of '", word, "': ", fhandReadFellow.count(word))
print("Number of occurances of '", wordAllLowerCase, "': ", fhandReadFellow.count(wordAllLowerCase))
print("Number of occurances of '_", wordOneLeadSpace, "': ", fhandReadFellow.count(wordOneLeadSpace))
print("Number of occurances of '_", wordAllLowerCaseOneLeadSpace, "': ", fhandReadFellow.count(wordAllLowerCaseOneLeadSpace))
print("second book: ")
print("Number of occurances of '", word, "': ", fhandReadTwoTowers.count(word))
print("Number of occurances of '", wordAllLowerCase, "': ", fhandReadTwoTowers.count(wordAllLowerCase))
print("Number of occurances of '_", wordOneLeadSpace, "': ", fhandReadTwoTowers.count(wordOneLeadSpace))
print("Number of occurances of '_", wordAllLowerCaseOneLeadSpace, "': ", fhandReadTwoTowers.count(wordAllLowerCaseOneLeadSpace))

print("third book: ")
print("Number of occurances of '", word, "': ", fhandReadReturnOfTheKing.count(word))
print("Number of occurances of '", wordAllLowerCase, "': ", fhandReadReturnOfTheKing.count(wordAllLowerCase))
print("Number of occurances of '_", wordOneLeadSpace, "': ", fhandReadReturnOfTheKing.count(wordOneLeadSpace))
print("Number of occurances of '_", wordAllLowerCaseOneLeadSpace, "': ", fhandReadReturnOfTheKing.count(wordAllLowerCaseOneLeadSpace))




# Initialize the DTM
dt_matrix = []

# Process each document in the corpus
for doc in corpus:
    # Count occurrences of the word in different cases
    count_exact = doc.count(word)
    count_lower = doc.count(wordAllLowerCase)
    count_wordOneSpace = doc.count(wordOneLeadSpace)
    count_wordAllLowerOneSpace = doc.count(wordAllLowerCaseOneLeadSpace)

    dt_matrix.append({
        "Document": corpus.index(doc) + 1,  # Document index (1-based)
        "Exact Match": count_exact,
        "Case-Insensitive Match": count_lower,
        "Word with Leading Space": count_wordOneSpace,
        "All Lowercase with Leading Space": count_wordAllLowerOneSpace
    })

# Convert the DTM to a DataFrame for better visualization
dtm_df = pd.DataFrame(dt_matrix)

# Display the DTM
""" print("\nDocument-Term Matrix for the word '{}':".format(word))
print(dtm_df)

plt.figure(figsize=(10, 8))
plt.imshow(dtm_df, aspect='auto', cmap='viridis')
plt.colorbar(label='DT Matrix')
plt.title('Document Term Matrix')
plt.xlabel('Features')
plt.ylabel('Documents')
plt.show() """

# Replace document indices with document names
document_names = ["The Fellowship Of The Ring", "The Two Towers", "The Return Of The King"]
dtm_df["Document"] = document_names

# Create a bar graph for the DTM data
plt.figure(figsize=(12, 6))

# Plot each column of the DTM as a separate bar group
for column in dtm_df.columns[1:]:  # Skip the "Document" column
    plt.bar(dtm_df["Document"], dtm_df[column], label=column)

# Add labels and title
plt.title(f"Occurrences of the Word '{word}' in Each Document", fontsize=14)
plt.xlabel("Documents", fontsize=12)
plt.ylabel("Number of Occurrences", fontsize=12)

# Add a legend to differentiate between the counts
plt.legend(title="Count Type", fontsize=10)

# Show the graph
plt.xticks(rotation=45)  # Rotate x-axis labels for better readability
plt.tight_layout()
plt.show()