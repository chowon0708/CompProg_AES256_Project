#pragma once
#include <vector>
#include <string>
#include <cstdint>
#include <array>

std::vector<uint8_t> generateAES256Key();
std::array<uint8_t, 16> generateRandomNonce();

void saveKeyToFile(const std::vector<uint8_t>& key, const std::string& filename);
std::vector<uint8_t> loadKeyFromFile(const std::string& filePath);

std::string generateRandomFilename();

void encryptFileCTR(const std::string& inputFilename, const std::vector<uint8_t>& key, const std::string& outputFilename);
void decryptFileCTR(const std::string& inputFilename, const std::vector<uint8_t>& key, const std::string& outputFilename);