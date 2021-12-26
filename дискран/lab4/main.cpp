#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string line;
    vector<unsigned int> sample;
    vector<unsigned int> string;
    bool first = true;
    vector<unsigned int> linesPosition = {0};
    vector<unsigned int> *vectorToWork = &sample;
    while (getline(std::cin, line)) {
        std::istringstream is(line);
        unsigned int num;
        while (is >> num) {
            vectorToWork->push_back(num);
        }
        if (first) {
            first = false;
            vectorToWork = &string;
        } else {
            linesPosition.push_back(vectorToWork->size());
        }
    }
    std::vector<bool> result(string.size());
    {
        for (size_t i = 0; i < string.size(); ++i) {
            int size_of_match = 0;
            for (size_t j = 0; j < std::min(sample.size(), string.size() - i); ++j) {
                if (string[i + j] == sample[j]) {
                    size_of_match++;
                } else {
                    break;
                }
            }
            if (size_of_match == sample.size()) {
                result[i] = true;
            }
        }
    }
    int lineIndex = 1;
    for (size_t i = 0; i < string.size(); ++i) {
        if (result[i]) {
            size_t stringIndex = i;
            while (stringIndex >= linesPosition[lineIndex]) {
                lineIndex++;
            }
            std::cout << lineIndex << ", " << stringIndex - linesPosition[lineIndex - 1] + 1 << "\n";
        }
    }

}
