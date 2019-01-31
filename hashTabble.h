/*
 * G.Yu
 * Dec. 1st, 2018
 * Version 2
 */
/*
 * library used: string
 * The class support the basic operation of a hash table, insertion and search and countUnique for the users.
 * The insertion first check the word if it's length is greater or equal to 4.
 * Get the index by hashing the string
 * Increment the freq in the node if it's a duplicates, otherwise, insert it in the array. If it's a empty spot, just put it as the head of the linked list, otherwise,
 * in case of collision, insert it at the head and linked the rest of the linked list to the next of new node.
 *
 * search would return the frequencies of the word being search, if it's not in the list, return 0;Treating it as a boolean if on the if statements(confirmed with instructor in class)
 * It will go over each spot on the array, and the entire linked list to check if it's there.
 *
 * The constructor would create a new arrays of pointers point to the head of the linked list, initialize it to nullptr for each one slot.
 *
 * The destructor would delete each node create in each slot of the array, and de-allocate the whole array from the heap memory
 *
 * sort method will receive a integer from user to output the number of sorted elements that the user wants, and return the result array.
 *
 * countUnique would return the number of unique words in the table by going over each bucket in each slot of the array, and check if the frequency is one, then it's unique.
 *
 * Private members:
 * Defined structure Node which contain the data field word which store a string from the file.
 * The freq field keeps track of how many times does the word appears on the file
 * next field would link the node to the next node.
 *
 * int cap is the capacity of the array, which is a prime number.
 * size is the number of elements actually inserted in the hash table
 * copying is suppressed in hash table
 * double pointer array table would store an  array of pointers that point to the head of the linked list.
 * findItems would accept a string , then find the node it's stored in, then return it.
 *
 * hash function would return an integer as index to the array.
 * word_freq is a function that accepts an integer array and string array, that put the frequencies into the integer array, and the word to the string array
 */

#ifndef P5_HASHTABLE_H
#define P5_HASHTABLE_H

#include <string>

using namespace std;

class hashTable {

public:
    hashTable();

    ~hashTable();

    string *sort(const unsigned int TOP);

    int search(string &key);

    void insert(string &key);
    unsigned int collision;

    int countUnique();
    bool remove(string& target);

private:
    struct Node {
        string word;
        int freq = 0;
        Node *next;

        Node() {
            word = "";
            freq = 1;
            next = nullptr;
        }

        Node(string input) {
            word = input;
            freq = 1;
            next = nullptr;
        }
    };

    unsigned int cap;
    unsigned int size;
    Node **table;

    Node *findItem(string &key);

    hashTable(const hashTable &ref);

    hashTable *operator=(const hashTable &rhs);

    unsigned int hash(string &word);

    void word_freq(string *&texts, int *&frequencies);

};

#endif //P5_HASHTABLE_H
