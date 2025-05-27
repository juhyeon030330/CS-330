#ifndef CCIPHER_H_
#define CCIPHER_H_
#include "cipher.h"

using namespace std;

/* A class that implements a
   Caesar cipher class. It 
   inherits the Cipher class */
// TODO: Implement this class





class CCipher : public Cipher {
public:
    CCipher();              // Default constructor (rotation 0)
    CCipher(int rot);       // Constructor with rotation
    ~CCipher();
};






/* Helper function headers 
 */
void rotate_string(string& in_str, int rot);
#endif

