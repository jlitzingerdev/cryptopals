#include <iostream>
#include <string>
#include <vector>
#include <iterator>

//1c0111001f010100061a024b53535009181c
//686974207468652062756c6c277320657965
//746865206b696420646f6e277420706c6179


void xor_buffers(const std::vector<unsigned char>& left,
        const std::vector<unsigned char>& right,
        std::vector<unsigned char>& result)
{
    if (left.size() != right.size())
        return;

    for (auto it = left.begin(); it != left.end(); it = std::next(it)) {
        auto i = std::distance(left.begin(), it);
        result.push_back(*it ^ right[i]);
    }
}

int main(int argc, char *argv[])
{
    std::vector<unsigned char> left{0x1c, 0x01, 0x11, 0x00, 0x1f, 0x01, 0x01,
        0x00, 0x06, 0x1a, 0x02, 0x4b, 0x53, 0x53, 0x50, 0x09, 0x18, 0x1c};

    std::vector<unsigned char> right{0x68, 0x69, 0x74, 0x20, 0x74, 0x68, 0x65,
        0x20, 0x62, 0x75, 0x6c, 0x6c, 0x27, 0x73, 0x20, 0x65, 0x79, 0x65};

    std::vector<unsigned char> solution{0x74, 0x68, 0x65, 0x20, 0x6b, 0x69, 0x64,
        0x20, 0x64, 0x6f, 0x6e, 0x27, 0x74, 0x20, 0x70, 0x6c, 0x61, 0x79};

    std::vector<unsigned char> result;

    xor_buffers(left, right, result);
    for (auto v : result) {
        std::cout << std::hex << int(v);
    }
    std::cout << std::endl;

    if (solution != result) {
        std::cout << "Fail" << std::endl;
    }

    return 0;
}
