#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <omp.h>


extern void KMPSearch(const std::string& pat, const std::string& txt);
extern const char* kmp_desc;


std::string readFile(const std::string& fileName) {
    std::ifstream file(fileName);
    if (!file) {
        std::cerr << "Unable to open file: " << fileName << std::endl;
        return "";
    }
    std::string str;
    std::string content;
    while (std::getline(file, str)) {
        content += str + "\n";
    }
    file.close();
    return content;
}


void measureTime(const std::string& pattern, const std::string& text) {

}


int main() {
    std::cout << "Description:\t" << kmp_desc << std::endl << std::endl;

    std::cout << std::fixed << std::setprecision(5);
    std::string pattern = "Modern";
    std::vector<std::string> myVector;
    int problemSize[5] = {1,5,10,20,700};
    int n = sizeof(problemSize) / sizeof(problemSize[0]);
    for (int i = 0; i < n; ++i) {
        std::string filename = "../dataset/" + std::to_string(problemSize[i]) + "mb.txt";
        // You can now use 'filename' as needed
        std::string text = readFile(filename);
        myVector.push_back(text);
    }

    for (int i = 0; i < n; ++i) {
        std::cout << std::endl << "Working with "<< problemSize[i]<<" Mb Dataset" << std::endl << std::endl;
        std::chrono::time_point<std::chrono::high_resolution_clock> start_time = std::chrono::high_resolution_clock::now();
        KMPSearch(pattern, myVector[i]);

        std::chrono::time_point<std::chrono::high_resolution_clock> end_time = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end_time - start_time;
        std::cout << std::endl << "Elapsed time is : " << elapsed.count() << " " << std::endl;
        auto elapsed_mi = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
        std::cout << "Elapsed time in milliseconds: " << elapsed_mi.count() << " ms" << std::endl;
    }

    return 0;
}
