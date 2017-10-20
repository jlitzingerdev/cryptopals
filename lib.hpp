#include <string>
#include <vector>

int score_string(const std::string& plaintext);
std::string encode_base64(const std::vector<unsigned char>& input);

void decode_string(
        std::ostringstream& output,
        const std::vector<char> &ciphertext,
        char key);

void hex_to_binary(const std::string &input, std::vector<char> &output);
