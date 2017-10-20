#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <iterator>
#include <locale>
#include <algorithm>
#include <lib.hpp>

std::vector<char> ct{0x1b, 0x37, 0x37, 0x33, 0x31, 0x36, 0x3f, 0x78,
    0x15, 0x1b, 0x7f, 0x2b, 0x78, 0x34, 0x31, 0x33,
    0x3d, 0x78, 0x39, 0x78, 0x28, 0x37, 0x2d, 0x36,
    0x3c, 0x78, 0x37, 0x3e, 0x78, 0x3a, 0x39, 0x3b,
    0x37, 0x36};

const std::locale test_locale{"en_US.utf8"};

int main(int argc, char *argv[])
{
    char start = 0x20;
    char end = 0x7E;
    std::ostringstream plaintext;
    int score = 0;
    int high_score = -999999;
    std::string result;
    char key = 0;
 
    for (char i = start; i <= end; ++i) {
        decode_string(plaintext, ct, i);
        score = score_string(plaintext.str());
        if (score > high_score) {
            result = plaintext.str();
            high_score = score;
            key = i;
        }
    }

    std::cout << "string: " << result << std::endl;
    std::cout << "score: " << high_score << std::endl;
    plaintext.clear();
    plaintext.str("");
    plaintext.put(key);
    std::cout << "key: " << plaintext.str() << std::endl;
    return 0;
}
