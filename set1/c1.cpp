#include <iostream>
#include <string>
#include <vector>
#include <sstream>

std::vector<unsigned char> input{0x49, 0x27, 0x6d, 0x20, 0x6b, 0x69, 0x6c,
    0x6c, 0x69, 0x6e, 0x67, 0x20, 0x79, 0x6f,
    0x75, 0x72, 0x20, 0x62, 0x72, 0x61, 0x69,
    0x6e, 0x20, 0x6c, 0x69, 0x6b, 0x65, 0x20,
    0x61, 0x20, 0x70, 0x6f, 0x69, 0x73, 0x6f,
    0x6e, 0x6f, 0x75, 0x73, 0x20, 0x6d, 0x75,
    0x73, 0x68, 0x72, 0x6f, 0x6f, 0x6d};

const std::string SOLUTION{"SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t"};

const std::string ALPHABET{"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/="};

// 1111 1122 2222 3333 3344 4444

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

int main(int argc, char *argv[])
{
    std::string res{encode_base64(input)};

    std::cout << "input = " << res << std::endl;
    if (res != SOLUTION)
        std::cerr << "Fail" << std::endl;

    res = encode_base64(std::vector<unsigned char>{0x66});
    std::cout << "t1 = " << res << std::endl;

    res = encode_base64(std::vector<unsigned char>{0x66, 0x6F});
    std::cout << "t2 = " << res << std::endl;

    res = encode_base64(std::vector<unsigned char>{});
    std::cout << "t3 = " << res << std::endl;

    return 0;
}
