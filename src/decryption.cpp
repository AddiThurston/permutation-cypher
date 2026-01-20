#include <iostream>
#include <fstream>
#include <unordered_set>
#include <map>
#include <string>

using namespace std;

// reads a file to an unordered_set of strings
int readToSet(unordered_set<string>& d, string fileName) {
    ifstream fin(fileName);
    if (!fin.is_open()) {
        cout << "Error opening " << fileName << endl;
        return -1;
    }

    string word;
    while (fin >> word) {
        d.insert(word);
    }
    fin.close();
    return 0;
}

// reads a file to a single string
int readToString(string& s, string fileName) {
    s = "";
    ifstream fin(fileName);
    if (!fin.is_open()) {   // check that the file is opened correctly
        cout << "Error opening " << fileName << endl;
        return -1;
    }

    string input;
    while (fin >> input) {
        s += input;  // keep appending the string with the new input
    }
    fin.close();
    return 0;
}

// reads the frequency of letters to a map
void getCharFreq(string& s, map<char, int>& freq) {
    // initialize the frequency of the characters to 0
    for (char c = 'A'; c <= 'Z'; c++) {
        freq.insert({c, 0});
    }

    for (char& c : s) {
        freq[c]++; // increment the frequency of the current character by 1;
    }
}

int main() {
    unordered_set<string> dict; // the dictionary from dictionary.txt
    string ciphertext;  // the ciphertext from ciphertext.txt
    map<char, int> cipherFreq; // the frequency of all letters in the ciphertext

    if (readToSet(dict, "dictionary.txt") == -1) {
        return 1;
    }
    cout << "Done reading dictionary file\n";

    if (readToString(ciphertext, "ciphertext.txt") == -1) {
        return 1;
    }
    cout << "Done reading ciphertext file\n";

    getCharFreq(ciphertext, cipherFreq);
    cout << "Done counting frequencies of ciphertext letters\n";
    for (const auto& pair : cipherFreq) {
        std::cout << pair.first << " - " << pair.second << std::endl;
    }
    
    return 0;
}