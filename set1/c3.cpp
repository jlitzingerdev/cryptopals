#include <iostream>
#include <sstream>
#include <string>
#include <array>
#include <iterator>
#include <locale>
#include <algorithm>

std::array<char, 34> ct{0x1b, 0x37, 0x37, 0x33, 0x31, 0x36, 0x3f, 0x78,
    0x15, 0x1b, 0x7f, 0x2b, 0x78, 0x34, 0x31, 0x33,
    0x3d, 0x78, 0x39, 0x78, 0x28, 0x37, 0x2d, 0x36,
    0x3c, 0x78, 0x37, 0x3e, 0x78, 0x3a, 0x39, 0x3b,
    0x37, 0x36};

const std::string COMMON{"etaoin shrdlu"};

const std::locale test_locale{"en_US.utf8"};

void decode_string(std::ostringstream& output, char key)
{
    output.clear();
    output.str("");
    char tmp = 0;

    for (auto c : ct) {
        output.put(std::tolower(c ^ key));
    }
}

int score_string(const std::string& plaintext)
{
    // Non-printable is -255
    int score = 0;
    std::string::size_type idx;

    for (auto c : plaintext) {
        idx = COMMON.find_first_of(c);
        if (idx != std::string::npos) {
            score += 50;
        }
    }

    return score;
}

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
        decode_string(plaintext, i);
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
