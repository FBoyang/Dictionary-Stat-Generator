# Dictionary-Stat-Generator
Read in a collection of dictionary and data file pairs and generates statistics about each pair
Using Trie as my data structure, for each node, I store a substring
Running time:
O(n+m) [read file and extract word]
O(nlog(n)) [create the Trie]
Log(1)+log(2)+log(3)+…+log(n) = O(nlog(n))
O(mlog(n)) [traverse the Data]
Log(n) + log(n)+…+log(n), (m times because have m words to traverse)

Note: m is the word in data file, n is the word in dictionary file

Challenge:
Malloc the exact space for node->word in order not to waste space
How to reduce the if condition time in order to optimize the operation

Memory storage:
Since each node take constant memory, and there are at most nk[k is the total letters of the longest word] nodes, therefore the Memory needed is O(nk)
