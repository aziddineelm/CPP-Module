#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

int main(int ac, char** av) {
    if (ac != 4) {
        std::cerr << "Usage: <filename> <s1> <s2>" << std::endl;
        return 1;
    }

    std::string filename = av[1];
    std::string s1 = av[2];
    std::string s2 = av[3];

    if (s1.empty()) {
        std::cerr << "Error: s1 cannot be empty." << std::endl;
        return 1;
    }

    std::ifstream inputFile(filename.c_str());
    if (!inputFile.is_open()) {
        std::cerr << "Error: Cannot open input file." << std::endl;
        return 1;
    }

    std::string outputFilename = filename + ".replace";
    std::ofstream outputFile(outputFilename.c_str());
    if (!outputFile.is_open()) {
        std::cerr << "Error: Cannot create output file." << std::endl;
        return 1;
    }

    std::string line;

    // Read line by line
    while (std::getline(inputFile, line)) 
    {
        // Find and Replace loop
        for (size_t pos = 0; (pos = line.find(s1, pos)) != std::string::npos; pos += s2.length()) 
        {
            line.erase(pos, s1.length());
            line.insert(pos, s2);
        }
        outputFile << line;
        if (!inputFile.eof()) {
            outputFile << '\n';
        }
    }

    inputFile.close();
    outputFile.close();

    return 0;
}