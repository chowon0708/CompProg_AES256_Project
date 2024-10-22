#include "FileUtils.hpp"
#include "CTR.hpp"
#include <vector>
#include <cstdint>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <filesystem>
#include <random>
#include <stdexcept>
#include <chrono>
#include <sstream>

std::vector<uint8_t> generateAES256Key() {
    std::vector<uint8_t> key(32); 
    std::random_device rd;
    
    for (size_t i = 0; i < key.size(); ++i) {
        key[i] = static_cast<uint8_t>(rd());
    }

    return key;
}

std::array<uint8_t, 16> generateRandomNonce() {
    std::random_device rd;
    std::array<uint8_t, 16> nonce;
    for (size_t i = 0; i < 16; ++i) {
        nonce[i] = static_cast<uint8_t>(rd());
    }

    return nonce;
}

void saveKeyToFile(const std::vector<uint8_t>& key, const std::string& filename) {
    std::filesystem::create_directories("./key");

    std::ofstream keyFile("./key/" + filename + ".bin", std::ios::binary);
    if (!keyFile) {
        std::cerr << "Error: Unable to open file for writing: " << filename << std::endl;
        return;
    }

    keyFile.write(reinterpret_cast<const char*>(key.data()), key.size());

    keyFile.close();

    std::cout << "Key saved to " << "./key/" + filename <<".bin"<< std::endl;
}

std::vector<uint8_t> loadKeyFromFile(const std::string& filePath) {
    std::ifstream keyFile(filePath, std::ios::binary);
    if (!keyFile) {
        std::cerr << "Error: Unable to open key file: " << filePath << std::endl;
        return {};
    }

    std::vector<uint8_t> key(32); // AES256 uses a 32-byte key
    keyFile.read(reinterpret_cast<char*>(key.data()), key.size());
    keyFile.close();

    return key;
}

std::string generateRandomFilename() {
    auto now = std::chrono::system_clock::now();
    auto now_time_t = std::chrono::system_clock::to_time_t(now);

    std::stringstream ss;
    ss << "key_" << now_time_t;
    return ss.str();
}


void encryptFileCTR(const std::string& inputFilename, const std::vector<uint8_t>& key, const std::string& outputFilename) {

    std::ifstream inputFile(inputFilename, std::ios::binary);
    if (!inputFile) {
        std::cerr << "Error: Unable to open input file: " << inputFilename << std::endl;
        return;
    }

    std::vector<uint8_t> fileData((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());
    inputFile.close();

    std::array<uint8_t, 16> nonce = generateRandomNonce();

    AES256_CTR aes256Ctr(key, nonce);

    std::vector<uint8_t> encryptedData = aes256Ctr.encrypt(fileData);

    std::ofstream outputFile(outputFilename, std::ios::binary);
    if (!outputFile) {
        std::cerr << "Error: Unable to open output file: " << outputFilename << std::endl;
        return;
    }
    outputFile.write(reinterpret_cast<const char*>(nonce.data()), nonce.size());
    outputFile.write(reinterpret_cast<const char*>(encryptedData.data()), encryptedData.size());
    outputFile.close();

    std::cout << "File encrypted and saved to " << outputFilename << std::endl;
}

bool loadEncryptedFile(const std::string& filepath, std::array<uint8_t, 16>& nonce, std::vector<uint8_t>& encryptedData) {
    std::ifstream inputFile(filepath, std::ios::binary);
    if (!inputFile) {
        std::cerr << "Error: Unable to open encrypted file: " << filepath << std::endl;
        return false;
    }

    //read nonce
    inputFile.read(reinterpret_cast<char*>(nonce.data()), nonce.size());

    //read encrypted data
    encryptedData.assign((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());

    inputFile.close();
    return true;
}

void decryptFileCTR(const std::string& inputFilename, const std::vector<uint8_t>& key, const std::string& outputFilename) {
    std::array<uint8_t, 16> nonce;
    std::vector<uint8_t> encryptedData;

    if (!loadEncryptedFile(inputFilename, nonce, encryptedData)) {
        std::cerr << "Error: Failed to load encrypted file." << std::endl;
        return;
    }

    AES256_CTR aes256Ctr(key, nonce);
    std::vector<uint8_t> decryptedData = aes256Ctr.decrypt(encryptedData);

    std::ofstream outputFile(outputFilename, std::ios::binary);
    if (!outputFile) {
        std::cerr << "Error: Unable to open output file: " << outputFilename << std::endl;
        return;
    }

    outputFile.write(reinterpret_cast<const char*>(decryptedData.data()), decryptedData.size());
    outputFile.close();

    std::cout << "File decrypted and saved to " << outputFilename << std::endl;
}