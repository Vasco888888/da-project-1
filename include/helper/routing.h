/**
 * @file routing.h
 * @brief Routing functions.
 * @details Functions to compute the best and the alternative routes between two points,
 * and to compute a restricted route based on node/edge restrictions.
 *
 * @authors João Júnior, Mário Pereira, Vasco Sá
 */

#ifndef ROUTING_H
#define ROUTING_H

#include <iostream>
#include "../data_structs/Graph.h"
#include "Dijkstra.h"
#include "removers.h"
using namespace std;

/**
 * @brief Computes the best and the alternative routes between two points.
 * @details Uses Dijkstra's algorithm to find the shortest path, removes it,
 * and then finds an alternative path.
 *
 * @param g1 Graph representation of the routes.
 * @param source Starting node.
 * @param destination Target node.
 * @param primPath Stores the primary route.
 * @param secPath Stores the secondary (alternative) route.
 * @param primaryW Stores the weight of the primary route.
 * @param alterW Stores the weight of the alternative route.
 * @complexity O((V + E) log V) for Dijkstra’s execution twice.
 */
void Routing(Graph<int> & g1, int source, int destination, std::vector<int> & primPath,
                                std::vector<int> & secPath, int & primaryW, int & alterW){
    dijkstra(&g1, source);
    primPath = getPath(&g1, destination, primaryW);

    if (primPath.empty()){
        return;
    }

    removePath(&g1, primPath);
    dijkstra(&g1, source);
    secPath = getPath(&g1, destination, alterW);

    if (alterW < primaryW && alterW != 0) {
        cerr << "bad dijkstra handling-- alterWeight < primaryWeight" << endl;
        exit(EXIT_FAILURE);
    }
}

/**
 * @brief Computes a restricted route based on node/edge restrictions.
 * @details Removes restricted nodes/edges and finds a route using Dijkstra's algorithm.
 * The boolean vector NSI indicates which restrictions apply, dependent on the user input.
 * If including a node, the function computes the shortest path to that node and then to the destination.
 *
 * @param g1 Graph representation of the routes.
 * @param source Starting node.
 * @param destination Target node.
 * @param NSI Boolean vector indicating which restrictions apply.
 * @param N Node to avoid (if applicable).
 * @param S Edge to avoid (if applicable).
 * @param I Node that must be included in the path (if applicable).
 * @param path Stores the computed restricted route.
 * @param weight Stores the weight of the computed route.
 * @complexity O((V + E) log V) for Dijkstra’s algorithm, possibly twice if including a node.
 */
void avoidRouting(Graph<int>& g1, int source, int destination, std::vector<bool> NSI, string N,
                                    string S, int I, std::vector<int> & path, int & weight) {
    if (NSI[0] == true) {
        remNode(&g1, N);
    }
    if (NSI[1] == true) {
        remEdge(&g1, S);
    }


    if (NSI[2] == true) {
        //shortest path to 'IncludeNode'
        dijkstra(&g1, source);
        int w1 = 0;
        vector<int> primPath = getPath(&g1, I, w1);
        if (primPath.empty()) {
            return;
        }
        //shortest path from 'IncludeNode' to destination
        dijkstra(&g1, I);
        int w2 = 0;
        vector<int> secPath = getPath(&g1, destination, w2);
        if (secPath.empty()) {
            return;
        }
        //
        //appends------
        //
        path = primPath;
        for (int i = 1; i < secPath.size(); i++) {
            path.push_back(secPath[i]);
        }
        weight = w1 + w2;
    }
}

#endif //ROUTING_H
