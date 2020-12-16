#include <iostream>
#include <string>
#include <vector>

struct TWord {
    std::string word;
    long long wordNumber, lineNumber;
};
bool operator ==(const TWord& l, const TWord& r) {
    if (l.word != r.word) {
        return false;
    }
    return true;
}
std::vector<long long> ZFunction(const std::vector<TWord>& pattern) {
    long long size = pattern.size();
    std::vector<long long> z(size, 0);
    long long l = 0, r = 0;
    for (long long i = 1; i < size; ++i) {
        if (i <= r) {
            z[i] = std::min(r-i+1, z[i-l]);
        }
        while (i + z[i] < size && pattern[z[i]] == pattern[i + z[i]]) {
            ++z[i];
        }
        if (i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }
    }
    return z;
}
std::vector<long long> StrongPrefixFunction(const std::vector<TWord>& pattern) {
    std::vector<long long> z = ZFunction(pattern);
    long long size = pattern.size();
    std::vector<long long> sp(size, 0);
    for (long long i = size - 1; i > 0; --i) {
        sp[i + z[i] - 1] = z[i];
    }
    return sp;
}
std::vector<long long> KMP(const std::vector<TWord>& pattern, const std::vector<TWord>& text) {
    std::vector<long long> sp = StrongPrefixFunction(pattern);
    std::vector<long long> result;
    long long tSize = text.size();
    long long pSize = pattern.size();
    if (pSize > tSize) {
        return result;
    }
    long long i = 0;
    while (i < tSize - pSize + 1) {
        long long j = 0;
        while (j < pSize && pattern[j] == text[i + j]) {
            ++j;
        }
        if (j == pSize) {
            result.push_back(i);
        }
        else if (j > 0) {
            i = i + j - sp[j - 1] - 1;
        }
        ++i;
    }
    return result;
}
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    TWord read;
    read.wordNumber = 1;
    read.lineNumber = 0;
    std::vector <TWord> pattern;
    std::vector <TWord> text;
    bool patternExist = false;
    char c = getchar();
    while (c > 0) {
        if (c == '\n') {
            if (patternExist == false) {
                if (!read.word.empty()) {
                    pattern.push_back(read);
                    read.word.clear();
                    patternExist = true;
                }
            }
            else if (!read.word.empty()) {
                text.push_back(read);
                read.word.clear();
            }
            read.wordNumber = 1;
            ++read.lineNumber;
        }
        else if (c == ' ' || c == '\t') {
            if (patternExist == false) {
                if (!read.word.empty()) {
                    pattern.push_back(read);
                    read.word.clear();
                    ++read.wordNumber;
                }
            }
            else if (!read.word.empty()) {
                text.push_back(read);
                read.word.clear();
                ++read.wordNumber;
            }
        }
        else {
            read.word += std::tolower(c);
        }
        c = getchar();
    }
    std::vector<long long> result = KMP(pattern, text);
    for (int i = 0; i < result.size(); ++i) {
        std::cout << text[result[i]].lineNumber << ", " << text[result[i]].wordNumber << '\n';
    }
}
