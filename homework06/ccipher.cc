#include <string>
#include <iostream>
#include <algorithm>
#include "ccipher.h"
#include <cctype>

// -------------------------------------------------------
// Caesar Cipher implementation





// Helper function that returns rotated string
string make_rotated_key(int rot) {
    if (rot < 0) {
        cerr << "Error: Caesar cipher is less than 0" << endl;
        exit(EXIT_FAILURE);
    }

    string key = "abcdefghijklmnopqrstuvwxyz";
    rot = rot % 26;
    rotate_string(key, rot);
    return key;
}


CCipher::CCipher() : Cipher() {}


CCipher::CCipher(int rot) : Cipher(make_rotated_key(rot)) {}





// -------------------------------------------------------






// Rotates the input string in_str by rot positions
void rotate_string(string& in_str, int rot)
{
    // TODO: You will likely need this function. Implement it.
    rotate(in_str.begin(), in_str.begin() + rot, in_str.end());
}
