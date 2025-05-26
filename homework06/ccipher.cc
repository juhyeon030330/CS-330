#include <string>
#include <iostream>
#include <algorithm>
#include "ccipher.h"
#include <cctype>

// -------------------------------------------------------
// Caesar Cipher implementation






// Default constructor
CCipher::CCipher() : rotation(0) {}

// Constructor with parameter
CCipher::CCipher(int rot) {

    if (rot < 0) {
        cerr << "Error: Caesar cipher is less than 0" << endl;
        exit(EXIT_FAILURE);
    }

    // make the number less than 26
    rotation = (rot % 26);
}


// find index and substitute
string CCipher::encrypt(string raw) {
    
    string key = "abcdefghijklmnopqrstuvwxyz";
    rotate_string(key, rotation);

    for(char& c : raw) {
        if(islower(c)) {
            c = key[c - 'a'];
        } else if(isupper(c)) {
            c = key[tolower(c) - 'a'];
            c = toupper(c);
        }



    }

    

    return raw;
}

// do the reverse
string CCipher::decrypt(string enc) {

    string key = "abcdefghijklmnopqrstuvwxyz";
    rotate_string(key, rotation);

    for(char& c : enc) {
        if(islower(c)) {
            c = 'a' + key.find(c);
        } else if(isupper(c)) {
            c = 'a' + key.find(tolower(c));
            c = toupper(c);
        }



    }

    return enc;
}






// -------------------------------------------------------






// Rotates the input string in_str by rot positions
void rotate_string(string& in_str, int rot)
{
    // TODO: You will likely need this function. Implement it.
    rotate(in_str.begin(), in_str.begin() + rot, in_str.end());
}
