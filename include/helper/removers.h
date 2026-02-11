/**
* @file removers.h
 * @brief Implements functions to remove paths, nodes, and edges from a graph.
 *
 * @authors João Júnior, Mário Pereira, Vasco Sá
 */

#ifndef REMOVERS_H
#define REMOVERS_H

#include <vector>
#include <sstream>

#include "../data_structs/Graph.h"
using namespace std;

/**
 * @brief Removes a path from the graph.
 * @details Iterates through the given path and removes edges between consecutive nodes.
 *          Then removes the intermediate vertices from the graph.
 *
 * @param g Pointer to the graph.
 * @param path Vector containing the sequence of nodes in the path.
 * @complexity O(V + E), where V is the number of nodes in the path and E is the number of edges checked.
 */
void removePath(Graph<int>* g, const std::vector<int>& path) {
    for (int i = 1; i < path.size() - 1; i++) {
        int from = path[i];
        int to = path[i + 1];

        Vertex<int>* v = g->findVertex(from);
        if (v != nullptr) {
            for (auto& adj : v->getAdj()) {
                if (adj->getDest()->getInfo() == to) {
                    v->removeEdge(to);
                    break;
                }
            }
        }
    }
    for (int i = 1; i < path.size() - 1; i++) {
        g->removeVertex(path[i]);
    }
} //alterRouting

/**
 * @brief Removes specified nodes from the graph.
 * @details Parses a comma-separated string of node IDs, removes their edges, then deletes the nodes.
 *
 * @param g Pointer to the graph.
 * @param nodes String containing node IDs to be removed, separated by commas.
 * @complexity O(V + E), where V is the number of nodes to remove and E is the number of edges connected to them.
 */
void remNode(Graph<int>* g, string nodes) {
    vector<int> avoidNodes;
    istringstream iss(nodes);
    string node;
    while (getline(iss, node, ',')) {
        avoidNodes.push_back(stoi(node));
    }

    for (int i = 0; i < avoidNodes.size() - 1; i++) {
        Vertex<int>* v = g->findVertex(avoidNodes[i]);
        if (v != nullptr) {
            for (auto& adj : v->getAdj()) {
                v->removeEdge(adj->getDest()->getInfo());
            }
        }
        g->removeVertex(avoidNodes[i]);
    }
} //avoidNode

/**
 * @brief Removes specified edges from the graph.
 * @details Parses a string of edge pairs in the format "(id1,id2)", removes corresponding edges.
 *
 * @param g Pointer to the graph.
 * @param Segments String containing edge pairs to be removed, formatted as "(id1,id2)".
 * @complexity O(E), where E is the number of edges checked for removal.
 */
void remEdge(Graph<int>* g, string Segments) {
    vector<int> avoidSegments;
    istringstream ss(Segments);
    char ignore; // For characters like '(', ')', and ','
    int id1, id2;

    while (ss >> ignore >> id1 >> ignore >> id2 >> ignore) {
        avoidSegments.push_back(id1);
        avoidSegments.push_back(id2);
    }

    int i = 0;
    int j = 1;

    while (i != avoidSegments.size() && j != avoidSegments.size()) {
        Vertex<int>* v = g->findVertex(avoidSegments[i]);
        if (v != nullptr) {
            for (auto& adj : v->getAdj()) {
                if (adj->getDest()->getInfo() == avoidSegments[j]) {
                    v->removeEdge(avoidSegments[j]);
                    break;
                }
            }
        }
        i+=2;
        j+=2;
    }
} //avoidSegment

#endif //REMOVERS_H
