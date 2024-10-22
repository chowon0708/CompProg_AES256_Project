#include "CTR.hpp"
#include "AES256.hpp"
#include <vector>
#include <array>
#include <cstdint>

AES256_CTR::AES256_CTR(const std::vector<uint8_t> &key, const std::array<uint8_t, 16> &nonce)
    : aes_(key), nonce_(nonce), counter_(nonce) {}

std::vector<uint8_t> AES256_CTR::encrypt(const std::vector<uint8_t> &plaintext) {
    std::vector<uint8_t> ciphertext(plaintext.size());
    std::array<std::array<uint8_t, 4>, 4> state;
    counter_ = nonce_;
    for (size_t i = 0; i < plaintext.size(); i += 16) {
        for (size_t i = 0; i < 16; ++i) {
            state[i % 4][i / 4] = counter_[i];
        }

        aes_.encrypt(state);

        for (size_t j = 0; j < 16 && i + j < plaintext.size(); ++j) {
            ciphertext[i + j] = plaintext[i + j] ^ state[j % 4][j / 4];
        }

        incrementCounter();
    }

    return ciphertext;
}

std::vector<uint8_t> AES256_CTR::decrypt(const std::vector<uint8_t> &ciphertext) {
    counter_ = nonce_;
    // CTR mode decryption is identical to encryption
    return encrypt(ciphertext);
}

void AES256_CTR::incrementCounter() {
    for (int i = 15; i >= 0; --i) {
        if (++counter_[i] != 0) break;
    }
}
