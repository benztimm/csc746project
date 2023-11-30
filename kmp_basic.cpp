#include <string>
#include <vector>
#include <iostream>
#include <omp.h>

const char* kmp_desc = "Basic implementation of KMP.";


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

void KMPSearch(const std::string& pat, const std::string& txt) {
    int M = pat.length();
    int N = txt.length();
    int count = 0;

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
            //td::cout << "Found pattern at index " << i - j << std::endl;
            j = lps[j - 1];
            count += 1;
        } else if (i < N && pat[j] != txt[i]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }
    std::cout << "Total pattern found: " << count << std::endl;

}