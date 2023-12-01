#include <string>
#include <vector>
#include <iostream>
#include <omp.h>
const char* kmp_desc = "Openmp implementation of KMP.";

/*
void computeNewNextArray(const std::string& pat, std::vector<int>& newnext) {
    int M = pat.size();
    newnext.resize(M + 1);
    newnext[0] = newnext[1] = 0; // Assuming newnext[0] is not used as we start from index 1

    int j = 0;
    #pragma omp parallel for
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

    int j = 0; // index for pat (1-based in pseudocode, adjusted to 0-based here)
    std::vector<int> match(N, 0); // To keep track of matches
    int maxprefixlen = 0; // To track the max prefix length
    #pragma omp parallel for
    for (int i = 0; i < N; i++) { // Loop through text
        while (j > 0 && pat[j] != txt[i]) {
            j = newnext[j];
        }
        if (pat[j] == txt[i]) {
            j++;
        }
        if (j == M) { // Full match found
            match[i - M + 1] = 1;
            j = newnext[M]; // Reset j, but this line might need adjustment
        }
        maxprefixlen = std::max(maxprefixlen, j);
    }

    // Print the positions of matches
    
    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        if (match[i] == 1) {
            //std::cout << "Pattern found at index " << i << std::endl;
        }
    }
    
    std::cout << "Maximum prefix length: " << maxprefixlen - 1 << std::endl; // Adjusted back to 1-based indexing for output
}
*/

void computeNewNextArray(const std::string& pat, std::vector<int>& newnext) {
    int M = pat.size();
    newnext.resize(M + 1);
    newnext[0] = newnext[1] = 0; 

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

    std::vector<int> match(N, 0); // To keep track of matches

    int numThreads = omp_get_max_threads();
    //std::cout << "Number of threads: " << numThreads << std::endl;
    //std::vector<int> maxPrefixLen(numThreads, 0); // To track the max prefix length for each thread
    // Determine chunk boundaries
    std::vector<int> chunkStart(numThreads), chunkEnd(numThreads);
    int chunkSize = N / numThreads;
    for (int t = 0; t < numThreads; ++t) {
        chunkStart[t] = t * chunkSize;
        chunkEnd[t] = (t == numThreads - 1) ? N : (t + 1) * chunkSize;

        // Adjust start and end to avoid splitting words
        if (chunkStart[t] != 0 && txt[chunkStart[t] - 1] != ' ') {
            while (chunkStart[t] < N && txt[chunkStart[t]] != ' ') {
                ++chunkStart[t];
            }
        }
        if (chunkEnd[t] != N && txt[chunkEnd[t] - 1] != ' ') {
            while (chunkEnd[t] < N && txt[chunkEnd[t]] != ' ') {
                ++chunkEnd[t];
            }
        }
        //std::cout << "Thread " << t << " working on " << chunkStart[t] << " to " << chunkEnd[t] << std::endl;

    }
    //int count = 0;
    #pragma omp parallel
    {
        int threadId = omp_get_thread_num();
        int start = chunkStart[threadId];
        int end = chunkEnd[threadId];
        //std::cout << "Thread " << threadId << " working on " << start << " to " << end << std::endl;
        int j = 0; // Index for pattern
        for (int i = start; i < end; i++) {
            while (j > 0 && pat[j] != txt[i]) {
                j = newnext[j];
            }
            if (pat[j] == txt[i]) {
                j++;
            }
            if (j == M) {
                match[i - M + 1] = 1;
                //count++;
                j = newnext[M];
                //#pragma omp critical
                //std::cout << "Pattern found at index " << i << " Thread number: " << omp_get_thread_num() << std::endl;
                
            }
        }
    }
    /*
        #pragma omp parallel for
        for (int i = 0; i < N; i++) {
            if (match[i] == 1) {
                std::cout << "Pattern found at index " << i << std::endl;
        }
    }
    */
    //std::cout << "Total matches: " << count << std::endl;
}


