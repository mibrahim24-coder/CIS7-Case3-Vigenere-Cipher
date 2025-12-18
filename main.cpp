#include <iostream>
#include <string>
#include <cctype>

using namespace std;

int letterIndex(char c) {
    return toupper(static_cast<unsigned char>(c)) - 'A'; // A=0 ... Z=25
}

char applyCase(char original, char upperResult) {
    if (islower(static_cast<unsigned char>(original))) {
        return static_cast<char>(tolower(static_cast<unsigned char>(upperResult)));
    }
    return upperResult;
}

string cleanKeywordLettersOnly(const string& keyword) {
    string k;
    for (char c : keyword) {
        if (isalpha(static_cast<unsigned char>(c))) {
            k += static_cast<char>(toupper(static_cast<unsigned char>(c)));
        }
    }
    return k;
}

string encryptVigenere(const string& plaintext, const string& keyword) {
    string k = cleanKeywordLettersOnly(keyword);
    if (k.empty()) return "";

    string cipher;
    cipher.reserve(plaintext.size());

    int keyPos = 0;

    for (char c : plaintext) {
        if (isalpha(static_cast<unsigned char>(c))) {
            int p = letterIndex(c);
            int keyVal = letterIndex(k[keyPos % static_cast<int>(k.size())]);

            // Ei = (Pi + Ki) mod 26
            int e = (p + keyVal) % 26;
            char outUpper = static_cast<char>('A' + e);
            cipher += applyCase(c, outUpper);

            keyPos++;
        }
        else {
            cipher += c; // keep spaces/punctuation
        }
    }

    return cipher;
}

string decryptVigenere(const string& ciphertext, const string& keyword) {
    string k = cleanKeywordLettersOnly(keyword);
    if (k.empty()) return "";

    string plain;
    plain.reserve(ciphertext.size());

    int keyPos = 0;

    for (char c : ciphertext) {
        if (isalpha(static_cast<unsigned char>(c))) {
            int e = letterIndex(c);
            int keyVal = letterIndex(k[keyPos % static_cast<int>(k.size())]);

            // Di = (Ei - Ki + 26) mod 26
            int d = (e - keyVal + 26) % 26;
            char outUpper = static_cast<char>('A' + d);
            plain += applyCase(c, outUpper);

            keyPos++;
        }
        else {
            plain += c;
        }
    }

    return plain;
}

int main() {
    cout << "=== Vigenere Cipher (Case 3) ===\n";

    string plaintext;
    string keyword;

    cout << "Enter plaintext (you can type spaces):\n";
    getline(cin, plaintext);

    cout << "Enter keyword (letters recommended):\n";
    getline(cin, keyword);

    string cleanedKey = cleanKeywordLettersOnly(keyword);
    if (cleanedKey.empty()) {
        cout << "\nError: Keyword must contain at least one letter (A-Z).\n";
        return 0;
    }

    string cipherText = encryptVigenere(plaintext, keyword);
    string decryptedText = decryptVigenere(cipherText, keyword);

    cout << "\nEncrypted Text:\n" << cipherText << "\n";
    cout << "\nDecrypted Text:\n" << decryptedText << "\n";

    if (decryptedText == plaintext) {
        cout << "\nVerification: PASS (Decrypted text matches original plaintext)\n";
    }
    else {
        cout << "\nVerification: NOTE (Decrypted text differs from original)\n";
        cout << "This can happen if your plaintext includes letters outside A-Z.\n";
    }

    return 0;
}
