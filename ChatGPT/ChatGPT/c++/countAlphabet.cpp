#include <iostream>
#include <string>
#include <unordered_map>
#include <cctype>

int main() {
    std::string input;
    std::unordered_map<char, int> counts;

    std::cout << "알파벳을 입력하세요: ";
    std::getline(std::cin, input);

    for (char c : input) {
        if (std::isalpha(c)) {
            c = std::tolower(c);
            counts[c]++;
        }
    }

    std::cout << "입력한 알파벳의 개수:" << std::endl;
    for (char c = 'a'; c <= 'z'; ++c) {
        std::cout << c << ": " << counts[c] << std::endl;
    }

    return 0;
}
