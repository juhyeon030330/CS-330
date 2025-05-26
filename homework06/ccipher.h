#ifndef CCIPHER_H_
#define CCIPHER_H_
#include "cipher.h"

using namespace std;

/* A class that implements a
   Caesar cipher class. It 
   inherits the Cipher class */
// TODO: Implement this class





class CCipher : public Cipher {
protected:
    int rotation; // Rotation value for Caesar cipher
public:
    CCipher();              // Default constructor (rotation 0)
    CCipher(int rot);       // Constructor with rotation
    string encrypt(string raw) override;
    string decrypt(string enc) override;
};






/* Helper function headers 
 */
void rotate_string(string& in_str, int rot);
#endif

