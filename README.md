# 415project3
Using a 2-3 tree, we want to create a list of all the words that appear in a given document. For each word, our index contains a list of all the
line numbers in which the word occurs.

Following are the properties of the code that will be applicable for this project as well.

Since strings can be compared in C++ using < and == operators, there is a built-in order defined on strings, which is used to maintain the binary search tree property.
Punctuations are used as word delimiters and removed after the words are extracted. Thus the text containing: “I came; I saw, I won.” has 4 distinct words, namely I, came, saw and won. (Some exceptions are words like "family-owned" and "can’t ", which should be stored as a single word.) Also, note that upper-case letters and lower-case letters are treated differently. Thus “Apple” and “apple” count as two distinct words. The following rules are used to identify the next word from the current scanning position on the text:
skip the blank symbols.
If the next symbol is a non-alphanumerical symbol, skip until the next blank symbol and repeat. Else, the current symbol marks the beginning of the next word.
Scan until a blank symbol or newline symbol is reached.  That determines the end of the word. Any trailing non-alphanumerical symbols must be removed from the word.
The input and output format of the program supports the following operations:
Read an input file specified by the user, and build the index table, and reports the following: the number of distinct words (the number of nodes in the tree), the height of the tree, and the total CPU time to complete index building
Display the index in a specific format.
Search for a word. (Display the line numbers containing the word and the frequency.)
Save the index (as a specified text file).
