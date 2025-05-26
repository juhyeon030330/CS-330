#ifndef KCIPHER_H_
#define KCIPHER_H_
#include "cipher.h"
#include "ccipher.h"
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

const unsigned int MAX_LENGTH = 100;

/* A class that implements a
   Running key cipher class. It 
   inherts class Cipher */
// TODO: Implement this function


class KCipher : public Cipher {
protected: 
    struct CipherCheshire;
    CipherCheshire *smile;

public:

    KCipher();

    KCipher(const string& page);

    ~KCipher();

    void add_key(const string& page);

    void set_id(unsigned int i);

    string encrypt(string plaintext) override;

    string decrypt(string ciphertext) override;

};


#endif

