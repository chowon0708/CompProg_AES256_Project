#include "AES256.hpp"
#include "CTR.hpp"
#include "HexUtils.hpp"
#include "FileUtils.hpp"
#include <iostream>
#include <sstream>
#include <iomanip> 
#include <cstring>

int main(int argc, char* argv[]) {
    if (argc >= 2) {
        // Generate a random AES256 key
        if (std::strcmp(argv[1], "-k") == 0) {
            std::string filename;

            if (argc == 3 && std::strlen(argv[2]) > 0) {
                filename = argv[2];
            } else {
                filename = generateRandomFilename(); 
            }

            std::vector<uint8_t> aes256Key = generateAES256Key();
            saveKeyToFile(aes256Key, filename);
            return 0;
        }   // Encrypt a file 
        else if (std::strcmp(argv[1], "-e") == 0 && argc == 4) {

            std::string keyFilename = argv[2];
            std::string inputFilename = argv[3];

            std::vector<uint8_t> key = loadKeyFromFile(keyFilename);
            if (key.empty()) {
                std::cerr << "Error: Failed to load key." << std::endl;
                return 1;
            }

            std::string outputFilename = inputFilename + ".enc"; 
            encryptFileCTR(inputFilename, key, outputFilename);
            return 0;
        }   // Decrypt a file 
        else if (std::strcmp(argv[1], "-d") == 0 && argc == 4) {
            std::string keyFilename = argv[2];
            std::string inputFilename = argv[3];


            std::vector<uint8_t> key = loadKeyFromFile(keyFilename);
            if (key.empty()) {
                std::cerr << "Error: Failed to load key." << std::endl;
                return 1;
            }

            // remove the .enc extension
            std::string outputFilename = inputFilename.substr(0, inputFilename.size() - 4) + ".dec"; 

            decryptFileCTR(inputFilename, key, outputFilename);
            return 0;
        }
    }

    std::cerr << "Usage: " << argv[0] << " -k [filename]" << std::endl;
    std::cerr << "       " << argv[0] << " -e <keyfile> <inputfile>" << std::endl;
    std::cerr << "       " << argv[0] << " -d <keyfile> <encfile>" << std::endl;
    return 1;
    
    

    return 0;
}


// Uncomment the following code to test the correctness of AES256_CTR class
// The example is based on the NIST document: https://csrc.nist.gov/CSRC/media/Projects/Cryptographic-Standards-and-Guidelines/documents/examples/AES_CTR.pdf

// int main(){
//     std::string keyStr = "603deb1015ca71be2b73aef0857d77811f352c073b6108d72d9810a30914dff4";
//     std::string plaintextStr = "6BC1BEE22E409F96E93D7E117393172AAE2D8A571E03AC9C9EB76FAC45AF8E5130C81C46A35CE411E5FBC1191A0A52EFF69F2445DF4F9B17AD2B417BE66C3710";
//     std::string nonceStr = "F0F1F2F3F4F5F6F7F8F9FAFBFCFDFEFF";
//     std::vector<uint8_t> aes256Key = hexStringToBytes(keyStr);
//     std::vector<uint8_t> plaintext = hexStringToBytes(plaintextStr);
//     std::array<uint8_t, 16> nonce = hexStringToArray(nonceStr);

//     AES256_CTR aes256Ctr(aes256Key, nonce);

//     std::vector<uint8_t> ciphertext = aes256Ctr.encrypt(plaintext); 
//     std::vector<uint8_t> decrypted = aes256Ctr.decrypt(ciphertext);

//     std::cout << "Plaintext: " << std::endl;
//     printHexFormatted(plaintext);

//     std::cout << "Ciphertext: " << std::endl;
//     printHexFormatted(ciphertext);

//     std::cout << "Decrypted: " << std::endl;
//     printHexFormatted(decrypted);
//     return 0;
// }