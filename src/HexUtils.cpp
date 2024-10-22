#include "HexUtils.hpp"

#include <iostream>
#include <sstream>
#include <iomanip> 

std::vector<uint8_t> hexStringToBytes(const std::string& hexStr) {
    std::vector<uint8_t> bytes;

    for (size_t i = 0; i < hexStr.length(); i += 2) {
        std::string byteString = hexStr.substr(i, 2);
        uint8_t byte = static_cast<uint8_t>(std::stoul(byteString, nullptr, 16));
        bytes.push_back(byte);
    }

    return bytes;
}

std::array<uint8_t, 16> hexStringToArray(const std::string& hexStr) {
    std::array<uint8_t, 16> bytes{};

    if (hexStr.length() != 32) {
        std::cerr << "Error: The input hex string must be 32 characters long." << std::endl;
        return bytes; // Return empty array if size is incorrect
    }

    for (size_t i = 0; i < 16; ++i) {
        std::string byteString = hexStr.substr(i * 2, 2); // Extract 2 characters for each byte
        bytes[i] = static_cast<uint8_t>(std::stoul(byteString, nullptr, 16)); // Convert hex to byte
    }

    return bytes;
}

void printHexFormatted(const std::vector<uint8_t>& data) {
    for (size_t i = 0; i < data.size(); ++i) {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(data[i]);
        if ((i + 1) % 4 == 0) {
            std::cout << " ";
        }
        if ((i + 1) % 16 == 0) {
            std::cout << std::endl;
        }
    }

    if (data.size() % 16 != 0) {
        std::cout << std::endl;
    }
}