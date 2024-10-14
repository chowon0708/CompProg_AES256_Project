#include "AES256.hpp"
#include <iostream>
#include <sstream>
#include <iomanip> 

std::array<uint32_t, 8> hexStringToKey(const std::string& hexStr) {
    std::array<uint32_t, 8> key{};
    std::stringstream ss(hexStr);

    for (size_t i = 0; i < 8; ++i) {
        std::string part = hexStr.substr(i * 8, 8); // Each part is 8 hex characters (32 bits)
        key[i] = std::stoul(part, nullptr, 16); // Convert hex string to uint32_t
    }

    return key;
}
int main(){
    std::string keyStr = "000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f";
    std::array<uint32_t, 8> aes256Key = hexStringToKey(keyStr);
    AES256 aes(aes256Key);
    std::array<std::array<uint8_t, 4>, 4> state = {
        0x00, 0x44, 0x88, 0xcc,
        0x11, 0x55, 0x99, 0xdd,
        0x22, 0x66, 0xaa, 0xee,
        0x33, 0x77, 0xbb, 0xff
    };
    aes.encrypt(state);
    for (const auto& row : state) {
        for (auto val : row) {
            std::cout << std::hex <<std::setw(2) << std::setfill('0') << static_cast<int>(val) << " ";
        }
        std::cout << std::endl;
    }
    aes.decrypt(state);
    std::cout << std::endl;
    for (const auto& row : state) {
        for (auto val : row) {
            std::cout << std::hex <<std::setw(2) << std::setfill('0') << static_cast<int>(val) << " ";
        }
        std::cout << std::endl;
    }
    //aes.printRoundKeys();
    return 0;
}