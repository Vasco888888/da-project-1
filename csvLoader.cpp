#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>

using namespace std;

// para já so do driving
void loadDistances(const string& filePath, unordered_map<string, unordered_map<string, int>> & walk,
                   unordered_map<string, unordered_map<string, int>> & drive) {
    ifstream file(filePath);
    string line, src, dest;
    int driving, walking;

    if (!file.is_open()) {
        cerr << "Error opening file: " << filePath << endl;
        return;
    }

    getline(file, line); // Skip header
    while (getline(file, line)) {
        stringstream ss(line);
        getline(ss, src, ',');
        getline(ss, dest, ',');
        ss >> driving;
        ss >> walking;

        drive[src][dest] = driving;
        walk[src][dest] = walking;
    }
    file.close();
}

// Load locations into a map
void loadLocations(const string& filePath, unordered_map<string, string> & locations, unordered_map<string, bool> & park) {
    ifstream file(filePath);
    string line, loc, loc_id, code;
    int parking;

    if (!file.is_open()) {
        cerr << "Error opening file: " << filePath << endl;
        return;
    }

    getline(file, line); // Skip header
    while (getline(file, line)) {
        stringstream ss(line);
        getline(ss, loc, ',');
        getline(ss, loc_id, ',');
        getline(ss, code, ',');
        ss >> parking;

        locations[loc_id] = code;
        if (parking == 1) {
            park[loc_id] = true;
        }
    }
    file.close();
}

int main() {
    string distancesFile = "data/Distances.csv";
    string locationsFile = "data/Locations.csv";

    unordered_map<string, unordered_map<string, int>> walk;
    unordered_map<string, unordered_map<string, int>> drive;
    unordered_map<string, string> locations;
    unordered_map<string, bool> park;

    loadDistances(distancesFile, walk, drive);
    loadLocations(locationsFile, locations, park);

    // Example output
    cout << "Graph loaded successfully!" << endl;
    for (const auto& pair : drive) {
        cout << "Location: " << pair.first << " -> ";
        for (const auto& neighbor : pair.second) {
            cout << "(" << neighbor.first << ", " << neighbor.second << ") ";
        }
        cout << endl;
    }

    cout << "Locations loaded successfully!" << endl;
    for (const auto& loc : locations) {
        cout << loc.first << ": " << loc.second << "..." << park[loc.first] << endl;
    }

    return 0;
}

// drive n walk -- drive[id][id] =  dist ..
// locations -- locations[id] = code .. park[id] = true/false