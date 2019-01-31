/*
 * G.Yu
 * Dec. 1st, 2018
 * Version 5
 */

/*
 * Library used: iostream, hashTable.h,cmath
 * constructor would initialize the capacity to a large prime number, size to zero and create the new array on the heap, and initialze everything in it to nullptr
 * insert function would accept string from user, insert only words greater or equal to 4. Get the index by hashing the string,
 * check if it's duplicate, increment the freq in the Node, otherwise, insert it in the slot of the array. Or if there is a collision, insert it before the node(s) that already exist in
 * the slot, to form a linked list.
 *
 * Search would take in a string, and look it up in the hash table. go to the slot directly by hashing the string, then traverse the linked list if there is more than one element. If
 * the word is found, return the freqency of it, otherwise, return 0;
 *
 * findItem will accept a string as paramerter, and locate where the items is by hashing it, then locate where is it in the array, traverse if there is more than one element in the slot.
 * Then return a node pointer. This is a private unitility function
 *
 * hash function is implemented to get the index of the string. Defined a factor which is prime number,
 * then raise it to the power of i(from 0 to the length of the string ) and multiply it to the current character in the string(key[i])
 *
 * sort function would get an input from the user, and return an array that contain that many elements in a sorted order.
 * countUnique function would return the number of unique word in the table, by examining each node, and see if the freq is one, then it's unique
 * word_freq is a private utility function to the sort, which will split the each node into freq and the word itself, and put them into two arrays.
 *
 * the destructor would simply remove all the nodes in the hash table, then delete the array from the heap.
 */

#include "hashTable.h"
#include <iostream>
#include <cmath>

hashTable::hashTable() {
    cap = 15001;
    size = 0;
    collision = 0;
    table = new Node *[cap];
    for (unsigned int i = 0; i < cap; i++) {
        table[i] = nullptr;
    }
}

void hashTable::insert(string &key) {
    const unsigned int REQ_LENGTH = 4;
    if (key.length() < REQ_LENGTH) {
        return;
    }
    unsigned int index = hash(key);
    if (search(key)) {
        findItem(key)->freq++;
        return;
    }
    Node *temp = new Node(key);
    size++;
    if (table[index] == nullptr) {
        table[index] = temp;
        return;
    }
    collision++;
    temp->next = table[index];
    table[index] = temp;

}

int hashTable::search(string &key) {
    unsigned int index = hash(key);
    if (table[index] == nullptr) {
        return 0;
    }
    Node *current = table[index];
    while (current != nullptr) {
        if (current->word == key) {
            return current->freq;
        }
        current = current->next;
    }
    return 0;
}

hashTable::Node *hashTable::findItem(string &key) {
    unsigned int index = hash(key);
    Node *current = table[index];
    while (current != nullptr) {
        if (current->word == key) {
            return current;
        }
        current = current->next;
    }
    return 0;
}

unsigned int hashTable::hash(string &key) {
    const int factor = 37;
    unsigned int result = 0;
    for (unsigned int i = 0; i < key.length(); i++) {
        result += (unsigned int) (pow(factor, i) * key[i]);
    }
    return (result & 0x7fffffff) % cap ;
}

string *hashTable::sort(const unsigned int TOP) {

    string *texts = new string[size];
    int *frequencies = new int[size];

    string *result = new string[TOP];
    word_freq(texts, frequencies);
    int index = 0;
    int max = 0;
    for (unsigned int i = 0; i < TOP; i++) {
        for (unsigned int j = 0; j < size; j++) {
            if (frequencies[j] > frequencies[max]) {
                max = j;
            }
        }
        string temp = "\tWord:\t" + texts[max] + "\n\tFrequencies: " + to_string(frequencies[max]);
        result[index] = temp;
        index++;
        frequencies[max] = -1;
    }
    delete[] texts;
    delete[] frequencies;
    return result;

}

int hashTable::countUnique() {
    int unique = 0;
    for (unsigned int i = 0; i < cap; i++) {
        Node *current = table[i];
        while (current != nullptr) {
            if (current->freq == 1) {
                unique++;
            }
            current = current->next;
        }
    }
    return unique;
}

void hashTable::word_freq(string *&texts, int *&frequencies) {
    int index = 0;
    for (unsigned int i = 0; i < cap; i++) {
        Node *current = table[i];
        while (current != nullptr) {
            texts[index] = current->word;
            frequencies[index] = current->freq;
            index++;
            current = current->next;
        }
    }
}


bool hashTable :: remove(string& target){
    unsigned int index = hash(target);
    Node* current = table[index];
    Node* prev = nullptr;
    bool done = false;

    while (current && !done){
        if (current -> word == target){
            done = true;
        }else{
            prev = current;
            current = current -> next;
        }
    }

    if (done && prev){
        if (current-> freq > 1){
            current->freq--;
        }else{
            Node* delPtr = current;
            prev -> next = current-> next;
            current = current ->next;
            delete delPtr;
        }
        return true;
    }else if(done && !prev){
            if (current-> freq > 1) {
                current->freq--;
            }else {
                Node *delPtr = current;
                current = current->next;
                delete delPtr;
            }
        return true;
    }
    return false;
}
hashTable::~hashTable() {
    for (unsigned int i = 0; i < cap; i++) {
        while (table[i] != nullptr) {
            Node *delPtr = table[i];
            table[i] = table[i]->next;
            delete delPtr;
        }
    }
    delete[] table;
}

