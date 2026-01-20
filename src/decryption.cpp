#include <iostream>
#include <fstream>
#include <unordered_set>
#include <string>

using namespace std;

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

int readToString(string& s, string fileName) {
    ifstream fin(fileName);
    if (!fin.is_open()) {
        cout << "Error opening " << fileName << endl;
        return -1;
    }

    string line;
    while (fin >> line) {
        s += line;
    }
    fin.close();
    return 0;
}

int main() {
    unordered_set<string> dict;
    string ciphertext = "";

    if (readToSet(dict, "dictionary.txt") == -1) {
        return 1;
    }
    cout << "Done reading dictionary file\n";
    cout << dict.size() << endl;

    if (readToString(ciphertext, "ciphertext.txt") == -1) {
        return 1;
    }
    cout << "Done reading ciphertext file\n";
    cout << ciphertext << endl;
    return 0;
}