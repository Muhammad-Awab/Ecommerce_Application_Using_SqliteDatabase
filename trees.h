

#include<iostream>
using namespace std;

// Alphabet size (# of symbols)
#define ALPHABET_SIZE (26)

// Converts key current character into index
// use only 'a' through 'z' and lower case
#define CHAR_TO_INDEX(c) ((int)c - (int)'a')

// trie node
class TrieNode{
    public:
    TrieNode* children[ALPHABET_SIZE];
    // isWordEnd is true if the node represents
    // end of a word
    bool isWordEnd;
    TrieNode()
    {
        children[ALPHABET_SIZE] = 0;
    }
    TrieNode *getnode(void)
    {
         TrieNode* pNode = new TrieNode;
         pNode->isWordEnd = false;  //root node
         for (int i = 0; i < ALPHABET_SIZE; i++)
         pNode->children[i] = NULL;
         return pNode;
    }
};

// Returns new trie node (initialized to NULLs)
class TrieNodeList
{
    public:
    TrieNode *root;
    TrieNode* pCrawl; //move root to leaf node
    TrieNodeList()
    {
        root = NULL;
        pCrawl = NULL;
    }
    void insert(TrieNode* root,  string key)
    {
        pCrawl = root;
    for (int level = 0; level < key.length(); level++) {
        int index = CHAR_TO_INDEX(key[level]);  // huza
        if (!pCrawl->children[index])
        {
            pCrawl->children[index] = pCrawl->getnode(); //crawling and leaf node make children
        pCrawl = pCrawl->children[index];
        }
    }
    // mark last node as leaf
    pCrawl->isWordEnd = true;
}
    bool isLastNode(TrieNode* root)
    {
    for (int i = 0; i < ALPHABET_SIZE; i++)
        if (root->children[i])
            return 0;
    return 1;
    }
    void suggestionsRec(TrieNode* root, string currPrefix)
    {
    // found a string in Trie with the given prefix
    if (root->isWordEnd)
        cout << currPrefix << endl;
    for (int i = 0; i < ALPHABET_SIZE; i++)
        if (root->children[i]) {
            // child node character value
            char child = 'a' + i;
            suggestionsRec(root->children[i], currPrefix + child);//for crawling
        }
    }
    int printAutoSuggestions(TrieNode* root,  string query)
    {
        pCrawl = root;
        for (char c :query) { //ranged based loop and every char in a string and loop iterate based on string length
        int ind = CHAR_TO_INDEX(c);
        // no string in the Trie has this prefix
        if (!pCrawl->children[ind])
            return 0;
        pCrawl = pCrawl->children[ind];
    }
    // If prefix is present as a word, but
    // there is no subtree below the last
    // matching node.
    if (isLastNode(pCrawl))
        {
        cout << query << endl;
        return -1;
        }
    suggestionsRec(pCrawl, query);
    return 1;
    }
};
