/**
 * @file Dijkstra.h
 * @brief Implementation of Dijkstra's algorithm for shortest paths like studied in class.
 *
 * @authors João Júnior, Mário Pereira, Vasco Sá
 */

#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <iostream>
#include <vector>
#include "../data_structs/MutablePriorityQueue.h"
#include "../data_structs/Graph.h"
#include <algorithm>
using namespace std;

/**
 * @brief Runs Dijkstra's shortest path algorithm.
 * @details Initializes distances, inserts the source node into a priority queue, and relaxes edges iteratively.
 *
 * @tparam T Type of the graph vertices.
 * @param g Pointer to the graph.
 * @param origin Source vertex for shortest path computation.
 * @complexity O((V + E) log V), where V is the number of vertices and E is the number of edges.
 */
template <class T>
void dijkstra(Graph<T> * g, const int &origin) {
    auto vertSet = g->getVertexSet();
    for (auto v : vertSet) {
        v->setDist(INF);
        v->setPath(nullptr);
        v->setVisited(false);
    }
    Vertex<T> *start = g->findVertex(origin);
    if (start == nullptr) return;
    start->setDist(0);
    MutablePriorityQueue<Vertex<T>> q;
    q.insert(start);
    while (!q.empty()) {
        auto u = q.extractMin();
        u->setVisited(true);
        for (auto e : u->getAdj()) {
            if (relax(e)) {
                if (!e->getDest()->isVisited()) {
                    q.insert(e->getDest());
                } else {
                    q.decreaseKey(e->getDest());
                }
            }
        }
    }
}

/**
 * @brief Relaxes an edge in Dijkstra's algorithm.
 * @details Updates the destination vertex distance and path if a shorter path is found.
 *
 * @tparam T Type of the graph vertices.
 * @param edge Pointer to the edge being relaxed.
 * @return True if the relaxation was successful, false otherwise.
 * @complexity O(1).
 */
template <class T>
bool relax(Edge<T> *edge) {
    if (edge->getOrig()->getDist() + edge->getWeight() < edge->getDest()->getDist()) {
        edge->getDest()->setDist(edge->getOrig()->getDist() + edge->getWeight());
        edge->getDest()->setPath(edge);
        return true;
    }
    return false;
}

/**
 * @brief Retrieves the shortest path from source to destination.
 * @details Traces back from the destination to the source using recorded paths and computes the total weight.
 *
 * @tparam T Type of the graph vertices.
 * @param g Pointer to the graph.
 * @param dest Destination vertex.
 * @param w Reference to store the total path weight.
 * @return A vector of vertex IDs representing the shortest path.
 * @complexity O(V), where V is the number of vertices in the path.
 */
template <class T>
std::vector<T> getPath(Graph<T> * g, const int &dest, int & w) {
    std::vector<T> res;
    Vertex<T> *v = g->findVertex(dest);
    if (v == nullptr || v->getDist() == INF) {
        return res; // No path found
    }
    w = 0; // Initialize weight to zero
    while (v != nullptr) {
        res.push_back(v->getInfo());
        Edge<T> *e = v->getPath();
        if (e == nullptr) {
            break;
        }
        w += e->getWeight(); // Accumulate the weight
        v = e->getOrig();
    }
    std::reverse(res.begin(), res.end());
    return res;
}

#endif // DIJKSTRA_H