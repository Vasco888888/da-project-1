/**
 * @file best-route.cpp
 * @brief Implements routing functionality using Dijkstra's algorithm.
 * @details This program allows users to find optimal and restricted routes
 * using a graph-based approach. It supports command-line, for faster
 * testing of the code, and file-based input.
 * 
 * @authors João Júnior, Mário Pereira, Vasco Sá
 */

#include <iostream>
#include "helper/csvLoader.h"
#include "data_structs/Graph.h"
#include "helper/Dijkstra.h"
#include "helper/inputLoader.h"
#include "helper/routing.h"

using namespace std;

string test; ///< Mode of input: "cmd" for command-line, "file" for file-based input.
int type = 0; ///< Route type: 0 for alternativeRoute, 1 for restrictedRoute.

string mode;
int source, destination;
string N, S, temp; int I = 0; ///< Used for "avoidNodes", "avoidSegments", "includeNode".
vector<bool> NSI; ///< Used for triggering what of the above is used to calculate the restricted route.

/**
 * @brief Displays the menu and handles user input.
 * @details Parses input from command line or file to set up routing parameters.
 * @complexity O(1), assuming standard input size.
 */
void menu() {
    cout << "Enter 'cmd' or 'file' to choose the type of test to proceed: ";
    cin >> test;
    
    if (test == "cmd") {
        cout << "Enter mode, source, destination, avoidNodes*, avoidSegments*, includeNode* (use '_' if empty): ";
        cin >> mode >> source >> destination >> N >> S >> temp;

        if (temp == "_") {I = 0;}
        else {I = stoi(temp);}

        NSI = {N != "_", S != "_", I != 0};
        type = (NSI[0] || NSI[1] || NSI[2]) ? 1 : 0;
    }
    else if (test == "file") {
        vector<string> l = loader("input.txt");
        
        mode = l[0];
        source = stoi(l[1]);
        destination = stoi(l[2]);
        
        if (l[5] == "") I = 0;
        else I = stoi(l[5]);
        N = l[3]; S = l[4];

        NSI = {N != "", S != "", I != 0};
        type = (NSI[0] || NSI[1] || NSI[2]) ? 1 : 0;

    }
    else { ///< In case of a misspelled input, the program exits.
        cout << "Exited successfully" << endl;
        exit(EXIT_SUCCESS);
    }
}

/**
 * @brief Computes and displays routing results.
 * @details Calls Dijkstra's algorithm for optimal and restricted routing.
 * @complexity O((V + E) log V) for Dijkstra's algorithm, where E is edges and V is vertices.
 */
void results() {
    Graph<int> drive, walk; ///< Graphs for driving and walking routes.
    loadGraphs(drive, walk); ///< Loads Graphs with vertices(locations) and edges(distances).

    if (type == 0) { ///< Best and Alternative Routes
        int primW = 0, secW = 0;
        vector<int> primPath, secPath;

        Routing(drive, source, destination, primPath, secPath, primW, secW);

        if (test == "cmd") {
            cout << "Source:" << source << endl << "Destination:" << destination << endl;
            if (!primPath.empty()) {
                cout << "BestDrivingRoute:" << primPath[0];
                for (int i = 1; i < primPath.size(); i++) {
                    cout << "," << primPath[i];
                }
                cout << "(" << primW << ")" << endl;
            } else {
                cout << "BestDrivingRoute:none" << endl;
            }
            if (!secPath.empty()) {
                cout << "AlternativeDrivingRoute:" << secPath[0];
                for (int i = 1; i < secPath.size(); i++) {
                    cout << "," << secPath[i];
                }
                cout << "(" << secW << ")" << endl;
            } else {
                cout << "AlternativeDrivingRoute:none" << endl;
            }
        }
        else {
            ofstream outFile("output.txt");
            if (!outFile.is_open()) {
                cerr << "Error: Could not open output file" << endl;
                return;
            }
            outFile << "Source:" << source << endl << "Destination:" << destination << endl;
            if (!primPath.empty()) {
                outFile << "BestDrivingRoute:" << primPath[0];
                for (int i = 1; i < primPath.size(); i++) {
                    outFile << "," << primPath[i];
                }
                outFile << "(" << primW << ")" << endl;
            } else {
                outFile << "BestDrivingRoute:none" << endl;
            }
            if (!secPath.empty()) {
                outFile << "AlternativeDrivingRoute:" << secPath[0];
                for (int i = 1; i < secPath.size(); i++) {
                    outFile << "," << secPath[i];
                }
                outFile << "(" << secW << ")" << endl;
            } else {
                outFile << "AlternativeDrivingRoute:none" << endl;
            }
            cout << "Result in 'output.txt' file" << endl;
            outFile.close();
        }
    }
    if (type == 1) { ///< Restricted Route
        int w = 0;
        vector<int> path;
        avoidRouting(drive, source, destination, NSI, N, S, I, path, w);
        if (test == "cmd") {
            cout << "Source:" << source << endl << "Destination:" << destination << endl;
            if (!path.empty()) {
                cout << "RestrictedDrivingRoute:" << path[0];
                for (int i = 1; i < path.size(); i++) {
                    cout << "," << path[i];
                }
                cout << "(" << w << ")" << endl;
            } else {
                cout << "RestrictedDrivingRoute:none" << endl;
            }
        }
        else {
            ofstream outFile("output.txt");
            if (!outFile.is_open()) {
                cerr << "Error: Could not open output file" << endl;
                return;
            }
            outFile << "Source:" << source << endl << "Destination:" << destination << endl;
            if (!path.empty()) {
                outFile << "RestrictedDrivingRoute:" << path[0];
                for (int i = 1; i < path.size(); i++) {
                    outFile << "," << path[i];
                }
                outFile << "(" << w << ")" << endl;
            } else {
                outFile << "RestrictedDrivingRoute:none" << endl;
            }
            cout << "Result in 'output.txt' file" << endl;
            outFile.close();
        }
    }
}

/**
 * @brief Entry point for the routing program.
 * @return int Exit status.
 * @complexity O(E log V) for Dijkstra-based algorithms.
 */
int main() {
    menu();
    results();
    return 0;
}
