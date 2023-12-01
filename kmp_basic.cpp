#include <string>
#include <vector>
#include <iostream>
#include <omp.h>

const char* kmp_desc = "Basic implementation of KMP.";


void computeNewNextArray(const std::string& pat, std::vector<int>& newnext) {
    int M = pat.size();
    newnext.resize(M + 1);
    newnext[0] = newnext[1] = 0; // Assuming newnext[0] is not used as we start from index 1

    int j = 0;
    for (int i = 1; i < M; i++) {
        while (j > 0 && pat[i] != pat[j]) {
            j = newnext[j];
        }
        if (pat[i] == pat[j]) {
            j++;
        }
        newnext[i + 1] = j;
    }
}

void KMPSearch(const std::string& pat, const std::string& txt) {
    int M = pat.size();
    int N = txt.size();
    std::vector<int> newnext;
    computeNewNextArray(pat, newnext);
    //int count = 0;

    int j = 0; 
    std::vector<int> match(N, 0); // To keep track of matches

    for (int i = 0; i < N; i++) { // Loop through text
        while (j > 0 && pat[j] != txt[i]) {
            j = newnext[j];
        }
        if (pat[j] == txt[i]) {
            j++;
        }
        if (j == M) { // Full match found
            match[i - M + 1] = 1;
            //count++;
            j = newnext[M];
        }
    }

    // Print the positions of matches
    /*
    for (int i = 0; i < N; i++) {
        if (match[i] == 1) {
            std::cout << "Pattern found at index " << i << std::endl;
        }
    }
    */
    //std::cout << "Total matches: " << count << std::endl;
}