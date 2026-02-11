/**
 * @file inputLoader.h
 * @brief Loads input data from a .txt file.
 *
 * @authors João Júnior, Mário Pereira, Vasco Sá
 */

#ifndef INPUTLOADER_H
#define INPUTLOADER_H

#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

/**
 * @brief loads input into a vector
 * @details the loader function reads the input.txt file
 * and loads all the data, even if missing, into a vector.
 * The vector then passes all the information about mode,
 * source, destination, avoidNodes, avoidSegments, and includeNode
 * of the file, to the menu function in best-route.cpp.
 *
 * @param file Path to the input.txt file.
 * @return vector<string> containing the extracted data from the file.
 * @complexity O(1), since the input will always pass 6 arguments to the program.
 */
vector<string> loader(string file) {
    ifstream in(file);
    string line;
    if (!in.is_open()) {
        std::cerr << "Error: Could not open file " << file << std::endl;
        return {};
    }
    vector<string> data;
    while (getline(in, line)) {
        size_t pos = line.find(":");
        if (pos != string::npos) {
            string value = line.substr(pos + 1); // Extract part after ":"
            // Trim leading and trailing whitespace
            value.erase(0, value.find_first_not_of(" \t\n\r\f\v"));
            value.erase(value.find_last_not_of(" \t\n\r\f\v") + 1);
            data.push_back(value);
        } else {
            cerr << "Error: Invalid line format in input file" << endl;
            return {};
        }
    }
    in.close();
    return data;
}


#endif //INPUTLOADER_H
