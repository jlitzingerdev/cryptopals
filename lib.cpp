#include <sstream>
#include <algorithm>
#include <vector>
#include <string>
#include <iterator>
#include <iostream>
#include <lib.hpp>

const std::string COMMON{"etaoin shrdlu"};


int score_string(const std::string& plaintext)
{
    int score = 0;

    for (auto c : COMMON) {
        score += std::count(plaintext.cbegin(), plaintext.cend(), c) * 50;
    }

    return score;
}

const std::string ALPHABET{"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/="};

std::string encode_base64(const std::vector<unsigned char>& input)
{
    unsigned char i{};
    unsigned char rem{};
    auto p = 0;
    std::ostringstream out{};

    for (auto v : input) {
        switch (p) {
            case 0:
                i = (v >> 2) & 0x3F;
                rem = (v & 0x3) << 4;
                out << ALPHABET.at(i);
                ++p;
                break;
            case 1:
                i = rem | ((v >> 4) & 0xF);
                rem = (v & 0xF) << 2;
                out << ALPHABET.at(i);
                ++p;
                break;
            case 2:
                i = rem | ((v >> 6) & 0x3);
                out << ALPHABET.at(i);
                out << ALPHABET.at(v & 0x3F);
                rem = 0;
                p = 0;
                break;
            default:
                break;
        }
    }

    if (p == 1) {
        out << ALPHABET.at(rem);
    }

    while (p > 0) {
        out << ALPHABET.at(ALPHABET.size() - 1);
        --p;
    }
    return out.str();
}

void decode_string(
        std::ostringstream& output,
        const std::vector<char> &ciphertext,
        char key)
{
    output.clear();
    output.str("");
    char tmp = 0;

    for (auto c : ciphertext) {
        output.put(std::tolower(c ^ key));
    }
}

void decode_string(
        std::ostringstream& output,
        const std::string &ciphertext,
        char key)
{
    output.clear();
    output.str("");
    char tmp = 0;

    for (auto c : ciphertext) {
        output.put(std::tolower(c ^ key));
    }
}

/**
 * Decode hex encoded strings into a vector of chars. Assumes two byte
 * values.
 */
void hex_to_binary(const std::string &input, std::vector<char> &output)
{
    const auto &it = std::begin(input);
    std::string tmp;
    char v = 0;
    unsigned long tmpv = 0;

    for (auto c : input) {
        tmp += c;
        if (tmp.size() == 2) {
            tmpv = std::stoul(tmp, 0, 16);
            output.push_back(static_cast<char>(tmpv & 0xFF));
            tmp.clear();
        }
    }
}
