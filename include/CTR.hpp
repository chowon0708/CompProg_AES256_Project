#pragma once
#include "AES256.hpp"
#include <vector>
#include <array>
#include <cstdint>

class AES256_CTR {
public:
    AES256_CTR(const std::vector<uint8_t> &key, const std::array<uint8_t, 16> &nonce);

    std::vector<uint8_t> encrypt(const std::vector<uint8_t> &plaintext);
    std::vector<uint8_t> decrypt(const std::vector<uint8_t> &ciphertext);

private:
    void incrementCounter();

    AES256 aes_;
    std::array<uint8_t, 16> nonce_;
    std::array<uint8_t, 16> counter_;
};