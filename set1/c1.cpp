#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <lib.hpp>

std::vector<unsigned char> input{0x49, 0x27, 0x6d, 0x20, 0x6b, 0x69, 0x6c,
    0x6c, 0x69, 0x6e, 0x67, 0x20, 0x79, 0x6f,
    0x75, 0x72, 0x20, 0x62, 0x72, 0x61, 0x69,
    0x6e, 0x20, 0x6c, 0x69, 0x6b, 0x65, 0x20,
    0x61, 0x20, 0x70, 0x6f, 0x69, 0x73, 0x6f,
    0x6e, 0x6f, 0x75, 0x73, 0x20, 0x6d, 0x75,
    0x73, 0x68, 0x72, 0x6f, 0x6f, 0x6d};

const std::string SOLUTION{"SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t"};

// 1111 1122 2222 3333 3344 4444

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
