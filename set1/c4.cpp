#include <fstream>
#include <sstream>
#include <iostream>
#include <lib.hpp>


int main(int argc, char *argv[])
{
    std::ifstream ifs;

    ifs.open("4.txt");
    if (!ifs.is_open()) {
        std::cerr << "Unable to open file" << std::endl;
    }

    char start = 0x20;
    char end = 0x7E;
    std::string line;
    std::vector<char> bytes;
    int high_score = -999999;
    std::ostringstream plaintext;
    int score = 0;
    std::string result;
    char key = 0;
    std::string winning_line;
    int line_num = 1;
    int winning_line_no = 1;

    while (!ifs.eof()) {
        std::getline(ifs, line, '\n');
        hex_to_binary(line, bytes);
        for (char i = start; i <= end; ++i) {
            decode_string(plaintext, bytes, i);
            score = score_string(plaintext.str());
            if (score > high_score) {
                result = plaintext.str();
                high_score = score;
                key = i;
                winning_line = line;
                winning_line_no = line_num;
            }
        }
        bytes.clear();
        ++line_num;
    }
    std::cout << "winning string: " << result << std::endl;
    std::cout << "key: " << key << std::endl;
    std::cout << "winning line: " << winning_line << std::endl;
    std::cout << "winning line num: " << winning_line_no << std::endl;
    std::cout << "score: " << high_score << std::endl;

    ifs.close();
    return 0;
}
