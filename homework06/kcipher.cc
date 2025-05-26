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


//new structure. conatains pages and page number.
struct KCipher::CipherCheshire {
    vector<string> book;
    unsigned int id;
};



KCipher::KCipher() {
    smile = new CipherCheshire;
    smile->book.push_back(string(MAX_LENGTH, 'a'));
    smile->id = 0;
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

    smile = new CipherCheshire;
    smile->book.push_back(page);
    smile->id = 0;
}

KCipher::~KCipher()
{
    delete smile;
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

    smile->book.push_back(page);
}



// Set page id
void KCipher::set_id(unsigned int i) {
    if(i >= smile->book.size()) {
        cerr << "Warning: invalid id: " << i << endl;
        exit(EXIT_FAILURE);
    }

    smile->id = i;
}


// add the two alphabet offset from the base alphabet and calculate the target alphabet ascii
string KCipher::encrypt(string plaintext) {
    string result = "";
    string key = smile->book[smile->id];
    key.erase(remove(key.begin(), key.end(), ' '), key.end());  // remove space

    int index = -1;
    for (char& c : plaintext) {
        if (c == ' ') {
            continue;   // if space is found, don't increment index and continue
        }
        index++;

        char c2 = key[index % key.length()];
        char base = isupper(c) ? 'A' : 'a';
        c = ((c - base) + (c2 - 'a')) % 26 + base;
    }

    return plaintext;
}

// same but reverse
string KCipher::decrypt(string ciphertext) {
    string result = "";
    string key = smile->book[smile->id];
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


