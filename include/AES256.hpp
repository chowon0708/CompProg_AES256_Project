#pragma once
#include <iostream>
#include <vector>
#include <array>
#include <cstdint>
extern const uint8_t S_BOX[256];

class AES256{
    public:
        AES256(const std::vector<uint8_t> &key);

        void encrypt(std::array<std::array<uint8_t, 4>, 4> &state);
        void decrypt(std::array<std::array<uint8_t, 4>, 4> &state);

        void printRoundKeys() const;
        void printState(const std::array<std::array<uint8_t, 4>, 4> &state, int round) const;
    private:
        void keyExpansion();

        //static const int Nb = 4; //Block length
        static const int Nk = 8; //Key length
        static const int Nr = 14; //Number of rounds

        void addRoundKey(std::array<std::array<uint8_t, 4>, 4> &state, int round);
        void subBytes(std::array<std::array<uint8_t, 4>, 4> &state);
        void invSubBytes(std::array<std::array<uint8_t, 4>, 4> &state);
        void shiftRows(std::array<std::array<uint8_t, 4>, 4> &state);
        void invShiftRows(std::array<std::array<uint8_t, 4>, 4> &state);
        void mixColumns(std::array<std::array<uint8_t, 4>, 4> &state);
        void invMixColumns(std::array<std::array<uint8_t, 4>, 4> &state);

        std::vector<uint8_t> key_;
        std::vector<std::array<uint32_t, 4>> roundkeys_;
};