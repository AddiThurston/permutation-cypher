#include <iostream>
#include <fstream>
#include <unordered_set>
#include <map>
#include <vector>
#include <string>
#include <algorithm>

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

// reads the frequency of letters in the ciphertext to a vector
void setCipherFreq(string& s, vector<pair<char, int> >& freq) {
    map<char, int> freqMap;
    // initialize the frequency of the characters to 0
    for (char c = 'A'; c <= 'Z'; c++) {
        freqMap.insert({c, 0});
    }

    for (char& c : s) {
        freqMap[c]++; // increment the frequency of the current character by 1;
    }
    for (const auto& p : freqMap) {
        freq.push_back({p.first, p.second});
    }

}

// determines the character with the higher frequency to be greater
bool freqSort(pair<char, int>& a, pair<char, int>& b) {
    return a.second > b.second;
}

string decrypt(string& ciphertext, string& key) {
    string plaintext = ""; 
    for (char& c : ciphertext) {
        plaintext += key[c-'A'];
    }
    return plaintext;
}

void permuteKey(string& key, char a, char b) {
    for (char& c : key) {
        if (c == a) {
            c = b;
        } else if (c == b) {
            c = a;
        }
    }
}

size_t countMatches(const string& text, const unordered_set<string>& dict){
	size_t count = 0;
	for(const auto& word : dict){
		if(word.empty()) continue;
		if(word.size() > text.size()) continue;

		if(text.find(word) != string::npos){
			count += word.length()*word.length();
		}
	}
	return count;
}

void autoDecrypt(string& key, string& ciphertext, const unordered_set<string>& dict) {
    int highScore = countMatches(decrypt(ciphertext, key), dict);

    for (char a = 'A'; a <= 'Z'; a++) {
        for (char b = 'A'; b <= 'Z'; b++) {
            if (a == b) continue;
            permuteKey(key, a, b);
            int score = countMatches(decrypt(ciphertext, key), dict);
            if (score > highScore) {
                highScore = score;
            } else {
                permuteKey(key, a, b);
            }
        }
    }
}

int main() {
    unordered_set<string> dict; // the dictionary from dictionary.txt
    string ciphertext;  // the ciphertext from ciphertext.txt
    vector<pair<char, int> > cipherFreq; // the frequency of all letters in the ciphertext
    vector<pair<char, int> > dictFreq;  // the frequency of all letters in the dictionary

    if (readToSet(dict, "dictionary.txt") == -1) {
        return 1;
    }
    cout << "Done reading dictionary file\n";

    if (readToString(ciphertext, "ciphertext.txt") == -1) {
        return 1;
    }
    cout << "Done reading ciphertext file\n";

    setCipherFreq(ciphertext, cipherFreq);
    cout << "Done counting frequency of ciphertext letters\n\n";
    sort(cipherFreq.begin(), cipherFreq.end(), freqSort);

    string commonTextFreq = "ETAOINSHRDLCUMWFGYPBVKJXQZ";
    // solution's frequency chart - "ETAINOSRHDCMLPUGWFYBVJKXQZ"

    // setup the key from the vector of frequencies
    string key(26, ' '); // 26 spaces
    for (int i = 0; i < 26; i++) {
        // set the key's alphabetical position of the ith most frequent cipher letter to the ith most frequent common text letter
        key[cipherFreq[i].first - 'A'] = commonTextFreq[i]; 
    }    

    string solution = decrypt(ciphertext, key);
    cout << "Decrypted text using key: " << key << endl;
    cout << solution << endl;
    cout << "Initial Score: " << countMatches(solution, dict) << endl;

    string input;
    cout << "1: Swap two letters in the key\n2: Autosolver\n3: Quit\n";
    getline(cin, input);
    while (input != "3") {
        if (input == "1") {
            cout << "Which characters do you want to swap?\n";
            char a,b;
            cin >> a >> b;
            getline(cin, input);
            permuteKey(key, toupper(a), toupper(b));
        } else if (input == "2") {
            autoDecrypt(key, ciphertext, dict);
        } else {
            cout << "Invalid input\n\n";
        }
        solution = decrypt(ciphertext, key);
        cout << "Decrypted text using key: " << key << endl;
        cout << solution << endl;
        cout << "Score: " << countMatches(solution, dict) << endl;
        cout << "1: Swap two letters in the key\n2: Autosolver\n3: Quit\n";
        getline(cin, input);
    }

    return 0;
}
