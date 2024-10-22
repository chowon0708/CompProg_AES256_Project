// HexUtils.hpp
#pragma once
#include <vector>
#include <array>
#include <string>

std::vector<uint8_t> hexStringToBytes(const std::string& hexStr);
std::array<uint8_t, 16> hexStringToArray(const std::string& hexStr);
void printHexFormatted(const std::vector<uint8_t>& data);

