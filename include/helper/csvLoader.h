/**
* @file csvLoader.h
 * @brief Loads data from the csv files and updates
 * the graphs created with the locations and distances
 * (vertices and edges).
 *
 * @authors João Júnior, Mário Pereira, Vasco Sá
 */
#ifndef CSVLOADER_H
#define CSVLOADER_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include "../data_structs/Graph.h"

using namespace std;
/**
 * @brief Loads the distances from the data file.
 * @details Loads the distances from the csv file into the
 * respective graphs (drive and walk), updating its edges.
 *
 * @param filePath Path to the csv file containing the distances.
 * @param locations Map of location names to their respective IDs.
 * @param drive Graph containing the driving distances.
 * @param walk Graph containing the walking distances.
 * @complexity O(N) for N being the number of lines in the csv file.
 */
void loadDistances(const string& filePath, unordered_map<string, string>& locations, Graph<int>& drive, Graph<int>& walk) {
    ifstream file(filePath);
    string line, src, dest, driving, walking;

    if (!file.is_open()) {
        cerr << "Error opening file: " << filePath << endl;
        return;
    }

    getline(file, line); // Skip header
    while (getline(file, line)) {
        stringstream ss(line);
        getline(ss, src, ',');  // Read **source location name**
        getline(ss, dest, ','); // Read **destination location name**
        getline(ss, driving, ',');
        getline(ss, walking, ',');

        int src_id = stoi(locations[src]);
        int dest_id = stoi(locations[dest]);

        //Handle the driving and walking routes that are cut ('X' in the csv)
        if (driving != "X") {
            drive.addEdge(src_id, dest_id, stoi(driving));
        }
        if (walking != "X") {
            walk.addEdge(src_id, dest_id, stoi(walking));
        }
    }
    file.close();
}
/**
 * @brief Loads the locations from the data file.
 * @details Loads the locations from the csv file into the
 * respective graphs (g1 and g2), creating its vertices
 * with the ids of each location.
 *
 * @param filePath Path to the csv file containing the distances.
 * @param g1 Graph containing the driving distances.
 * @param g2 Graph containing the walking distances.
 * @param locations Map of location names to their respective IDs.
 * @complexity O(N) for N being the number of lines in the csv file.
 */
void loadLocations(const string& filePath, Graph<int>& g1, Graph<int>& g2, unordered_map<string, string>& locations) {
    ifstream file(filePath);
    string line, loc, code, loc_id;
    int parking, id;

    if (!file.is_open()) {
        cerr << "Error opening file: " << filePath << endl;
        return;
    }

    getline(file, line); // skip header
    while (getline(file, line)) {
        stringstream ss(line);
        getline(ss, loc, ',');
        getline(ss, loc_id, ',');
        getline(ss, code, ',');
        ss >> parking;

        locations[code] = loc_id;
        id = stoi(loc_id);
        g1.addVertex(id);
        g2.addVertex(id);
        g1.findVertex(id)->setParking(parking);
        g2.findVertex(id)->setParking(parking);
    }

    file.close();
}
void loadGraphs(Graph<int>& drive, Graph<int>& walk) {
    string distancesFile = "data/Distances.csv";
    string locationsFile = "data/Locations.csv";

    unordered_map<string, string> locations;

    // Load locations first (ensures vertices exist)
    loadLocations(locationsFile, drive, walk, locations);

    // Load distances (now vertices exist, so edges can be added safely)
    loadDistances(distancesFile, locations, drive, walk);
}
/**
 * @brief Main call of the csv loaders
 * @details Calls both loadLocations and loadDistances
 * to update both graphs (drive and walk).
 *
 * @param drive Graph containing the driving distances.
 * @param walk Graph containing the walking distances.
 * @complexity O(N) since the function calls 2 funtions that have complexity O(N).
 */
#endif //CSVLOADER_H
