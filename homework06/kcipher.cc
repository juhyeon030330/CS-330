#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include "kcipher.h"
using namespace std;



/* Helper function definitions
 */

// -------------------------------------------------------
// Running Key Cipher implementation
// -------------------------------------------------------



KCipher::KCipher() {
    book.push_back(string(MAX_LENGTH, 'a'));
    id = 0;
}



KCipher::KCipher(const string& page) {
    if(page.empty()) {
        cerr << "Invalid Running key: " << endl;
        exit(EXIT_FAILURE);
    }

    for(char c : page) {
        
        if((!isalpha(c)) && (c != ' ')) {

            cerr << "Invalid Running key: " << page << endl;
            exit(EXIT_FAILURE);
        }
    }

    book.push_back(page);
    id = 0;
}



// Add page
void KCipher::add_key(const string& page) {
    if(page.empty()) {
        cerr << "Invalid Running key: " << endl;
        exit(EXIT_FAILURE);
    }

    for(char c : page) {
        
        if((!isalpha(c)) && (c != ' ')) {

            cerr << "Invalid Running key: " << page << endl;
            exit(EXIT_FAILURE);
        }
    }

    book.push_back(page);
}



// Set page id
void KCipher::set_id(unsigned int i) {
    if((i < 0) || (i >= book.size())) {
        cerr << "Warning: invalid id: " << i << endl;
        exit(EXIT_FAILURE);
    }

    id = i;
}



string KCipher::encrypt(string plaintext) {
    string result = "";
    string key = book[id];
    key.erase(remove(key.begin(), key.end(), ' '), key.end());

    int index = -1;
    for (char& c : plaintext) {
        if (c == ' ') {
            continue;
        }
        index++;

        char c2 = key[index % key.length()];
        char base = isupper(c) ? 'A' : 'a';
        c = ((c - base) + (c2 - 'a')) % 26 + base;
    }

    return plaintext;
}

string KCipher::decrypt(string ciphertext) {
    string result = "";
    string key = book[id];
    key.erase(remove(key.begin(), key.end(), ' '), key.end());

    int index = -1;
    for (char& c : ciphertext) {
        if (c == ' ') {
            continue;
        }
        index++;

        char c2 = key[index % key.length()];
        char base = isupper(c) ? 'A' : 'a';
        c = ((c - base) - (c2 - 'a') + 26) % 26 + base;
    }

    return ciphertext;
}


