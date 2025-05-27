#include <string>
#include <iostream>
#include <vector>
#include "kcipher.h"
#include "vcipher.h"


// -------------------------------------------------------
// Running Key Cipher implementation
// -------------------------------------------------------

VCipher::VCipher() : KCipher() {
    
}

VCipher::VCipher(string key) : KCipher(key) {
    for(char c : key) {
        if(!isalpha(c)) {
            cerr << "Error: not a valid Vigenere key word" << endl;
            exit(EXIT_FAILURE);
        }
    }
}

VCipher::~VCipher() {}
