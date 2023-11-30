#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <fstream>

// Fills lps[] for given patttern pat[]
void computeLPSArray(const std::string& pat, int M, std::vector<int>& lps) {
    int length = 0;
    lps[0] = 0;

    int i = 1;
    while (i < M) {
        if (pat[i] == pat[length]) {
            length++;
            lps[i] = length;
            i++;
        } else {
            if (length != 0) {
                length = lps[length - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

// KMP search algorithm
void KMPSearch(const std::string& pat, const std::string& txt) {
    int M = pat.length();
    int N = txt.length();

    std::vector<int> lps(M);

    computeLPSArray(pat, M, lps);

    int i = 0; // index for txt[]
    int j = 0; // index for pat[]
    while (i < N) {
        if (pat[j] == txt[i]) {
            j++;
            i++;
        }

        if (j == M) {
            std::cout << "Found pattern at index " << i - j << std::endl;
            j = lps[j - 1];
        } else if (i < N && pat[j] != txt[i]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }
}


std::string readFile(const std::string& fileName) {
    std::ifstream file(fileName);
    std::string str;
    std::string content;
    while (std::getline(file, str)) {
        content += str + "\n";
    }
    file.close();
    return content;
}

void measureTime(const std::string& pattern, const std::string& text) {
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time = std::chrono::high_resolution_clock::now();

    KMPSearch(pattern, text);

    std::chrono::time_point<std::chrono::high_resolution_clock> end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end_time - start_time;
    std::cout << " Elapsed time is : " << elapsed.count() << " " << std::endl;
}


int main() {
    std::string pattern = "Modern";
    std::string text1 = readFile("dataset/1mb.txt");

    measureTime(pattern, text1);

    return 0;
}